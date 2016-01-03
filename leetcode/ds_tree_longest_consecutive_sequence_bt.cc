//g++ --std=c++11 -g -Wall -o ds_tree_longest_consecutive_sequence_bt ds_tree_longest_consecutive_sequence_bt.cc

/**
 * @file  BT Length of Longest Consequtive sequence
 * @brief Given BT, find longest consecutive sequence path length.
 */

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <queue>             /* std::priority_queue          */
using namespace std;

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

/* Note: there is an equivalent but succinct implementation  *
 * on leetcode - https://leetcode.com/discuss/66486/c-solution-in-4-lines */
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
	cout << "Need to implement Longest Consequtive Sequence length test-cases" << endl;
	return 0;
}
