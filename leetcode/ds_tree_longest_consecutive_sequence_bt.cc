//g++ --std=c++11 -g -Wall -o ds_tree_longest_consecutive_sequence_bt ds_tree_longest_consecutive_sequence_bt.cc

/**
 * @file  BT Length of Longest Consequtive sequence
 * @brief Given BT, find longest consecutive sequence path length.
 */

// https://leetcode.com/problems/binary-tree-longest-consecutive-sequence/

#include <iostream>          /* std::cout                    */
using namespace std;

/**
 * Given a binary tree, find the length of the longest consecutive
 * sequence path.
 * The path refers to any sequence of nodes from some starting node to any
 * node in the tree along the parent-child connections. The longest
 * consecutive path need to be from parent to child (cannot be the reverse).
 * For example:
 *    1
 *     \
 *      3
 *     / \
 *    2   4
 *         \
 *          5
 * Longest consecutive sequence path is 3-4-5, so return 3.
 *     2
 *      \
 *       3
 *      /
 *     2
 *    /
 *   1
 * Longest consecutive sequence path is 2-3,not3-2-1, so return 2.
 */

struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/**
 * @brief Recursive approach to find length of longest       *
 * consequtive parent->child sequence                        *
 * @param root = current node of BST.                        *
 * @param  len = current longest consequtive seq length      *
 * @param parent_val = value of parent node (calling node)   *
 * @ret Longest Consequtive Sequence length in subtree       *
 */
int longestConsecutiveDFS(TreeNode* root, int len, int parent_val) {
   int cur_len = len;
   if(root == NULL)                return cur_len;
   if(parent_val + 1 != root->val) cur_len = 0;
   cur_len = std::max(longestConsecutiveDFS(root->left,  cur_len+1, root->val),
                      longestConsecutiveDFS(root->right, cur_len+1, root->val));
   return std::max(len, cur_len);
}

/* Note: Alternate implementation (longestConsequtiveDFS)    *
 * taken from leetcode                                       *
 * https://leetcode.com/discuss/66486/c-solution-in-4-lines  */
int search(TreeNode *root, TreeNode *parent, int len) {
   if (!root) return len;
   len = (parent && root->val == parent->val + 1)?len+1:1;
   return max(len, max(search(root->left, root, len), search(root->right, root, len)));
}

int longestConsecutive(TreeNode* root) {
   return longestConsecutiveDFS(root, 0, 0);
}
	
int main()
{
   cout << "Info: Manual test-cases yet to be implemented." << endl;
   return 0;
}
