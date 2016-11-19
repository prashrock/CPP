//g++-5 -Wall --std=c++11 -g -o algo_dp_medium_paint_house algo_dp_medium_paint_house.cc

/**
 * @file  Paint House
 * @brief Given list of costs to paint each house, find min cost
 */

// https://leetcode.com/problems/paint-house/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
using namespace std;

/**
 * There are a row of n houses, each house can be painted with one of
 * the three colors: red, blue or green. The cost of painting each house
 * with a certain color is different. You have to paint all the houses
 * such that no two adjacent houses have the same color.
 * The cost of painting each house with a certain color is represented by
 * a n x 3 cost matrix. For example, costs[0][0] is the cost of painting
 * house 0 with color red; costs[1][2] is the cost of painting house 1 with
 * color green, and so on... Find the minimum cost to paint all houses.
 * Note: All costs are positive integers.
 */

/**
 * DP based solution:                                        *
 * Maintain sum of costs for each color. Iterate over all    *
 * houses and update the sum of costs                        *
 * For each house, what is the cost of painting it a given   *
 * color, depends on what is min cost of painting prev houses*/
int minCost(const vector<vector<int>>& costs) {
   if(costs.size() == 0) return 0;
   int n_colors = costs[0].size();
   vector<int> cur(n_colors, 0), prev(n_colors, 0); /* sums  */
   
   for(size_t i = 0; i < costs.size(); ++i) {
      for(int j = 0; j < n_colors; ++j) cur[j] = prev[j] + costs[i][j];
      /* Propagate current to prev, for next iteration       */
      prev[0] = std::min(cur[1], cur[2]);
      prev[1] = std::min(cur[0], cur[2]);
      prev[2] = std::min(cur[0], cur[1]);
   }
   return std::min({cur[0], cur[1], cur[2]});
}

struct test_vector {
   std::vector<std::vector<int>> nums;
   int exp;
};

const struct test_vector test[4] =  {
   { {},                                    0},
   { {{7,6,2}},                             2},
   { {{20,18,4},{9,9,10}},                 13},
   { {{17,2,17},{16,16,5}, {14,3,19}},     10},
};

int main()
{
   for(auto const &tst : test) {
      auto ans = minCost(tst.nums);
      if(ans != tst.exp) {
         cout << "Error:minCost failed. Exp "
              << tst.exp << " Got " << ans << " for ";
         for(auto v:tst.nums) {
            for(auto e:v) cout << e << " ,";
            cout << endl;
         }
         cout << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
