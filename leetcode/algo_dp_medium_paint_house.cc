//g++ -Wall --std=c++11 -g -o algo_dp_medium_paint_house algo_dp_medium_paint_house.cc

/**
 * @file  Paint House
 * @brief Given list of costs to paint each house, find min cost
 */

// https://leetcode.com/problems/paint-house/

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


#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/**
 * DP based solution:                                        *
 * Maintain sum of costs for each color. Iterate over all    *
 * houses and update the sum of costs
 * For each house, what is the cost of painting it a given   *
 * color, depends on what is min cost of painting prev 
 
 * When n <= 0 the number of ways we can climb is 0          *
 * When n = 1, there is exactly 1 way to climb the stairs    *
 * When n = 2, there are exactly 2 ways to climb the stairs  *
 * When n > 2, the number of ways to reach n, is the number  *
 * of ways to reach n-1 + number of ways to reach n-2 pos.   *
 * This is because, n-1 and n-2 do not overlap (1 step from  *
 * n-1 to reach n and 2 steps from n-2 to reach n)           *
 * Time Complexity = O(n), Space Complexity = O(1)           */
int minCost(vector<vector<int>>& costs) {
	if(costs.size() == 0) return 0;
	vector<int> cur(3, 0), prev(3, 0);

	for(int i = 0; i < (int)costs.size(); ++i) {
		for(int j = 0; j < 3; ++j)  cur[j] = prev[j] + costs[i][j];
		/* Propagate current to prev, for next iteration     */
		prev[0] = std::min(cur[1], cur[2]);
		prev[1] = std::min(cur[0], cur[2]);
		prev[2] = std::min(cur[0], cur[1]);
	}
	return std::min(cur[0], std::min(cur[1], cur[2]));
}

int main()
{
	int cost, exp;
	vector<vector<int>> inp;

	exp  = 0;
	cost = minCost(inp);
	if(exp != cost) goto ErrMain;

	inp = {{7,6,2}}; exp  = 2;
	cost = minCost(inp);
	if(exp != cost) goto ErrMain;

	inp = {{20,18,4},{9,9,10}}; exp = 13;
	cost = minCost(inp);
	if(exp != cost) goto ErrMain;

	inp = {{17,2,17},{16,16,5}, {14,3,19}}; exp = 10;
	cost = minCost(inp);
	if(exp != cost) goto ErrMain;
	
	cout << "Info: All manual cases passed." << endl;
	return 0;
ErrMain:
	cout << "Error: Failed for case: " << endl;
	for(auto v:inp) for(auto e:v) cout << e << " ,"; 
	cout << "\t exp_cost=" << exp << " calc_cost=" << cost << endl;
	return -1;
}
