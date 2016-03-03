//g++ -Wall --std=c++11 -g -o ds_list_remove_duplicates_sorted_i_ii ds_list_remove_duplicates_sorted_i_ii.cc

/**
 * @file  Remove Duplicate from Sorted Array
 * @brief Given sorted array remove duplicates in place.
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

// https://leetcode.com/problems/remove-duplicates-from-sorted-array/
/**
 * Given a sorted array, remove the duplicates in place such that each
 * element appear only once and return the new length.
 * Do not allocate extra space for another array, you must do this in
 * place with constant memory.
 * For example,
 * Given input array nums = [1,1,2],
 * Your function should return length = 2, with the first two elements
 * of nums being 1 and 2 respectively. It doesn't matter what you leave
 * beyond the new length.
 */

int removeDuplicates1(vector<int>& nums) {
   /* Corner case, where we have less than 2 elements        */
   if(nums.size() < 2) return nums.size();
   int old = 1; /* Keep old outside, so that we can resize   */
   for(int i = old; i < (int)nums.size(); ++i)
      if(nums[i] != nums[i - 1]) nums[old++] = nums[i];
   nums.resize(old);
   return nums.size();
}

int removeDuplicates1_test(){
   int ans, exp;
   vector<int> nums, copy;
   nums = copy = {}; exp = 0;
   ans = removeDuplicates1(nums);
   if(ans != exp) goto ErrMain;
   nums = copy = {1, 1, 1, 1}; exp = 1;
   ans = removeDuplicates1(nums);
   if(ans != exp) goto ErrMain;
   nums = copy = {1, 1, 2}; exp = 2;
   ans = removeDuplicates1(nums);
   if(ans != exp) goto ErrMain;
   nums = copy = {1, 2, 2, 2, 2, 3, 3}; exp = 3;
   ans = removeDuplicates1(nums);
   if(ans != exp) goto ErrMain;
   nums = copy = {1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3}; exp = 3;
   ans = removeDuplicates1(nums);
   if(ans != exp) goto ErrMain;
   cout << "Info: All removeDuplicates-1 manual test-cases passed" << endl;
   return 0;
 ErrMain:
   cout << "Error: removeDuplicates-1 failed for input ";
   for(auto val : copy) cout << val << ",";
   cout << " expected " << exp << " got " << ans << endl;
   return -1;
}

// https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/

/**
 * Follow up for "Remove Duplicates":
 * What if duplicates are allowed at most twice?
 * For example,
 * Given sorted array nums = [1,1,1,2,2,3],
 * Your function should return length = 5, with the first five elements
 * of nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond
 * the new length.
 */
/* Use a constant to allow upto K duplicates, K = MAX_DUP    */
static const int MAX_DUP = 1;
/* Allow upto MAX_DUP duplicates and remove all other dups   */
int removeDuplicates2(vector<int>& nums) {
   if(nums.size() < 2) return nums.size();
   int old = 1, dup_cnt = MAX_DUP;
   for(int i = old; i < (int)nums.size(); ++i) {
      if(nums[i] != nums[i-1]) { nums[old++] = nums[i]; dup_cnt = MAX_DUP; }
      else if(dup_cnt != 0)    { nums[old++] = nums[i]; dup_cnt--;         }
   }
   nums.resize(old);
   return nums.size();
}

int removeDuplicates2_test() {
   int ans, exp;
   vector<int> nums, copy;
   nums = copy = {}; exp = 0;
   ans = removeDuplicates2(nums);
   if(ans != exp) goto ErrMain;
   nums = copy = {1, 1, 1, 1}; exp = 2;
   ans = removeDuplicates2(nums);
   if(ans != exp) goto ErrMain;
   nums = copy = {1, 1, 2}; exp = 3;
   ans = removeDuplicates2(nums);
   if(ans != exp) goto ErrMain;
   nums = copy = {1, 2, 2, 2, 2, 3, 3}; exp = 5;
   ans = removeDuplicates2(nums);
   if(ans != exp) goto ErrMain;
   nums = copy = {1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3}; exp = 6;
   ans = removeDuplicates2(nums);
   if(ans != exp) goto ErrMain;
   cout << "Info: All removeDuplicates-2 manual test-cases passed" << endl;
   return 0;
 ErrMain:
   cout << "Error: removeDuplicates-2 failed for input ";
   for(auto val : copy) cout << val << ",";
   cout << " expected " << exp << " got " << ans  << endl;
   for(auto val : nums) cout << val << ",";  cout << endl;
   return -1;
}

int main()
{
   if(removeDuplicates1_test() != 0)      return -1;
   else if(removeDuplicates2_test() != 0) return -1;
   else                                   return 0;
}
