//g++ --std=c++11 -O3 -g  -o bench_gettime bench_gettime.cc
//taskset 0x1 ./bench_gettime -perf   #perf measure
//strace -t ./bench_gettime           ##syscalls for each API
//ltrace ./bench_gettime              ##libcalls for each API

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
#include <unistd.h>          /* getpid                       */
#include <sys/time.h>        /* gettimeofday()               */
#include <sys/syscall.h>     /* syscall                      */

#include "../../C/utils/time_api.h"  /*C based time mgmt API */
using namespace std;

/* Check if pattern occurs in text. If yes return first idx  */
const int number_of_iterations = MILLION;
struct timespec tspec;      /* clock_gettime                 */
struct timeval tval;        /* gettimeofday                  */
string s_trace = "-single"; /* Call exactly once             */
string s_perf   = "-perf";  /*Call number_of_iterations times*/

/**
 * Measure the time taken for num_of_iters loops of rdtsc()
 */
int measure_rdtsc(unsigned num_of_iters=number_of_iterations)
{
	struct time_api_t time;
	struct tsc_api_t tsc;
	int res;
	
	/* Init */
	rt_measure_init(&time);
	tsc_measure_init(&tsc);
		
	/* Prime TLB/Cache before going to the actual loop */
	res = rdtsc();

	/* Measure the time taken for the loop */
	rt_measure_start(&time, true);
	tsc_measure_start(&tsc);
	for (unsigned i = 0; i < num_of_iters; i++) {
		res = rdtsc();
	}
	tsc_measure_end(&tsc);
	rt_measure_end(&time, true);

	/* Dump the statistics */
	time_print_api(&time, "   Info: rdtsc");
	time_tsc_statistics_print(num_of_iters, &time, &tsc);
	return res;
}

/**
 * Measure the time taken for num_of_iters loops of clock_gettime(id)
 */
int measure_clockgettime(clockid_t clk_id,
						  unsigned num_of_iters=number_of_iterations)
{
	struct time_api_t time;
	struct tsc_api_t tsc;
	struct timespec tspec;
	int res;
	
	/* Init */
	rt_measure_init(&time);
	tsc_measure_init(&tsc);

	/* Prime TLB/Cache before going to the actual loop */
	res = clock_gettime(clk_id, &tspec);
	
	/* Measure the time taken for the loop */
	rt_measure_start(&time, true);
	tsc_measure_start(&tsc);
	for(unsigned i = 0; i < num_of_iters; ++i)
		res = clock_gettime(clk_id, &tspec);
	tsc_measure_end(&tsc);
	rt_measure_end(&time, true);

	/* Dump the statistics */
	time_print_api(&time, "clock_gettime()");
	time_tsc_statistics_print(num_of_iters, &time, &tsc);
	return res;
}

/**
 * Measure the time taken for num_of_iters loops of clock_gettime(id)
 */
int measure_gettimeofday(unsigned num_of_iters=number_of_iterations)
{
	struct time_api_t time;
	struct tsc_api_t tsc;
	int res;
	
	/* Init */
	rt_measure_init(&time);
	tsc_measure_init(&tsc);

	/* Prime TLB/Cache before going to the actual loop */
	res = gettimeofday(&tval, NULL);
	
	/* Measure the time taken for the loop */
	rt_measure_start(&time, true);
	tsc_measure_start(&tsc);
	for(unsigned i = 0; i < num_of_iters; ++i)
		res = gettimeofday(&tval, NULL);
	tsc_measure_end(&tsc);
	rt_measure_end(&time, true);

	/* Dump the statistics */
	time_print_api(&time, "gettimeofday()");
	time_tsc_statistics_print(num_of_iters, &time, &tsc);
	return res;
}

/**
 * Useful to check #syscalls, #libcalls to each gettime variant
 */
int single_call()
{
	int res;

	/* Marker for strace */
	cout << "rdtsc" << endl;
	res = rdtsc();

	/* Marker for strace */
	cout << "clock_gettime CLOCK_MONOTONIC_COARSE" << endl;
	res = clock_gettime(CLOCK_MONOTONIC_COARSE, &tspec);

	/* Marker for strace */
	cout << "clock_gettime CLOCK_MONOTONIC" << endl;
	res = clock_gettime(CLOCK_MONOTONIC, &tspec);

	/* Marker for strace */
	cout << "clock_gettime CLOCK_REALTIME" << endl;
	res = clock_gettime(CLOCK_REALTIME, &tspec);

	/* Marker for strace */
	cout << "gettimeofday" << endl;
	gettimeofday(&tval, NULL);
	return res;
}

/**
 * Runs perf_loops for each gettime variant
 */
int perf_call()
{
	int res = 0;
	cout << endl << "Running " << number_of_iterations
		 << " iterations:" << endl;
	
	cout << "1) rdtsc" << endl;
	measure_rdtsc();

	cout << "2) clock_gettime(CLOCK_MONOTONIC_COARSE)" << endl;
	measure_clockgettime(CLOCK_MONOTONIC_COARSE);

	cout << "3) clock_gettime(CLOCK_MONOTONIC)" << endl;
	measure_clockgettime(CLOCK_MONOTONIC);

	cout << "4) clock_gettime(CLOCK_REALTIME)" << endl;
	measure_clockgettime(CLOCK_REALTIME);

	cout << "5) gettimeofday()" << endl;
	measure_gettimeofday();

	return res;
}

void print_usage(char* argv[])
{
	cerr << "Usage: " << argv[0] << " < "
		 << s_trace << " | "
		 << s_perf  << " >" << endl;
}

int main(int argc, char* argv[])
{
	if (argc != 2) { /* 2 arguments: prog_name and -single | -perf */
		print_usage(argv);
		return 1;
	}

	if(!s_trace.compare(argv[1]))      single_call();
	else if(!s_perf.compare(argv[1]))  perf_call();
	else                               print_usage(argv);
	return 0;
}

