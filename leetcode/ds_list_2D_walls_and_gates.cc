//g++-5 --std=c++11 -Wall -g -o ds_list_2D_walls_and_gates ds_list_2D_walls_and_gates.cc -I../utils/

// https://leetcode.com/problems/walls-and-gates/

/**
 * @file  2D Walls and Gates
 * @brief Propagate value around cells
 */

/**
 * You are given a m x n 2D grid initialized with these three
 * possible values.
 * -1  - A wall or an obstacle.
 * 0   - A gate.
 * INF - Infinity means an empty room. We use the value
 *       231 - 1 = 2147483647 to represent INF as you may assume
 *       that the distance to a gate is less than 2147483647.
 * Fill each empty room with the distance to its nearest gate.
 * If it is impossible to reach a gate, it should be filled with INF.
 * For example, given the 2D grid:
 *     INF  -1  0  INF
 *     INF INF INF  -1
 *     INF  -1 INF  -1
 *       0  -1 INF INF
 * After running your function, the 2D grid should be:
 *       3  -1   0   1
 *       2   2   1  -1
 *       1  -1   2  -1
 *       0  -1   3   4
 */

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <queue>             /* std::queue                   */
#include <unordered_map>     /* std::unordered_map container */
#include "print_utils.h"     /* print_table_row              */
using namespace std;

typedef std::pair<int, int> pii_t;

/* Instead of adding if-conditions for each direction use a  *
 * for loop to generate each direction eg. (0, -1) is up     *
 * (-1, 0) is left, (0, 1) is down and (1, 0) is right       */
const std::vector<int> directions = {0, -1, 0, 1, 0};

/* Given a door (0)  use BFS to percolate to all neighbors   *
 * (in 4 directions). Use a queue to continue traversal      */
void VisitGridBFS(vector<vector<int>>& rooms, int m, int n,
                  std::queue<pii_t>& q) {
   /* Explore all 4 directions with the help of BFS (queue)  */
   while(!q.empty()) {
      int i = q.front().first, j = q.front().second;
      q.pop();
      for(int k = 0; k < (int)directions.size() - 1; k++) {
         int new_i = i + directions[k], new_j = j + directions[k+1];
         /* Can we and should we proceed with this node ?    */
         if((new_i < 0 || new_i == m) || /* row boundary chk */
            (new_j < 0 || new_j == n) || /* col boundary chk */
            (rooms[new_i][new_j]==-1) || /* we've hit a wall */
            (rooms[new_i][new_j] <= rooms[i][j])) /* already optimal */
            continue;
         rooms[new_i][new_j] = rooms[i][j] + 1;
         q.push(std::make_pair(new_i, new_j));
      }
   }
}

/* Use BFS to visit all the surrounding cells                */
void wallsAndGates(vector<vector<int>>& rooms) {
   if(rooms.size() == 0) return; /* corner case              */ 
   int m = rooms.size(), n = rooms[0].size();
   std::queue<pii_t> q;
   /* Round up all the 0's into a Q to start BFS search      */
   for(int i = 0; i < m; ++i) 
      for(int j = 0; j < n; ++j)
         if(rooms[i][j] == 0) q.push(std::make_pair(i, j));
   VisitGridBFS(rooms, m, n, q);
}

int main()
{
   const int max = std::numeric_limits<int>::max();
   vector<vector<int>> input = { {max, -1,    0, max},
                                 {max, max, max,  -1},
                                 {max,  -1, max,  -1},
                                 {0,    -1, max, max}};

   vector<vector<int>> ans = { {3, -1, 0,  1},
                               {2,  2, 1, -1},
                               {1, -1, 2, -1},
                               {0, -1, 3,  4}};
   
   wallsAndGates(input);
   //for (auto vec : input) print_table_row<int>(" ", vec, 2, 3);
   if(input == ans)  cout << "Info: Manual test-case passed." << endl;
   else              cout << "Error: Manual case failed." << endl;
   return 0;
}
