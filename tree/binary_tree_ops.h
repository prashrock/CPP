#ifndef _BT_OPS_CPP_
#define _BT_OPS_CPP_

#include <algorithm>           /* std::max                   */
#include <queue>               /* std::queue                 */
#include <stack>               /* std::stack                 */

namespace bt
{
 template<typename Tkey=int, typename Tval=int>
 class node
 {
 public:
    explicit node(Tkey k, Tval v) : key(k), val(v),
           left(nullptr), right(nullptr), cnt(1){}
    ~node() { //kp_cnt++;
       //std::cout << "del " << key << std::endl;
       left = nullptr; right = nullptr; key = 0;
    }
    unsigned size()  { return cnt; }
    Tkey key;          /* node's key                         */
    Tval val;          /* node's val                         */
    class node *left;  /* left branch                        */
    class node *right; /* right branch                       */
    unsigned cnt;      /* number of children + 1             */
    std::pair<int,int> loc;  /* (row, col) print info        */
 };

 template<typename Tkey, typename Tval>
 std::ostream& operator<<(std::ostream& os, const node<Tkey, Tval>& x)
 {
    os << x.key << ':' << x.val ;
    return os;
 }

 /* Common operations on BT and BST are listed here          */

 
 /* Check if given node's left and right child is null    */
 template<typename Tkey=int, typename Tval=int>
 bool is_leaf(node<Tkey, Tval> *x) {
    if(x->left == nullptr && x->right == nullptr) return true;
    else                                          return false;
 }
 
 /* Get #keys in BT. Time Complexity = O(1)               */
 template<typename Tkey=int, typename Tval=int>
 unsigned get_size(node<Tkey, Tval> *x) {
    if(x == nullptr) return 0;
    else   	     return x->size();
 }

 /* Calculate #Keys after Ins/Del. Time Complexity = O(1) */
 template<typename Tkey=int, typename Tval=int>
 unsigned calc_size(node<Tkey, Tval> *x) {
    if(is_leaf(x))   return 1;
    else return (1 + get_size(x->left) + get_size(x->right));
 }

 /* Get #Levels in BT(1-based). Time Complexity=O(lg n)   *
  * This logic can be slightly modified to achieve tail   *
  * recursion, but keeping as such for easy readability   */
 template<typename Tkey=int, typename Tval=int>
 unsigned calc_height(node<Tkey, Tval> *x) {
    if(x == nullptr) return 0;
    else
       return (1 + std::max(calc_height(x->left), calc_height(x->right)));
 }
 
 /* Get Node Depth @ BT(1-based). Time Complexity=O(lg n) */
 template<typename Tkey=int, typename Tval=int>
 unsigned calc_depth(node<Tkey, Tval> *rt, node<Tkey, Tval> *x,
                     unsigned cur_depth) {
    if(x == nullptr || rt == nullptr) return 0;
    else if(rt == x)                  return cur_depth;
    else
       return (std::max(calc_depth(rt->left, x, cur_depth + 1),
                        calc_depth(rt->right, x, cur_depth + 1)));
 }

 /* Get the deepest leaf node in the entire Binary Tree   *
  * This is an attempt to keep a check on height of BT    */
 template<typename Tkey=int, typename Tval=int>
 node<Tkey,Tval> *get_deepest_leaf_node(node<Tkey,Tval> *x) {
    if(x == nullptr || is_leaf(x)) return x;
    else if(x->left == nullptr)
       return get_deepest_leaf_node(x->right);
    else
       return get_deepest_leaf_node(x->left);
 }
 
 /* @brief Uses pre-order traversal to serialize the BT   *
  * @param x   - current node to serialize                *
  * @param ser - String which holds serialized values     *
  * @param tok - inter-value token (optional parameter)   *
  * Note: BT val should be serializable (via sstream) and *
  * should not contain tok.                               */
 template<typename Tkey=int, typename Tval=int>
 void serialize(node<Tkey,Tval> *x, std::string &s, char tok='#') {
    if(x) {
       std::stringstream ss;   /* avoid sprintf with ss */
       ss << x->val << tok;    /* add val + token to ss */
       s.append(ss.str());     /* serialize cur node    */
       serialize(x->left, s);  /* pre-order traverse    */
       serialize(x->right, s); /* pre-order traverse    */
    }
    else
       s += tok;  /* Empty node, append tok char to str */
 }
 
 /* @brief Uses pre-order output to re-construct BT       *
  * @param s   - String which holds serialized values     *
  * @param i   - Current idx reference being parsed in str*
  * @param tok - inter-value token (optional parameter)   *
  * Note: BT element should not contain Serialize token   */
 template<typename Tkey=int, typename Tval=int>
 node<Tkey,Tval> *deserialize(std::string &s, unsigned &i, char tok='#') {
    Tkey k;
    unsigned len = 0;    /* Length of current node       */
    unsigned start = i;  /* Start index where we started */
    
    /* First handle all cases where we can have a leaf nd*
     * 1) Index exceeds serial string bounds             *
     * 2) Two consecutive 'tok' characters               */
    if(i >= s.size())   return nullptr;  /* Leaf Node    */
    while(s[i++] != tok) ++len;  /* Calc cur node length */
    if(len == 0)   return nullptr; /* If empty, Leaf Node*/
    
    /* If not empty, extract key from substring & create *
     * a new element. Traverse sub-tree from this node   */
    else {
       /* Extract substring to StringStream to handle   *
        * keys of different types (due to template)     */
       std::stringstream ss(s.substr(start, len));
       ss >> k; /* Let Stringstream convert key to type */
       auto x = new node<Tkey, Tval>(k, k);
       
       if(!x)     return nullptr;
       x->left  = deserialize(s, i); /* i passed by ref */
       x->right = deserialize(s, i); /* i passed by ref */
       x->cnt = calc_size(x);        /* Update cnts     */
       return x;
    }
 }
 
} //end bt namespace

#endif //_BT_OPS_CPP_
