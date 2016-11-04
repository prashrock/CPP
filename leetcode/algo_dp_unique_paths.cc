//g++-5 --std=c++11 -g -o algo_dp_unique_paths algo_dp_unique_paths.cc
/**
 * @file  Unique Paths I, II
 * @brief Number of possible unique paths in a mxn grid
 */

// https://leetcode.com/problems/unique-paths/
// https://leetcode.com/problems/unique-paths-ii/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
using namespace std;

// https://leetcode.com/problems/unique-paths/
/**
 * A robot is located at the top-left corner of a m x n grid
 * (marked 'Start' in the diagram below).
 * The robot can only move either down or right at any point
 * in time. The robot is trying to reach the bottom-right corner
 * of the grid (marked 'Finish' in the diagram below).
 * How many possible unique paths are there?
 */

/** DP Based solution. There is 1 valid path from start which*
 * can be cached. All other values can be computed in bottom *
 * up fashing.                                               *
 * Time complexity = O(mn) Space Complexity = O(mn)          */
int uniquePaths(int m, int n) {
   std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
   dp[0][1] = 1; /* The first grid position pre-calculation  */
   for(size_t i = 1; i <= m; ++i)
      for(size_t j = 1; j <= n; ++j)
         dp[i][j] = dp[i-1][j] + dp[i][j-1];
   return dp[m][n];
}

/* Note: this can be optimized further. For each iteration   *
 * we only need previous two cols. so, we can optimize the   *
 * space complexity as shown in this leetcode answer @       *
 * https://discuss.leetcode.com/topic/15265/0ms-5-lines-dp-solution-in-c-with-explanations/2                                                */

// https://leetcode.com/problems/unique-paths-ii/
/**
 * Follow up for "Unique Paths":
 * Now consider if some obstacles are added to the grids. How many
 * unique paths would there be?
 * An obstacle and empty space is marked as 1 and 0 respectively
 * in the grid. For example,
 * There is one obstacle in the middle of a 3x3 grid as illustrated below.
 * [  [0,0,0],
 *    [0,1,0],
 *    [0,0,0] ]
 * The total number of unique paths is 2.
 */

/** DP Based bottom-up solution                              *
 * Time complexity = O(mn) Space Complexity = O(mn)          */
int uniquePathsWithObstacles(vector<vector<int>>& obsGrid) {
   auto m = obsGrid.size(), n = obsGrid[0].size();
   std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
   dp[0][1] = 1; /* The first grid position pre-calculation  */
   for(size_t i = 1; i <= m; ++i) {
      for(size_t j = 1; j <= n; ++j) {
         /* If this position is block, then no route here    */
         if(obsGrid[i-1][j-1])  dp[i][j] = 0;
         else                   dp[i][j] = dp[i-1][j] + dp[i][j-1];
      }
   }
   return dp[m][n];
}

struct test_vector_I {
   int m;
   int n;
   int exp;
};

const struct test_vector_I test1[4] =  {
   {1, 2,           1},
   {2, 2,           2},
   {3, 7,          28},
   {4, 10,        220},
};

struct test_vector_II {
   std::vector<std::vector<int>> grid;
   int exp;
};

const struct test_vector_II test2[6] =  {
   { {{0}},                                              1},
   { {{1}},                                              0},
   { {{1,0}},                                            0},
   { {{1,0,0},{0,0,0},{0,0,0}},                          0},
   { {{0,0,0},{0,1,0},{0,0,0}},                          2},
   { {{0,0,0,0,0,0},{0,1,0,0,1,0},{0,0,0,0,0,0}},        5},
};

int main()
{
   for(auto tst : test1) {
      auto ans = uniquePaths(tst.m, tst.n);
      if(ans != tst.exp) {
         cout << "Error:uniquePaths failed for "
              << tst.m << " x " << tst.n
              << " Exp: " << tst.exp
              << " Got: " << ans << endl;
         return -1;
      }
   }
   for(auto tst : test2) {
      auto ans = uniquePathsWithObstacles(tst.grid);
      if(ans != tst.exp) {
         cout << "Error:uniquePathsWithObstacles failed, "
              << " Exp: " << tst.exp
              << " Got: " << ans << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}

