//g++-5 --std=c++11 -Wall -g -o ds_list_maximum_size_subarray_sum_equals_k ds_list_maximum_size_subarray_sum_equals_k.cc

/**
 * @file  Maximum size sub-array sum equals k
 * @brief find maximum length subarray that sums to k
 */

// https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/


#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include <unordered_map>     /* std::unordered_map           */
using namespace std;

/**
 * Given an array nums and a target value k, find the maximum length
 * of a subarray that sums to k. If there isn't one, return 0 instead.
 * Note:
 * The sum of the entire nums array is guaranteed to fit within the
 * 32-bit signed integer range.
 * Example 1: Given nums = [1, -1, 5, -2, 3], k = 3,
 * Return 4. ([1, -1, 5, -2] is the longest subarray that sums to 3)
 * Example 2: Given nums = [-2, -1, 2, 1], k = 1,
 * Return 2. ([-1, 2] is the longest subarray that sums to 1)
 * Follow Up: Can you do it in O(n) time?
 */

/* Note: Also check out ds_list_minimum_size_subarray_sum.cc */

/** Approach - 1 - 2 pointer window based O(n) approach.     */
/* Use a hash-table to store prefix sum upto each idx */
int maxSubArrayLen(std::vector<int>& nums, int k) {
   int maxlen = 0;
   std::unordered_map<int, int> map;
   for(int i = 0, sum = 0, curlen = 0; i < (int)nums.size(); ++i) {
      sum += nums[i]; /* Maintain the prefix sum upto this idx */
      /* If prefix-sum @ [0, i] = k, use this as cur-length    */
      if(sum == k)                           curlen = i - 0 + 1;
      /* Check if we have seen a prefix sum of [sum-k]. If yes *
       * we have a subarray in the range                       */
      else if(map.find(sum-k) != map.end())  curlen = i - map[sum-k];
      maxlen = std::max(maxlen, curlen);
      /* If we already have this prefix sum, dont update, since we need longest length */
      if(map.find(sum) == map.end())         map[sum] = i;
   }
   return maxlen;
}

struct test_vector {
   std::vector<int> nums;
   int k;
   int exp;
};

const struct test_vector test[2] =  {
   {{1, -1, 5, -2, 3},       3,  4},
   {{-2, -1, 2, 1},          1,  2},
};

int main()
{
   for(auto tst : test) {
      auto ans = maxSubArrayLen(tst.nums, tst.k);
      if(ans != tst.exp) {
         cout << "Error: maxSubArrayLen failed. Exp "
              << tst.exp  << " Got " << ans
              << " for:";
         for(auto v : tst.nums) cout << v << ", "; cout << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
