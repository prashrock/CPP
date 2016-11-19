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

/* Morris Algorithm for pre-order traversal (No stack used)  *
 * Time Complexity = O(n)     Space Complexity = O(1)        *
 * Every node is visited by cur exactly once and by pre at   *
 * most once. So runtime = #steps of cur/pre = O(n)          *
 * Inspired by Leetcode solution @                           *
 * https://discuss.leetcode.com/topic/3995/share-my-simple-non-recursive-solution-o-1-space-complexity */
void flatten_without_stack(TreeNode* root) {
   if (root == nullptr)       return;
   TreeNode *cur = root;
   while(cur) {
      if(cur->left) {
         /* Find right-most node in the left sub-tree (pre)  */
         TreeNode *pre = cur->left;
         while(pre->right)  pre = pre->right;
         /* Add cur's right sub-tree to end of left-subtree  */
         pre->right = cur->right;
         /* Finish processing cur-node. Move left pointer to *
          * right and empty the left pointer. Then repeat..  */
         cur->right = cur->left;
         cur->left  = nullptr;
      }
      cur = cur->right;
   }
}


int main()
{
   cout << "Info: Manual test-cases yet to be written" << endl;
   return 0;
}
