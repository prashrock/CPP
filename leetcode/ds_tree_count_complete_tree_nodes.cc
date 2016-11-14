//g++-5 --std=c++11 -Wall -g -o ds_tree_count_complete_tree_nodes ds_tree_count_complete_tree_nodes.cc

/**
 * @file  Count Complete Tree Nodes
 * @brief Given root of a complete BT, find #nodes in BT
 */

// https://leetcode.com/problems/count-complete-tree-nodes/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::vector                  */
using namespace std;

/**
 * Given a complete binary tree, count the number of nodes.
 * Definition of a complete binary tree from Wikipedia:
 * In a complete binary tree every level, except possibly the
 * last, is completely filled, and all nodes in the last level
 * are as far left as possible. It can have between 1 and 2h
 * nodes inclusive at the last level h.
 * Example: root = [5,3,6,2,4,null,7] has 6 nodes
 *         5
 *        / \
 *       3   6
 *      / \   \
 *     2   4   7
 * root = [5,4,6,2,null,null,7] has 5 nodes
 *         5
 *        / \
 *       4   6
 *      /     \
 *     2       7
 */

struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode *next;
   TreeNode(int x):val(x),left(NULL),right(NULL),next(NULL){}
};

/* Approach 1:                                                              */
/* Use recursion and exploit perfect binary tree property to find the size  */
int countNodes1(TreeNode* root) {
   if(root == nullptr) return 0;
   int lh = 0, rh = 0;
   /* Find the min height(1-based) of left and right sub-tree */
   for(auto l = root;  l != nullptr; l = l->left)  lh++;
   for(auto r = root;  r != nullptr; r = r->right) rh++;
   /* If this is a perfect binary tree (both sub-trees are fully populated) */
   if(lh == rh) return (1 << lh) - 1; /* #nodes = (2^h) - 1  (h: 1-based ht)*/
   /* Recursively find the #nodes in the left and right sub-trees.          */
   else return 1 + countNodes1(root->left) + countNodes1(root->right);
}

/* Approach 2: exploit the property of perfect tree some more          */
/* Given a complete BT, return the 0-based maximum height of the tree  *
 * Note: in a complete BT, right node is not populated before left node*/
int max_height(TreeNode* root) {
   int cnt;
   for(cnt = 0; root != nullptr; root = root->left) cnt++;
   return cnt-1;
}
/* Inspired by https://discuss.leetcode.com/topic/15533/concise-java-solutions-o-log-n-2 */
int countNodes2(TreeNode* root) {
   int n = 0;
   for(int h = max_height(root); root != nullptr; --h) {
      /* If right subtree's ht = parent tree's ht - 1        *
       * then left subtree is perfect BT                     */
      if(max_height(root->right) == h - 1) {
         n += (1 << (h-1)) + 1; /* add #nodes in left perfect BT + root.    */
         root = root->right;    /* Explore right sub-tree to calculate size */
      }
      /* This means left-sub tree itself is not perfect      *
       * so explore it further                               */
      else {
         n += (1 << (h-2)) + 1; /* add #nodes in right perfect BT + root.   */
         root = root->left;     /* Explore left sub-tree to calc its size   */
      }
   }
   return n;
}

//{[],                                                   0},
//{[1,2,3],                                              3},
//{[4,2,6,1,3,5,7],                                      7},
//{[5,3,6,2,4,null,7],                                   6},

int main()
{
   cout << "Info: Manual test-cases yet to be written" << endl;
   return 0;
}
