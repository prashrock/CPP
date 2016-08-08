#ifndef _BT_CPP_
#define _BT_CPP_

#include <algorithm>           /* std::max                   */
#include <queue>               /* std::queue                 */
#include <vector>              /* std:vector                 */
#include <stack>               /* std::stack                 */
#include <sstream>             /* std::stringstream          */
#include "binary_tree_ops.h"   /* node + common operations   */
#include "binary_tree_traversal.h" /* BT traversal algos     */

namespace bt
{
   
/* Binary Tree Implementation                                *
 * Height = Number of levels below (1-based)                 *
 * Depth  = Number of levels above (1-based)                 */
template<typename Tkey=int, typename Tval=int>
class binary_tree{
public:
   /* Two constructors - Empty, Deserialize                  */
   binary_tree(): ins_cnt(0),del_cnt(0),dup_ins_cnt(0),root(nullptr) { }
   binary_tree(std::string &s): ins_cnt(s.size()) {
      unsigned i = 0; /* need to pass a reference            */
      root = deserialize(s, i);
   }

   node<Tkey, Tval>* get_root() const { return root;                   }
   unsigned size()              const { return get_size(get_root());   }
   unsigned height()            const { return calc_height(get_root());}
   bool is_root(node<Tkey, Tval> *x) const {
      return (get_root() && (get_root() == x));
   }
   void ins(Tkey key, Tval val) {
      root = ins(get_root(), key, val);
   }
   void del(Tkey key) {
      root = del(get_root(), key);
   }
   bool find(Tkey key) const {
      return (find(get_root(), key) != nullptr);
   }
   unsigned depth(node<Tkey, Tval> *x) const {
      return calc_depth(get_root(), x, 1);
   }
   std::vector<Tkey> get_keys(Traversal t) const {
      return key_traversal(get_root(), t);
   }
   bool find_lcp(Tkey a, Tkey b, Tkey &res) {
      /* Trade keys for node pointers. If there are more     *
       * than one node with same key, get first found node   */
      auto a_node = find(get_root(), a);
      auto b_node = find(get_root(), b);
      auto lcp = find_lcp(get_root(), a_node, b_node);
      if(lcp) {
         res = lcp->key; /* If LCP found, get its key        */
         return true;
      }
      else return false;
   }

   /* BT_ONLY - Find first node that has the key.            */
   node<Tkey,Tval> *find(node<Tkey,Tval> *rt, Tkey key) const {
      auto x = rt;
      if(x == nullptr || x->key == key)     return x;
      else if((x = find(rt->left, key)))    return x;
      else if((x = find(rt->right, key)))   return x;
      else                                  return nullptr;
   }

   /* BT_ONLY - Recursive find all keys implementation.      *
    * Returns bool to indicate success/fail and also         *
    * populates a vector of values                           */
   bool findall(node<Tkey,Tval> *x, Tkey key, std::vector<Tval> &valv) {
      bool ret = false;
      if(x == nullptr)                             return ret;
      if(x->key == key)  {
         valv.push_back(x->val);
         ret = true;
      }
      ret |= findall(x->left, key, valv);
      ret |= findall(x->right, key, valv);
      return ret;
   }

   /* BT_ONLY - Find lowest common parent given 2 nodes      *
    * Two possible cases:                                    *
    * - If a is parent of b, return a. This is accomplished  *
    *   by returning a as soon as we find it and no other    *
    *   node will reply back.                                *
    * - If a and b occur in two different branches, then the *
    *   first node that has both left and right sub-tree set *
    *   is the LCP. All other nodes are parent nodes are     *
    *   ancestors, they will just pass on LCP result         */
   node<Tkey,Tval> *
   find_lcp(node<Tkey,Tval> *cur, node<Tkey,Tval> *a, node<Tkey,Tval> *b) {
      if(cur == nullptr)            return nullptr;
      else if(cur == a || cur == b) return cur;
      
      /* Search for a and b in both left & right sub-tree    */
      auto left  = find_lcp(cur->left, a, b);
      auto right = find_lcp(cur->right, a, b);
      
      /* If both left & right trees have a, b, then this     *
       * node is the LCP. Return this node                   */
      if(left && right)             return cur;
		
      /* If both left and right are not set, either a, b     *
       * do not occur in subtree or this node is ancestor    *
       * in either case, pass on result from left/right      */
      else if(left)                 return left;
      else                          return right;
   }

   /* BT_ONLY - Get Parent node of given node 'x'            */
   node<Tkey,Tval> *get_parent_node(node<Tkey,Tval> *parent,
                                    node<Tkey,Tval> *x) {
      if(parent == nullptr)                        return parent;
      else if(parent->left==x || parent->right==x) return parent;
      auto y = get_parent_node(parent->left, x);
      if(y == nullptr)
         y = get_parent_node(parent->right, x);
      return y;
   }

   /* BT_ONLY - Insert while trying to maintain a perfect BT */
   node<Tkey,Tval> *ins(node<Tkey,Tval> *x, Tkey key, Tval val) {
      if(x == nullptr)  return new node<Tkey, Tval>(key, val);
      if(get_size(x->left) <= get_size(x->right))
         x->left  = ins(x->left, key, val);
      else   x->right = ins(x->right, key, val);
      x->cnt = calc_size(x);
      return x;
   }

   /* BT_ONLY - When the deepest node is removed, propagate  *
    * pointer updates from deleted node till the min node    */
   node<Tkey,Tval> *del_propagate_pointers(node<Tkey,Tval> *x,
                                           node<Tkey,Tval> *del) {
      if(x == nullptr)            return nullptr;
      else if(x == del)           return nullptr;
      else if(x->left == del)     x->left = nullptr;
      else if(x->right== del)     x->right= nullptr;
      else {
         x->left = del_propagate_pointers(x->left, del);
         x->right= del_propagate_pointers(x->right, del);
      }
      x->cnt  = calc_size(x);
      return x;
   }

   /* BT_ONLY - Delete **all** occurences of this key        *
    * Follow Hibbard deletion condition to del current node  *
    * 3 possibile cases:                                     *
    * 0 child: Set parent link to null and update cnts       *
    * 1 child: Set parent link to other child + update cnts  *
    * 2 child: Replace current node with another node from   *
    *        : subtree starting at this node + update cnts   *
    *        : For BT chose node from deepest subtree        *
    *        : For BST chose min node from subtree           */
   node<Tkey,Tval> *del(node<Tkey,Tval> *x, Tkey key) {
      if(x == nullptr)        return x;
      x->left  = del(x->left, key);
      x->right = del(x->right, key);
      if(x->key == key) {
         auto old_x = x;
         /* Takes care of 1st 2 cases of Hibbard Deletion    */
         if     (x->right == nullptr) x = x->left;
         else if(x->left  == nullptr) x = x->right;
         /* Takes care of 3rd case of Hibbard Deletion       */
         else {
            x = get_deepest_leaf_node(old_x->right);
            x->right = del_propagate_pointers(old_x->right,x);
            x->left  = old_x->left;
         }
         delete old_x;
      }
      if(x == nullptr) return x;
      x->cnt = calc_size(x);
      return x;
   }
private:
   unsigned ins_cnt;
   unsigned del_cnt;
   unsigned dup_ins_cnt;
   node<Tkey, Tval> *root;
};

template<typename Tkey, typename Tval>
std::ostream& operator<<(std::ostream& os, binary_tree<Tkey, Tval>& bin) {
   pretty_print(bin.get_root());
   os << std::endl;
   return os;
}

} //end namespace

#endif //_BT_CPP_
