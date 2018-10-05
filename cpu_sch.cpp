#include "cpu_sch.h"

using namespace std;


long int seed = 56329; //This should be changed if you need to make
                       // different runs.

 double Scheduler::random( long int* seed )

  // Warning:  random number generators are, by their
  //   nature, very machine dependent. This generator
  //   will require modification if not run on a
  //   machine with at least a 32 bit word for
  //   integers.

/* Park & Miller function (see CACM Oct. 88) integer version */
/* of their generator.                                       */
/* This should work correctly if largest integer is 2^31 - 1 */
/* or larger.                                                */

{  // function random
	long int  a = 16807,        // 7^5
	          m = 2147483647,   // 2^31 - 1
		  q = 127773,           // m / a (int divide)
		  r = 2836,		        // m % a
		  lo, hi, test;
	double dm = 2147483647;

	hi = *seed / q;
	lo = *seed % q;
	test = a * lo - r * hi;
	*seed = test > 0 ? test : test + m;
	return (double)(*seed/dm);
}  // function random

double Scheduler::exponential(float mean)
{ // function exponential
       return (double)(-mean*log(random(&seed)));
} // function exponential


// Generate process attributes:  primary memory size,
//   execution time (memory references), process type,
//   priority, generation time

void Scheduler::parameters(int   ave_interarrival_time, //between process arrivals
                    int   last_arival_time, //last process arrival time
                    int max_CPU_size,   //Maximum CPU Burst Size
                    int min_CPU_size,   // Minimum CPU Burst Size
                    int* priority,          //Priority
                    long*  arrival_time, //Time of arrival
                    int* CPU_burst_size) //CPU Burst Size

  // Procedures called:
  //   random:  to generate uniformly distributed random variates.
 //    exponential: to generate exponentially distributed random variates
  // Global variables:
  //   seed:  used by function random.

{ // function parameters
  *priority = 1 + int(9*random(&seed)); //generates priority between 1 and 10
  *arrival_time = (long) (last_arival_time + exponential((float) (ave_interarrival_time)) + 0.5);
  *CPU_burst_size = min_CPU_size + int((max_CPU_size-min_CPU_size)*random(&seed)); // generates CPU Burst size
} // function parameters

bool Scheduler::acompare(Request lhs, Request rhs) {

    return lhs.arrivalTime < rhs.arrivalTime; }



void Scheduler::algorithmSelector (){

char algorithmChoice;

cout << "Scheduling algorithm options are as follows:"<< endl;
cout << "\n";

cout << "First In First Out = 1" << endl;
cout << "Shortest Job First = 2" << endl;
cout << "Round Robin = 3" << endl;
cout << "Priority = 4"<< endl;
cout << "\n";


cout << "Please select a scheduling algorithm 1-4: ";
cin >> algorithmChoice;
cout << "\n";

if (algorithmChoice == '1')
    {
        firstInFirstOut();
    }
else if (algorithmChoice == '2')
    {
        shortestJobFirst();
    }
else if (algorithmChoice == '3')
    {
        roundRobin();
    }
else if (algorithmChoice == '4')
    {
        priority();
    }
else cout << "Invalid choice";

}



void Scheduler::fileReader()
{

int iN,aT,bL,p;
float time =0.0;
string line;
  ifstream myfile ("test.txt");
  if (myfile.is_open())
  {

for (int i = 0; i < 10000; i++ )
{
    myfile >> iN >> aT >> bL >> p;
    requestArchive[i].index = iN;
    requestArchive[i].arrivalTime = aT;
    requestArchive[i].burstLength = bL;

    requestArchive[i].priority = p;



}
   cout << time;
    myfile.close();
  }

  //for (int i = 0; i < 9999; ++i )
//{


//}

}


void Scheduler::firstInFirstOut(){

    float sum=0.0;
    float art =0.0;
    float thrput=0.0;
    int i,b[10000];
    int idle=0;
    int tbt = 0;
    int n =10000;
twt=0.0;
for(i=0;i<n;i++)
{
b[i]=requestArchive[i].burstLength;

}
wt[1]=0.0;
for(i=2;i<=n;i++)
{
wt[i]=b[i-1]+wt[i-1];

}
for(i=1;i<=n;i++)
{
twt=twt+wt[i];
tat[i]=b[i-1]+wt[i];
rt[i]=tat[i]+requestArchive[i-1].arrivalTime;



sum+=tat[i];

art+=rt[i];
tbt += b[i-1];
}
awt=twt/n +0.1;
sum=sum/n+0.1;
art=art/n+0.1;
int et = rt[n]-b[0];
thrput=et/n;


idle = et-tbt;

float cpuUse=(et-idle);//rt[n-1];
cpuUse = (cpuUse/et)*100;



cout << "Number of processes: " << "10000" << endl;
cout << "Total elapsed time: " << et*0.0020 << "ms" << endl;
cout << "Throughput: " << thrput << endl;
cout << "CPU utilization: " << cpuUse << "%"<< endl;
cout << "Average waiting time: " << awt*0.0020 << "ms" << endl;
cout << "Average turnaround time: " << sum*0.0020 << "ms" << endl;
cout << "Average response time: " << art*0.0020 << "ms" << endl;
}

void Scheduler::shortestJobFirst()
{
    int i,j,temp,b[10000];
    int idle=0;
    int tbt = 0;
    int n = 10000;
float sum=0.0;
float art =0.0;
float thrput=0.0;
twt=0.0;
for(i=0;i<n;i++)
{
b[i]=requestArchive[i].burstLength;

}
for(i=n;i>=1;i--)
{
for(j=2;j<=n;j++)
{
if(b[j-1]>b[j])
{
temp=b[j-1];
b[j-1]=b[j];
b[j]=temp;
}
}
}
wt[1]=0;
for(i=2;i<=n;i++)
{
wt[i]=b[i-1]+wt[i-1];
}
for(i=1;i<=n;i++)
{
twt=twt+wt[i];
tat[i]=b[i-1]+wt[i];
rt[i]=tat[i]+requestArchive[i-1].arrivalTime;



sum+=tat[i];

art+=rt[i];
tbt += b[i-1];
}
awt=twt/n;
sum=sum/n;
art=art/n;
int et = rt[n]-b[0];
thrput=et/n;


idle = et-tbt;

float cpuUse=(et-idle);//rt[n-1];
cpuUse = (cpuUse/et)*100;

int earliest = requestArchive[0].arrivalTime ;
    for ( int i=1;  i < sizeof(requestArchive)/sizeof(requestArchive[0]);  ++i )
        if ( requestArchive[i].arrivalTime < earliest )
             earliest = requestArchive[i].arrivalTime ;



    awt = awt-earliest+0.1;

    sum = sum-earliest+0.1;
    art = art-earliest+0.1;

cout << "Number of processes: " << "10000" << endl;
cout << "Total elapsed time: " << et*0.0020 << "ms" << endl;
cout << "Throughput: " << thrput << endl;
cout << "CPU utilization: " << cpuUse << "%"<< endl;
cout << "Average waiting time: " << awt*0.0020 << "ms" << endl;
cout << "Average turnaround time: " << sum*0.0020 << "ms" << endl;
cout << "Average response time: " << art*0.0020 << "ms" << endl;
    }

void Scheduler::roundRobin()
{
int i,j,tq,k,b[10000],Rrobin[10000][10000],count[10000];
int max=0;
int m;
int n =10000;
int idle =0;
int tbt = 0;
float sum=0.0;
float art =0.0;
float thrput=0.0;
twt=0.0;
for(i=1;i<=n;i++)
{
b[i]=requestArchive[i-1].burstLength;

if(max<b[i])
max=b[i];
wt[i]=0;
}
cout<<"\nEnter the Time Quantum=";
cin>>tq;
//TO find the dimension of the Round robin array
m=max/tq+1;
//initializing Round robin array
for(i=1;i<=n;i++)
{
for(j=1;j<=m;j++)
{
Rrobin[i][j]=0;
}
}
//placing value in the Rrobin array
i=1;
while(i<=n)
{
j=1;
while(b[i]>0)
{
if(b[i]>=tq)
{
b[i]=b[i]-tq;
Rrobin[i][j]=b[i];
j++;
}
else
{
Rrobin[i][j]=b[i];
b[i]=0;
j++;
}
}
count[i]=j-1;
i++;
}


for(j=1;j<=n;j++)
{
for(i=1;i<=count[j];i++)
{
if(i==count[j])
{
for(k=1;k<j;k++)
{
if(k!=j)
wt[j]+=Rrobin[k][i];
}
}
else
for(k=1;k<=n;k++)
{
if(k!=j)
wt[j]+=Rrobin[k][i];
}
}
}

//calculating Average Weighting Time
for(i=1;i<=n;i++)
{
twt=twt+wt[i]+requestArchive[i-1].burstLength;
tat[i]=requestArchive[i-1].burstLength+requestArchive[i-1].burstLength+wt[i];
rt[i]=tat[i]+requestArchive[i-1].arrivalTime;
sum+=tat[i];

art+=rt[i];
tbt += requestArchive[i-1].burstLength;
}
awt=twt/n;
sum=sum/n;

art=art/n;
int et = rt[n]-requestArchive[0].arrivalTime+requestArchive[0].burstLength;
thrput=et/n;


idle = et-tbt;

float cpuUse=(et-idle);//rt[n-1];
cpuUse = (cpuUse/et)*100;

cout << "Number of processes: " << "10000" << endl;
cout << "Total elapsed time: " << et*0.0020 << "ms" << endl;
cout << "Throughput: " << thrput << endl;
cout << "CPU utilization: " << cpuUse << "%"<< endl;
cout << "Average waiting time: " << (awt-0.1)*0.0020 << "ms" << endl;
cout << "Average turnaround time: " << (sum-0.1)*0.0020 << "ms" << endl;
cout << "Average response time: " << art*0.0020 << "ms" << endl;
}

void Scheduler::priority()
{

int i,j,temp,b[10000],p[10000];
    int idle=0;
    int tbt = 0;
    int n = 10000;
float sum=0.0;
float art =0.0;
float thrput=0.0;
twt=0.0;
for(i=0;i<n;i++)
{
b[i]=requestArchive[i].burstLength;
p[i]=requestArchive[i].priority;

}
for(i=n;i>=1;i--)
{
for(j=2;j<=n;j++)
{
if(p[j-1]>p[j])
{
temp=p[j-1];
p[j-1]=p[j];
p[j]=temp;
}
}
}
wt[1]=0;
for(i=2;i<=n;i++)
{
wt[i]=b[i-1]+wt[i-1];
}
for(i=1;i<=n;i++)
{
twt=twt+wt[i];
tat[i]=b[i-1]+wt[i];
rt[i]=tat[i]+requestArchive[i-1].arrivalTime;


sum+=tat[i];

art+=rt[i];
tbt += b[i-1];
}
awt=twt/n;
sum=sum/n;
art=art/n;
int et = rt[n]-b[0];
thrput=et/n;


idle = et-tbt;

float cpuUse=(et-idle);//rt[n-1];
cpuUse = (cpuUse/et)*100;

int earliest = requestArchive[0].arrivalTime ;
    for ( int i=1;  i < sizeof(requestArchive)/sizeof(requestArchive[0]);  ++i )
        if ( requestArchive[i].arrivalTime < earliest )
             earliest = requestArchive[i].arrivalTime ;

             int shortest = wt[0];
             for (int q=1;  q < sizeof(wt)/sizeof(wt[0]);  ++q){
             if (wt[0] <=0){
                shortest = wt[q];
             }
        }
    for ( int i=1;  i < sizeof(wt)/sizeof(wt[0]);  ++i ){
        if ( wt[i] < shortest){

            if (wt[i]>0){
             shortest = wt[i] ;
           }
        }
    }

    awt = awt-earliest-shortest-0.1;

    sum = sum-earliest-shortest-0.1;
    art = art-earliest-shortest-0.1;

cout << "Number of processes: " << "10000" << endl;
cout << "Total elapsed time: " << et*0.0020 << "ms" << endl;
cout << "Throughput: " << thrput << endl;
cout << "CPU utilization: " << cpuUse << "%"<< endl;
cout << "Average waiting time: " << awt*0.0020 << "ms" << endl;
cout << "Average turnaround time: " << sum*0.0020 << "ms" << endl;
cout << "Average response time: " << art*0.0020 << "ms" << endl;
    }
