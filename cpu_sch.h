#ifndef CPU_SCH_H_INCLUDED
#define CPU_SCH_H_INCLUDED

#include <stdio.h>
#include <iomanip>
#include <math.h> // for log function
#include <iostream>
#include <fstream>
#include<conio.h>
#include <algorithm>

class Scheduler {

    public:

 float twt,awt,wt[10000],tat[10000], rt[10000];

struct Request
{
	int index;
	long arrivalTime;
	int burstLength;
	int priority;
};

Request requestArchive[10000];



double random(long int* seed);

double exponential(float mean);

void parameters(int ave_interarrival_time, //between process arrivals
                int last_arival_time, //last process arrival time
                int max_CPU_size,   //Maximum CPU Burst Size
                int min_CPU_size,   // Minimum CPU Burst Size
                int* priority,          //Priority
                long* arrival_time, //Time of arrival
                int* CPU_burst_size);

bool acompare(Request lhs, Request rhs);

void algorithmSelector ();

void firstInFirstOut();

void shortestJobFirst();

void roundRobin();

void priority();

void archive();

void fileReader();

};
#endif // CPU_SCH_H_INCLUDED


