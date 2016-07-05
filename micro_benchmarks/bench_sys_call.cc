//g++ -O3  --std=c++11 -o bench_sys_call bench_sys_call.cc -I../../C/utils
//taskset 0x1 ./bench_sys_call
//strace -e trace=gettid -c -S calls ./bench_sys_call
//ltrace ./bench_sys_call              ##libcalls for each API

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
#include <sys/syscall.h>     /* syscall                      */
#include <unistd.h>          /* getpid                       */

#include "time_api.h"        /* C based time mgmt API        */
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
		
   /* Prime TLB/Cache before going to the actual loop        */
   res = rdtsc();

   /* Measure the time taken for the loop */
   rt_measure_start(&time, true);
   tsc_measure_start(&tsc);
   for (unsigned i = 0; i < num_of_iters; i++) {
      /* Avoid loop vectorization + act as compile time      *
       * memory barrier: http://goo.gl/T0RpLD                */
      __asm volatile("" ::: /* pretend to clobber */ "memory");
      res += rdtsc();
   }
   tsc_measure_end(&tsc);
   rt_measure_end(&time, true);

   /* Dump the statistics */
   time_print_api(&time, "   Info: rdtsc");
   time_tsc_statistics_print(num_of_iters, &time, &tsc);
}

void measure_sys_call_overhead(unsigned num_of_iters=number_of_iterations)
{
   struct time_api_t time;
   struct tsc_api_t tsc;

   /* Init */
   rt_measure_init(&time);
   tsc_measure_init(&tsc);

   /* Prime TLB/Cache before going to the actual loop */
   gtid = syscall(SYS_gettid);
	
   /* Measure the time taken for the loop */
   rt_measure_start(&time, true);
   tsc_measure_start(&tsc);
   for(unsigned i = 0; i < num_of_iters; ++i) {
      /* Avoid loop vectorization + act as compile time      *
       * memory barrier: http://goo.gl/T0RpLD                */
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
   measure_sys_call_overhead();
   return 0;
}
