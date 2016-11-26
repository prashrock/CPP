//g++-5 -Wall --std=c++11 -g -o ds_list_easy_stl_remove ds_list_easy_stl_remove.cc -I ../utils/

/**
 * @file  Move Zeroes
 * @brief Remove all occurences of a given number from a list
 */

// https://leetcode.com/problems/move-zeroes/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include "print_utils.h"     /* print_table_row              */
using namespace std;

/**
 * Given an array nums, write a function to move all 0's to the
 * end of it while maintaining the relative order of the non-zero
 * elements.
 * For example, given nums = [0, 1, 0, 3, 12], after calling your
 * function, nums should be [1, 3, 12, 0, 0].
 * Note:
 * You must do this in-place without making a copy of the array.
 * Minimize the total number of operations.
 */

/** @brief maintain two pointers to move all other elements  *
 *  forward. Fill list with 0's in the end                   */
void moveZeroes(vector<int>& nums, int del_elem = 0) {
   size_t cur = 0;
   for(size_t i = 0; i < nums.size(); ++i)
      if(nums[i] != del_elem) nums[cur++] = nums[i];
   for(; cur < nums.size(); ++cur) nums[cur] = 0;
}

/** @brief Use STL remove and STL fill                       */
void moveZeroesSTL(vector<int>& nums, int del_elem = 0) {
   /* Remove all occurences of del_elem and move elems front */
   auto it = std::remove(nums.begin(), nums.end(), del_elem);
   /* After deleting, instead of resizing fill remain with 0 */
   if(it != nums.end()) std::fill(it, nums.end(), 0);
}

struct test_vector {
   std::vector<int> nums;
   std::vector<int> exp;
};

const struct test_vector test[5] =  {
   { {},                           {} },
   { {1, 3},                   {1, 3} },
   { {0, 1, 0, 3, 12},   {1,3,12,0,0} },
   { {0, 1, 0, 3, 0},     {1,3,0,0,0} },
   { {0, 0, 0, 0},          {0,0,0,0} },
};

int main()
{
   for(auto tst : test) {
      auto ans = tst.nums;
      moveZeroes(ans);
      if(ans != tst.exp) {
         cout << "Error:moveZeroes():" << endl;
         print_table_row("Input:", tst.nums);
         print_table_row("Exp:",   tst.exp);
         print_table_row("Got:",   ans);
         return -1;
      }
      ans = tst.nums;
      moveZeroesSTL(ans);
      if(ans != tst.exp) {
         cout << "Error:moveZeroesSTL():" << endl;
         print_table_row("Input:", tst.nums);
         print_table_row("Exp:",   tst.exp);
         print_table_row("Got:",   ans);
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
