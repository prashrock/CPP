//g++-5 -Wall --std=c++11 -g -o ds_list_easy_remove_duplicate_number ds_list_easy_remove_duplicate_number.cc

/**
 * @file  Remove Duplicate
 * @brief Remove duplicates in place in sorted array.
 */

// https://leetcode.com/problems/remove-duplicates-from-sorted-array/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/**
 * Given a sorted array, remove the duplicates in place such that
 * each element appear only once and return the new length.
 * Do not allocate extra space for another array, you must do this
 * in place with constant memory.
 * For example,
 *  Given input array nums = [1,1,2],
 * Your function should return length = 2, with the first two elements
 * of nums being 1 and 2 respectively. It doesn't matter what you leave
 * beyond the new length.
 */

/* Simple function to remove duplicates in place             */
int removeDuplicates(vector<int>& nums) {
   if(nums.size() < 2) return nums.size();
   int old = 1;
   for(int i = old; i < (int)nums.size(); ++i)
      if(nums[i] != nums[i - 1]) nums[old++] = nums[i];
   nums.resize(old);
   return nums.size();
}

int main()
{
   int ans, exp;
   vector<int> nums, copy;
   nums = copy = {}; exp = 0;
   ans = removeDuplicates(nums);
   if(ans != exp) goto ErrMain;
   nums = copy = {1, 1, 1, 1}; exp = 1;
   ans = removeDuplicates(nums);
   if(ans != exp) goto ErrMain;
   nums = copy = {1, 1, 2}; exp = 2;
   ans = removeDuplicates(nums);
   if(ans != exp) goto ErrMain;
   nums = copy = {1, 2, 2, 2, 2, 3, 3}; exp = 3;
   ans = removeDuplicates(nums);
   if(ans != exp) goto ErrMain;
   nums = copy = {1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3}; exp = 3;
   ans = removeDuplicates(nums);
   if(ans != exp) goto ErrMain;
   cout << "Info: All removeDuplicates manual test-cases passed" << endl;
   return 0;
ErrMain:
   cout << "Error: removeDuplicates failed for input ";
   for(auto val : copy) cout << val << ",";
   cout << " expected " << exp << " got " << ans << endl;
   return -1;
}
