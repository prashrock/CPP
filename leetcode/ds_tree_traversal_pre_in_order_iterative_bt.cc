//g++ --std=c++11 -Wall -g -o ds_tree_traversal_pre_in_order_iterative_bt ds_tree_traversal_pre_in_order_iterative_bt.cc

/**
 * @file  BT - Preorder/Inorder Traversal
 * @brief Given a tree return pre/in order traversal of nodes
 */

// https://leetcode.com/problems/binary-tree-preorder-traversal/
// https://leetcode.com/problems/binary-tree-inorder-traversal/

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
 * Given a binary tree, return pre/in order traversal of its nodes' values.
 * For example:
 * Given binary tree {1,#,2,3},
 *  1
 *   \
 *    2
 *   /
 *  3
 * return [1,2,3] for pre-order and [1,3,2] for in-order
 * Note: Recursive solution is trivial, could you do it iteratively ?
 */


struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   void reset() { left = NULL; right = NULL;}
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/**
 * @brief Iterative solution using stack. The trick is to    *
 * push right and then left so that all left nodes are       *
 * visited before any right node is visited                  *
 * @param Root of the tree                                   *
 * @ret   Pre-order traversal result vector                  *
 */
vector<int> preorderTraversal(TreeNode* root) {
   stack<TreeNode*> st;
   vector<int> ans;
   if(root) st.push(root);
   while(!st.empty()) {      /* Cover all nods in stack      */
      auto x = st.top();
      st.pop();
      ans.push_back(x->val); /* Preorder = root,left,right   */
      if(x->right) st.push(x->right);
      if(x->left)  st.push(x->left);
   }
   return ans;
}

/**
 * @brief Iterative solution using stack. The trick is to    *
 * push all left-leaning nodes and maintaining a separate    *
 * current node pointer. At each stage process current node  *
 * Note: Could use Morris traversal approach for O(1) space  *
 * @param Root of the tree                                   *
 * @ret   In-order traversal result vector                   *
 */
vector<int> inorderTraversal(TreeNode* root) {
   vector<int> ans;
   stack<TreeNode *> st;
   TreeNode *cur = root;

   while(!st.empty() || cur) {
      while(cur) {st.push(cur); cur = cur->left;}
      cur = st.top();
      st.pop();
      ans.push_back(cur->val);
      cur = cur->right;
   }
   return ans;
}

/* BST Inorder iterator based on Inorder iterative traversal *
 * Same as above code, but split into different functions.   *
 * Time complexity for hasNext and next is O(1)              *
 * Space complexity for iterator = O(h) where h=tree_height  */
class BSTIterator {
private:
   stack<TreeNode *> st;
public:
   BSTIterator(TreeNode *root) {
      while(root) {st.push(root); root = root->left;}
   }

   /** @return whether we have a next smallest number        */
   bool hasNext() { return (!st.empty()); }

   /** @return the next smallest number                      */
   int next() {
      auto cur = st.top();
      st.pop();
      int x = cur->val;
      cur = cur->right;
      while(cur) {st.push(cur); cur = cur->left;}
      return x;
   }
};

bool match(const vector<int> &a, const vector<int> &b) {
   return std::equal(a.begin(), a.end(), b.begin());
}

int manual_test()
{
   struct TreeNode one(1), two(2), three(3);
   struct TreeNode *root = NULL;
   auto ans = preorderTraversal(root);
   if(match(ans, {}) == false) {
      cout << "Error: Preorder Null Tree test-case failed" << endl;
      return -1;
   }
   ans = inorderTraversal(root);
   if(match(ans, {}) == false) {
      cout << "Error: Inorder Null Tree test-case failed" << endl;
      return -1;
   }

   one.reset(); two.reset(); three.reset();
   root = &one; root->right = &two; root->right->left = &three;
   ans = preorderTraversal(root);
   if(match(ans, {1, 2, 3}) == false) {
      cout << "Error: Preorder 3-node test-case failed" << endl;
      return -1;
   }
   ans = inorderTraversal(root);
   if(match(ans, {1, 3, 2}) == false) {
      cout << "Error: Inorder 3-node test-case failed" << endl;
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
