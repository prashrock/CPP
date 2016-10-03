//g++-5 -Wall --std=c++11 -g -o math_sort_transformed_array math_sort_transformed_array.cc -I../utils/

/**
 * @file  Math Sort Transformed Array
 * @brief Given a Quadratic equation and x values, sort y values
 */

// https://leetcode.com/problems/sort-transformed-array/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include "print_utils.h"     /* print_table_row              */
using namespace std;

/**
 * Given a sorted array of integers nums and integer values
 * a, b and c. Apply a function of the form f(x) = ax2 + bx + c
 * to each element x in the array.
 * The returned array must be in sorted order.
 * Expected time complexity: O(n)
 * Example:
 * nums = [-4,-2,2,4], a = 1, b = 3, c = 5, Result: [3,9,15,33]
 * nums = [-4,-2,2,4], a = -1,b = 3, c = 5, Result: [-23,-5,1,7]
 */

inline int transform(int x, int a, int b, int c) {
   return (a * x * x) + (b * x) + c;
}

/** @brief Leverage the property that y=ax^2+bx+c can only   *
 *  form either an upward facing (cup) if a >=0 or a         *
 *  downward facing(cap) if a < 0. So traverse accordingly   */
std::vector<int> sortTransformedArray(const std::vector<int>& nums,
                                      int at, int bt, int ct) {
   std::vector<int> ans(nums.size(), 0);
   if(at >= 0) { /* Parabola is in the shape of a cup        */
      for(int b = 0, e = nums.size()-1, i = nums.size() - 1; b <= e; --i) {
         int bv = transform(nums[b], at, bt, ct);
         int ev = transform(nums[e], at, bt, ct);
         if(bv > ev) { ans[i] = bv;  b++; }
         else        { ans[i] = ev;  e--; }
      }
   }
   else {        /* Parabola is in the shape of a cap        */
      for(int b = 0, e = nums.size()-1, i = 0; b <= e; ++i) {
         int bv = transform(nums[b], at, bt, ct);
         int ev = transform(nums[e], at, bt, ct);
         if(bv < ev) { ans[i] = bv;  b++; }
         else        { ans[i] = ev;  e--; }
      }
   }
   return ans;
}

struct test_vector {
   std::vector<int> nums;
   int a; int b; int c;
   std::vector<int> exp;
};

const struct test_vector test[6] =  {
   { {-5, -4,-2,2,4}, 1, 3,  5, {3,9,15,15,33} },
   { {-4, -2, 2, 4},  0, -1, 5, {1,3,7,9}      },
   { {-4, -2, 2, 4},  0, 3,  5, {-7,-1,11,17}  },
   { {-4, -2, 2, 4},  1, 3,  5, {3,9,15,33}    },
   { {-4, -2, 2, 4}, -1, 3,  5, {-23, -5, 1, 7}},
   { {-99,-94,-90,-88,-84,-83,-79,-68,-58,-52,-52,-50,-47,-45,-35,-29,-5,-1,9,12,13,25,27,33,36,38,40,46,47,49,57,57,61,63,73,75,79,97,98}, -2, 44, -56, 
     {-24014,-21864,-20216,-19416,-17864,-17486,-16014,-14952,-14606,-12296,-9336,-9062,-8006,-7752,-7752,-7502,-7256,-6542,-6086,-5222,-4814,-4046,-4046,-4046,-3014,-2702,-2406,-2264,-1496,-1272,-1064,-782,-326,-326,-206,-102,178,178,184} },
};

int main()
{
   for(auto tst : test) {
      auto ans = sortTransformedArray(tst.nums, tst.a, tst.b, tst.c);
      if(ans != tst.exp) {
         cout << "Error:sort_transformed_array failed." << endl;
         print_table_row("Exp:", tst.exp);
         print_table_row("Got:", ans);
         print_table_row("For:", tst.nums);
         return -1;
      }
   }
   
   cout << "Info: All manual test-cases passed." << endl;
   return 0;
}
