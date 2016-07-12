//g++ --std=c++11 -Wall -g -o ds_tree_is_same_tree_bt ds_tree_is_same_tree_bt.cc

/**
 * @file  Is BT Same Tree
 * @brief Check if two given binary trees are equal
 */

// https://leetcode.com/problems/same-tree/

/**
 * Given two binary trees, write a function to check if they
 * are equal or not.
 * Two binary trees are considered equal if they are structurally
 * identical and the nodes have the same value.
 */

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <queue>             /* std::priority_queue          */
using namespace std;

struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/**
 * @brief Recursive DFS based approach to check tree equality*
 * @param root node of both BT's                             *
 * @ret   true if tree is both BT's are identical            *
 */
bool isSameTreeRec(TreeNode* p, TreeNode* q) {
   /* If either trees has a NULL make sure other has one too */
   if(p == nullptr || q == nullptr) return (p == q);
   /* We reach here only if p and q are non-nul. Now check   *
    * If p, q val's match. If yes, recursively do same check */
   else return (p->val == q->val &&
                isSameTreeRec(p->left, q->left) &&
                isSameTreeRec(p->right, q->right));
}

/**
 * @brief Iterative level-order approach for tree equality   *
 * @param root node of both BT's                             *
 * @ret   true if tree is both BT's are identical            *
 */
bool isSameTreeBFS(TreeNode* p, TreeNode* q) {
   std::vector<TreeNode *> p_lev, q_lev;
   /* If either trees has a NULL make sure other has one too */
   if(p == nullptr || q == nullptr) { return (p == q); }
   /* Else, add roots->vector to begin level-order traversal */
   else                             { p_lev.push_back(p); q_lev.push_back(q); }
   /* While vector is non-empty this level has leaf nodes    */
   while(p_lev.size() > 0) {
      int n = p_lev.size();
      /* The number of nodes in cur-level must match         */
      if(p_lev.size() != q_lev.size())           return false;
      /* Match all level elements and add children to vector */
      for(int i = 0; i < n; ++i) {
         /* Make sure current element is valid in p / q tree */
         if(p_lev[i] != nullptr && q_lev[i] != nullptr) {
            if(p_lev[i]->val != q_lev[i]->val) return false;
            p_lev.push_back(p_lev[i]->left); p_lev.push_back(p_lev[i]->right);
            q_lev.push_back(q_lev[i]->left); q_lev.push_back(q_lev[i]->right);
         }
         /* If either p or q's cur element is null and we    *
          * reach here. Make sure both elements are NULL     */
         else if(p_lev[i] != q_lev[i])          return false;
      }
      /* Clear all elements in current level                 */
      p_lev.erase(p_lev.begin(), p_lev.begin() + n);
      q_lev.erase(q_lev.begin(), q_lev.begin() + n);
   }
   return (p_lev.empty() && q_lev.empty());
}
	
int main()
{
   cout << "Info: Need to write manual test-cases." << endl;
   return 0;
}
