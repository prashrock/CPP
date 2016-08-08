//g++ --std=c++11 -Wall -g -o ds_tree_right_side_view_bt ds_tree_right_side_view_bt.cc

/**
 * @file  Binary Tree Right Side View
 * @brief Get Right most node in each level
 */

// https://leetcode.com/problems/invert-binary-tree/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::vector                  */
#include <vector>            /* std:vector                   */
using namespace std;

/**
 * Given a binary tree, imagine yourself standing on the right
 * side of it, return the values of the nodes you can see ordered
 * from top to bottom.
 * For example:
 * Given the following binary tree,
 *       1            <---
 *     /   \
 *    2     3         <---
 *     \     \
 *      5     4       <---
 * You should return [1, 3, 4].
 */

struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode *next;
   TreeNode(int x):val(x),left(NULL),right(NULL),next(NULL){}
};


/**
 * @brief Iterative level order approach to get all nodes in *
 * next level and pick right most node in current level. All *
 * nodes in each level are required since we dont know which *
 * node has children.                                        *
 * Note: This can be achieved with Pre-Order DFS traversal @ *
 * https://discuss.leetcode.com/topic/11310/my-c-solution-modified-preorder-traversal *
 * @param root node of the BT                                *
 */
std::vector<int> rightSideViewIterativeLevelOrder(TreeNode* root) {
   std::vector<int>       ans; /* right node @ each level    */
   std::vector<TreeNode*> lev(1, root);
   if(root == nullptr)    return ans; /* corner-case         */
   while(lev.size() > 0) {
      int n = lev.size();
      for(int i = 0; i < n; ++i) { /* cover 1 level at a time*/
         if(lev[i]->left)  lev.push_back(lev[i]->left);
         if(lev[i]->right) lev.push_back(lev[i]->right);
      }
      ans.push_back(lev[n-1]->val);
      lev.erase(lev.begin(), lev.begin() + n); /* del level  */
   }
   return ans;
}

//Sample test-vectors
//{1}       {1}
//{1,2}     {1,2}
//}1,2,3,4} {1,3,4}

int main()
{
   cout << "Info: Manual test-cases yet to be written." << endl;
   return 0;
}
