//g++ -O3 -Wall --std=c++11 -g -o math_validate_perfect_square math_validate_perfect_square.cc  -I../utils/

/**
 * @file  Valid Perfect Square
 * @brief Given a positive integer find out if its a perfect square
 */

// https://leetcode.com/problems/valid-perfect-square/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow, tgamma(factorial)       */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <string>            /* std::string                  */
#include "time_api.h"        /* C based time mgmt API        */
#include "rand_generator.h"  /* fill_vector_rand (CPP based) */
using namespace std;

/**
 * Given a positive integer num, write a function which returns
 * True if num is a perfect square else False.
 * Note: Do not use any built-in library function such as sqrt.
 * Example 1:
 * Input: 16, Returns: True
 * Example 2:
 * Input: 14, Returns: False
 */

/**
 * @brief - Iterative approach to find out if a number is a  *
 * perfect square                                            *
 * Time Complexity = O(n) and Space Complexity = O(1)        */
bool isPerfectSquareLinear(int num) {
   /* Use the series [2, 3, 5, 7, .... ] to find and remove  *
    * all the factors of the given number(num)               */
   for(int i = 2; num > 1 && i <= num / i; i++) {
      /* If i is a factor then remove all multiple of i      */
      while(num % i == 0) {
         if(num % (i*i) == 0) num /= i*i;
         else                 return false;
      }
      if(i != 2) i++; /* Change loop, from 2, do 3, 5, 7..   */
   }
   /* If num is split into its factor^2, 1 should remain     */
   if(num == 1) return true;
   else         return false;
}

/* Binary Search to find out if number is a perfect square   *
 * Time Complexity = O(lg n) and Space Complexity = O(1)     */
bool isPerfectSquareBinarySearch(int num) {
   for(long b = 0, e = num; b <= e; ) {
      /* mid * mid will overflow, so switch to long          */
      long mid = b + (e - b)/2;
      if     ((long)num > (mid * mid)) b = mid + 1;
      else if((long)num < (mid * mid)) e = mid - 1;
      else                             return true;
   }
   return false;
}

/* Newton's integer square-root method to find if a number   *
 * is a perfect square (refer to ./math_find_sqrt.cc)        *
 * Time Complexity = O(lg n) and Space Complexity = O(1)     */
bool isPerfectSquareNewton(int num) {
   long r = num;
   while(r  > num / r) r = (r + num/r) / 2;
   return ((int)(r * r) == num);
}

struct test_vector {
   int num;
   bool exp;
};

/* Manual test-vector to cover corner cases                  */
const struct test_vector test[12] =  {
   {1,           true},   {2,          false},
   {9,           true},   {16,          true},
   {14,         false},   {1,           true},
   {243,        false},   {500,        false},
   {625,         true},   {729,         true},
   {2147302921,  true},   {2147483647, false},
};

const std::vector<std::string> func_names = {
   "isPerfectSquareLinear",
   "isPerfectSquareBinarySearch",
   "isPerfectSquareNewton", 
};
const std::vector<bool (*)(int)> funcs = {
   isPerfectSquareLinear,
   isPerfectSquareBinarySearch,
   isPerfectSquareNewton, 
};

/* Generate 100K random elements and use this as input to    *
 * validate performance of all 3 algorithms.                 */
static void perfect_square_performance(int N = 100000)
{
   struct time_api_t time[funcs.size()];
   struct tsc_api_t tsc[funcs.size()];
   std::vector<int> input(N);
   
   /* Init code (init both clock_gettime and rdtsc           */
   init_rand(); /* Seed the random number generator          */
   fill_vector_rand(input, 0, std::numeric_limits<int>::max());
   for(auto &t : time) rt_measure_init(&t);
   for(auto &t : tsc)  tsc_measure_init(&t);

   /* Run all three perfect square algorithms in a loop      */
   for(int i = 0; i < (int)funcs.size(); ++i) {
      rt_measure_start(&time[i], true);
      tsc_measure_start(&tsc[i]);

      for(auto val : input) {
         /* Avoid loop vectorization + act as compile time   *
          * memory barrier: http://goo.gl/T0RpLD             */
         __asm volatile("" ::: /* pretend to clobber */ "memory");
         funcs[i](val);
      }
      
      tsc_measure_end(&tsc[i]);
      rt_measure_end(&time[i], true);
   }

   /* Dump all time related statistics                       */
   for(int i = 0; i < (int)funcs.size(); ++i) {
      time_print_api(&time[i], func_names[i].c_str());
      time_tsc_statistics_print(N, &time[i], &tsc[i]);
   }
}

int main()
{
   for(auto tst : test) {
      auto ans = isPerfectSquareLinear(tst.num);
      if(ans != tst.exp) {
         cout << "Error:isPerfectSquareLinear failed. Exp "
              << tst.exp << " Got " << ans << " for "
              << tst.num << endl;
         return -1;
      }
      auto ans2 = isPerfectSquareBinarySearch(tst.num);
      if(ans2 != tst.exp) {
         cout << "Error:isPerfectSquareBinarySearch failed. Exp "
              << tst.exp << " Got " << ans2 << " for "
              << tst.num << endl;
         return -1;
      }
      auto ans3 = isPerfectSquareNewton(tst.num);
      if(ans3 != tst.exp) {
         cout << "Error:isPerfectSquareNewton failed. Exp "
              << tst.exp << " Got " << ans3 << " for "
              << tst.num << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   cout << "Generating 100K Numbers and validating perf" << endl;
   perfect_square_performance();
   return 0;
}

