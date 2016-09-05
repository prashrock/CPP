//g++-5 -Wall --std=c++11 -g -o math_reverse_int_overflow math_reverse_int_overflow.cc

/**
 * @file  Math Reverse integer
 * @brief Given an integer, return its reverse (handle overflow)
 */

// https://leetcode.com/problems/reverse-integer/

#include <iostream>          /* std::cout                    */
#include <cmath>             /* pow, tgamma(factorial)       */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */

using namespace std;

/**
 * Reverse digits of an integer.
 * Example1: x = 123, return 321
 * Example2: x = -123, return -321
 * If the integer's last digit is 0, what should the output be?
 * ie, cases such as 10, 100.
 * Did you notice that the reversed integer might overflow?
 * Assume the input is a 32-bit integer, then the reverse of
 * 1000000003 overflows. How should you handle such cases?
 * For the purpose of this problem, assume that your function
 * returns 0 when the reversed integer overflows.
 */

/** @brief - Use a bigger integer to catch overflow          */
int reverse1(int x, int base = 10) {
   unsigned long ans = 0;   /* bigger container = no overflow*/
   int sign = (x > 0) ? 1 : -1;
   unsigned long xmax = std::numeric_limits<int>::max();
   for(x *= sign; x > 0; x /= base)
      ans = ans * base + (x % base);
   if(ans > xmax) return 0;              /* catch overflow   */
   else           return (static_cast<int>(ans) * sign);
}

/** @brief - Evaluate overflow at each step                  *
 *  Note this implementation is generic and does not need a  *
 *  bigger container to detect overflow                      *
 *  Inspired by http://stackoverflow.com/questions/199333/how-to-detect-integer-overflow-in-c-c
 * Can also use GCC/Clang built-ins to detect an overflow    */
template<typename T=int>
int reverse2(T x, int base = 10) {
   int sign = (x > 0) ? 1 : -1;
   T ans = 0, xmax = std::numeric_limits<T>::max();
   for(x *= sign; x > 0; x /= base) {
      T a = ans * base;
      T b = x   % base;
      /* Detect overflow during the below 2 operations:      *
       * - multiplication, does ans * base overflow ?        *
       * - addition, does a + b overflow  (a + b <= xmax)    */
      if((ans > xmax/base) || (a > xmax - b)) return 0;
      ans = a + b;
   }
   return ans * sign;
}

struct test_vector {
   int n;
   int exp;
};

const struct test_vector test[11] =  {
   { 0,                     0 },
   { 1,                     1 },
   { 9,                     9 },
   { 123,                 321 },
   { -123,               -321 },
   { 12300,               321 },
   { -12300,             -321 },
   { -12304,           -40321 },
   { 2147483647,            0 },
   { -2147483648,           0 },
   { 1534236469,            0 },
};

int main()
{
   for(auto tst : test) {
      auto ans1 = reverse1(tst.n);
      auto ans2 = reverse2(tst.n);
      if(ans1 != tst.exp) {
         cout << "Error: reverse1 failed. Exp " << tst.exp
              << " Got " << ans1 << endl;
         return -1;
      }
      if(ans2 != tst.exp) {
         cout << "Error: reverse2 failed. Exp " << tst.exp
              << " Got " << ans2 << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
