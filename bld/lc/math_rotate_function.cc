//g++-5 -Wall --std=c++11 -g -o math_rotate_function math_rotate_function.cc

/**
 * @file  Math Rotate Function
 * @brief Given a set of numbers find max F() amongst all rotations
 */

// https://leetcode.com/problems/rotate-function/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
using namespace std;

/**
 * Given an array of integers A and let n to be its length.
 * Assume Bk to be an array obtained by rotating the array A,
 * k positions clock-wise, we define a "rotation function"
 * F on A as follow:
 * F(k) = 0 * Bk[0] + 1 * Bk[1] + ... + (n-1) * Bk[n-1].
 * Calculate the maximum value of F(0), F(1), ..., F(n-1).
 * Note: n is guaranteed to be less than 105.
 * Example:  A = [4, 3, 2, 6]
 * F(0) = (0 * 4) + (1 * 3) + (2 * 2) + (3 * 6) = 0 + 3 + 4 + 18 = 25
 * F(1) = (0 * 6) + (1 * 4) + (2 * 3) + (3 * 2) = 0 + 4 + 6 + 6 = 16
 * F(2) = (0 * 2) + (1 * 6) + (2 * 4) + (3 * 3) = 0 + 6 + 8 + 9 = 23
 * F(3) = (0 * 3) + (1 * 2) + (2 * 6) + (3 * 4) = 0 + 2 + 12 + 12 = 26
 * So the maximum value of F(0), F(1), F(2), F(3) is F(3) = 26.
 */

/* Note: to solve this problem with brute force we need 2    *
 * loops, Outer loop to start from each possible idx, inner  *
 * loop to calculate F(i) for each rotation - O(n^2) sol     */

/**
 * @brief - Key insight to avoid inner loop is below pattern:*
 * F(0) = 0A + 1B + 2C + 3D + 4E                             *
 * F(1) = 4A + 0B + 1C + 2D + 3E                             *
 * F(2) = 3A + 4B + 0C + 1D + 2E                             *
 * F(3) = 2A + 3B + 4C + 0D + 1E                             *
 * F(4) = 1A + 2B + 3C + 4D + 0E                             *
 * From the above equations, we can see that:                *
 * F(1) = F(0) - sum + 5A,                                   *
 * F(2) = F(1) - sum + 5B,   (and so on...)                  *
 * Or in general: F(n) = F(n-1) - sum + n * A[n-1]           *
 */
int maxRotateFunction(vector<int>& A) {
   int F0(0), sum(0), n(A.size());
   /* Get the sum and the first series - F(0) simultaneously */
   for(int i = 0; i < n; ++i) {
      sum  += A[i];
      F0   += A[i] * i;
   }
   int ans = F0; /* ans = max(F0, F1, .. Fn). Init ans = F0  */
   /* To calculate F1, .., Fn, use formula mentioned above   */
   for(int i = 1; i < n; ++i) {
      F0  = F0 - sum + (A[i-1] * n);
      ans = std::max(ans, F0);
   }
   return ans;
}

struct test_vector {
   std::vector<int> nums;
   int exp;
};

const struct test_vector test[5] =  {
   { {},                                 0 },
   { {1000000007},                       0 },
   { {1, 2, 3},                          8 },
   { {4, 3, 2, 6},                       26},
   { {-2147483648,-2147483648}, -2147483648},
};

int main()
{
   for(auto tst : test) {
      auto ans = maxRotateFunction(tst.nums);
      if(ans != tst.exp) {
         cout << "Error:maxRotateFunction failed. Exp "
              << tst.exp << " Got " << ans << " for ";
         for(auto v: tst.nums) cout  << v << ","; cout << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
