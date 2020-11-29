/////////////////////////////////
//Name:  Advait Churi
//ID:    01738336 
//FILE:  OS_program3.c
/////////////////////////////////



#include "sched_sim.h"
int interval,n=0;
int file_info[1000];
int no_process;
int main(int argc, char *argv[])
{

FILE *input,*output;
int i =0;


input = fopen(argv[1],"r");
output = fopen(argv[2],"w");
interval = atoi(argv[3]);

while(fscanf(input,"%d",&n)!=EOF)
{
file_info[i]=n;
i++;
}
fclose(input);
no_process = i/3;

process p[no_process];
int f=0;
int max_time = 0;
for(int k=0;k<no_process;k++)
{
p[k].process_id=k;
p[k].burst=file_info[f];
p[k].priority=file_info[++f];
p[k].arrival_time=file_info[++f];
max_time += p[k].burst;
f++;
}

//printf("%d",max_time);

fcfs(p,no_process,interval,max_time,output );
sjf(p,no_process,interval,max_time,output );
//rr(p,no_process,interval,max_time,output );
priority(p,no_process,interval,max_time,output );
stcf(p,no_process,interval,max_time,output );

overall(output);
//close(output);
return 0;

}
