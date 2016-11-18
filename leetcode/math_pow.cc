//g++-5 -Wall --std=c++11 -g -o math_pow math_pow.cc

/**
 * @file  Integer Pow(x,n)
 * @brief Implement Pow(x,n)
 */

// https://leetcode.com/problems/powx-n/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <cmath>             /* std::round                   */
using namespace std;

/**  Implement int pow(x, n)                                 */
/* If n is -ve and x is an integer, we can avoid floating pt *
 * ops by using a long to store the ans till the end         */
double myPow(double x, int n) {
   double ans = 1;
   /* Handle special cases first (x^0 and overflow of -n to n)     */
   if(n == 0)                   return ans;
   if(n == std::numeric_limits<int>::min()) {
      if(x == 1 || x == -1)     return ans;
      else                      return 0;
   }
   /* If n is negative, make it +ve and instead change x to 1/x */
   if(n <  0)   {  x = 1/x; n = -n; }
   for(; n > 0; n >>= 1) {
      if(n & 1) ans *= x;
      x *= x;
   }
   return ans;
}

struct test_vector {
   double x;
   int n;
   double exp;
};

const struct test_vector test[11] =  {
   { 8.88023,               7,  4354812.89022},
   { 8.84372,              -5,        0.00002},
   {34.00515,               3,    39321.86291},
   {34.00515,              -3,        0.00003},
   { 0.00001,      2147483647,        0.00000},
   { 1.00000,      2147483647,        1.00000},
   { 2.00000,     -2147483648,        0.00000},
   { 1.00000,     -2147483648,        1.00000},
   {-1.00000,     -2147483648,        1.00000},
   { 1.00005,     -2147483648,        0.00000},
   {12351235,     -2147483648,        0.00000},
};

int main()
{
   for(auto tst : test) {
      auto ans = pow(tst.x, tst.n);
      ans      = ((double)std::round(ans * 10000.0))     / 10000.0;
      auto exp = ((double)std::round(tst.exp * 10000.0)) / 10000.0;
      if(ans  != exp) {
         cout << "Error:pow failed. Exp "
              << exp   << " Got " << ans   << " for "
              << tst.x << "^"       << tst.n << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
