//g++ --std=c++11 -Wall -g -o ds_tree_is_symmetric_bt ds_tree_is_symmetric_bt.cc

/**
 * @file  is BT symmetric
 * @brief Given BT check if it is symmetric around its center
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
 * @brief Recursive DFS based approach to check tree symmetry*
 * @param root node of the BT                                *
 * @ret   true if tree is symmetrical around center          *
 */
bool isSymmetric(TreeNode* left, TreeNode* right) {
	if(left == NULL || right == NULL) {
		if(left == NULL && right == NULL)              return true;
		else                                           return false;
	}
	if(left->val != right->val)                        return false;
	if(isSymmetric(left->left, right->right) == false) return false;
	else   return isSymmetric(left->right, right->left);
}
bool isSymmetric(TreeNode* root) {
	return isSymmetric(root, root);
}

bool manual_test()
{
	/* First test the empty tree test-case                    */
	struct TreeNode *x = NULL;
	struct TreeNode one = TreeNode(1), two = TreeNode(2);
	if(isSymmetric(x) != true)
	{	cout << "Error: Empty test failed" << endl; return false; }

	/* Create a tree with a single node (only root node)     */
	x = &one;    /* Add first node into the BT               */
	if(isSymmetric(x) != true)
	{	cout << "Error: Single node test failed" << endl; return false; }

	/* Create a tree with 2 nodes. 1 parent and 1 child.     */
	x->left = &two;   /* Add second node to BT               */
	if(isSymmetric(x) != false)
	{	cout << "Error: Two node test failed" << endl; return false; }
	
	/* Create a tree with 3 nodes. 1 parent and 2 children.  */
	x->right = &two;   /* Add second node to BT              */
	if(isSymmetric(x) != true)
	{	cout << "Error: Three node test failed" << endl; return false; }
	
	return true;
}
	
int main()
{
	if(manual_test())
		cout << "Info: All manual test-cases passed" << endl;
	return 0;
}
