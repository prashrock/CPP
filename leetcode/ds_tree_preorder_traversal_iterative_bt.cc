//g++ --std=c++11 -g -o ds_tree_preorder_traversal_iterative_bt ds_tree_preorder_traversal_iterative_bt.cc

/**
 * @file  BT - Preorder Traversal
 * @brief Given a tree return preorder traversal of nodes
 */

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <stack>             /* std::stack                   */
using namespace std;

/*
 * Given a binary tree, return the preorder traversal of its nodes' values.
 * For example:
 * Given binary tree {1,#,2,3},
 *  1
 *   \
 *    2
 *   /
 *  3
 * return [1,2,3].
 * Note: Recursive solution is trivial, could you do it iteratively?
 */


struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	void reset() { left = NULL; right = NULL;}
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/**
 * @brief Iterative solution using stack. The trick is to   *
 * push right and then left so that all left nodes are      *
 * visited before any right node is visited                 *
 * @param Root of the tree                                  *
 * @ret   Pre-order traversal result vector                 *
 */
vector<int> preorderTraversal(TreeNode* root) {
	stack<TreeNode*> st;
	vector<int> ans;
	if(root) st.push(root);
	while(!st.empty()) { /* Cover all nods in stack           */
		auto x = st.top();
		st.pop();
		ans.push_back(x->val);  /* Preorder = root,left,right */
		if(x->right) st.push(x->right);
		if(x->left)  st.push(x->left);
	}
	return ans;
}

bool match(const vector<int> &a, const vector<int> &b)
{
	return std::equal(a.begin(), a.end(), b.begin());
}

int manual_test()
{
	struct TreeNode one(1), two(2), three(3);
	struct TreeNode *root = NULL;
	auto ans = preorderTraversal(root);
	if(match(ans, {}) == false) {
		cout << "Error: Null Tree test-case failed" << endl;
		return -1;
	}

	one.reset(); two.reset(); three.reset();
	root = &one; root->right = &two; root->right->left = &three;
	ans = preorderTraversal(root);
	if(match(ans, {1, 2, 3}) == false) {
		cout << "Error: Null Tree test-case failed" << endl;
		return -1;
	}

	return 0;
}

int main()
{
	if(manual_test() == 0)
		cout << "Info: All manual test-cases passed" << endl;
	return 0;
}
