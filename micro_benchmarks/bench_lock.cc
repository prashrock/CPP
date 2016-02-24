//g++ --std=c++11 -O3 -g  -o bench_lock bench_lock.cc -lpthread
//taskset 0x1 ./bench_gettime -perf   #perf measure
//strace -t ./bench_gettime           ##syscalls for each API
//ltrace ./bench_gettime              ##libcalls for each API

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
#include <unistd.h>          /* getpid                       */
#include <sys/time.h>        /* gettimeofday()               */
#include <sys/syscall.h>     /* syscall                      */
#include <pthread.h>         /* Pthread Spinlock             */

#include "../../C/utils/time_api.h"  /*C based time mgmt API */
using namespace std;

/* Check if pattern occurs in text. If yes return first idx  */
const int number_of_iterations = MILLION;
struct timespec tspec;      /* clock_gettime                 */
struct timeval tval;        /* gettimeofday                  */
string s_trace = "-single"; /* Call exactly once             */
string s_perf   = "-perf";  /*Call number_of_iterations times*/

static inline int barebones_spinlock(volatile int *dst)
{
   char res;
   int exp = 0;
   int src = 1;
  
   do {
      asm volatile(
         MPLOCKED
         "cmpxchgl %[src], %[dst];"
         "sete %[res];"
         : [res] "=a" (res),     /* output */
           [dst] "=m" (*dst)
         : [src] "r" (src),      /* input */
           "a" (exp),
           "m" (*dst)
         : "memory");            /* no-clobber list */
  
   }
   while (res != 1);
   return 0;
}

static inline int barebones_spinunlock(volatile int *v)
{
   *v = 0;
   return 0;
}

/**
 * Measure the time taken for num_of_iters loops of rdtsc()
 */
int measure_pthread_lock(unsigned num_of_iters=number_of_iterations)
{
	struct time_api_t time;
	struct tsc_api_t tsc;
   pthread_spinlock_t lock;
   int res, pshared;
   res = pthread_spin_init(&lock, pshared);

	/* Init */
	rt_measure_init(&time);
	tsc_measure_init(&tsc);
		
	/* Prime TLB/Cache before going to the actual loop   */
   res = pthread_spin_lock(&lock); /* lock the spinlock */
   res = pthread_spin_unlock(&lock); /* unlock the spinlock */
   
	/* Measure the time taken for the loop */
	rt_measure_start(&time, true);
	tsc_measure_start(&tsc);
	for (unsigned i = 0; i < num_of_iters; i++) {
      res = pthread_spin_lock(&lock);
      res = pthread_spin_unlock(&lock); /* unlock the spinlock */
	}
	tsc_measure_end(&tsc);
	rt_measure_end(&time, true);

	/* Dump the statistics */
	time_print_api(&time, "   Info: pthread_lock");
	time_tsc_statistics_print(num_of_iters, &time, &tsc);
	return res;
}

/**
 * Measure the time taken for num_of_iters loops barebones_spinlock
 */
int measure_barebones_spinlock(unsigned num_of_iters=number_of_iterations)
{
	struct time_api_t time;
	struct tsc_api_t tsc;
   volatile int val = 0;
   int res;

	/* Init */
	rt_measure_init(&time);
	tsc_measure_init(&tsc);
		
	/* Prime TLB/Cache before going to the actual loop   */
   res = barebones_spinlock(&val); /* lock the spinlock */
   res = barebones_spinunlock(&val); /* unlock the spinlock */

	/* Measure the time taken for the loop */
	rt_measure_start(&time, true);
	tsc_measure_start(&tsc);
	for (unsigned i = 0; i < num_of_iters; i++) {
      res = barebones_spinlock(&val); /* lock the spinlock */
      res = barebones_spinunlock(&val); /* unlock the spinlock */
	}
	tsc_measure_end(&tsc);
	rt_measure_end(&time, true);

	/* Dump the statistics */
	time_print_api(&time, "   Info: barebones_spinlock");
	time_tsc_statistics_print(num_of_iters, &time, &tsc);
	return res;
}


/**
 * Useful to check #syscalls, #libcalls to each gettime variant
 */
int single_call()
{
   pthread_spinlock_t lock;
   int res, pshared;
   volatile int val = 0;
   res = pthread_spin_init(&lock, pshared);

   /* Marker for pthread_spinlock */
	cout << "pthread_spin_lock" << endl;
   res = pthread_spin_lock(&lock); /* lock the spinlock */
   res = pthread_spin_unlock(&lock); /* unlock the spinlock */

   /* Marker for barebones_spinlock */
	cout << "barebones_spinlock_lock" << endl;
   res = barebones_spinlock(&val);   /* lock the spinlock */
   res = barebones_spinunlock(&val); /* unlock the spinlock */
   
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
	
	cout << "1) pthread_lock" << endl;
   measure_pthread_lock();

   cout << "2) barebones_spinlock" << endl;
   measure_barebones_spinlock();

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

