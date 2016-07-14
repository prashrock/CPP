//g++ --std=c++11 -g -Wall -o algo_dp_unique_binary_search_trees algo_dp_unique_binary_search_trees.cc

/**
 * @file  Structurally Unique Binary Search Trees
 * @brief Given n return # structurally unique BST's possible
 */

// https://leetcode.com/problems/unique-binary-search-trees/

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
 * Given n, how many structurally unique BST's (binary search trees)
 * that store values 1...n?
 * For example, Given n = 3, there are a total of 5 unique BST's.
 *    1         3     3      2      1
 *     \       /     /      / \      \
 *      3     2     1      1   3      2
 *     /     /       \                 \
 *    2     1         2                 3
 */

/**
 * @brief Use bottom up DP to iteratively construct answer   *
 * @param positive integer, n                                *
 * @ret   number of structurally unique BST's possible       *
 * Taking 1~n as root respectively:                          *
 *      1 as root: # of trees = F(0) * F(n-1)  // F(0) == 1  *
 *      2 as root: # of trees = F(1) * F(n-2)                *
 *      3 as root: # of trees = F(2) * F(n-3)                *
 *      ...                                                  *
 *      n-1 as root: # of trees = F(n-2) * F(1)              *
 *      n as root:   # of trees = F(n-1) * F(0)              *
 *                                                           *
 * So, the formulation is:                                   *
 *      F(n) = F(0) * F(n-1) + F(1) * F(n-2) + F(2) * F(n-3) *
 *            + ... + F(n-2) * F(1) + F(n-1) * F(0)          *
 * Inspired by the solution posted in Leetcode:              *
 * Leetcode.com/discuss/17674/dp-problem-10-lines-with-comments *
 * Time Complexity = O(n^2) Space Complexity = O(n^2)        *
 */
int numTrees(int n) {
   vector<int> cost(n + 1, 0);
   cost[0] = cost[1] = 1;
   cost[2] = 2;
   for(int i = 3; i <= n; ++i) {
      for(int j = 1; j <= i; ++j)
         cost[i] += cost[j-1] * cost[i-j];
   }
   return cost[n];
}

int main()
{
   int ans, n, exp;
   n = 0; exp = 1;
   ans = numTrees(n);
   if(ans != exp) goto ErrMain;
   n = 1; exp = 1;
   ans = numTrees(n);
   if(ans != exp) goto ErrMain;
   n = 3; exp = 5;
   ans = numTrees(n);
   if(ans != exp) goto ErrMain;
   n = 5; exp = 42;
   ans = numTrees(n);
   if(ans != exp) goto ErrMain;

   cout << "Info: All manual test-cases passed" << endl;
   return 0;
ErrMain:
   cout << "Error: numTrees failed for n = " << n
        << " expected=" << exp << " ans=" << ans << endl;
   return -1;
}
