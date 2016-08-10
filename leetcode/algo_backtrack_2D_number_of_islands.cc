//g++-5 --std=c++11 -Wall -g -o algo_backtrack_2D_number_of_islands algo_backtrack_2D_number_of_islands.cc

/**
 * @file  Number of Islands
 * @brief Count islands with 1s in the 2D array
 */

// https://leetcode.com/problems/number-of-islands/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
using namespace std;

/**
 * Given a 2d grid map of '1's (land) and '0's (water), count the
 * number of islands. An island is surrounded by water and is formed
 * by connecting adjacent lands horizontally or vertically. You may
 * assume all four edges of the grid are all surrounded by water.
 * Example 1:
 * 11110
 * 11010
 * 11000
 * 00000                    Answer: 1
 * Example 2:
 * 11000
 * 11000
 * 00100
 * 00011                    Answer: 3
 */


/* Instead of adding if-conditions for each direction use a  *
 * for loop to generate each direction eg. (0, -1) is up     *
 * (-1, 0) is left, (0, 1) is down and (1, 0) is right       */
static vector<int> directions = {0, -1, 0, 1, 0};
/* Below are 8 directions from center (0,0) in a single list:*
 * Use this to go propagate along diagonal directions as well*/
static vector<int> directions8= {-1, 0, -1, -1, 1, 0, 1, 1, -1};

/* Given a current point which is set, use DFS to visit all  *
 * of its neighbors (in 4 directions) and clear them         */
void VisitGridDFS(vector<vector<char>>& grid, int m, int n, int i, int j) {
   grid[i][j] = '0'; /* Mark current node as visited         */
   /* Explore all 4 directions with the help of DFS          */
   for(int k = 0; k < (int)directions.size() - 1; k++) {
      int new_i = i + directions[k], new_j = j + directions[k+1];
      /* Make sure if valid direction before using DFS       */
      if((new_i < 0 || new_i == m) || (new_j < 0 || new_j == n) ||
         (grid[new_i][new_j] == '0'))
         continue;
      VisitGridDFS(grid, m, n, new_i, new_j);
   }
}

/* Use above DFS based approach and count #1s                */
int numIslands(vector<vector<char>>& grid) {
   if(grid.size() == 0) return 0;  /* empty set              */
   int cnt = 0, m = grid.size(), n = grid[0].size();
   for(int i = 0; i < m; ++i) {
      for(int j = 0; j < n; ++j) {
         if(grid[i][j] == '1') {
            cnt++;
            VisitGridDFS(grid, m, n, i, j);
         }
      }
   }
   return cnt;
}

struct test_vector {
   std::vector<std::vector<char>> grid;
   int exp;
};

const struct test_vector test[4] =  {
   { { {'1','1','1','1','0'},
       {'1','1','0','1','0'},
       {'1','1','0','0','0'},
       {'0','0','0','0','0'} } ,         1 },
   { { {'1','0','1','1','0','1','1' } }, 3 },
   { { {'1','1','1'},
       {'0','1','0'},
       {'1','1','1'} },                  1 },
   { { {'1','1','0','0','0'},
       {'1','1','0','0','0'},
       {'0','0','1','0','0'},
       {'0','0','0','1','1'} },          3},
   
};

int main()
{
   for(auto tst : test) {
      auto ans = numIslands(tst.grid);
      if(ans != tst.exp) {
         cout << "Error:numIslands failed. Exp "  
              << tst.exp << " got " << ans << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
