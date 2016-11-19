//g++-5 --std=c++11 -Wall -g -o ds_tree_invert_bt ds_tree_invert_bt.cc

/**
 * @file  Invert BT
 * @brief Invert a binary tree
 */

// https://leetcode.com/problems/invert-binary-tree/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::vector                  */
#include <vector>            /* std::vector                  */
using namespace std;

/**
 * Invert a binary tree.
 *         4
 *       /   \
 *      2     7
 *     / \   / \
 *    1   3 6   9
 * to
 *         4
 *       /   \
 *      7     2
 *     / \   / \
 *    9   6 3   1
 */

struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode *next;
   TreeNode(int x):val(x),left(NULL),right(NULL),next(NULL){}
};

/**
 * @brief Recursive DFS Post-order approach to mirror the BT *
 * @param root node of the BT                                *
 */
TreeNode* invertTreeRecursiveDFS(TreeNode* root) {
   if(root != nullptr) {
      invertTreeRecursiveDFS(root->left);   
      invertTreeRecursiveDFS(root->right);
      std::swap(root->left, root->right); /* flip cur node   */
   }
   return root;
}


/**
 * @brief Iterative level order approach to create mirror img*
 * Traverse the BT one level at a time with a queue          *
 * Check out the stack based implementation in Discussions @ *
 * https://discuss.leetcode.com/topic/16138/recursive-and-non-recursive-c-both-4ms/2 *
 * @param root node of the BT                                *
 */
TreeNode* invertTreeIterativeLevelOrder(TreeNode* root) {
   std::vector<TreeNode *> lev(1, root);
   while(lev.size() > 0) {
      int n = lev.size();
      for(int i = 0; i < n; ++i) { /* Cover 1 level at a time*/
         /* Flip left/right ptrs and enqueue both into vector*/
         if(lev[i] != nullptr) {
            std::swap(lev[i]->left, lev[i]->right);
            lev.push_back(lev[i]->left);
            lev.push_back(lev[i]->right);
         }
      }
      lev.erase(lev.begin(), lev.begin() + n); /* del level  */
   }
   return root;
}

int main()
{
   cout << "Info: Manual test-cases yet to be written" << endl;
   return 0;
}
