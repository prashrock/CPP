//g++ --std=c++11 -g -Wall -o ds_tree_path_sum_i_ii ds_tree_path_sum_i_ii.cc

/**
 * @file  BT Path Sum
 * @brief Given BT, find root->leaf path with particular sum
 */

// https://leetcode.com/problems/path-sum/
// https://leetcode.com/problems/path-sum-ii/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::vector                  */
#include <vector>            /* std:vector                   */
using namespace std;

/**
 * Given a binary tree and a sum, determine if the tree has a
 * root-to-leaf path such that adding up all the values along
 * the path equals the given sum.
 * For example:
 * Given the below binary tree and sum = 22,
 *              5
 *             / \
 *            4   8
 *           /   / \
 *          11  13  4
 *         /  \      \
 *        7    2      1
 * return true, as there exist a root-to-leaf path
 * 5->4->11->2 which sum is 22.
 */

struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/**
 * @brief Recursive Pre-Order DFS approach to explore all    *
 * root->leaf paths and find if sum of any equal to given sum*
 * @param x = current node of BT.                            *
 * @ret true if there is a root->leaf path with sum          */
bool hasPathSum(TreeNode* x, int sum) {
   if(x == nullptr)                                    return false;
   else if(x->left == nullptr && x->right == nullptr) return (sum == x->val);
   else return (hasPathSum(x->left, sum - x->val) | hasPathSum(x->right, sum - x->val));
}

/* Path sum II (same as above but also return paths)         *
 * For the above example return:                             *
 * [ [5,4,11,2],                                             *
 *   [5,8,4,5] ]                                             */

/**
 * @brief Recursive Pre-Order DFS approach to explore all    *
 * root->leaf paths and pass current traversal list along    *
 * @param r = current node of BT.                            */
void pathSumII(TreeNode* x, int sum, std::vector<int>& cur,
             std::vector<std::vector<int>>& ans) {
   sum -= x->val;
   cur.push_back(x->val);  /* add cur node to visit list     */
   if(x->left == nullptr && x->right == nullptr) {
      if(sum == 0) ans.push_back(cur);
   }
   else {
      if(x->left)  pathSumII(x->left,  sum, cur, ans);
      if(x->right) pathSumII(x->right, sum, cur, ans);
   }
   /* Remove cur node from the visit list                    */
   cur.erase(cur.begin() + cur.size() - 1);
}

vector<vector<int>> pathSumII(TreeNode* root, int sum) {
   std::vector<std::vector<int>> ans;
   std::vector<int> cur;
   if(root)  pathSumII(root, sum, cur, ans);
   return ans;
}


int main()
{
   cout << "Info: Manual test-cases yet to be implemented." << endl;
   return 0;
}
