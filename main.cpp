#include "cpu_sch.h"

using namespace std;



int main(){
   Scheduler sch;

    int   hist[10];
  int   index;
  int   i;

  int   max_CPU_burst, min_CPU_burst;
  int   this_CPU_burst_length;
  int   this_priority;
  int   ave_interarr_time;
  int last_arrival_time = 0;
  long this_arrival_time;
  int temp;
  char choice;

  cout << "Maximum CPU Burst: ";
  cin >>   max_CPU_burst;
  cout << "Minimum CPU Burst: ";
  cin >>   min_CPU_burst;
  cout << "Average Interarrival Time: ";
  cin >>   ave_interarr_time;




  cout << "Do you want to display the input data? y/n: ";
  cin >> choice;
  cout << "\n";
  ofstream outfile ("test.txt");




  if (choice == 'y'){

// Assuming that there are 10000 processes
cout << "Index " << "Arrival time  "<< "CPU Burst Length " << "  Priority" << endl;
    for ( i=1; i<=10000; i++ )
	{
      sch.parameters(ave_interarr_time, last_arrival_time, max_CPU_burst, min_CPU_burst, &this_priority, &this_arrival_time, &this_CPU_burst_length);
      cout << setw( 4 ) << i << setw(12)  << this_arrival_time << setw( 20) << this_CPU_burst_length;
        cout << setw(6) << this_priority << endl;
        outfile << i << " " << this_arrival_time << " " << this_CPU_burst_length << " " << this_priority << endl;
        last_arrival_time = this_arrival_time;
    }
    outfile.close();
    sch.fileReader();

    sch.algorithmSelector();
  }
  else if (choice =='n'){


    for ( i=1; i<=10000; i++ )
	{
      sch.parameters(ave_interarr_time, last_arrival_time, max_CPU_burst, min_CPU_burst, &this_priority, &this_arrival_time, &this_CPU_burst_length);
        outfile << i << " " << this_arrival_time << " " << this_CPU_burst_length << " " << this_priority << endl;
        last_arrival_time = this_arrival_time;
    }
    outfile.close();
    sch.fileReader();
    sch.algorithmSelector();
  }

  else cout << "Invalid Choice";

return 0;
  } // function main
