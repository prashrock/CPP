//g++-5 --std=c++11 -Wall -g -o ds_tree_serialize_deserialize_bt ds_tree_serialize_deserialize_bt.cc

/**
 * @file  Serialize/De-Serialize BT
 * @brief Serialize and De-Serialize a BT
 */

// https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::vector                  */
#include <stack>             /* std::stack                   */
using namespace std;

/**
 * Serialization is the process of converting a data structure or object
 * into a sequence of bits so that it can be stored in a file or memory
 * buffer, or transmitted across a network connection link to be
 * reconstructed later in the same or another computer environment.
 *
 * Design an algorithm to serialize and deserialize a binary tree. There
 * is no restriction on how your serialization/deserialization algorithm
 * should work. You just need to ensure that a binary tree can be
 * serialized to a string and this string can be deserialized to the
 * original tree structure.
 * For example, you may serialize the following tree
 *      1
 *     /  \
 *    2    3
 *       /   \
 *      4     5
 * as "[1,2,3,null,null,4,5]", You do not necessarily need to follow
 * this format, so please be creative and come up with different approaches
 * yourself.
 * Note: Do not use class member/global/static variables to store states.
 */

struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode *next;
   TreeNode(int x):val(x),left(NULL),right(NULL),next(NULL){}
};

/** @brief Iterative Pre-Order traversal based encoder       */
std::string serialize(TreeNode* root, const char delim = '#') {
   std::string ans;
   std::stack<TreeNode *>stk;
   if(root) stk.push(root);
   /* Regular iterative Pre-order traversal of BT            */
   while( !stk.empty() ) {
      auto cur   = stk.top(); stk.pop();
      /* If cur is valid, add right/left to stack            */
      if(cur) {
         stk.push(cur->right);
         stk.push(cur->left);
         ans += std::to_string(cur->val);
      }
      ans.push_back(delim);
   }
   //cout << ans << endl;
   return ans;
}

/* Recursive, pre-order traversal based decoder              */
TreeNode* deserialize(std::string& data, int& b, const char delim = '#') {
   TreeNode *cur = nullptr;
   int e = data.find_first_of(delim, b); /* e holds pos of # */
   if(e > b) {
      auto val   = std::stoi(data.substr(b, e));
      cur        = new TreeNode(val);
   }
   b = e + 1;                   /* Go beyond the last # seen */
   if(cur && b<(int)data.size()) { /* If more chars, proceed */
      cur->left  = deserialize(data, b);
      cur->right = deserialize(data, b);
   }
   return cur;
}

/* Wrapper function to call recursive decode API             */
TreeNode* deserialize(std::string data) {
   int b = 0;
   TreeNode *rt = deserialize(data, b);
   return rt;
}

/* Note each test-case must return the same string after decode */
//[]
//[1,null,2]
//[1,2]
//[1,2,3]
//[1,2,3,null,null,4,5,null,null,6]

int main()
{
   cout << "Info: Manual test-cases yet to be written" << endl;
   return 0;
}


/* Below is an iterative implementation for the decode API   */
#if 0
TreeNode* deserialize(std::string data, const char delim = '#') {
   TreeNode *root = nullptr, *parent = nullptr;
   std::stack<TreeNode *> stk;
   for(int b = 0, e = 0; e < data.size() - 1; b = e + 1) {
      e = data.find_first_of(delim, b);
      if(e == b) {
         if(parent) parent = nullptr;
         else       stk.pop();
      }
      if(e > b) {
         auto cur = new TreeNode(std::stoi(data.substr(b, e)));
         /* If this is the first node, populate root as well */
         if(root == nullptr) { root = parent = cur; stk.push(parent); }
         /* Process left or right sub-tree based on parent ptr */
         else {
            if(parent) { parent->left = cur;
               if(stk.empty() || stk.top() != parent) stk.push(parent);
            }
            else {
               parent = stk.top(); stk.pop();
               parent->right = cur;
            }
            stk.push(cur);
            parent = cur;
         }
      }
   }
   return root;
}
#endif
