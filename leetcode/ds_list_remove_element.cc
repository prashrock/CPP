//g++-5 -Wall --std=c++11 -g -o ds_list_remove_element ds_list_remove_element.cc  -I../utils/

/**
 * @file  Remove Element from Unsorted Array
 * @brief Given unsorted array remove all instances of value.
 */

// https://leetcode.com/problems/remove-element/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include "print_utils.h"     /* print_table_row              */
using namespace std;

/**
 * Given an array and a value, remove all instances of that value
 * in place and return the new length.
 * Do not allocate extra space for another array, you must do this
 * in place with constant memory.
 * The order of elements can be changed. It doesn't matter what you
 * leave beyond the new length.
 * Example:
 * Given input array nums = [3,2,2,3], val = 3
 * Your function should return length = 2, with the first two elements
 * of nums being 2.
 * Hint:
 * - Try two pointers.
 * - Did you use the property that "order of elements can be changed"?
 * - What happens when the elements to remove are rare?
 */

/* Simple two-pointer approach to remove all *
 * occurences of val from nums               *
 * Note: this approach involves a lot of movement *
 *       even if the duplicates are rare          *
 * Note: very similar to ds_list_remove_duplicates_sorted_i_ii.cc */
int removeElementI(vector<int>& nums, int val) {
   int cur = 0;
   for(int i = 0; i < (int)nums.size(); ++i)
      if(nums[i] != val) nums[cur++] = nums[i];
   nums.resize(cur);
   return cur;
}

/* Optimization over the two pointer approach. If elements   *
 * to remove are rare, then move duplicate elements to end   */
int removeElementII(vector<int>& nums, int val) {
   int n = nums.size();
   /* Increase i manually. What if last element is also val  */
   for(int i = 0; i < n;) {
      if(nums[i] == val) nums[i] = nums[--n];
      else               i++;
   }
   nums.resize(n);
   return n;
}

struct test_vector {
   std::vector<int> nums;
   int val;
   std::vector<int> exp;
};

const struct test_vector test[9] =  {
   {{3,2,2,3},        3,   {2, 2}},
   {{},               3,   {}},
   {{3},              3,   {}},
   {{2},              3,   {2}},
   {{3, 3},           3,   {}},
   {{4, 5},           4,   {5}},
   {{1,2,3},          3,   {1, 2}},
   {{2,2,3},          2,   {3}},
   {{1,2,3,4,5,3},    3,   {1,2,4,5}},
};

int main()
{
   for(auto tst : test) {
      auto ans = tst.nums;
      removeElementI(ans, tst.val);
      std::sort(ans.begin(), ans.end());
      if(ans != tst.exp) {
         cout << "Error:removeElementI failed for val=" << tst.val << endl;
         print_table_row("Exp:", tst.exp);
         print_table_row("Got:", ans);
         print_table_row("For:", tst.nums);
         return -1;
      }
      ans = tst.nums;
      removeElementII(ans, tst.val);
      std::sort(ans.begin(), ans.end());
      if(ans != tst.exp) {
         cout << "Error:removeElementII failed for val=" << tst.val << endl;
         print_table_row("Exp:", tst.exp);
         print_table_row("Got:", ans);
         print_table_row("For:", tst.nums);
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
