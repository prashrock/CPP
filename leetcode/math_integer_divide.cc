//g++-5 --std=c++11 -Wall -g -o math_integer_divide math_integer_divide.cc

/**
 * @file  Math Divide Integer
 * @brief Divide two integers without using *, /, % operators
 */

// https://leetcode.com/problems/divide-two-integers/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
using namespace std;

/**
 * Divide two integers without using multiplication, division
 * and mod operator.
 * If it is overflow, return MAX_INT.
 */

int divide(int dividend, int divisor) {
   /* Handle Edge-cases of divisor first 0, 1, -1            */
   const int int_max = std::numeric_limits<int>::max();
   if(divisor == 1)                        return dividend;
   else if(dividend == 0 || divisor == 0)  return 0;
   else if(dividend == divisor)            return 1;
   else if(divisor == -1)  {
      if(dividend < -(int_max))            return int_max;
      else                                 return -(dividend);
   }

   int ans = 0;
   unsigned int udividend = (dividend > 0) ? dividend : -(dividend),
      udivisor  = (divisor  > 0) ? divisor  : -(divisor);
   bool neg_flag = (dividend < 0) ^ (divisor < 0);
   /* Find the largest power of divisor and subtract it from *
    * dividend. Repeat this still dividend >= divisor        */
   for(; udividend >= udivisor; ) {
      int pow_cnt;
      unsigned int sum = udivisor;
      for(pow_cnt = 1; sum <= udividend; pow_cnt += pow_cnt, sum += sum) {
         /* If max sum is reached or if is overflow break    */
         if(sum + sum > udividend || sum + sum < sum) break;
      }
      ans       += pow_cnt;
      udividend -= sum;
   }
   if(neg_flag)   return -ans;
   else           return  ans;
}

struct test_vector {
   int dividend;
   int divisor;
   int quotient;
};

const struct test_vector test[14] =  {
   {0,               1,           0},
   {0,               0,           0},
   {25,              7,           3},
   {25,              5,           5},
   {125,             1,         125},
   {2147483647,      1,  2147483647},
   {21474836, 21474836,           1},
   {2147483647,      2,  1073741823},
   {-1,              1,          -1},
   {-1,             -1,           1},
   {-2147483648,    -1,  2147483647},
   {-2147483648,     2, -1073741824},
   {214748363,      -2,  -107374181},
   {-2147483648,    -3,   715827882},   
};

int main()
{
   for(auto tst : test) {
      auto ans = divide(tst.dividend, tst.divisor);
      if(ans != tst.quotient) {
         cout << "Error:Integer divide failed for "
              << tst.dividend << "/" << tst.divisor
              << ". Exp:" << tst.quotient << " Got:" << ans << endl; 
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
