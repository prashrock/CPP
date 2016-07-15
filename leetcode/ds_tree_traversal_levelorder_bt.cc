//g++ --std=c++11 -g -o ds_tree_traversal_levelorder_bt ds_tree_traversal_levelorder_bt.cc

/**
 * @file  BT/BST tree traversal code (level_order, level_order bottup-up)
 * @brief Implement all forms of tree traversal
 */

// https://leetcode.com/problems/binary-tree-level-order-traversal-ii/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <queue>             /* std::queue                   */
using namespace std;

/**
 * Given a binary tree, return the bottom-up level order traversal of
 * its nodes' values. (ie, from left to right, level by level from
 * leaf to root).
 */

struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* -----------Level-order traversal:Approach 1-------------- */
/**
 * @brief Iterative(BFS) levelorder traversal for BT/BST     *
 * @param root = current node of BT/BST.                     *
 * @ret   vector of level order vector keys                  *
 * Note: This traversal is a Pre-order traversal approach    *
 */
vector<vector<int>> LevelOrderIterative(TreeNode* root) {
   int depth = 0;
   vector<vector<int>> ans(0, vector<int>());
   queue<TreeNode *> q;   /* Hold all nodes in each level    */
   if(root) q.push(root); /* handle empty tree corner case   */
   while(!q.empty()) {    /* Iterate level by level with q   */
      depth++;         /* 0-based level counter              */
      int n = q.size(); /* cache q_size as it will change    */
      vector<int> level(n);
      /* For loop covers all nodes in a given level          */
      for(int i = 0; i < n; ++i) {
         auto x = q.front();
         q.pop();
         level[i] = x->val;
         if(x->left)  q.push(x->left);
         if(x->right) q.push(x->right);
      }
      ans.push_back(level);
   }
   return ans;
}


/* -----------Level-order traversal:Approach 2-------------- */
/**
 * @brief Recursive(BFS) based preorder traversal to achieve *
 *        level order traversal for BT/BST                   *
 * @param root  = current node of BT/BST.                    *
 * @param depth = 0-based current depth of the tree          *
 * @param ans   = vector of level order vector keys          *
 * Note: This traversal is a Pre-order traversal approach    *
 */
void LevelOrderRecursive(TreeNode* root, int depth, vector<vector<int>> &ans)
{
   if(root == NULL)          return;
   /* For every new level, add an empty vetor to ans        */
   if(ans.size() == depth)   ans.push_back(vector<int>());

   /* Now follow pre-order traversal on the current node    */
   ans[depth].push_back(root->val);
   if(root->left)  LevelOrderRecursive(root->left,  depth+1, ans);
   if(root->right) LevelOrderRecursive(root->right, depth+1, ans);

}
vector<vector<int>> LevelOrderRecursive(TreeNode* root) {
   vector<vector<int>> ans;
   LevelOrderRecursive(root, 0, ans);
   return ans;
}

/* Given a BT, return the bottom-up level order traversal of *
 * its nodes' values. (ie:from left to right, level by level *
 * & from leaf to root).                                     */
vector<vector<int>> LevelOrderBottomUp(TreeNode* root) {
   vector<vector<int>> ans;
   LevelOrderRecursive(root, 0, ans);
   std::reverse(ans.begin(), ans.end());
   return ans;
}

	
int main()
{
   cout << "Need to implement tree traversal test-cases" << endl;
   return 0;
}
