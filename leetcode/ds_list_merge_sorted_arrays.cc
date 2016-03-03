//g++ --std=c++11 -Wall -g -o ds_list_merge_sorted_arrays ds_list_merge_sorted_arrays.cc

/**
 * @file  Merge Sorted Arrays
 * @brief Given 2 sorted integer arrays, merge them as one sorted array
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

// https://leetcode.com/problems/merge-sorted-array/

/**
 * Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1
 * as one sorted array.
 * Note:
 * You may assume that nums1 has enough space (size that is greater or
 * equal to m + n) to hold additional elements from nums2. The number of
 * elements initialized in nums1 and nums2 are m and n respectively.
 */

/* Since num1 is larger array and it has enough space to hold*
 * all elements from num2, start filling from end of num1    *
 * Time Complexity = O(n+m), Space Complexity = O(1)         */
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
   while(m || n) {
      int next_val;
      if(m && n)  next_val = nums1[m-1]>nums2[n-1] ? nums1[--m]:nums2[--n];
      else if(m)  next_val = nums1[--m];
      else        next_val = nums2[--n];
      nums1[m+n] = next_val;
   }
}

int main()
{
   cout << "Info: Need to add manual tests for merge sorted arrays" << endl;
   return 0;
}
