//g++-5 -Wall --std=c++11 -g -o math_rotate_array_matrix math_rotate_array_matrix.cc -I ../utils/

/**
 * @file  Math Rotate an Array and Matrix
 * @brief Given an array/matrix of numbers rotate them
 */

// https://leetcode.com/problems/rotate-array/
// https://leetcode.com/problems/rotate-image/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include "print_utils.h"     /* print_table_row              */
using namespace std;

enum rotDirection { Clockwise = 1, AntiClockwise };

/**
 * Rotate an array of n elements to the right by k steps.
 * For example, with n = 7 and k = 3, the array
 * [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].
 * Note:
 * Try to come up as many solutions as you can, there are
 * at least 3 different ways to solve this problem.
 */

/**  @brief - Approach-1: Brute force approach (move + rot)  *
 *   Time Complexity = O(n + k)  Space Complexity = O(k)     */
void rotate_array1(std::vector<int>& nums, int k,
                  enum rotDirection dir=Clockwise) {
   const size_t n = nums.size();
   k = k % n;              /* reduce k to range [0, n-1]     */
   if(dir == Clockwise && k > 0 && n > 1) {
      /* Copy out the last k elements to a separate buffer   */
      std::vector<int> knums(nums.begin()+n-k, nums.end());
      /* Move values [0, n-k) to [k, n)                      */
      std::copy(std::make_move_iterator(nums.begin()),
                std::make_move_iterator(nums.begin()+n-k),
                nums.begin()+k);
      /* Paste back the last k elements into [0, k)          */
      std::copy(knums.begin(), knums.end(), nums.begin());
   }
   else if(dir == AntiClockwise && k > 0 && n > 1) {
      /* Copy out the first k elements to a separate buffer  */
      std::vector<int> knums(nums.begin(), nums.begin()+k);
      /* Move values [k, n) to [0, n-k)                      */
      std::copy(std::make_move_iterator(nums.begin()+k),
                std::make_move_iterator(nums.end()),
                nums.begin());
      /* Paste back the first k elements into [n-k, n)       */
      std::copy(knums.begin(), knums.end(), nums.begin()+n-k);
   }
}

/**  @brief - Approach-2: Rotate by reversing 3 times        *
 *   Good for Bidirectional iterators                        *
 *   Time Complexity = O(n)    Space Complexity = O(1)       */
void rotate_array2(std::vector<int>& nums, int k,
                  enum rotDirection dir=Clockwise) {
   k = k % nums.size();    /* reduce k to range [0, n-1]     */
   if(dir == Clockwise && k > 0) {
      std::reverse(nums.begin(), nums.end());     /* Rev [0,n) */
      std::reverse(nums.begin(), nums.begin()+k); /* Rev [0,k) */
      std::reverse(nums.begin()+k, nums.end());   /* Rev [k,n) */
   }
   else if(dir == AntiClockwise && k > 0) {
      const size_t n = nums.size();
      std::reverse(nums.begin(), nums.end());       /* Rev [0,n) */
      std::reverse(nums.begin(), nums.begin()+n-k); /* Reverse [0, n-k) */
      std::reverse(nums.begin()+n-k, nums.end());   /* Rev [n-k ,n) */
   }
}

/**  @brief - Approach-3: Juggling algorithm implementation  *
 *   Approach 2 and Approach 3 are from Programming Pearls   */
void rotate_array3(std::vector<int>& nums, int k,
                   enum rotDirection dir=Clockwise) {
   size_t n = nums.size();
   k = k % nums.size();    /* reduce k to range [0, n-1]     */
   /* Instead of implementing Juggle algo, shift left (hack) */
   if(dir == AntiClockwise) std::reverse(nums.begin(), nums.end());
   for(size_t b = 0; k %= n; n -= k, b += k)
      for(int i = 0; i < k; i++)
         std::swap(nums[i + b], nums[n - k + i + b]);
   /* Instead of implementing Juggle algo, shift left (hack) */
   if(dir == AntiClockwise) std::reverse(nums.begin(), nums.end());
}

struct test_array_st {
   enum rotDirection d;
   std::vector<int>  nums;
   int               k;
   std::vector<int>  exp;
};

const struct test_array_st test_array[8] = {
   {Clockwise,     {1},            5, {1} },
   {AntiClockwise, {1},            5, {1} },
   {Clockwise,     {1,2},          3, {2,1} },
   {AntiClockwise, {1,2},          3, {2,1} },
   {Clockwise,     {1,2,3,4,5,6,7},3, {5,6,7,1,2,3,4} },
   {AntiClockwise, {1,2,3,4,5,6,7},3, {4,5,6,7,1,2,3} },
   {Clockwise,     {1,2,3,4,5,6,7},8, {7,1,2,3,4,5,6} },
   {AntiClockwise, {1,2,3,4,5,6,7},8, {2,3,4,5,6,7,1} },
};

bool test_array_rotate() {
   /* Execute all test-cases for matrix rotation             */
   for(const auto& tst : test_array) {
      auto ans = tst.nums;
      rotate_array1(ans, tst.k, tst.d);
      if(ans != tst.exp) {
         cout << "Error:rotate_array1 failed for "
              << "direction (" << tst.d << ")" << endl;
         print_table_row("Inp", tst.nums);
         print_table_row("Exp", tst.exp);
         print_table_row("Got", ans);
         return false;
      }
      ans = tst.nums;
      rotate_array2(ans, tst.k, tst.d);
      if(ans != tst.exp) {
         cout << "Error:rotate_array2 failed for "
              << "direction (" << tst.d << ")" << endl;
         print_table_row("Inp", tst.nums);
         print_table_row("Exp", tst.exp);
         print_table_row("Got", ans);
         return false;
      }
      ans = tst.nums;
      rotate_array3(ans, tst.k, tst.d);
      if(ans != tst.exp) {
         cout << "Error:rotate_array3 failed for "
              << "direction (" << tst.d << ")" << endl;
         print_table_row("Inp", tst.nums);
         print_table_row("Exp", tst.exp);
         print_table_row("Got", ans);
         return false;
      }
   }   
   return true;
}

/**
 * You are given an n x n 2D matrix representing an image.
 * Rotate the image by 90 degrees (clockwise).
 * Follow up: Could you do this in-place?
 */

/**
 * @brief - Rotate a given matrix clockwise/anti-clockwise   *
 * @note  - expects a non-empty matrix (no dim size checks)  *
 * Inspired by below leetcode implementation:                *
 * https://discuss.leetcode.com/topic/6796/a-common-method-to-rotate-the-image */
void rotate_matrix(std::vector<std::vector<int>>& matrix,
                   enum rotDirection dir=Clockwise) {
   /* For clockwise rotation reverse all the rows first      */
   if(dir == Clockwise)        std::reverse(matrix.begin(), matrix.end());
   /* For anti-clockwise rotation reverse all columns first  */
   else  for(auto &r : matrix) std::reverse(r.begin(), r.end());
   for(size_t i = 0; i < matrix.size(); ++i)
      for(size_t j = i + 1; j < matrix[i].size(); ++j)
         std::swap(matrix[i][j], matrix[j][i]);
}

struct test_matrix_st {
   enum rotDirection d;
   std::vector<std::vector<int>> nums;
   std::vector<std::vector<int>> exp;
};

const struct test_matrix_st test_matrix[6] = {
   {Clockwise,     {{1}}, {{1}} },
   {AntiClockwise, {{1}}, {{1}} },
   {Clockwise,     {{1,2},{3,4}}, {{3,1},{4,2}} },
   {AntiClockwise, {{1,2},{3,4}}, {{2,4},{1,3}} },
   {Clockwise,     {{1,2,3},{4,5,6},{7,8,9}}, {{7,4,1},{8,5,2},{9,6,3}} },
   {AntiClockwise, {{1,2,3},{4,5,6},{7,8,9}}, {{3,6,9},{2,5,8},{1,4,7}} },
};

bool test_matrix_rotate() {
   /* Execute all test-cases for matrix rotation             */
   for(auto tst : test_matrix) {
      auto ans = tst.nums;
      rotate_matrix(ans, tst.d);
      if(ans != tst.exp) {
         cout << "Error:rotate_matrix failed for "
              << "direction (" << tst.d << ")" << endl;
         for(auto v : tst.nums) {
            print_table_row(" ", v);
            cout << endl;
         }
         cout << endl;
         return false;
      }
   }
   return true;
}

int main()
{   
   if(test_array_rotate()  == false) return -1;
   if(test_matrix_rotate() == false) return -1; 
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
