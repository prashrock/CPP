//g++-5 --std=c++11 -Wall -g -o ds_list_minimum_size_subarray_sum ds_list_minimum_size_subarray_sum.cc

/**
 * @file  Minimum Size Subarray Sum
 * @brief find minimal length subarray with sum atleast s
 */

// https://leetcode.com/problems/minimum-size-subarray-sum/


#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
using namespace std;

/**
 * Given an array of n positive integers and a positive integer s,
 * find the minimal length of a subarray of which the sum >= s.
 * If there isn't one, return 0 instead.
 * For example, given the array [2,3,1,2,4,3] and s = 7,
 * the subarray [4,3] has the minimal length under the problem constraint.
 * More practice:
 * If you have figured out the O(n) solution, try coding another
 * solution of which the time complexity is O(n log n).
 */

/* Note: O(n) implementation of this problem is similar to   *
 * ds_string_longest_substring_without_repeating_chars.cc    *
 * Note: Also check out algo_dp_maximum_sum_product_subarray.cc */

/** Approach - 1 - 2 pointer window based O(n) approach.     */
int minSubArrayLen(int s, vector<int>& nums) {
   int minlen = 0;
   for(int b = 0, e = 0, sum = 0; e < (int)nums.size(); ++e) {
      sum += nums[e];
      if(sum < s) continue; /* Continue if no successful window found */
      /* If we've found a window, see if b can be adjusted   */
      for(; sum - nums[b] >= s; ++b) sum -= nums[b];
      if(minlen == 0) minlen = e - b + 1; /* First window    */
      else            minlen = std::min(minlen, e - b + 1);
   }
   return minlen;
}

/** Approach - 2 - Divide and Conquer based O(nlgn) approach */
//https://discuss.leetcode.com/topic/17063/4ms-o-n-8ms-o-nlogn-c/4

struct test_vector {
   int s;
   std::vector<int> nums;
   int exp;
};

const struct test_vector test[2] =  {
   {100, {},                                       0},
   {7,   {2,3,1,2,4,3},                            2},
};

int main()
{
   for(auto tst : test) {
      auto ans = minSubArrayLen(tst.s, tst.nums);
      if(ans != tst.exp) {
         cout << "Error: minSubArrayLen failed. Exp "
              << tst.exp  << " Got " << ans
              << " for:";
         for(auto v : tst.nums) cout << v << ", "; cout << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
