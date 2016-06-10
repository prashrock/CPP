//g++ --std=c++11 -Wall -g -o math_integer_break math_integer_break.cc

/**
 * @file  Math Integer Break
 * @brief Given a positive integer break it for largest product
 */

// https://leetcode.com/problems/integer-break/

/**
 * Given a positive integer n, break it into the sum of at least
 * two positive integers and maximize the product of those
 * integers. Return the maximum product you can get.
 * For example, given n = 2, return 1 (2 = 1 + 1); given n = 10,
 * return 36 (10 = 3 + 3 + 4).
 * Note: you may assume that n is not less than 2.
 * Hints:
 * - There is a simple O(n) solution to this problem.
 * - You may check the breaking results of n ranging from 7 to 10
 *   to discover the regularities.
 */


#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow, tgamma(factorial)       */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
using namespace std;

/* DP based ~O(n^2) approach. Look at math after this func   */
int integerBreak(int n) {
   vector<int> dp(n+1, 0); 
   assert(n > 0); /* expect n is a positive integer          */
   /* Populate pre-calculated base-cases, 1, 2, 3            */
   for(int i = 1; i <= 3; ++i) dp[i] = i-1;
   /* Populate the DP table for all other cases 4 to n       */
   for(int i = 4; i <= n; ++i) {
      /* Explore all possible ways to split i.               */
      for(int x = 1; (i - x) > 1; ++x) {
         /* For this split, either use x and i-x directly or *
          * refer to the DP table to find out best split     */
         auto val1 = std::max(x,   dp[x]);
         auto val2 = std::max(i-x, dp[i-x]);
         dp[i] = std::max(dp[i], (val1 * val2));
      }
   }
   //for (auto val : dp) cout << val << ",";
   //cout << endl;
   return dp[n];
}

/* Math is clearly explained in https://leetcode.com/discuss/98276/why-factor-2-or-3-the-math-behind-this-problem                                         *
 * For convenience, say n is sufficiently large and can be   *
 * broken into any smaller real positive numbers. We now try *
 * to calculate which real number generates the largest      *
 * product. Assume we break n into (n / x) x's, then the     *
 * product will be xn/x, and we want to maximize it.         *
 *                                                           *
 * Taking its derivative gives us n * x^(n/x-2) * (1-ln(x)). *
 * The derivative is positive when 0 < x < e, and equal to 0 *
 * when x = e, then becomes negative when x > e, which       *
 * indicates that the product increases as x increases, then *
 * reaches its maximum when x = e, then starts dropping.     *
 *                                                           *
 * This reveals the fact that if n is sufficiently large and *
 * we are allowed to break n into real numbers, the best idea*
 * is to break it into nearly all e's. On the other hand, if *
 * n is sufficiently large and we can only break n into      *
 * integers, we should choose integers that are closer to e. *
 * The only potential candidates are 2 and 3 since 2 < e < 3 */


struct test_vector {
   int X;
   int exp;
};

const struct test_vector test[3] =  {
   { 4, 4 },
   { 5, 6 },
   { 6, 9 },
};

int main()
{
   for(auto tst : test) {
      int ans = integerBreak(tst.X);
      if(ans != tst.exp) {
         cout << "Error:IntegerBreak failed for " << tst.X 
              << " exp " << tst.exp << " got " << ans;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
