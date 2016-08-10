//g++-5 --std=c++11 -Wall -g -o ds_tree_populate_next_pointer ds_tree_populate_next_pointer.cc

/**
 * @file  BT Populate next-pointer
 * @brief Populate next pointer (level order right pointer) for each node
 */

// https://leetcode.com/problems/populating-next-right-pointers-in-each-node/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
using namespace std;

/**
 * Populate each next pointer to point to its next right node.
 * If there is no next right node, the next pointer should be set to NULL.
 * Initially, all next pointers are set to NULL.
 * Note:
 *  - You may only use constant extra space.
 *  - You may assume that it is a perfect binary tree (ie, all leaves
 *    are at the same level, and every parent has two children).
 * For example:
 *            1
 *           /  \
 *	        2    3
 *         / \  / \
 *        4  5  6  7
 * After calling your function, the tree should look like this:
 *            1 -> NULL
 *          /   \
 *         2 ->  3 -> NULL
 *        / \   / \
 *       4->5->6->7-> NULL
 */

struct TreeLinkNode {
   int val;
   TreeLinkNode *left;
   TreeLinkNode *right;
   TreeLinkNode *next;
   TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

/**
 * @brief Recursive DFS based approach to construct next ptr *
 * @param root node of the BT                                *
 */
void connect(TreeLinkNode *left, TreeLinkNode *right) {
   if(left == NULL || right == NULL) return;
   left->next = right;
   connect(left->left, left->right);
   connect(left->right, right->left);
   connect(right->left, right->right);
}

void connectRecurse(TreeLinkNode *root) {
   if(root == NULL)    return;
   else                return connect(root->left, root->right);
}

/**
 * @brief Iterative DFS based approach to construct next ptr *
 * This is inspired from Leet solution posted @ below link   *
 * https://leetcode.com/discuss/26868/my-simple-non-iterative-c-code-with-o-1-memory  *
 * @param root node of the BT                                *
 */
void connectIterative(TreeLinkNode *root) {
   while(root && root->left) {
      TreeLinkNode *cur = root;
      /* Complete all elements in this level */
      while(cur) {
         cur->left->next = cur->right;
         if(cur->next)
            cur->right->next = cur->next->left;
         cur = cur->next;
      }
      root = root->left;
   }
}

int main()
{
   cout << "Info: All manual test-cases yet to be written" << endl;
   return 0;
}
