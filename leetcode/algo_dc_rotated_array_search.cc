//g++ --std=c++11 -Wall -g -o algo_dc_rotated_array_search algo_dc_rotated_array_search.cc

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
 * @file  Search in Rotated Sorted Array
 * @brief Given a rotated sorted array, search for value
 */

// https://leetcode.com/problems/search-in-rotated-sorted-array/


/**
 * Suppose a sorted array is rotated at some pivot unknown to you
 * beforehand.
 * (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
 * You are given a target value to search. If found in the array
 * return its index, otherwise return -1.
 * 
 * You may assume no duplicate exists in the array.
 */


 /**
 * @brief - Iterative Binary Search implementation. Returns  *
 * the index of target if found, else returns -1             *
 * Time Complexity = O(lg n).   Space Complexity = O(1)      */
int binarySearch(vector<int>& nums, int first, int last, int target) {
   if(first < 0 || first > last) return -1;

   for(int mid; first <= last; ) {
      mid = first + (last - first) / 2;
      if(nums[mid] < target)          first = mid + 1;
      else if(nums[mid] > target)     last = mid - 1;
      else                            return mid;
   }
   return -1;
}

int search(vector<int>& nums, int target) {
   if(nums.size() == 0)  return 0;
   int mid = 0;

   /* If input is rotated, find index of smallest element    *
    * with Binary Search                                     */
   for(int first = 0, last = nums.size() - 1;
       first < last && nums[first] > nums[last]; ) {
      mid = first + (last - first) / 2 + 1;
      /* [first, mid] is not-rotated  */
      if(nums[mid] > nums[first])  first = mid;
      /* [mid, last]  is not-rotated  */
      else                         last  = mid-1;
   }
   int pivot = mid;
   //cout << endl << "smallest @ " << pivot << endl;
   int ret = binarySearch(nums, 0, pivot-1, target);
   if(ret == -1)  ret = binarySearch(nums, pivot, nums.size()-1, target);

   return ret;
}

struct test_vector {
   std::vector<int> nums;
   int target;
   int exp;
};

const struct test_vector test[12] =  {
   { {7}, 7, 0       },
   { {7}, 4, -1      },
   { {3, 2}, 3, 0    },
   { {3, 2}, 2, 1    },
   { {1, 3, 5}, 5, 2 },
   { {5, 1, 3}, 5, 0 },
   { {3, 5, 1}, 5, 1 },
   { {3, 5, 1}, 1, 2 },
   { {5, 6, 1, 2}, 5, 0 },
   { {5, 6, 1, 2}, 1, 2 },
   { {4, 5, 6, 7, 0, 1, 2}, 7, 3 },
   { {4, 5, 6, 7, 8, 1, 2, 3}, 8, 4 },
};

int main()
{
   for(auto tst : test) {
      int ans = search(tst.nums, tst.target);
      if(ans != tst.exp) {
         cout << "Error: Search number in sorted rotated array failed: ";
         for(auto e : tst.nums) cout << e << ","; cout << endl;
         cout << "Target = " << tst.target <<  " Expected pos = " << tst.exp
              << " Got   = " << ans << endl;
         return -1;
      }
   }
   cout << "Info: All manual test-cases passed successfully" << endl;
   return 0;
}
