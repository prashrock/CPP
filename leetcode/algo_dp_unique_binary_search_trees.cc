//g++-5 --std=c++11 -g -Wall -o algo_dp_unique_binary_search_trees algo_dp_unique_binary_search_trees.cc

/**
 * @file  Structurally Unique Binary Search Trees
 * @brief Given n return # structurally unique BST's possible
 */

// https://leetcode.com/problems/unique-binary-search-trees/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
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

struct test_vector {
   int n;
   int exp;
};

const struct test_vector test[4] =  {
   {0,   1},
   {1,   1},
   {3,   5},
   {5,  42},
};

int main()
{
   for(auto tst : test) {
      auto ans = numTrees(tst.n);
      if(ans != tst.exp) {
         cout << "Error:numTrees failed. Exp "
              << tst.exp << " Got " << ans << " for "
              << tst.n   << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
