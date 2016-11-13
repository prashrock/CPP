//g++-5 --std=c++11 -g -o algo_dp_burst_balloons algo_dp_burst_balloons.cc
/**
 * @FILE  Burst Balloons
 * @brief Given n balloons burst them in right order to maximize profit
 */

// https://leetcode.com/problems/burst-balloons/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
using namespace std;


/**
 * Given n balloons, indexed from 0 to n-1. Each balloon is painted
 * with a number on it represented by array nums. You are asked to
 * burst all the balloons. If the you burst balloon i you will get
 * nums[left] * nums[i] * nums[right] coins. Here left and right
 * are adjacent indices of i. After the burst, the left and right
 * then becomes adjacent.
 * Find the maximum coins you can collect by bursting the balloons wisely.
 * Note:
 * (1) You may imagine nums[-1] = nums[n] = 1. They are not real
 * therefore you can not burst them.
 * (2) 0 <= n <= 500, 0 <= nums[i] <= 100
 * Example:
 * Given [3, 1, 5, 8]
 * Return 167
 *   nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
 *   coins =  3*1*5     +  3*5*8    +  1*3*8      + 1*8*1   = 167
 */

/* Top-Down DP approach                                        *
 * In each recursive call, left and right are fixed. Calculate *
 * maximum value possible within [left, right] and store it.   */
int maxCoinsDP(std::vector<int>& nums, int left, int right,
               std::vector<std::vector<int>>& dp) {
   /* We need atleast 3 balloons to calculate coins            */
   if(right - left + 1 < 3) return 0;
   /* If Top-Down DP has already calculated this value, skip it */
   else if(dp[left][right]) return dp[left][right];
   /* Try popping all balloons inbetween left and right        */
   for(int i = left + 1; i < right; ++i) {
      /* Calculate the value of the balloon we just popped     */
      auto cur = nums[left] * nums[i] * nums[right];
      /* Calculate value of remaining balloon to left & right  */
      if(i    - left + 1 >= 3) cur += maxCoinsDP(nums, left, i,     dp);
      if(right- i    + 1 >= 3) cur += maxCoinsDP(nums, i,    right, dp);
      dp[left][right] = std::max(dp[left][right], cur);
   }
   return dp[left][right];
}

int maxCoins1(std::vector<int>& nums) {
   /* Burst every balloon that has a value of 0                 */
   for(auto it = nums.begin(); it != nums.end();) {
      if(*it == 0) nums.erase(it);
      else         ++it;
   }
   /* Add a balloon of value 1 to left and right                */
   nums.push_back(1); nums.insert(nums.begin(), 1);
   vector<vector<int>> dp(nums.size(), vector<int>(nums.size(), 0));
   return maxCoinsDP(nums, 0, nums.size() - 1, dp);
}


struct test_vector {
   std::vector<int> nums;
   int exp_profit;
};

const struct test_vector test[3] =  {
   { {1,2,3,4},                                       40},
   { {3,1,5,8},                                      167},
   { {5,0,1,3},                                       35},
   { {125,6,5,0,1,3,0,0},                           6140},
};

int main()
{
   for(auto tst : test) {
      auto ans = maxCoins1(tst.nums);
      if(ans != tst.exp_profit) {
         cout << "Error:maxCoins1 failed for: ";
         for(auto v : tst.nums) cout << v << ",";
         cout << endl;
         cout << " Exp: " << tst.exp_profit
              << " Got: " << ans << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}

