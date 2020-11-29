/////////////////////////////////
//Name:  Advait Churi
//ID:    01738336 
//FILE:  sched_sim.c
/////////////////////////////////

#include "sched_sim.h"

float fcfsWT=0,fcfsTT=0,priorityWT=0,priorityTT=0,sjfWT=0,sjfTT=0,rrWT=0,rrTT=0,stcfWT=0,stcfTT=0;
int fcfs_contex_switch=0,priority_contex_switch=0,sjf_contex_switch=0,rr_contex_switch=0,stcf_contex_switch=0;
int pros_seq[10];


queue fcfs_q,sjf_q;
//////////////////    1. fcfs     /////////////////////////

int fcfs(process p[],int no_process,int interval ,int max_time, FILE *output)
{
//queue fcfs_q;
int fcfs_p_burst[no_process];
for(int i=0;i<no_process;i++)
{
fcfs_p_burst[i]=p[i].burst;
}

///  first come first serve algorithem using ascending sort

for(int i=0;i<no_process;i++)
{
for(int j=i+1;j<no_process;j++)
{
  if(p[i].arrival_time > p[j].arrival_time)
   {
    int temp_id =p[i].process_id;
    int temp_time =p[i].arrival_time;

    p[i].process_id=p[j].process_id;
    p[i].arrival_time=p[j].arrival_time;

    p[j].process_id=temp_id; 
    p[j].arrival_time=temp_time; 
   }
  
}
}

fprintf(output,"******  FCFS Scheduling ******\n");

int t=0;
for(int i=0;i<no_process;i++)
 {
  p[i].start = t+1;
  p[i].end= t+p[i].burst; 
  t +=p[i].burst;
  }
//save process number on timeline
 
int turn;
int current=0;
int data=0;

for(int i=0;i<max_time;i++)
{
turn = p[current].process_id;

if(fcfs_p_burst[turn]>0)
{
fcfs_q.queue_info[data]=p[turn].process_id;
fcfs_q.burst_info[data]=fcfs_p_burst[turn];
//printf("data is %d burst is %d at %d\n",fcfs_q.queue_info[data],p[turn].burst,i);
data++;
fcfs_p_burst[turn]--;
}
else{
current ++;
i--;}
}


snapshot(fcfs_q,p,output,no_process,max_time);


printf("FCFS Summary (WT = wait tme, TT = turnaround time):\n");
fprintf(output,"FCFS Summary (WT = wait tme, TT = turnaround time):\n");
struct summ s;
s=summary(no_process,p,fcfs_q,max_time,output);
fcfsWT=s.avgWT;
fcfsTT=s.avgTT;
fcfs_contex_switch=s.contex_switch;
}


/////////////   2.sjf       //////////////////

int sjf(process p[],int no_process,int interval ,int max_time, FILE *output)
{
//queue sjf_q;
int sjf_p_burst[no_process];
for(int i=0;i<no_process;i++)
{
sjf_p_burst[i]=p[i].burst;
}

///  shortest job first algorithem using ascending sort
for(int i=0;i<no_process;i++)
{
printf("%d-",p[i].burst);
}

for(int i=0;i<no_process;i++)
{
for(int j=0;j<no_process;j++)
{
  if(p[i].arrival_time < p[j].arrival_time)
   {
    int temp_id =p[j].process_id;
    int temp_burst =p[j].burst;
    int temp_time =p[j].arrival_time;

    p[j].process_id=p[i].process_id;
    p[j].burst=p[i].burst;
    p[j].arrival_time=p[i].arrival_time;

    p[i].process_id=temp_id; 
    p[i].burst=temp_burst; 
    p[i].arrival_time=temp_time;
   }
  
}
}



int k=1,min;
int btime=0;

for(int j=0;j<no_process;j++)
{
btime=btime+p[j].burst; 
min=p[k].burst;
for(int i=k;i<no_process;i++)
{
  
   if(btime>=p[i].arrival_time && p[i].burst<=min)
    {

    int temp_id =p[k].process_id;
    int temp_burst =p[k].burst;
    int temp_time =p[k].arrival_time;

    p[k].process_id=p[i].process_id;
    p[k].burst=p[i].burst;
    p[k].arrival_time=p[i].arrival_time;

    p[i].process_id=temp_id; 
    p[i].burst=temp_burst; 
    p[i].arrival_time=temp_time;
     
        
   }
}
k++;
}




fprintf(output,"\n******  SJF Scheduling  ******\n");

int t=0;
for(int i=0;i<no_process;i++)
 {
  p[i].start = t+1;
  p[i].end= t+p[i].burst; 
  t +=p[i].burst;
  }
//save process number on timeline

int turn;
int current=0;
int data=0;

for(int i=0;i<max_time;i++)
{

turn=current;
if(sjf_p_burst[turn]>0)
{
sjf_q.queue_info[data]=p[turn].process_id;
sjf_q.burst_info[data]=sjf_p_burst[turn];
//printf("data is %d burst is %d at %d\n",sjf_q.queue_info[data],p[turn].burst,i);
data++;
sjf_p_burst[turn]--;
}
else{
current ++;
i--;}
}

snapshot(sjf_q,p,output,no_process,max_time);
fprintf(output,"**************************************************\n");

printf("sjf Summary (WT = wait tme, TT = turnaround time):\n");
fprintf(output,"sjf Summary (WT = wait tme, TT = turnaround time):\n");
struct summ s;
s=summary(no_process,p,sjf_q,max_time,output);


sjfWT=s.avgWT;
sjfTT=s.avgTT;
sjf_contex_switch=s.contex_switch;

}


//////////////////////////////////   priority    //////////////////



int priority(process p[],int no_process,int interval ,int max_time, FILE *output)
{
queue pri_q;

int pri_p_burst[no_process];
for(int i=0;i<no_process;i++)
{
pri_p_burst[i]=p[i].burst;
}


for(int i=0;i<no_process;i++)
{
for(int j=i+1;j<no_process;j++)
{
  if(p[i].arrival_time > p[j].arrival_time)
   {
    int temp_id =p[j].process_id;
    int temp_burst =p[j].burst;
    int temp_time =p[j].arrival_time;
    int temp_pri = p[j].priority;  
  
    p[j].process_id=p[i].process_id;
    p[j].burst=p[i].burst;
    p[j].arrival_time=p[i].arrival_time;
    p[j].priority =p[i].priority;  

    p[i].process_id=temp_id; 
    p[i].burst=temp_burst; 
    p[i].arrival_time=temp_time;
    p[i].priority=temp_pri;
   }
  
}
}


int k=1,min;
int btime=0;

for(int j=0;j<no_process;j++)
{
btime=btime+p[j].priority; 
min=p[k].priority;
for(int i=k;i<no_process;i++)
{
   if(btime>=p[i].arrival_time && p[i].priority<min)
    {

    int temp_id =p[k].process_id;
    int temp_burst =p[k].burst;
    int temp_time =p[k].arrival_time;
    int temp_pri = p[k].priority;    

    p[k].process_id=p[i].process_id;
    p[k].burst=p[i].burst;
    p[k].arrival_time=p[i].arrival_time;
     p[k].priority =p[i].priority;

    p[i].process_id=temp_id; 
    p[i].burst=temp_burst; 
    p[i].arrival_time=temp_time;
    p[i].priority=temp_pri; 
        
   }
}
k++;
}

fprintf(output,"******  Priority Scheduling  ******\n");

int t=0;
for(int i=0;i<no_process;i++)
 {
  p[i].start = t+1;
  p[i].end= t+p[i].burst; 
  t +=p[i].burst;
  }
//save process number on timeline
 
int turn;
int current=0;
int data=0;

for(int i=0;i<max_time;i++)
{

turn=current;

if(pri_p_burst[turn]>0)
{
pri_q.queue_info[data]=p[turn].process_id;
pri_q.burst_info[data]=pri_p_burst[turn];
//printf("data is %d burst is %d at %d\n",pri_q.queue_info[data],p[turn].burst,i);
data++;
pri_p_burst[turn]--;
}
else{
current ++;
i--;}
}


snapshot(pri_q,p,output,no_process,max_time);

fprintf(output,"**************************************************\n");
printf("Priority Summary (WT = wait tme, TT = turnaround time):\n");
fprintf(output,"Priority Summary (WT = wait tme, TT = turnaround time):\n");
struct summ s;
s=summary(no_process,p,pri_q,max_time,output);

priorityWT=s.avgWT;
priorityTT=s.avgTT;
priority_contex_switch=s.contex_switch;

}



//////////////////     3.rr         //////////////////////
int rr(process p[],int no_process,int interval ,int max_time, FILE *output)
{
int turn=0;
int t=0;
int data=0;
queue rr_q;

int rr_p_burst[no_process];
for(int i=0;i<no_process;i++)
{
rr_p_burst[i]=p[i].burst;
}

for(int i=0;i<no_process;i++)
p[i].start = -2;



for(int i=0;i<max_time;i++)
{
turn = t%5;


if(p[turn].arrival_time<=i && rr_p_burst[turn]>0)
{
if(p[turn].start == -2)
p[turn].start=i+1;

rr_q.queue_info[data]=p[turn].process_id;
rr_q.burst_info[data]=rr_p_burst[turn];
//printf("data is %d burst is %d  at %d\n",rr_q.queue_info[data],rr_q.burst_info[data],i);
rr_p_burst[turn]--;
t++;
data++;
if(rr_p_burst[turn]==0)
p[turn].end=i+1;

}
else
{
i--;
t++;
}
}
fprintf(output,"\n******  Round robin Scheduling  ******\n");
snapshot(rr_q,p,output,no_process,max_time);

fprintf(output,"**************************************************\n");
printf("sjf Summary (WT = wait tme, TT = turnaround time):\n");
fprintf(output,"sjf Summary (WT = wait tme, TT = turnaround time):\n");
struct summ s;
s=summary(no_process,p,rr_q,max_time,output);
rrWT=s.avgWT;
rrTT=s.avgTT;
rr_contex_switch=s.contex_switch;
}

///////////////     stcf      ////////////////////

int stcf(process p[],int no_process,int interval ,int max_time, FILE *output)
{
queue stcf_q;

///  shortest time to complete first algorithem using ascending sort


///  sort according to arrival time


for(int i=0;i<no_process;i++)
{
for(int j=i+1;j<no_process;j++)
{
  if(p[i].arrival_time > p[j].arrival_time)
   {
    int temp_id =p[j].process_id;
    int temp_burst =p[j].burst;
    int temp_time =p[j].arrival_time;
    int temp_pri = p[j].priority;  
  
    p[j].process_id=p[i].process_id;
    p[j].burst=p[i].burst;
    p[j].arrival_time=p[i].arrival_time;
    p[j].priority =p[i].priority;  

    p[i].process_id=temp_id; 
    p[i].burst=temp_burst; 
    p[i].arrival_time=temp_time;
    p[i].priority=temp_pri;
   }
  
}
}


int a[no_process][max_time];
int bus[no_process][max_time];
for(int j=0;j<max_time;j++)
{
for(int i=0;i<no_process;i++)
{

a[i][j]=-1;
bus[i][j]=-1;
}

}
int min;

min=p[0].process_id;

/////   sort according to arrival

for(int j=0;j<max_time;j++)
{
int i=0;
for(int k=0;k<no_process;k++)
{
if(p[k].arrival_time<=j){
a[i][j]=p[k].process_id;
}
i++;
}
}
/////  --- ////



for(int j=0;j<max_time;j++)
{



int i=0;

 for(int m=0;m<no_process;m++)
  {
   //printf("row is %d and data %d\n",j ,a[m][j]);
   if(a[m][j]>=0)
    i++;
   }

  /// sort row by row according to burst time

  for(int k=0;k<i;k++)
   {
  for(int l =k+1;l<i;l++)
   {
    if(p[a[k][j]].burst >p[a[l][j]].burst)
     {
    int temp_i =a[l][j];
    a[l][j]=a[k][j];
    a[k][j]=temp_i;
 
    }
   } 
  }



stcf_q.queue_info[j]=a[0][j];
stcf_q.burst_info[j]=p[a[0][j]].burst;
p[a[0][j]].burst--;
//printf("pro is %d burst is %d at %d\n",stcf_q.queue_info[j],stcf_q.burst_info[j],j);

 if(p[a[0][j]].burst == 1)
   {
  int r = a[0][j];
   for(int d=0;d<max_time;d++)
    {
    for(int f=0;f<no_process;f++)
      {
      if(a[f][d]==r)
       a[f][d]=-1;
      }

    }
  }



    
     int n;
     n = a[0][j];
     int f;
     for(f=0;f<no_process-1;f++){
        a[f][j]=a[f][j];
       }
       a[f][j]=n;   
    




}
fprintf(output,"\n******  STCF Scheduling  ******\n");

snapshot(stcf_q,p,output,no_process,max_time);

fprintf(output,"**************************************************\n");
printf("stcf Summary (WT = wait tme, TT = turnaround time):\n");
fprintf(output,"stcf Summary (WT = wait tme, TT = turnaround time):\n");
struct summ s;
s=summary(no_process,p,stcf_q,max_time,output);
stcfWT=s.avgWT;
stcfTT=s.avgTT;
stcf_contex_switch=s.contex_switch;


}

/////////////////    snapshot     /////////////////////////

void snapshot(queue snap,process p[],FILE *output ,int no_process,int max_time)
{
int count=0;
int b=0;
int running=0;
int set=0;

for(int time=0;time<=max_time;time+=interval)
{
int run;
if(b==no_process-1)
set=1;
printf("t = %d \n",time);
fprintf(output,"t = %d \n",time);
if(time==0){

printf("CPU: Loading process %d (CPU burst = %d)\n",snap.queue_info[time],snap.burst_info[time]);
fprintf(output,"CPU: Loading process %d (CPU burst = %d)\n",snap.queue_info[time],snap.burst_info[time]);

printf("Ready queue: ");
fprintf(output,"Ready queue: ");


for( int i =0;i<no_process;i++)
{

if(p[i].arrival_time <= time && time <p[i].end)
{
printf("-%d",p[i].process_id);
fprintf(output,"-%d",p[i].process_id);
}
}
printf("\n");
fprintf(output,"\n");
}
else{
//printf("end %d time %d count %d\n",p[count].end,time,count);
if(p[count].end==time){
printf("CPU: Finishing process %d ",snap.queue_info[time-1]);
fprintf(output,"CPU: Finishing process %d ",snap.queue_info[time-1]);
count++;

//if(snap.burst_info[time-1]==1)
b++;
}

if(p[count].start==time+1){
printf("Loading process %d (CPU burst =%d)",snap.queue_info[time],snap.burst_info[time]);
fprintf(output,"Loading process %d (CPU burst =%d)",snap.queue_info[time],snap.burst_info[time]);
}


if(p[count].start <= time && time <= p[count].end && time!=0){
printf("CPU: Running process %d (remaining CPU burst = %d)",snap.queue_info[time-1],snap.burst_info[time-1]-1);
running =snap.queue_info[time-1];
fprintf(output,"CPU: Running process %d (remaining CPU burst = %d)",snap.queue_info[time-1],snap.burst_info[time-1]-1);
}
if(time!=0)
{

printf("\nReady queue: ");
fprintf(output,"\nReady queue: ");

for( int i =0;i<no_process;i++)
{

if(p[i].arrival_time <= time && time <p[i].end)
{
if(p[i].process_id != running)
printf("-%d",p[i].process_id);
fprintf(output,"-%d",p[i].process_id);
if(set==1){
printf("empty");
fprintf(output,"empty");}
}
}
printf("\n\n");
fprintf(output,"\n\n");
}

}

}

}

//////////////////   summary  ///////////////////////////

struct summ summary(int no_process,process p[],queue q,int max_time,FILE *output)
{
int avgWT=0,avgTT=0;
struct summ s;

printf("PID\t WT \t TT\n");
fprintf(output,"PID\t WT \t TT\n");
for(int i=0;i<no_process;i++)
{
p[i].turnaround = p[i].end-p[i].arrival_time;
p[i].wait = p[i].start - p[i].arrival_time-1;

avgWT+=p[i].wait;
avgTT+=p[i].turnaround;
s.avgWT=(float)avgWT/no_process;
s.avgTT=(float)avgTT/no_process;
printf("%d\t %d \t %d\n",p[i].process_id,p[i].wait,p[i].turnaround);
fprintf(output,"%d\t %d \t %d\n",p[i].process_id,p[i].wait,p[i].turnaround);
}

printf("AVG\t %f \t %f\n",(float)avgWT/no_process,(float)avgTT/no_process);
fprintf(output,"AVG\t %f \t %f\n",(float)avgWT/no_process,(float)avgTT/no_process);
int contex_switch=0;
int buf[5000];
int k=0;
buf[k]=q.queue_info[0];
for(int i =0;i<max_time;i++)
{
if(i+1<=25){
if(q.queue_info[i]!=q.queue_info[i+1])
{
contex_switch++;
k++;

buf[k]=q.queue_info[i+1];
}
}

} 
printf("\nProcess sequence: %d",buf[0]);
fprintf(output,"\nProcess sequence: %d",buf[0]);
for(int i=1;i<contex_switch+1;i++){
printf("-%d",buf[i]);
fprintf(output,"-%d",buf[i]);}

printf("\nContex Switches: %d\n",contex_switch+1);
fprintf(output,"\nContex Switches: %d\n",contex_switch+1);
s.contex_switch=contex_switch+1;

return s;
}

void overall(FILE *output)
{
printf("\n********** OVERALL SUMMARY***************\n");
printf("Wait Time Comparison\n");
printf("1  STCF         %f\n",stcfWT);
printf("2  SJF          %f\n",sjfWT);
printf("3  FCFS         %f\n",fcfsWT);
printf("4  Round robin  %f\n",rrWT);
printf("5  Priority     %f\n\n",priorityWT);

printf("Turnaround Time Comparison\n");
printf("1  STCF         %f\n",stcfTT);
printf("2  SJF          %f\n",sjfTT);
printf("3  FCFS         %f\n",fcfsTT);
printf("4  Round robin  %f\n",rrTT);
printf("5  Priority     %f\n\n",priorityTT);

printf("Contex Switch Comparison\n");
printf("1  STCF         %d\n",stcf_contex_switch);
printf("2  SJF          %d\n",sjf_contex_switch);
printf("3  FCFS         %d\n",fcfs_contex_switch);
printf("4  Round robin  %d\n",rr_contex_switch);
printf("5  Priority     %d\n",priority_contex_switch);

fprintf(output,"\n********** OVERALL SUMMARY***************\n");
fprintf(output,"Wait Time Comparison\n");
fprintf(output,"1  STCF         %f\n",stcfWT);
fprintf(output,"2  SJF          %f\n",sjfWT);
fprintf(output,"3  FCFS         %f\n",fcfsWT);
fprintf(output,"4  Round robin  %f\n",rrWT);
fprintf(output,"5  Priority     %f\n\n",priorityWT);

fprintf(output,"Turnaround Time Comparison\n");
fprintf(output,"1  STCF         %f\n",stcfTT);
fprintf(output,"2  SJF          %f\n",sjfTT);
fprintf(output,"3  FCFS         %f\n",fcfsTT);
fprintf(output,"4  Round robin  %f\n",rrTT);
fprintf(output,"5  Priority     %f\n\n",priorityTT);

fprintf(output,"Contex Switch Comparison\n");
fprintf(output,"1  STCF         %d\n",stcf_contex_switch);
fprintf(output,"2  SJF          %d\n",sjf_contex_switch);
fprintf(output,"3  FCFS         %d\n",fcfs_contex_switch);
fprintf(output,"4  Round robin  %d\n",rr_contex_switch);
fprintf(output,"5  Priority     %d\n",priority_contex_switch);



}









