//g++ --std=c++11 -g -Wall -o ds_tree_sum_root_to_leaf_paths ds_tree_sum_root_to_leaf_paths.cc

/**
 * @file  BT Sum Root to Leaf Paths
 * @brief Given BT, find total sum of all root-to-leaf numbers.
 */

// https://leetcode.com/problems/sum-root-to-leaf-numbers/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
using namespace std;

/**
 * Given a binary tree containing digits from 0-9 only, each 
 * root-to-leaf path could represent a number.
 * An example is the root-to-leaf path 1->2->3 which represents
 * the number 123.
 * Find the total sum of all root-to-leaf numbers.
 * For example,
 *     1
 *   /   \
 *  2     3
 * The root-to-leaf path 1->2 represents the number 12.
 * The root-to-leaf path 1->3 represents the number 13.
 * Return the sum = 12 + 13 = 25.
 */

struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/**
 * @brief Recursive Pre-Order DFS approach                   *
 * @param root = current node of BST.                        *
 * @ret Sum of all root->leaf paths                          *
 */
int sumNumbers(TreeNode* root, int num = 0) {
   if(root == NULL) return 0;
   num = num * 10 + root->val; /* left-shift and add cur num*/
   /* If this is a leaf node, return and let parent add sum */
   if(root->left == NULL && root->right == NULL) return num;
   else return sumNumbers(root->left,  num) + sumNumbers(root->right, num);
}
	
int main()
{
   cout << "Info: Need to implement sum root->leaf paths" << endl;
   return 0;
}
