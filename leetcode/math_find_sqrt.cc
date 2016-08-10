//g++-5 -Wall --std=c++11 -g -o math_find_sqrt math_find_sqrt.cc

/**
 * @file  Integer Square Root
 * @brief Given a positive integer find its integral square root
 */

// https://leetcode.com/problems/sqrtx/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow, tgamma(factorial)       */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
using namespace std;

/**
 * Implement int sqrt(int x).
 * Compute and return the square root of x.
 */

/**
 * @brief -                                                  *
 * Time Complexity = O(n) and Space Complexity = O(1)        */
int mySqrtIterative(int num) {
   return 0;
}

/* Binary Search to find out the square root                 *
 * Time Complexity = O(lg n) and Space Complexity = O(1)     */
int mySqrtBS(int num) {
   int b = 1;
   for(int e = num;  e >= b ; ) {
      int mid = b + (e - b)/2;
      if(mid <= num/mid) b = mid + 1;
      else               e = mid - 1; 
   }
   return b - 1;
}

/* Newton's integer method to find square-root of a positive *
 * integer. Inspired by solution posted on Leetcode @        *
 * https://leetcode.com/discuss/58631/3-4-short-lines-integer-newton-every-language */
int mySqrtNewton(int num) {
   if(num == 0) return num; /* avoid divide by zero error    */
   long r = num;
   while(r > num / r) r = (r + num/r) / 2;
   return (int)r;
}

struct test_vector {
   int num;
   int exp;
};

const struct test_vector test[11] =  {
   {0,              0},
   {1,              1},
   {2,              1},
   {3,              1}, 
   {4,              2},
   {15,             3},
   {16,             4},
   {81,             9},
   {250,           15},
   {2147395599, 46339},
   {2147483647, 46340},
};

int main()
{
   for(auto tst : test) {
      auto ans1 = mySqrtBS(tst.num);
      if(ans1 != tst.exp) {
         cout << "Error:mySqrtBS failed. Exp "
              << tst.exp << " Got " << ans1 << " for "
              << tst.num << endl;
         return -1;
      }
      auto ans2 = mySqrtNewton(tst.num);
      if(ans2 != tst.exp) {
         cout << "Error:mySqrtLog failed. Exp "
              << tst.exp << " Got " << ans2 << " for "
              << tst.num << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
