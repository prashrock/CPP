//g++-5 --std=c++11 -Wall -g -o algo_dc_rotated_array_search algo_dc_rotated_array_search.cc

/**
 * @file  Search in Rotated Sorted Array
 * @brief Given a rotated sorted array, search for value
 */

// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
// https://leetcode.com/problems/search-in-rotated-sorted-array/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
using namespace std;

// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
/**
 * Suppose a sorted array is rotated at some pivot unknown to you beforehand.
 * (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
 * Find the minimum element. You may assume no duplicate exists in the array.
 */

/**
 * @brief - Modified Iterative Binary Search implementation. *
 * Additional check to check we are in rotated array along   *
 * with incrementing begin position only each loop.          *
 * Time Complexity = O(lg n).   Space Complexity = O(1)      */
int findMin(vector<int>& nums) {
   int b = 0;
   /* Create an iterative loop (similar to binary search) */
   for(int e = nums.size() - 1; b < e && nums[b] > nums[e]; ) {
      int m = b + (e - b) / 2;       /* calc mid point   */
      if(nums[m] < nums[e]) e = m;   /* go to left half  */
      else                  b = m+1; /* go to right half */
   }
   return nums[b];
}

struct test_vector_min {
   std::vector<int> nums;
   int exp;
};

const struct test_vector_min test_min[7] =  {
   { {0},                       0},
   { {4, 5, 6, 7, 0, 1, 2},     0},
   { {0, 1, 2, 4, 5, 6, 7},     0},
   { {1, 2, 4, 5, 6, 7, 0},     0},
   { {4, 5, 6, 7, 8, 0, 1, 2},  0},
   { {0, 1, 2, 4, 5, 6, 7, 8},  0},
   { {1, 2, 4, 5, 6, 7, 8, 0},  0},
};

//https://leetcode.com/problems/search-in-rotated-sorted-array/
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
   int m = 0;
   /* If input is rotated, find index of smallest element    *
    * with Binary Search                                     */
   for(int b = 0, e = nums.size() - 1; b <= e && nums[b] > nums[e]; ) {
      /* If len is even, mid needs to be higher element      */
      m = b + (e - b) / 2;
      if((e-b+1) % 2 == 0)   m++;
      if(nums[m] > nums[b])  b = m;  /* Is [b, m] not-rotated*/
      else                   e = m-1;/* Is [m, e] not-rotated*/
   }
   int pivot = m;
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
   /* First handle find minimum test-case                    */
   for(auto tst : test_min) {
      auto ans = findMin(tst.nums);
      if(ans != tst.exp) {
         cout << "Error: Find Minimum number in sorted rotated array failed: ";
         for(auto e : tst.nums) cout << e << ","; cout << endl;
         cout << "Expected = " << tst.exp << " Got   = " << ans << endl;
         return -1;
      }
   }
   /* Second handle search in rotated sorted array test-case */
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
