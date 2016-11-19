//g++-5 --std=c++11 -g -Wall -Werror -o ds_graph_2D_pacific_atlantic_water_flow ds_graph_2D_pacific_atlantic_water_flow.cc

/**
 * @file  Pacific Atlantic water flow
 * @brief Given a 2D matrix, find connectivity from corners
 */

// https://leetcode.com/problems/pacific-atlantic-water-flow/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
using namespace std;

/*
 * Given an m x n matrix of non-negative integers representing
 * the height of each unit cell in a continent, the "Pacific ocean"
 * touches the left and top edges of the matrix and the "Atlantic
 * ocean" touches the right and bottom edges.
 * Water can only flow in four directions (up, down, left, or right)
 * from a cell to another one with height equal or lower.
 * Find the list of grid coordinates where water can flow to both
 * the Pacific and Atlantic ocean.
 * Note:
 * The order of returned grid coordinates does not matter.
 * Both m and n are less than 150.
 * Example: Given the following 5x5 matrix:
 *     Pacific ~   ~   ~   ~   ~
 *          ~  1   2   2   3  (5) *
 *          ~  3   2   3  (4) (4) *
 *          ~  2   4  (5)  3   1  *
 *          ~ (6) (7)  1   4   5  *
 *          ~ (5)  1   1   2   4  *
 *             *   *   *   *   * Atlantic
 * Return:
 * [[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]]
 * (positions with parentheses in above matrix).
 */

typedef std::pair<int, int> pii_t;
const std::vector<int> dirs = {0, -1, 0, 1, 0}; /* up, left, right, down */
const int PFLAG = 1, AFLAG = 2, PAVFLAG = 3;

void visitMatrixDFS(const std::vector<std::vector<int>>& matrix,
                    int i, int j, int prev_val, int FLAG,
                    std::vector<std::vector<int>>& visit) {
   const int nrow = matrix.size(), ncol = matrix[0].size(), cur_val = matrix[i][j];
   /* If current node does not have this flag and the cur val*
    * is less or equal to prev val, then DFS from here       */
   if(visit[i][j] & FLAG)       return;
   else if(cur_val < prev_val)  return;
   else                         visit[i][j] |= FLAG;
   /* Try covering all four directions from the current node */
   for(int k = 0; k < (int)dirs.size() - 1; k++) {
      const int new_i = i + dirs[k], new_j = j + dirs[k+1];
      /* Make sure if valid next node before using DFS       */
      if((new_i < 0 || new_i == nrow) ||    /* If i out of bounds  */
         (new_j < 0 || new_j == ncol) ||    /* If j out of bounds  */
         (visit[new_i][new_j] & FLAG)  ||   /* Or pre-visited node */
         (matrix[new_i][new_j] < cur_val))  /* ! Flow condition    */
         continue;
      else
         visitMatrixDFS(matrix, new_i, new_j, cur_val, FLAG, visit);
   }
}

std::vector<pii_t> pacificAtlantic(const vector<vector<int>>& matrix) {
   std::vector<pii_t> ans;
   if(matrix.empty()) return ans; /* handle corner case first*/
   const int nrow = matrix.size(), ncol = matrix[0].size();
   const int MINT = std::numeric_limits<int>::min();
   std::vector<vector<int>> visit(nrow, vector<int>(ncol, 0));
   /* Row-wise traversal. Start from first and last row      */
   for(int j = 0; j < ncol; ++j) {
      visitMatrixDFS(matrix, 0,      j, MINT, PFLAG, visit);
      visitMatrixDFS(matrix, nrow-1, j, MINT, AFLAG, visit);
   }
   /* Col-wise traversal. Start from first and last col      */
   for(int i = 0; i < nrow; ++i) {
      visitMatrixDFS(matrix, i, 0,      MINT, PFLAG, visit);
      visitMatrixDFS(matrix, i, ncol-1, MINT, AFLAG, visit);
   }
   /* Every node that has both flags is visited by both dirs */
   for(int i = 0; i < nrow; ++i) {
      for(int j = 0; j < ncol; ++j) {
         if(visit[i][j] == PAVFLAG) ans.push_back({i, j});
      }
   }
   return ans;
}

int main() {
   cout << "Note: Manual testcases yet to be written" << endl;
   return 0;
}
