//taskset 0x1 ./bitmap_test
#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */

#include "print_utils.h"     /* print_table_row, MILLION     */
#include "rand_generator.h"  /* init_rand,fill_vector_rand   */
#include "bitmap.h"          /* My Bitmap implementation     */
#include "../../C/utils/time_api.h"  /*C based time mgmt API */
using namespace std;

/* Number of inserts == Coupon Collector problem = n ln(n)   *
 * inserts to ensure every bitmap position [1, max_rand_val] *
 * is covered                                                */
const int max_rand_val      = 128;
const int number_of_inserts = 620; //~n ln(n)
const int num_test_iters    = 10;

/* Perf test constants (container size, #ops, max set bit)   */
static const size_t perf_size     = MILLION;

/* Compare performance of STL Bitmap and my Bitmap           */
void bitmap_perf_test()
{
   std::vector<size_t> val(perf_size);
   /* Fill vector with an increasing sequence 0, 1,...,10^6  */
   std::iota (std::begin(val), std::end(val), 0);
   //std::shuffle(val.begin(), val.end(), std::default_random_engine{});
   struct time_api_t stl_time, my_time;
   struct tsc_api_t stl_tsc, my_tsc;
   
   cout << "Running a Micro-Benchmark comparing Bitmap with STL bitset "
        << "with a container of size " << val.size() << " and "
        << perf_size << " operations" << endl;

   /* Init code (init both clock_gettime and rdtsc           */
   rt_measure_init(&stl_time);  rt_measure_init(&my_time);
   tsc_measure_init(&stl_tsc);  tsc_measure_init(&my_tsc);

   /* Measure STL Container first (init, set, get, clear)    */
   rt_measure_start(&stl_time, true);
   tsc_measure_start(&stl_tsc);
   {
      std::bitset<perf_size> stl_bmp;   /* create and reset  */
      for(auto v : val) stl_bmp.set(v); /* set all bits      */
      for(auto v : val) stl_bmp.test(v);/* get all bits      */
      stl_bmp.reset();                  /* clear all bits    */
   }
   tsc_measure_end(&stl_tsc);
   rt_measure_end(&stl_time, true);

   /* Measure My Bitmap Container nxt(init, set, get, clear) */
   rt_measure_start(&my_time, true);
   tsc_measure_start(&my_tsc);
   {
      class Bitmap my_bmp(perf_size);   /* create and reset  */
      for(auto v : val) my_bmp.set(v);  /* set all bits      */
      for(auto v : val) my_bmp.get(v);  /* get all bits      */
      my_bmp.reset();                   /* clear all bits    */
   }
   tsc_measure_end(&my_tsc);
   rt_measure_end(&my_time, true);

   /* Dump all time related statistics                       */
   time_print_api(&stl_time, "   Info: STL Bitmap");
   time_tsc_statistics_print(perf_size, &stl_time, &stl_tsc);
   time_print_api(&my_time,  "   Info: My Bitmap");
   time_tsc_statistics_print(perf_size, &my_time, &my_tsc);
}

/* Generate a sequence of random numbers. Insert them into   *
 * the bitmap and then manually check if all the bits are set*/
bool bitmap_auto_test()
{
   vector<uint64_t> v(number_of_inserts);
   class Bitmap bmp(max_rand_val);
   
   fill_vector_rand(v, 0, max_rand_val);
        
   /* Sort the random input vector and remove duplicates */
   sort(v.begin(), v.end());
   v.erase(unique(v.begin(), v.end()), v.end());

   bmp.set(v);
   if(bmp.count() != v.size()) {
      cout << "Error: Auto test size match issue."
           << " Unique vector holds " << v.size() << " elements"
           << " while bitmap hosts  " << bmp.count() <<  " elements" << endl;
      return false;
   }
   for(auto val : v) {
      if(bmp.get(val) == false) {
         cout << "Error: Auto test get failed for " << val << endl;
      return false;
      }
   }
   return true;
}

std::vector<size_t> manual_pos = {0, 1, 2, 3, 4, 16, 25, 36, 37, 98, 99, 100, 126, 127};

bool bitmap_manual_test(size_t bmp_size = 128)
{
   class Bitmap bmp(bmp_size);
   if(bmp.size() < bmp_size) {
      cout << "Error: Created bitmap is smaller than requested"
           << "Exp=" << bmp_size << " Got=" << bmp.size() << endl;
      return false;
   }
   bmp.resize(bmp_size * 2);
   if(bmp.size() < bmp_size * 2) {
      cout << "Error: Bitmap resize failed. "
           << "Exp=" << bmp_size*2 << " Got=" << bmp.size() << endl;
      return false;
   }
   bmp.set(manual_pos);  /* set all positions at 1 shot      */
   if(bmp.count() != manual_pos.size()) {
      bmp.dump();
      cout << "Error: Bitmap Set test failed. Count not correct after set."
           << " Exp=" << manual_pos.size() << " Got=" << bmp.count()  << endl;
      return false;
   }
   /* Get test: Make sure all the bits are set               */
   for(auto pos : manual_pos) {
      if(bmp.get(pos) == false) {
         cout << "Error: Bitmap Set test failed."
              << pos << " bit not found in bitmap " << endl;
         return false;
      }
   }
   /* GetNextSet test: Verify get_next_set calculations      */
   for(size_t i = 0; i < manual_pos.size(); ++i) {
      size_t nxt;
      if(i == manual_pos.size() - 1) {/* last bit is spl case*/
         if(bmp.get_next_set_pos(manual_pos[i], nxt) == true) {
            cout << "Error: Bitmap Get Next test failed. "
                 << "get_next_set_pos failed for last set bit "
                 << manual_pos[i] << " expected false but got pos = "
                 << nxt           << endl;
            return false;
         }
      }
      else {
         if(bmp.get_next_set_pos(manual_pos[i], nxt) == false ||
            nxt != manual_pos[i+1]) {
            bmp.dump();
            cout << "Error: Bitmap Get Next test failed. "
                 << "get_next_set_pos failed for "
                 << manual_pos[i] << " expected=" << manual_pos[i+1]
                 << " got="       << nxt
                 << " bitmap_cnt="<< bmp.count() << endl;
            return false;
         }
      }
   }
   bmp.reset();           /* reset all positions at 1 shot   */
   if(bmp.isEmpty() == false) {
      cout << "Error: Bitmap Clear test failed. Bitmap not empty (count="
           << bmp.count() << ")"  << endl;
      return false;
   }
   return true;
}

int main()
{
   init_rand();
   if(bitmap_manual_test() == false)     return -1;
   for(auto i = 0; i < num_test_iters; ++i)
      if(bitmap_auto_test() == false) return -1;
   cout << "Info: All manual and randomized test-cases passed" << endl;
   bitmap_perf_test();
}
