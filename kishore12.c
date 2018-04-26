#include<stdio.h>
#include<pthread.h>
struct record
{
       int p,atime,btime,wtime,tatime,rtime;
};


void sortarrivaltime(struct record a[],int processes)   //selection sort
{
       int i,j;
       struct record temp;
       for(i=0;i<processes;i++)
       {
              for(j=i+1;j<processes;j++)
              {
                     if(a[i].atime > a[j].atime)
                     {
                           temp = a[i];
                           a[i] = a[j];
                           a[j] = temp;
                     }
              }
       }
       return;
}

int main()
{
	
       int i,j,processes,time,remain,flag=0,ts;
       struct record a[7];
       float avgturnaround=0;
       printf("Round robin algorithm \n");
       printf("Number Of processes");
       scanf("%d",&processes);
       remain=processes;
       for(i=0;i<processes;i++)
       {
              printf("Enter arrival time and Burst time for processes P%d : ",i);
              scanf("%d%d",&a[i].atime,&a[i].btime);
              a[i].p = i;
              a[i].rtime = a[i].btime;
       }
       sortarrivaltime(a,processes);
       printf("Enter Time Quantum for each process: ");
       scanf("%d",&ts);
       for(time=0,i=0;remain!=0;)
       {
              if(a[i].rtime<=ts && a[i].rtime>0)
              {
                     time = time + a[i].rtime;
                     a[i].rtime=0;
                     flag=1;
              }
              else if(a[i].rtime > 0)
              {
                     a[i].rtime = a[i].rtime - ts;
                     time = time + ts;
              }
              if(a[i].rtime==0 && flag==1)
              {
                     remain--;
                     a[i].tatime = time-a[i].atime;
                     a[i].wtime = time-a[i].atime-a[i].btime;
                     avgturnaround = avgturnaround + time-a[i].atime;
                     flag=0;
              }
              if(i==processes-1)
                     i=0;
              else if(a[i+1].atime <= time)
                     i++;
              else
                     i=0;
       }
       printf("\n processes\t	arrivaltime\t	bursttime\t	turnaround\t	waittime\n");
       printf("************************************************************************************************************\n");
       for(i=0;i<processes;i++)
       {
              printf("P%d\t		%d\t		%d\t		%d\t		%d\n",a[i].p,a[i].atime,a[i].btime,a[i].tatime,a[i].wtime);
       }
       avgturnaround = avgturnaround/processes;
       printf("Average Turnaround Time : %.2f 	\n",avgturnaround);
}
