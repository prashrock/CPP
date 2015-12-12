//g++ --std=c++11 -g -o ds_tree_min_max_depth_bt ds_tree_min_max_depth_bt.cc

/**
 * @file  BT Find min and max depth
 * @brief The minimum depth is the number of nodes along the shortest path from the root node
 *        down to the nearest leaf node.
 *        

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
 * @brief Recursive DFS based approach to find max depth     *
 * @param root node of the BT                                *
 * @ret   max root->leaf depth                               *
 */
int maxDepth(TreeNode* root) {
	return (root) ? 1 + std::max(maxDepth(root->left), maxDepth(root->right)) : 0;
}

/**
 * @brief Recursive DFS based approach to find min depth     *
 * @param root node of the BT                                *
 * @ret   min root->leaf depth                               *
 * Note: Min-Depth has some extra processing because we want *
 * to avoid returning 1 in the case of 1-sided tree          *
 */
int minDepth(TreeNode* root) {
	if(root == NULL)      return 0;
	else if(!root->left)  return 1 + minDepth(root->right);
	else if(!root->right) return 1 + minDepth(root->left);
	else                  return 1 + std::min(minDepth(root->left), minDepth(root->right));
}

int manual_test()
{
	/* First test the empty tree test-case                    */
	struct TreeNode *x = NULL;
	struct TreeNode one = TreeNode(1), two = TreeNode(2), three = TreeNode(3);
	int d = minDepth(x);
	if(d != 0) { cout << "Error:MinDepth Empty ret=" << d << endl; return -1; }
	d = maxDepth(x);
	if(d != 0) { cout << "Error:MaxDepth Empty ret=" << d << endl; return -1; }

	/* Create a tree with 2 nodes. 1 parent and 1 child.     *
	 * Note: Now, both min-depth and max-depth must return 2 *
	 * since there is exactly 1 root-leaf path               */
	x = &one;    /* Add first node into the BT               */
	d = minDepth(x);
	if(d != 1) { cout << "Error:MinDepth one ret=" << d << endl; return -1; }
	d = maxDepth(x);
	if(d != 1) { cout << "Error:MaxDepth one ret=" << d << endl; return -1; }

	x->left = &two;   /* Add second node into the BT         */
	d = minDepth(x);
	if(d != 2) { cout << "Error:MinDepth two ret=" << d << endl; return -1; }
	d = maxDepth(x);
	if(d != 2) { cout << "Error:MaxDepth two ret=" << d << endl; return -1; }
	return 0;

	x->right = &two;  /* Add second node into the BT         */
	x->right->left = &three;  /* Add third node into BT      */
	d = minDepth(x);
	if(d != 2) { cout << "Error:MinDepth two ret=" << d << endl; return -1; }
	d = maxDepth(x);
	if(d != 3) { cout << "Error:MaxDepth 3 ret=" << d << endl; return -1; }
	return 0;
}
	
int main()
{
	if(manual_test() == 0)
		cout << "Info: All manual test-cases passed" << endl;
	return 0;
}
