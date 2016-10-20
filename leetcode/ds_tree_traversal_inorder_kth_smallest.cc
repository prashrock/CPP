//g++-5 --std=c++11 -Wall -g -o ds_tree_traversal_inorder_kth_smallest ds_tree_traversal_inorder_kth_smallest.cc

/**
 * @file  Kth Smallest Element in a BST
 * @brief Find kth smallest element in a BST
 */

// https://leetcode.com/problems/kth-smallest-element-in-a-bst/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <stack>             /* std::stack                   */
using namespace std;

/**
 * Given a binary search tree, write a function kth Smallest
 * to find the kth smallest element in it.
 * Note:
 * You may assume k is always valid, 1 <= k <= BSTs total elements.
 * Follow up:
 * What if the BST is modified (insert/delete operations) often
 * and you need to find the kth smallest frequently? How would
 * you optimize the kth Smallest routine ?
 * Hint:
 * - Try to utilize the property of a BST.
 * - What if you could modify the BST node's structure?
 * - The optimal runtime complexity is O(height of BST).
 */


struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   void reset() { left = NULL; right = NULL;}
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/**
 * @brief In-order traversal to identify kth smallest elem   *
 * @param Root of the tree                                   *
 * @ret   kth element in In-order traversal                  *
 */
int kthSmallest(TreeNode* root, int k) {
   std::stack<TreeNode*> st;
   auto cur(root);
   while(st.empty() == false || cur) {
      while(cur) { st.push(cur); cur = cur->left; }
      cur = st.top(); st.pop();
      if(--k == 0) return cur->val;
      cur = cur->right;
   }
   return -1;
}

/* Refer to a 4 line recursive implementation of the above here:  *
 * https://discuss.leetcode.com/topic/17573/4-lines-in-c          */


int main()
{
   cout << "Info: Manual test-cases yet to be written" << endl;
   return 0;
}
