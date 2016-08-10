//g++-5 -Wall --std=c++11 -g -o math_patching_array math_patching_array.cc

/**
 * @file  Math Patching Array
 * @brief Given sorted input and n, reach all possible sum upto n
 */

// https://leetcode.com/problems/patching-array/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow, tgamma(factorial)       */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
using namespace std;

/**
 * Given a sorted positive integer array nums and an integer n,
 * add/patch elements to the array such that any number in range [1, n]
 * inclusive can be formed by the sum of some elements in the array.
 * Return the minimum number of patches required.
 * Example 1:
 * nums = [1, 3], n = 6
 * Return 1.
 * Combinations of nums are [1], [3], [1,3], which form possible
 * sums of: 1, 3, 4.
 * Now if we add/patch 2 to nums, the combinations are: [1], [2],
 * [3], [1,3], [2,3], [1,2,3].
 * Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
 * So we only need 1 patch.
 *
 * Example 2:
 * nums = [1, 5, 10], n = 20
 * Return 2.
 * The two patches can be [2, 4].
 *
 * Example 3:
 * nums = [1, 2, 2], n = 5
 * Return 0.
 */

/**
 * @brief - can use DP or Binary Indexed Tree approach, but  *
 * found a much simpler greedy algorithm from Leet Discussion*
 * https://leetcode.com/discuss/82822/solution-explanation   *
 * Explanation:                                              *
 * Let patch be the smallest sum in [0,n] that we might be   *
 * missing. Meaning we already know we can build all sums in *
 * [0,patch). Then if we have a number num <= patch in the   *
 * given array, we can add it to those smaller sums to build *
 * all sums in [0,patch+num). If we don't, then we must add  *
 * such a number to the array, and it's best to add patch    *
 * itself, to maximize the reach.                            *
 * Time Complexity = O(n) and Space Complexity = O(1)        */
int minPatches(vector<int>& nums, int n) {
   long int patch = 1;
   int num_patches = 0;
   for(unsigned int i = 0; patch <= n; ) {
      /* If a number in nums is available for patch, use it */
      if(i < nums.size() && nums[i] <= patch) patch += nums[i++];
      /* Else apply current patch and double patch          */
      else                { num_patches++;    patch += patch; }
   }
   return num_patches;
}


struct test_vector {
   std::vector<int> nums;
   int n;
   int exp_num_patches;
};

const struct test_vector test[4] =  {
   { {1, 3},               6,  1},
   { {1, 5, 10},          20,  2},
   { {1, 2, 2},            5,  0},
   { {1,2,31,33}, 2147483647, 28},
};

int main()
{
   for(auto tst : test) {
      auto ans = minPatches(tst.nums, tst.n);
      if(ans != tst.exp_num_patches) {
         cout << "Error:minPatches failed. Exp "
              << tst.exp_num_patches << " Got " << ans << " for ";
         for(auto v: tst.nums) cout  << v << ","; cout << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
