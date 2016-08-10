//g++-5 --std=c++11 -Wall -g -o algo_dc_equal_range algo_dc_equal_range.cc

/**
 * @file  Equal Range
 * @brief Find start/end of a given target value (in sorted array).
 */

// https://leetcode.com/problems/search-for-a-range/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/**
 * Given a sorted array of integers, find the starting and ending
 * position of a given target value.
 * Your algorithm's runtime complexity must be in the order
 * of O(log n).
 * If the target is not found in the array, return [-1, -1].
 * For example,
 * Given [5, 7, 7, 8, 8, 10] and target value 8,
 * return [3, 4].
 */

/**
 * @brief: Use Equal Range to calculate lb and ub            *
 * Time Complexity = O(lg n).   Space Complexity = O(1)      */
vector<int> searchRangeSTL(vector<int>& nums, int target) {
   auto eq = std::equal_range(nums.begin(), nums.end(), target);
   /* If lower_bound is in end or does not point to target   */
   if(eq.first == nums.end() || *eq.first != target)
      return std::vector<int> {-1, -1};
   /* If upper_bound points to element after tgt, come back  */
   else if(eq.second != nums.begin() && *std::prev(eq.second) == target)
      eq.second--;
   return std::vector<int> { (int)(eq.first  - nums.begin()),
                             (int)(eq.second - nums.begin()) };
}

/**
 * @brief: Use Binary Search to calculate lb and ub          *
 * Time Complexity = O(lg n).   Space Complexity = O(1)      */
vector<int> searchRangeBS(vector<int>& num, int t) {
   vector<int> v = {-1, -1};
   int b, e, N = num.size();
   if(num.size() == 0)            return v;
   
   /* First find the lower bound (almost equivalent to BS)   */
   for(b = 0, e = N - 1; b <= e; ) {
      int mid = b + (e - b) / 2;
      if(num[mid] < t)            b = mid + 1;
      else                        e = mid - 1;
   }
   /* If no LB, there can be no UB                           */
   if(num[b] == t)                v[0] = b;
   else                           return v;

   /* Second, find the UB                                    */
   for(e = N - 1; b <= e; ) {
      int mid = b + (e - b) / 2;
      if(num[mid] > t)            e = mid - 1;
      else                        b = mid + 1;
   }
   v[1] = e;
   return v;
}

struct test_vector {
   std::vector<int> num;
   int target;
   std::vector<int> exp;
};

const struct test_vector test[11] =  {
   {{},                       2,  {-1, -1}},
   {{1},                      0,  {-1, -1}},
   {{3},                      3,  {0, 0}  },
   {{0, 1},                   2,  {-1, -1}},
   {{5, 7},                   4,  {-1, -1}},
   {{5, 7},                   6,  {-1, -1}},
   {{5, 7, 7, 8, 8, 10},      8,  {3, 4}},
   {{5, 7, 7, 8, 8, 10},      5,  {0, 0}},
   {{5, 5, 7, 7, 8, 8, 10},   5,  {0, 1}},
   {{5, 5, 7, 7, 8, 8, 10},  10,  {6, 6}},
   {{5, 7, 7, 8, 8, 10, 10}, 10,  {5, 6}},
};
   
int main()
{
   for(auto tst : test) {
      auto ans = searchRangeSTL(tst.num, tst.target);
      if(ans != tst.exp) {
         cout << "Error:searchRangeSTL failed. Input ";
         for(auto val : tst.num) cout << val << ",";
         cout << "  Target = " << tst.target << endl << "Exp: ";
         for(auto val : tst.exp) cout << val << ",";
         cout << endl << "Got: ";
         for(auto val : ans) cout << val << ",";
         cout << endl;
         return -1;
      }

      ans = searchRangeBS(tst.num, tst.target);
      if(ans != tst.exp) {
         cout << "Error:searchRangeBS failed. Input ";
         for(auto val : tst.num) cout << val << ",";
         cout << "  Target = " << tst.target << endl << "Exp: ";
         for(auto val : tst.exp) cout << val << ",";
         cout << endl << "Got: ";
         for(auto val : ans) cout << val << ",";
         cout << endl;
         return -1;
      }
   }
   cout << "Info: All manual test-cases passed." << endl;
   return 0;
}
