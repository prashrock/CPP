//g++ --std=c++11 -Wall -g -o ds_list_missing_number ds_list_missing_number.cc

/**
 * @file  Find Missing Number from Array
 * @brief Given array containing n distinct integers [0, n) find missing integer
 */

// https://leetcode.com/problems/missing-number/

/**
 * Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find
 * the one that is missing from the array.
 * For example,
 * Given nums = [0, 1, 3] return 2.
 * Note:
 * Your algorithm should run in linear runtime complexity. Could you implement it
 * using only constant extra space complexity?
 */

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/* Since numbers are in a specific sequence [0, n), use AP   *
 * to deduce what should be the total of all numbers. Next   *
 * subtract this from observed total to find missing elem    */
int missingNumber(vector<int>& nums) {
   /* sum of n numbers (1, 2, 3, ... n) = n(n+1)/2.          *
    * Handle 0 as a spl case                                 */
   int n = nums.size();
   unsigned long obs_sum = 0, calc_sum = n * (n + 1) / 2;
   for(int i = 0; i < (int)nums.size(); ++i) obs_sum += nums[i];
   return calc_sum - obs_sum;
}

int main()
{
   int ans, exp;
   vector<int> nums;

   nums = {0}; exp = 1;
   ans  = missingNumber(nums);
   if(ans != exp) goto Errmain;
	
   nums = {1}; exp = 0;
   ans  = missingNumber(nums);
   if(ans != exp) goto Errmain;
	
   nums = {5, 4, 6, 3, 1, 2}; exp = 0;
   ans  = missingNumber(nums);
   if(ans != exp) goto Errmain;
	
   nums = {5, 0, 6, 3, 1, 2}; exp = 4;
   ans  = missingNumber(nums);
   if(ans != exp) goto Errmain;
	
   cout << "All test-cases passed." << endl;
   return 0;
 Errmain:
   cout << "Error: Missing Integer failed for - ";
   for(auto val: nums) cout << val << ", "; cout << endl;
   cout << "Expected = " << exp << " Got = " << ans << endl;
   return -1;
}
