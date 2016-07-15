//g++ --std=c++11 -g -Wall -o ds_tree_path_sum ds_tree_path_sum.cc

/**
 * @file  BT Path Sum
 * @brief Given BT, find root->leaf path with particular sum
 */

// https://leetcode.com/problems/path-sum/

#include <iostream>          /* std::cout                    */
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
 * @param r = current node of BT.                            *
 * @ret true if there is a root->leaf path with sum          *
 */
bool hasPathSum(TreeNode* rt, int sum) {
   if(rt == nullptr)                                    return false;
   else if(rt->left == nullptr && rt->right == nullptr) return (sum == rt->val);
   else return (hasPathSum(rt->left, sum-rt->val) | hasPathSum(rt->right, sum-rt->val));
}

int main()
{
   cout << "Info: Manual test-cases yet to be implemented." << endl;
   return 0;
}
