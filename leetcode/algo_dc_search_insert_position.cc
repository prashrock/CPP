//g++ --std=c++11 -Wall -g -o algo_dc_search_insert_position algo_dc_search_insert_position.cc

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/**
 * @file  Search Insert Position in Sorted Array
 * @brief Given sortedarray + target, return 1st index of target.
 */

// https://leetcode.com/problems/search-insert-position/

/**
 * Given a sorted array and a target value, return the index if the
 * target is found. If not, return the index where it would be if it
 * were inserted in order.
 * You may assume no duplicates in the array.
 * Examples:
 *    [1,3,5,6], 5 . 2
 *    [1,3,5,6], 2 . 1
 *    [1,3,5,6], 7 . 4
 *    [1,3,5,6], 0 . 0
 */

/**
 * @brief: Using STL Lower Bound for binary search           *
 * Using Lower Bound to handle duplicates as well.           *
 * Time Complexity = O(lg n).   Space Complexity = O(1)      */
int searchInsertSTL(vector<int>& nums, int target) {
   /* Returns an iterator pointing to the first element in   *
    * the range [first, last) that is greater/equal to value */
   auto it = std::lower_bound(nums.begin(), nums.end(), target);
   if(it == nums.end()) {
      if(nums.size() == 0 || target < nums[0]) return 0;
      else                                     return nums.size();
   }
   else if(*it < target)       return it - nums.begin() + 1;
   else                        return it - nums.begin();
}

/**
 * @brief: Implement Iterative Binary Search with logic to   *
 * handle duplicates. As this is analogous to binary search, *
 * i.e, we will visit only one half sub-array each time -    *
 * iterative solution works best in this case.               *
 * Time Complexity = O(lg n). Space Complexity = O(1)        */
int searchInsertDC(vector<int>& nums, int target) {
   int first = 0, last = nums.size() - 1;
   if(nums.size() == 0)  return 0;
   /* Loop invariant: target lies between [first, last+1].   *
    * When mid element repeats, else case results in picking *
    * the smallest idx where we can put the target           */
   for(int mid; first <= last;) {
      mid = first + (last - first) / 2;
      if(nums[mid] < target)  first = mid + 1;
      else                    last  = mid - 1;
   }
   /* At this point, first > high, i.e., first == high+1     */
   return first;
}


int main()
{
   vector<int> nums;
   int exp, ans1, ans2, find;

   /* Craft a bunch of manual test-cases for this prob  */
   nums = {1,3,5,6}; find = 2;
   exp = 1;
   ans1 = searchInsertSTL(nums, find);
   ans2 = searchInsertDC(nums, find);
   if     (ans1 != exp) goto Errmain1;
   else if(ans2 != exp) goto Errmain2;

   nums = {}; find = 2;
   exp = 0;
   ans1 = searchInsertSTL(nums, find);
   ans2 = searchInsertDC(nums, find);
   if     (ans1 != exp) goto Errmain1;
   else if(ans2 != exp) goto Errmain2;

   nums = {5}; find = 2;
   exp = 0;
   ans1 = searchInsertSTL(nums, find);
   ans2 = searchInsertDC(nums, find);
   if     (ans1 != exp) goto Errmain1;
   else if(ans2 != exp) goto Errmain2;

   nums = {5}; find = 7;
   exp = 1;
   ans1 = searchInsertSTL(nums, find);
   ans2 = searchInsertDC(nums, find);
   if     (ans1 != exp) goto Errmain1;
   else if(ans2 != exp) goto Errmain2;

   nums = {5, 5, 5, 5, 5, 5}; find = 5;
   exp = 0;
   ans1 = searchInsertSTL(nums, find);
   ans2 = searchInsertDC(nums, find);
   if     (ans1 != exp) goto Errmain1;
   else if(ans2 != exp) goto Errmain2;
        
   nums = {1,3,5,5,6}; find = 5;
   exp = 2;
   ans1 = searchInsertSTL(nums, find);
   ans2 = searchInsertDC(nums, find);
   if     (ans1 != exp) goto Errmain1;
   else if(ans2 != exp) goto Errmain2;
        
   nums = {1,3,5,6}; find = 7;
   exp = 4;
   ans1 = searchInsertSTL(nums, find);
   ans2 = searchInsertDC(nums, find);
   if     (ans1 != exp) goto Errmain1;
   else if(ans2 != exp) goto Errmain2;

   nums = {1,3,5,6}; find = 0;
   exp = 0;
   ans1 = searchInsertSTL(nums, find);
   ans2 = searchInsertDC(nums, find);
   if     (ans1 != exp) goto Errmain1;
   else if(ans2 != exp) goto Errmain2;

   nums = { 1,1,3,5,5,6}; find = 2;
   exp = 2;
   ans1 = searchInsertSTL(nums, find);
   ans2 = searchInsertDC(nums, find);
   if     (ans1 != exp) goto Errmain1;
   else if(ans2 != exp) goto Errmain2;

   nums = {1,3,5,5,6,6}; find = 7;
   exp = 6;
   ans1 = searchInsertSTL(nums, find);
   ans2 = searchInsertDC(nums, find);
   if     (ans1 != exp) goto Errmain1;
   else if(ans2 != exp) goto Errmain2;

   nums = {1,1,3,5,5,6,6}; find = 0;
   exp = 0;
   ans1 = searchInsertSTL(nums, find);
   ans2 = searchInsertDC(nums, find);
   if     (ans1 != exp) goto Errmain1;
   else if(ans2 != exp) goto Errmain2;
   cout << "Info: All manual test-cases passed." << endl;
   return 0;
 Errmain1:
   cout << "Error: STL mode failed for input: ";
   for(auto e : nums) cout << e << ","; cout << endl;
   cout << "Target = " << find <<  " Expected = " << exp
        << " Got = " << ans1 << endl;
   return -1;
 Errmain2:
   cout << "Error: BinarySearch mode failed for input: ";
   for(auto e : nums) cout << e << ","; cout << endl;
   cout << "Target = " << find <<  " Expected = " << exp
        << " Got = " << ans2 << endl;
   return -1;
}
