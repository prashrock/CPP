//g++ --std=c++11 -Wall -g -o ds_list_range_addition ds_list_range_addition.cc

/**
 * @file  Range Addition
 * @brief k update operations onto array
 */

// https://leetcode.com/problems/range-addition/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/**
 * Assume you have an array of length n initialized with all 0's
 * and are given k update operations.
 * Each operation is represented as a triplet: [startIndex,endIndex,inc]
 * which increments each element of subarray A[startIndex...endIndex]
 * (startIndex and endIndex inclusive) with inc.
 * Return the modified array after all k operations were executed.
 * Example:
 * Given:
 * length = 5,
 * updates = [ [1,  3,  2],
 *             [2,  4,  3],
 *             [0,  2, -2] ]
 * Output:  [-2, 0, 3, 5, 3]
 */

/* Brute-force: Apply each update immediately                */
vector<int> getModifiedArrayBrute(int len, vector<vector<int>>& updates) {
   vector<int> ans(len, 0);
   for(auto &up: updates)
      for(int i = up[0]; i <= up[1]; ++i) ans[i] += up[2];
   return ans;
}

int main()
{
   cout << "Info: Need to add manual tests for merge sorted arrays" << endl;
   return 0;
}
