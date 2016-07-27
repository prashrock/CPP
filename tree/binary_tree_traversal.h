#ifndef _BT_TRAVERSAL_CPP_
#define _BT_TRAVERSAL_CPP_

#include <algorithm>           /* std::max                   */
#include <queue>               /* std::queue                 */
#include <stack>               /* std::stack                 */
#include "binary_tree_ops.h"   /* node + common operations   */

 /* Implement all possible traversal orders for a BT/BST     */
namespace bt
{
 enum class Traversal { PREORDER, INORDER, POSTORDER, BFS,
                        SPIRALORDER, BOTTOMUPORDER};
 
/* Recursive pre-order traversal of all nodes.               *
 * @param x   - root node of current sub-tree                *
 * @param vec - output vec to populate nodes @ level         */
 template<typename Tkey=int, typename Tval=int>
 void preorder(node<Tkey,Tval> *x, std::vector<node<Tkey,Tval> *> &vec) {
    if(x == nullptr) return;
    vec.push_back(x);
    preorder(x->left, vec);
    preorder(x->right, vec);
 }

 /* Recursive in-order traversal of all nodes.               *
  * @param x   - root node of current sub-tree               *
  * @param vec - output vec to populate nodes @ level        */
 template<typename Tkey=int, typename Tval=int>
 void inorder(node<Tkey,Tval> *x, std::vector<node<Tkey,Tval> *> &vec) {
    if(x == nullptr) return;
    inorder(x->left, vec);
    vec.push_back(x);
    inorder(x->right, vec);
 }

 /* Recursive post-order traversal of all nodes.             *
  * @param x   - root node of current sub-tree               *
  * @param vec - output vec to populate nodes @ level        */
 template<typename Tkey=int, typename Tval=int>
 void postorder(node<Tkey,Tval> *x, std::vector<node<Tkey,Tval> *> &vec) {
    if(x == nullptr) return;
    postorder(x->left, vec);
    postorder(x->right, vec);
    vec.push_back(x);
 }

 /* Recursive Level Order traversal - Given a level get all  *
  * nodes in that level.                                     *
  * @param rt  - root node of current sub-tree               *
  * @param vec - output vec to populate nodes @ level        *
  * @param level - 1-based level number                      *
  * Refer to https://github.com/prashrock/CPP/blob/master/leetcode/ds_tree_traversal_levelorder_bt.cc
  * for an iterative implementation                          */
 template<typename Tkey=int, typename Tval=int>
 void levelorder(node<Tkey,Tval> *rt, std::vector<node<Tkey,Tval> *>
                 &vec, unsigned int level) {
    if(rt == nullptr || level < 1) return;
    else if(level == 1) vec.push_back(rt);
    else {
       levelorder(rt->left, vec, level-1);
       levelorder(rt->right, vec, level-1);
    }
 }

 /* Iterative BFS (level-order) traversal of all the         *
  * nodes and returns all the node pointers in a vector.     *
  * Note: Using a head and tail index, we can avoid the      *
  * queue, but in interest of keeping code readable, use q   */
 template<typename Tkey=int, typename Tval=int>
 void bfs(node<Tkey,Tval> *rt, std::vector<node<Tkey, Tval> *> &vec) {
    if(rt == nullptr) return;
    /* Temporary queue to go over all elements               *
     * max# nodes = 2^h - 1 (h = 1 based height)             */
    //unsigned max_nodes = std::pow(2, calc_height(rt)) - 1;
    std::queue<node<Tkey, Tval> *> q;
    q.push(rt);
    while(q.empty() == false) { /* Visit each element once   */
       auto x = q.front();  /* BFS = Queue traversal         */
       q.pop();
       if(x && is_leaf(x) == false) { /*nonleaf, add children*/
          q.push(x->left);
          q.push(x->right);
       }
       vec.push_back(x); /*  x->output after adding children */
    }
 }

 /* Iterative spiral-order traversal of all nodes with       *
  * the help of two stacks. This function returns all        *
  * node pointers in a vector                                *
  * Time Complexity = O(n)                                   *
  * Space Complexity = O(2^h) (h = height(0 based))          *
  * space complexity is to accomodate  max # nodes that      *
  * each stack would have to hold (max leaf nodes)           */
 template<typename Tkey=int, typename Tval=int>
 void spiralorder(node<Tkey,Tval> *rt,std::vector<node<Tkey,Tval> *> &vec) {
    if(rt == nullptr) return;
    /* Temporary stack to go over L2R and R2L elements       */
    std::stack<node<Tkey, Tval> *> l2r, r2l, *q1, *q2;
    l2r.push(rt);
    q1 = &l2r;
    q2 = &r2l;
    /* Visit each element once and use 2 stacks and LIFO     *
     * ordering to change direction across levels            */
    while(l2r.size() != 0 || r2l.size() != 0) {
       while(q1->empty() == false) {
          auto x = q1->top();
          q1->pop();
          if(x == nullptr) continue;
          /* If leaf element, dont go any further            */
          if(is_leaf(x) == false) {
             if(q1 == &l2r) {
                q2->push(x->right); q2->push(x->left);
             }
             else {
                q2->push(x->left);  q2->push(x->right);
             }
          }
          /* After adding all children to q, x->output       */
          vec.push_back(x);
       }
       /* Toggle queues after iterating over each queue      */
       if(q1 == &l2r) { q1 = &r2l; q2 = &l2r; }
       else           { q1 = &l2r; q2 = &r2l; }
    }
 }

 /* Recursive bottom-up order traversal of all nodes.        *
  * This function returns all node pointers in a vector      */
 template<typename Tkey=int, typename Tval=int>
 void bottomuporder(node<Tkey,Tval> *rt,std::vector<node<Tkey,Tval> *>& vec){
    auto nlevels = calc_height(rt);
    /* Go from last level to first level, get all nodes      */
    for (int level = nlevels; level >= 1; level--)
       levelorder(rt, vec, level);
 }

 /* Pretty print BT. Time Complexity = O(n lg n)             *
  * Straightforward logic:                                   *
  *    = Row #: Depth of node                                *
  *    = Col #: In-order Traversal idx                       *
  * Output can be made more "pretty"/aligned by tweaking     *
  * In-order traversal to keep track of ghost nodes (i.e)    *
  * if left node is present & right node absent, account     *
  * right node in column number calculation                  */
 template<typename Tkey=int, typename Tval=int>
 void pretty_print(node<Tkey,Tval> *root, unsigned width=4) {
    int print_row = 0, print_col = 0; 
    if(root == nullptr) return;
    
    std::vector<node<Tkey, Tval> *> inorder_nodes, bfs_nodes;
    /* 1) Do BFS traversal to get row#                   */
    bfs(root, bfs_nodes);
    for(auto x: bfs_nodes)
       if(x) x->loc.first = calc_depth(root, x, 1);
    
    /* 2) Do Inorder traversal to get col#               */
    inorder(root, inorder_nodes);
    for(auto x : inorder_nodes)
       if(x) x->loc.second = ++print_col;
    
    /* 3) Use BFS traversal to print nodes               */
    print_row = print_col = 0;
    for(auto x: bfs_nodes) {
       if(x == nullptr) continue;
       auto row = x->loc.first;
       auto col = x->loc.second;
       if(row == print_row + 1) {
          print_col = 0;
          std::cout << std::endl;
       }
       for(auto i = print_col; i < col; ++i)
          std::cout << std::setw(width) << " ";
       std::cout << std::setw(width) << x->key;
       print_col = col + 1;
       print_row = row;
    }
    std::cout << std::endl;
 }
 
 /* Given a traversal order, traverse nodes and get keys  */
 template<typename Tkey=int, typename Tval=int>
 std::vector<Tkey> key_traversal(node<Tkey,Tval> *rt, Traversal t) {
    std::vector<Tkey> keys;
    std::vector<node<Tkey, Tval> *> nodes;
    if     (t == Traversal::PREORDER)      preorder(rt, nodes);
    else if(t == Traversal::INORDER)       inorder(rt, nodes);
    else if(t == Traversal::POSTORDER)     postorder(rt, nodes);
    else if(t == Traversal::BFS)           bfs(rt, nodes);
    else if(t == Traversal::SPIRALORDER)   spiralorder(rt, nodes);
    else if(t == Traversal::BOTTOMUPORDER) bottomuporder(rt, nodes);
    for (auto x : nodes) {
       if(x)                               keys.push_back(x->key);
       else                                keys.push_back(-1);
    }
    return keys;
 }

} //end bt namespace

#endif //_BT_TRAVERSAL_CPP_
