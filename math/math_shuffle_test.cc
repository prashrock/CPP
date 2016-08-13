//Use 'taskset -c <core> ./math_shuffle_test' to run micro-benchmark
#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */

#include "print_utils.h"     /* print_table_row, MILLION     */
#include "rand_generator.h"  /* init_rand,fill_vector_rand   */
#include "math_shuffle.h"    /* math::shuffle implementation */
#include "time_api.h"        /*C based time mgmt API         */
using namespace std;

const int num_loops = MILLION;

void shuffle_perf_test(const int N = num_loops) {
   std::vector<int> v(N);
   
   /* Fill vector with an increasing sequence 0,1,..,(10^6)-1*/
   std::iota (std::begin(v), std::end(v), 0);
   cout << "Running a Micro-Benchmark comparing shuffle with STL shuffle "
        << "with a container of size " << N << endl;

   /* Init code (init both clock_gettime and rdtsc           */
   struct time_api_t stl_time, my_time;
   struct tsc_api_t stl_tsc, my_tsc;
   rt_measure_init(&stl_time);  rt_measure_init(&my_time);
   tsc_measure_init(&stl_tsc);  tsc_measure_init(&my_tsc);

   /* Measure STL shuffle first                              */
   rt_measure_start(&stl_time, true);
   tsc_measure_start(&stl_tsc);
   {
      std::shuffle(v.begin(), v.end(), std::default_random_engine{});
   }
   tsc_measure_end(&stl_tsc);
   rt_measure_end(&stl_time, true);

   /* Measure my Knuth shuffle next                          */
   rt_measure_start(&my_time, true);
   tsc_measure_start(&my_tsc);
   {
      math::shuffle(v);
   }
   tsc_measure_end(&my_tsc);
   rt_measure_end(&my_time, true);

   /* Dump all time related statistics                       */
   time_print_api(&stl_time, "   Info: STL Shuffle");
   time_tsc_statistics_print(N, &stl_time, &stl_tsc);
   time_print_api(&my_time,  "   Info: My Shuffle");
   time_tsc_statistics_print(N, &my_time, &my_tsc);
}

int main(){
   init_rand();
   shuffle_perf_test();
   cout << "Info: All Math Shuffle tests completed successfully." << endl;
   return 0;
}
