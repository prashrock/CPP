//g++-5 --std=c++11 -Wall -g -o algo_dc_rotated_array_search_ii algo_dc_rotated_array_search_ii.cc

/**
 * @file  Search in Rotated Sorted Array II
 * @brief Given a rotated sorted array(with duplicates), search for value
 */

// https://leetcode.com/problems/search-in-rotated-sorted-array-ii/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
using namespace std;

/**
 * Follow up for "Search in Rotated Sorted Array":
 * What if duplicates are allowed?
 * Would this affect the run-time complexity? How and why?
 * Write a function to determine if a given target is in the array.
 */

/** @brief - Modified binary search to handle rotation + duplicates *
 *  Worst case Time Complexity = O(n)  Space Complexity = O(1)      */
bool search(vector<int>& nums, int target) {
   for(int b = 0, e = nums.size() - 1; b <= e; ) {
      int m = b + (e - b) / 2;
      if(nums[m] == target)                         return true;
      else if(nums[b] < nums[m]) { /* 1st half is sorted            */
         /* If target is in first half then adjust the end-point    */
         if (target >= nums[b] && target < nums[m]) e = m - 1;
         else                                       b = m + 1;
      }
      else if(nums[m] < nums[e]) { /* 2nd half is sorted            */
         /* If target is in second half then adjust the begin-point */
         if (target > nums[m] && target <= nums[e]) b = m + 1;
         else                                       e = m - 1;
      }
      /* Rotation across both halfs. Can only move linearly         */
      else if(nums[b] != target)                    b++;
      else                                          e--;
   }
   return false;
}

struct test_vector {
   std::vector<int> nums;
   int target;
   bool exp;
};

const struct test_vector test[15] =  {
   { {7},                         7,  true },
   { {7},                         4, false },
   { {3, 2, 2},                   3,  true },
   { {3, 2},                      2,  true },
   { {1, 3, 5},                   5,  true },
   { {5, 1, 3},                   5,  true },
   { {3, 5, 1},                   5,  true },
   { {3, 5, 1},                   1,  true },
   { {5, 6, 1, 2},                5,  true },
   { {5, 6, 1, 2},                1,  true },
   { {4, 4, 4, 4, 7, 0, 1, 2},    7,  true },
   { {1, 2, 3, 4, 1, 1},          4,  true },
   { {1, 2, 3, 4, 1, 1},          5, false },
   { {1, 1, 1, 1, 1, 1},          1,  true },
   { {1,1,3,1,1,1,1,1,1,1,1,1},   3,  true },
};

int main()
{
   for(auto tst : test) {
      auto ans = search(tst.nums, tst.target);
      if(ans  != tst.exp) {
         cout << "Error: Search number in sorted rotated array failed: ";
         for(auto e : tst.nums) cout << e << ","; cout << endl;
         cout << "Target = " << tst.target <<  " Expected = " << tst.exp
              << " Got   = " << ans << endl;
         return -1;
      }
   }
   cout << "Info: All manual test-cases passed successfully" << endl;
   return 0;
}
