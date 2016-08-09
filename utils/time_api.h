#ifndef _TIME_API_H_
#define _TIME_API_H_
#include <stdio.h>
#include <stdlib.h>                /* atoi                              */
#include <stdbool.h>               /* bool, true, false                 */
#include <string.h>                /* memset                            */
#include <assert.h>                /* assert                            */
#include <limits.h>                /* INT_MAX                           */
#include <stdint.h>                /* uint64_t                          */
#include <inttypes.h>              /* PRIu64                            */
#include <time.h>                  /* timespec, clock_gettime           */
#include <errno.h>                 /* errno                             */

#ifdef __cplusplus
extern "C" {
#endif

#include "compiler_api.h"          /* likely(), unlikely()              */
#include "atomic.h"                /* rdtsc                             */

#define MILLION (1000000)          /* 10^6                              */
#define BILLION (1000000000ULL)    /* 10^9                              */
#define NANOSEC_PER_SEC BILLION

struct time_api_t {
   struct timespec start;
   struct timespec end;
   uint64_t time_ns;
};

struct tsc_api_t {
   uint64_t start;
   uint64_t end;
   uint64_t tsc_diff;
};

#define TIME_API_MAX_TIME_UNITS (sizeof(time_unit)/sizeof(char *))
#define TIME_API_SECONDS_UNIT   (3)
#ifndef TIME_API_MODE
#define TIME_API_MODE           (CLOCK_REALTIME)
#endif

static const char *time_unit[] = 
{
   "ns",
   "us",
   "ms",
   "s",
   "mins",
   "hours",
};

static inline uint64_t rdpmc(void)
{
   union {
      uint64_t tsc_64;
      struct {
         uint32_t lo_32;
         uint32_t hi_32;
      }t32; /* Please C++ anonymous struct error                        */
   } tsc;
   
   /* ecx = 0x10000 corresponds to the physical TSC for VMware          */
   asm volatile("rdpmc" :
                "=a" (tsc.t32.lo_32),
                "=d" (tsc.t32.hi_32) :
                "c"(0x10000));
   return tsc.tsc_64;
}

/* Read TSC counter. Below are Some useful settings in /proc/cpuinfo    *
 * 1) CONSTANT_TSC                                                      *
 * = indicates TSC runs at constant freq irrespective of P/T-states     *
 * 2) NONSTOP_TSC                                                       *
 * = indicates that TSC does not stop in deep C-states.                 *
 * 3) INVARIANT_TSC                                                     *
 * = TSC will run at a constant rate in all ACPI P-, C-. and T-states   *
 * INVARIANT is the best mode and with this TSC can be used for wall    *
 * clock timer services per socket.                                     *
 * Note: Ideally Pre-emption must be disabled (preempt_disable()) and   *
 * Hardware Interrupts must be disabled (raw_local_irq_save()) to       *
 * guarantee exclusive ownership of the CPU when measuring #cycles      *
 * Note: INVARIANT_TSC is applicable to only one socket. Cross-socket   *
 * synchronization is not implied as Synchronous RESET's have to be     *
 * provided to both sockets for cross-socket invariant_tsc              *
 * Note: RDTSC is not ordered, so, execution order is not guaranteed    *
 * Note: Invariant TSC update is not instantaneous (i.e., it does not   *
 * go up by 1 every cycle, so is not reliable to measure just a few     *
 * instruction (few clock cycles)                                       */ 
static inline uint64_t rdtsc(void)
{
   union {
      uint64_t tsc_64;
      struct {
         uint32_t lo_32;
         uint32_t hi_32;
      }t32; /* Please C++ anonymous struct error                        */
   } tsc;
   asm volatile ("rdtsc" :
                 "=a" (tsc.t32.lo_32),
                 "=d" (tsc.t32.hi_32));
   return tsc.tsc_64;
   //return tsc.lo_32  | (((uint64_t )tsc.hi_32 ) << 32);
}

/* RDTSCP = Assembly instruction to read timestamp register while       *
 * offering pseudo "serialization" by reading CPU identifier (CPUID)    *
 * Note: RDTSCP waits until all prev instructions have been executed    *
 * however, subsequent instructions may begin execution before the      *
 * read operation is performed                                          *
 * Practically RDTSCP has a higher overhead by itself, but alleviates   *
 * out of order instructions atleast those before the RDTSP.            *
 * Reference: download.intel.com/embedded/software/IA/324264.pdf        *
 * Note: Ideal measurement requires RDTSC+CPUID | code | RDTSCP+CPUID   *
 * Note: On virtualized environments, CPUID may trap to hypervisor      *
 * making it costlier to use RDTSCP.                                    *
 * Note: As per Akaros, LFENCE+RDTSC | code | RDTSCP+LFENCE is better   *
 * akaros.cs.berkeley.edu/lxr/akaros/kern/arch/x86/rdtsc_test.c         */
static inline uint64_t rdtscp(int *chip, int *core)
{
   unsigned cpu;
   union {
      uint64_t tsc_64;
      struct {
         uint32_t lo_32;
         uint32_t hi_32;
      }t32; /* Please C++ anonymous struct error                        */
   } tsc;
   asm volatile ("rdtscp" :
                 "=a" (tsc.t32.lo_32),
                 "=d" (tsc.t32.hi_32),
                 "=c" (cpu));
   
   *chip = (cpu & 0xFFF000) >> 12;
   *core = (cpu & 0xFFF);
   return tsc.tsc_64;
   //return tsc.lo_32  | (((uint64_t )tsc.hi_32 ) << 32);
}

/*------------------- Clock Gettime API --------------------------------*/
/* Translate timespec to ns */
static inline uint64_t timespec_to_ns(struct timespec *val)
{
   return (uint64_t)val->tv_sec * NANOSEC_PER_SEC + (uint64_t)val->tv_nsec;
}	
/* Convert time in ns to bestfit time-unit and return respective string */
static inline const char *convert_tv_ns_to_bestfit_time_unit(uint64_t *tv)
{
   int i = 0;
   /* covers ns to s                                                    */
   while((*tv/1000) && (i < TIME_API_SECONDS_UNIT)) {
      *tv = *tv/1000;
      i++;
   }
   /* covers seconds to hours                                           */
   while((*tv/60) && (i >= TIME_API_SECONDS_UNIT) &&
         (i != TIME_API_MAX_TIME_UNITS - 1)) {
      *tv = *tv/60;
      i++;
   }
   /* Avoid printing ns twice                                           */
   if(i == 0) return NULL;
   else       return time_unit[i];
}

/* Clear up Time API struct. This is helpful when struct is sitting     *
 * on stack or performing iterative computation.                        *
 * Note: tsc_measure_calc API maintains sum of differences              */
static inline void rt_measure_init(struct time_api_t *ta)
{
   memset(ta, 0, sizeof(struct time_api_t));
}

/* Calculate diff between two timespec values and maintain              *
 * sum of such differences                                              */
static inline void timespec_diff_calc(struct time_api_t *ta)
{
   struct timespec *start = &ta->start;
   struct timespec *end = &ta->end;
   struct timespec diff;
   if ((end->tv_nsec - start->tv_nsec) < 0) {
      diff.tv_sec = end->tv_sec - start->tv_sec - 1;
      diff.tv_nsec = NANOSEC_PER_SEC + end->tv_nsec - start->tv_nsec;
   }
   else {
      diff.tv_sec = end->tv_sec - start->tv_sec;
      diff.tv_nsec = end->tv_nsec - start->tv_nsec;
   }
   /* Maintain sum of differences for iterative rt measures             */
   ta->time_ns += timespec_to_ns(&diff);
}

/* Below are the user API's for measuring and printing time             */
/* RT = The identifier of the systemwide realtime clock.                */
static inline bool rt_measure_start(struct time_api_t *ta, bool print)
{
   int ret = clock_gettime(TIME_API_MODE, &ta->start);
   if(likely(ret == 0))
      return true;
   else {
      if(print)
         printf("Error:clock_gettime failed: '%s'\n", strerror(errno));
      return false;
   }
}

/* Register end time measurement, calculate the diff and update         *
 * diff variable. This supports iterative rt measurements               */
static inline bool rt_measure_end(struct time_api_t *ta, bool print)
{
   int ret = clock_gettime(TIME_API_MODE, &ta->end);
   if(likely(ret == 0)) {
      timespec_diff_calc(ta);
      return true;
   }
   else {
      if(print)
         printf("Error:clock_gettime failed: '%s'\n", strerror(errno));
      return false;
   }
}

/* Prints the time elapsed in best possible unit                        */
static inline void time_print_api(struct time_api_t *ta, const char *x)
{
   uint64_t val = ta->time_ns;
   const char *unit;
   unit = convert_tv_ns_to_bestfit_time_unit(&val);
   if(x) {
      printf("%s took %" PRIu64 " %s ", x, ta->time_ns, time_unit[0]);
      if(unit) /* If time > ns                                        */
         printf(" (%" PRIu64 " %s)", val, unit);
      printf("\n");
   }
   else {
      printf("%10" PRIu64 " %3s", val, unit);
   }
}

/*------------------- Timestamp(TSC) API -------------------------------*/
/* Clear up TSC structure. This is helpful when this struct is sitting  *
 * on stack or performing iterative computation.                        *
 * Note: tsc_measure_calc API maintains sum of differences              */
static inline void tsc_measure_init(struct tsc_api_t *tsc)
{
   memset(tsc, 0, sizeof(struct tsc_api_t));
}

/* Assuming starting value of TSC was not set manually to a huge number *
 * TSC wrap-around would take ~292 years on a 2 Ghz machine             *
 *     (#Years = 0xFFFFFFFF_FFFFFFFF / 2*10^9*60*60*24*365 = ~292)      *
 * Therefore - TSC wrap-around is not a viable corner case              */
static inline bool tsc_measure_calc(struct tsc_api_t *tsc, bool print)
{
   if(unlikely(tsc->end < tsc->start)) {
      if(print)
         printf("Error: Start TSC bigger than End TSC !\n");
      return false;
   }
   /* Maintain sum of differences to support iterative tsc measures     */
   tsc->tsc_diff += tsc->end - tsc->start;
   return true;
}

/* Below are the user API's for measuring and printing #clock cycles    *
 * Note1: This API needs constant CPU frequency (Power Mgmt = disabled) *
 * Note2: Either make both calls on 1 core or INVARIANT_TSC is available*
 * Note3: Compile Time Barrier to ensure OPT does not affect measurement*/
static inline void tsc_measure_start(struct tsc_api_t *tsc)
{
   tsc->start = rdtsc();
   compile_mem_barrier();
}

/* Register end TSC measurement, calculate the diff and update          *
 * diff variable. This supports iterative rt measurements               */
static inline void tsc_measure_end(struct tsc_api_t *tsc)
{
   compile_mem_barrier();
   tsc->end = rdtsc();
   tsc_measure_calc(tsc, true);
}

/* This function is useful to gather statistics from a tight loop task  *
 * Given a function with appropriate start/end time/tsc markers, this   *
 * function can be used to measure overall/per_loop/per_sec overhead    *
 * for that specfic task.                                               *
 * Tight loop provides an average to account for scheduling, timer and  *
 * other anamolies which might skew the task performance measurement    */
void time_tsc_statistics_print(uint64_t loop_cnt, struct time_api_t *time,
                               struct tsc_api_t *tsc)
{
   uint64_t tsc_interval, time_interval;
   uint64_t cycles_per_loop;
   double calls_per_sec, cycles_per_sec, time_per_loop_in_ns;
   double total_time_in_sec;

   /* Retrieve Measured Stats                                          */
   tsc_interval  = tsc->tsc_diff;
   time_interval = time->time_ns;

   /* Inferred Stats                                                   */
   total_time_in_sec  = ((double)time_interval / NANOSEC_PER_SEC);
   time_per_loop_in_ns= ((double)time_interval / loop_cnt);
   cycles_per_loop    = tsc_interval / loop_cnt;
   calls_per_sec      = (double)loop_cnt / total_time_in_sec;
   cycles_per_sec     = (double)tsc_interval / total_time_in_sec;

   printf("   Total stats    : %.2f s  | %lu cycles(tsc)\n"
          "   Each loop stats: %.2f ns | %lu cycles(tsc)\n"
          "   Each sec stats : %.2f loops | %.2f cycles(tsc)\n",
          total_time_in_sec, tsc_interval,
          time_per_loop_in_ns, cycles_per_loop,
          calls_per_sec, cycles_per_sec);
}

/* Measure the number of cycles per us available on a given core        *
 * Note: Pin thread to a given core (taskset) before using this func    *
 * This number is typically very close to current CPU freq in Mhz found *
 * with 'dmidecode -t processor | grep Speed' command                   */
int calc_num_cycles_per_us(int *cycles_per_us) {
   struct timespec sleeptime = { 0, 0 };
   struct timespec ts_start, ts_end;

   /* Set the sleep-time to 0.5 s in nanoseconds                        */
   sleeptime.tv_nsec = NANOSEC_PER_SEC / 2;
   
   if (clock_gettime(CLOCK_MONOTONIC_RAW, &ts_start) == 0) {
      uint64_t tsc_start, tsc_end, ns;
      double usecs;

      tsc_start = rdtsc();
      nanosleep(&sleeptime, NULL); /* Sleep for 0.5 seconds             */
      clock_gettime(CLOCK_MONOTONIC_RAW, &ts_end);
      tsc_end = rdtsc();
      ns = ((ts_end.tv_sec  - ts_start.tv_sec) * BILLION);
      ns += (ts_end.tv_nsec - ts_start.tv_nsec);

      usecs = (double)ns / 1000;
      *cycles_per_us = (uint64_t)((tsc_end - tsc_start)/usecs);
      return 0;
   }

   return -1;
}
   
#ifdef __cplusplus
}
#endif
#endif //_TIME_API_H_
