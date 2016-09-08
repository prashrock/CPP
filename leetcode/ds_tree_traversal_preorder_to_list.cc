//g++-5 --std=c++11 -Wall -g -o ds_tree_traversal_preorder_to_list ds_tree_traversal_preorder_to_list.cc

/**
 * @file  Flatten Binary Tree to Linked List
 * @brief Convert a BT to right-leaning tree (like linked-list)
 */

// https://leetcode.com/problems/flatten-binary-tree-to-linked-list/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <stack>             /* std::stack                   */
using namespace std;

/*
 * Given a binary tree, flatten it to a linked list in-place.
 * For example, given
 *                     1
 *                  /     \
 *                 2       5
 *                / \       \
 *               3   4       6
 * The flattened tree should look like:
 * 1
 *  \
 *   2
 *    \
 *     3
 *      \
 *       4
 *        \
 *         5
 *          \
 *           6
 */


struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   void reset() { left = NULL; right = NULL;}
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/**
 * @brief Iterative Pre-Order traversal using stack. The     *
 * trick is to push right and then left so that all the      *
 * left nodes are visited first. Update pointers along       *
 * @param Root of the tree                                   *
 * @ret   Pre-order traversal result as right leaning tree   *
 */
void flatten(TreeNode* root) {
   std::stack<TreeNode *> st;
   st.push(root);
   /* ans tracks the current node in pre-order traversal     */
   for(TreeNode *ans = nullptr; st.size() != 0; ) {
      auto node = st.top();
      st.pop();
      if(node != nullptr) {
         /* Pre-order iteration (push right then left node)  */
         if(node->right)    st.push(node->right);
         if(node->left)     st.push(node->left);
         /* Now manipulate pointers for the new tree         */
         if(ans == nullptr) ans = node; /* head node case    */
         /* Non-head, add to right and move right pointer    */
         else      { ans->right = node; ans = ans->right; }
         ans->left = nullptr;
      }
   }
}

int main()
{
   cout << "Info: Manual test-cases yet to be written" << endl;
   return 0;
}
