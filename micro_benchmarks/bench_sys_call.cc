//g++ --std=c++11 -o sys_call_overhead sys_call_overhead.cpp
//taskset 0x1 ./sys_call_overhead
//strace -e trace=gettid -c -S calls ./sys_call_overhead
#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
#include <sys/syscall.h>     /* syscall                      */
#include <unistd.h>          /* getpid                       */

#include "../../C/utils/time_api.h"  /* C based time mgmt API        */
using namespace std;

/* Check if pattern occurs in text. If yes return first idx  */
const int number_of_iterations = MILLION/10;
volatile pid_t gtid;
volatile uint64_t res;

void measure_rdtsc(unsigned num_of_iters=number_of_iterations)
{
	struct time_api_t time;
	struct tsc_api_t tsc;


	/* Init */
	rt_measure_init(&time);
	tsc_measure_init(&tsc);
		
	/* Prime TLB/Cache before going to the actual loop */
	res = rdtsc();

	rt_measure_start(&time, true);
	tsc_measure_start(&tsc);
	
	for (unsigned i = 0; i < num_of_iters; i++) {
		res += rdtsc();
	}
	
	tsc_measure_end(&tsc);
	rt_measure_end(&time, true);
	time_print_api(&time, "   Info: rdtsc");
	time_tsc_statistics_print(num_of_iters, &time, &tsc);
}

void sys_call_overhead_calculate(unsigned num_of_iters=number_of_iterations)
{
	struct time_api_t time;
	struct tsc_api_t tsc;
	rt_measure_init(&time);
	tsc_measure_init(&tsc);

	/* Prime TLB/Cache before going to the actual loop */
	gtid = syscall(SYS_gettid);
	
	/* Measure the time taken for the loop */
	rt_measure_start(&time, true);
	tsc_measure_start(&tsc);
	for(unsigned i = 0; i < num_of_iters; ++i)
	{
		gtid = syscall(SYS_gettid);
	}
	tsc_measure_end(&tsc);
	rt_measure_end(&time, true);

	/* Dump the statistics */
	time_print_api(&time, "gettid() syscall");
	time_tsc_statistics_print(num_of_iters, &time, &tsc);
}
	
int main()
{
	cout << endl << "Running " << number_of_iterations
		 << " iterations of rdtsc():" << endl;
	measure_rdtsc();
	cout << endl << "Running " << number_of_iterations
		 << " iterations of syscall(gettid):" << endl;
	sys_call_overhead_calculate();
	return 0;
}
