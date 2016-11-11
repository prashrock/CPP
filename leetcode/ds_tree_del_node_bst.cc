//g++-5 --std=c++11 -Wall -g -o ds_tree_del_node_bst ds_tree_del_node_bst.cc

/**
 * @file  Delete Node in a BST
 * @brief Given root of BST and value, delete it from BST
 */

// https://leetcode.com/problems/delete-node-in-a-bst/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::vector                  */
using namespace std;

/**
 * Given a root node reference of a BST and a key, delete the
 * node with the given key in the BST. Return the root node
 * reference (possibly updated) of the BST.
 * Basically, the deletion can be divided into two stages:
 * Search for a node to remove. If the node is found, delete the node.
 *  Note: Time complexity should be O(height of tree).
 * Example:
 * root = [5,3,6,2,4,null,7] and key = 3
 *         5
 *        / \
 *       3   6
 *      / \   \
 *     2   4   7
 * Given key to delete is 3. So we find the node with value 3 & delete it.
 * One valid answer is [5,4,6,2,null,null,7], shown in the following BST.
 *         5
 *        / \
 *       4   6
 *      /     \
 *     2       7
 * Another valid answer is [5,2,6,null,4,null,7].
 *         5
 *        / \
 *       2   6
 *        \   \
 *         4   7
 */

struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode *next;
   TreeNode(int x):val(x),left(NULL),right(NULL),next(NULL){}
};


/* Find the left-most node in the BST rooted at x            */
inline TreeNode* getMinNode(TreeNode* x) {
   for(; x != nullptr && x->left != nullptr; x = x->left);
   return x;
}

TreeNode* deleteNode(TreeNode* root, int key) {
   if     (root == nullptr)  return root;
   else if(key < root->val)  root->left  = deleteNode(root->left,  key);
   else if(key > root->val)  root->right = deleteNode(root->right, key);
   /* Cur node has to be deleted, handle 3 cases below       */
   else {
      auto oldroot = root;
      if     (root->left  == nullptr)  root = root->right;
      else if(root->right == nullptr)  root = root->left;
      /* Find smallest in right sub-tree, copy its val and delete it */
      else {
         auto next   = getMinNode(root->right);
         root->val   = next->val; /* curval = smallest in right subtree */
         root->right = deleteNode(root->right, next->val);
         /* next will already be deleted, nothing to del in this case */
         oldroot     = nullptr;
      }
      delete oldroot;
   }
   return root;
}

int main()
{
   cout << "Info: Manual test-cases yet to be written" << endl;
   return 0;
}
