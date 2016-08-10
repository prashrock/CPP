//g++-5 --std=c++11 -Wall -g -o algo_dc_search_2D_matrix_i_ii algo_dc_search_2D_matrix_i_ii.cc

/**
 * @file  Search a 2D Matrix
 * @brief In an increasing matrix, find a target
 */

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;


// https://leetcode.com/problems/search-a-2d-matrix/
// https://leetcode.com/problems/search-a-2d-matrix-ii/

/**
 * Write an efficient algorithm that searches for a value in an
 * m x n matrix. This matrix has the following properties:
 * Integers in each row are sorted from left to right.
 * The first integer of each row is greater than the last integer
 * of the previous row.
 * For example:
 * Consider the following matrix:
 *  [ [1,   3,  5,  7],
 *    [10, 11, 16, 20],
 *    [23, 30, 34, 50]
 *  ]
 *  Given target = 3, return true.
 */

/**
 * @brief: Implement Binary Search in 2D list to find target *
 * Time Complexity = O(lg mn).   Space Complexity = O(1)     */
bool searchMatrix(vector<vector<int>>& matrix, int target) {
   int m = matrix.size(), n = matrix[0].size();
   /* Treat 2D array as 1D array and find its mid-point      *
    * Note, mid-point is calculated as mid = (i * n) + j     */
   for(int first = 0, last = (m * n) - 1; first <= last;) {
      int mid = first + (last - first) / 2,
         i   = mid / n,  /* j < n. So mid / n will give us i */
         /* Find 1 unknown with 1 eq. Eqvn to j = mid % n    */
         j   = mid - (i * n); 
      /* Next do binary search with i, j + find new mid-point*/
      if     (matrix[i][j] < target) first = mid + 1;
      else if(matrix[i][j] > target) last  = mid - 1;
      else                           return true;
   }
   return false;
}

/**
 * Write an efficient algorithm that searches for a value in an m x n matrix.
 * This matrix has the following properties:
 * - Integers in each row are sorted in ascending from left to right.
 * - Integers in each column are sorted in ascending from top to bottom.
 * For example, given
 * [ [1,   4,  7, 11, 15],
 *   [2,   5,  8, 12, 19],
 *   [3,   6,  9, 16, 22],
 *   [10, 13, 14, 17, 24],
 *   [18, 21, 23, 26, 30]]
 * Given target = 5, return true.
 * Given target = 20, return false.
 */

/* Start at either bottom-left or top-right corner           *
 * In each step rule out one row or column until we          *
 * hit boundary conditions or find the answer                *
 * Time Complexity = O(m+n), Space Complexity = O(1)         *
 * Note: Need to add test-cases for this question.           */
bool searchMatrix_ii(vector<vector<int>>& matrix, int target) {
   if(matrix.size() == 0) return false;
   int m = matrix.size(), n = matrix[0].size();
   /* Start at the bottom-left corner                  */
   for(int i = m-1, j = 0; i >= 0 && j < n;) {
      if     (matrix[i][j] < target) j++; /* next col */
      else if(matrix[i][j] > target) i--; /* prev row */
      else   return true;                 /* found it!*/
   }
   return false;  /* Hit boundary condition, not found */
}


int main() {
   vector<vector<int>> matrix;
   int target, idx = 0;
   bool ans, exp;

   matrix = {{1}}; target = 2; exp = false; idx++;
   ans = searchMatrix(matrix, target);
   if(ans != exp) goto ErrMain;

   matrix = {{2}}; target = 2; exp = true;   idx++;
   ans = searchMatrix(matrix, target);
   if(ans != exp) goto ErrMain;

   matrix = {{1,1}}; target = 2; exp = false; idx++;
   ans = searchMatrix(matrix, target);
   if(ans != exp) goto ErrMain;

   matrix = {{1,2}}; target = 2; exp = true; idx++;
   ans = searchMatrix(matrix, target);
   if(ans != exp) goto ErrMain;

   matrix = {{2,1}}; target = 2; exp = true; idx++;
   ans = searchMatrix(matrix, target);
   if(ans != exp) goto ErrMain;

   matrix = {{1,1},{1,2}}; target = 2; exp = true; idx++;
   ans = searchMatrix(matrix, target);
   if(ans != exp) goto ErrMain;

   matrix = {{1},{3}}; target = 3; exp = true; idx++;
   ans = searchMatrix(matrix, target);
   if(ans != exp) goto ErrMain;

   matrix = {{-10,-8,-8,-8},{-5,-4,-2,0}}; target = 7; exp = false; idx++;
   ans = searchMatrix(matrix, target);
   if(ans != exp) goto ErrMain;

   cout << "Info: All manual test-cases passed" << endl;
   return 0;
 ErrMain:
   cout << "Error: Expected "   << exp << " got = " << ans
        << " for case " << idx << ":" << endl;
   for(auto row : matrix) {
      for(auto val : row) cout << val << " ";
      cout << endl;
   }
   return -1;
}
