//g++ -Wall --std=c++11 -g -o algo_dp_easy_house_robber algo_dp_easy_house_robber.cc

/**
 * @file  House Robber
 * @brief Given list of integers find max (not chosing 2 contiguous)
 */

/**
 * You are a professional robber planning to rob houses along a street.
 * Each house has a certain amount of money stashed, the only constraint
 * stopping you from robbing each of them is that adjacent houses have
 * security system connected and it will automatically contact the police
 * if two adjacent houses were broken into on the same night.

 * Given a list of non-negative integers representing the amount of money
 * of each house, determine the maximum amount of money you can rob tonight
 * without alerting the police.
 */

// https://leetcode.com/problems/house-robber/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

int rob(vector<int>& nums) {
   vector<int> dp(nums.size());

   /* First handle base cases */
   if(nums.size() == 0)      return 0;
   else if(nums.size() == 1) return nums[0];

   dp[0] = nums[0];
   dp[1] = std::max(nums[0], nums[1]);

   for(int i = 2; i < (int)nums.size(); ++i)
      dp[i] = std::max(dp[i-1], dp[i-2] + nums[i]);

   return dp[nums.size() - 1];
}

struct test_vector {
   std::vector<int> nums;
   int exp;
};

const struct test_vector test[2] =  {
   { {1, 3, 1},    3},
   { {2, 1, 1, 2}, 4},
};

int main()
{
   for(auto tst : test) {
      int ans = rob(tst.nums);
      if(ans != tst.exp) {
         cout << "Error: House Robber failed for case:" << endl;
         for(auto v : tst.nums) cout << v << ",";  cout << endl;
         return -1;
      }
   }
   cout << "Info: All manual test-cases for House Robber passed." << endl;
   return 0;
}
