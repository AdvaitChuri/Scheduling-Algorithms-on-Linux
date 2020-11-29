/////////////////////////////////
//Name:  Advait Churi
//ID:    01738336 
//FILE:  sched_sim.h
/////////////////////////////////



#ifndef prod_cons_MT_H
#define prod_cons_MT_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include<unistd.h>

typedef struct
{
int process_id;   //procees pid
int burst;        //cpu burst time
int priority;     //priority of process
int arrival_time; //process arrival time
int start;
int end;
int turnaround;
int wait;
}process;

typedef struct
{
int head;
int tail;
int queue_info[5000];
int burst_info[5000];
}queue;

 
struct summ
{
float avgWT;
float avgTT;
int contex_switch;
};

extern int interval;

int fcfs(process p[],int no_process,int interval ,int max_time, FILE *output);
int sjf(process p[],int no_process,int interval ,int max_time, FILE *output);
int rr(process p[],int no_process,int interval ,int max_time, FILE *output);
int priority(process p[],int no_process,int interval ,int max_time, FILE *output);
int stcf(process p[],int no_process,int interval ,int max_time, FILE *output);
void snapshot(queue snap,process p[],FILE *output ,int no_process,int max_time);
struct summ summary(int no_process,process p[],queue q,int max_time,FILE *output);
void overall(FILE *output);
#endif
