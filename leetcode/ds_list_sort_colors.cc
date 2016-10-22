//g++-5 -Wall --std=c++11 -g -o ds_list_sort_colors ds_list_sort_colors.cc  -I../utils/

/**
 * @file  Sort Colors
 * @brief Given unsorted array, divide it into 3 buckets
 */

// https://leetcode.com/problems/sort-colors/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include "print_utils.h"     /* print_table_row              */
using namespace std;

/**
 * Given an array with n objects colored red, white or blue,
 * sort them so that objects of the same color are adjacent,
 * with the colors in the order red, white and blue.
 * Here, we will use the integers 0, 1, and 2 to represent the
 * color red, white, and blue respectively.
 * Note:
 * You are not suppose to use the library's sort function for this problem.
 * Follow up:
 * - A rather straight forward solution is a two-pass algorithm using
 *   counting sort.
 * - First, iterate the array counting number of 0's, 1's, and 2's, then
 *   overwrite array with total number of 0's, then 1's followed by 2's.
 * Could you come up with an one-pass algorithm using only constant space?
 */

/* Simple two-pointer approach to sort list into 3 buckets   *
 * Treat p0 and p2 as mere container end-points. Iterate with*
 * i and whenever there is a match, push to container        *
 * Note: very similar to ds_list_remove_element.cc           *
 * Time complexity = O(n)     Space complexity = O(1)        */
void sortColorsI(vector<int>& nums) {
   int p0 = 0, p2 = nums.size() - 1;
   for(int i = p0; i <= p2;) {
      if     (i > p0 && nums[i] == 0) std::swap(nums[p0++], nums[i]);
      else if(i < p2 && nums[i] == 2) std::swap(nums[p2--], nums[i]);
      else ++i;
   }
}

/* Count-sort based approach involving two loops.            *
 * Time complexity = O(n+n)   Space complexity = O(1)        */
void sortColorsII(vector<int>& nums) {
   int c0 = 0, c1 = 0, c2 = 0;
   for(auto v : nums) {
      switch(v) {
      case 0 : ++c0; break;
      case 1 : ++c1; break;
      case 2 : ++c2; break;
      default: break;
      }
   }
   for(int i = 0; i < c0; ++i) nums[i]       = 0;
   for(int i = 0; i < c1; ++i) nums[i+c0]    = 1;
   for(int i = 0; i < c2; ++i) nums[i+c0+c1] = 2;
}

/* Another interesting approach with 3 pointers is implemented here:
 * https://discuss.leetcode.com/topic/24267/4ms-and-only-5-lines-c-code-without-delete-and-insert */

struct test_vector {
   std::vector<int> nums;
   std::vector<int> exp;
};

const struct test_vector test[9] =  {
   { {0},                     {0},         },
   { {2, 0},                  {0, 2},      },
   { {1, 0},                  {0, 1},      },
   { {1, 2},                  {1, 2},      },
   { {2, 1},                  {1, 2},      },
   { {1,2,0},                 {0, 1, 2},   },
   { {2,1,1,0},               {0,1,1,2},   },
   { {1,1,0,2,2},             {0,1,1,2,2}, },
   { {2,1,0,0,2},             {0,0,1,2,2}, },
};

int main()
{
   for(auto tst : test) {
      auto ans = tst.nums;
      sortColorsI(ans);
      if(ans != tst.exp) {
         cout << "Error:sortColorsI failed: " << endl;
         print_table_row("Exp:", tst.exp);
         print_table_row("Got:", ans);
         print_table_row("For:", tst.nums);
         return -1;
      }
      ans = tst.nums;
      sortColorsII(ans);
      if(ans != tst.exp) {
         cout << "Error:sortColorsII failed: " << endl;
         print_table_row("Exp:", tst.exp);
         print_table_row("Got:", ans);
         print_table_row("For:", tst.nums);
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
