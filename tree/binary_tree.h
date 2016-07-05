#include <algorithm>           /* std::max                   */
#include <queue>               /* std::queue                 */
#include <stack>               /* std::stack                 */
#include <sstream>             /* std::stringstream          */

namespace bt
{

/* Implement all possible traversal orders for a tree        */
enum class Traversal { PREORDER, INORDER, POSTORDER, BFS,
		SPIRALORDER, BOTTOMUPORDER};

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

template<typename Tkey=int, typename Tval=int>
/* Binary Tree Implementation                                *
 * Most API's defined here will directly be inherited by BST *
 * Height = Number of levels below (1-based)                 *
 * Depth  = Number of levels above (1-based)                 */
class binary_tree{
public:
   /* Two constructors - Empty, Deserialize                 */
   binary_tree(): ins_cnt(0),del_cnt(0),dup_ins_cnt(0),root(nullptr){}
   binary_tree(std::string &s): ins_cnt(s.size()) {
      unsigned i = 0;
      root = deserialize(s, i);
   }

   unsigned size()     { return get_size(root);    }
   unsigned height()   { return calc_height(root); } /* 1-based */
   node<Tkey, Tval>* get_root() {return root;      }
   void ins(Tkey key, Tval val) { root = ins(get_root(), key, val); }
   void del(Tkey key)           { root = del(get_root(), key); }
   bool find(Tkey key)          { return find(get_root(), key, nullptr); }
   unsigned depth(node<Tkey, Tval> *x) {return calc_depth(get_root(), x, 1);}
   std::vector<Tkey> get_keys(Traversal t) {return key_traversal(t); } 

   /* Check if given node is the root-node                  */
   bool is_root(node<Tkey, Tval> *x) {
      if(get_root() && get_root() == x) return true;
      else                              return false;
   }
   /* Check if given node's left and right child is null    */
   bool is_leaf(node<Tkey, Tval> *x) {
      if(x->left == nullptr && x->right == nullptr) return true;
      else                                          return false;
   }

   /* Get #keys in BT. Time Complexity = O(1)               */
   unsigned get_size(node<Tkey, Tval> *x) {
      if(x == nullptr) return 0;
      else   			 return x->size();
   }

   /* Calculate #Keys after Ins/Del. Time Complexity = O(1) */
   unsigned calc_size(node<Tkey, Tval> *x) {
      if(is_leaf(x))   return 1;
      else return (1 + get_size(x->left) + get_size(x->right));
   }

    /* Get #Levels in BT(1-based). Time Complexity=O(lg n)   *
     * This logic can be slightly modified to achieve tail   *
     * recursion, but keeping as such for easy readability   */
   unsigned calc_height(node<Tkey, Tval> *x) {
      if(x == nullptr) return 0;
      else
         return (1 + std::max(calc_height(x->left), calc_height(x->right)));
   }

   /* Get Node Depth @ BT(1-based). Time Complexity=O(lg n) */
   unsigned calc_depth(node<Tkey, Tval> *rt, node<Tkey, Tval> *x,
                       unsigned cur_depth) {
      if(x == nullptr || rt == nullptr) return 0;
      else if(rt == x)                  return cur_depth;
      else
         return (std::max(calc_depth(rt->left, x, cur_depth + 1),
                          calc_depth(rt->right, x, cur_depth + 1)));
   }

   /* Wrapper node to invoke find_lcp(root, a_node, b_node) */
   bool find_lcp(Tkey a, Tkey b, Tkey &res) {
      /* Trade keys for node pointers. If there are more   *
       * than one node with same key, get first found node */
      auto rt     = get_root();
      auto a_node = find(rt, a);
      auto b_node = find(rt, b);
      /* Call main LCP routine */
      auto lcp = find_lcp(rt, a_node, b_node);
      if(lcp) {
         res = lcp->key; /* If LCP found, get its key     */
         return true;
      }
      else return false;
   }

   /* Get the deepest leaf node in the entire Binary Tree   *
    * This is an attempt to keep a check on height of BT    */
   node<Tkey,Tval> *get_deepest_leaf_node(node<Tkey,Tval> *x) {
      if(x == nullptr || is_leaf(x)) return x;
      else if(x->left == nullptr)
         return get_deepest_leaf_node(x->right);
      else
         return get_deepest_leaf_node(x->left);
   }

   /* Recursive pre-order traversal of all nodes.           *
    * @param x   - root node of current sub-tree            *
    * @param vec - output vec to populate nodes @ level     */
   void preorder(node<Tkey,Tval> *x,
                 std::vector<node<Tkey,Tval> *> &vec) {
      if(x == nullptr) return;
      vec.push_back(x);
      preorder(x->left, vec);
      preorder(x->right, vec);
   }

   /* Recursive in-order traversal of all nodes.            *
    * @param x   - root node of current sub-tree            *
    * @param vec - output vec to populate nodes @ level     */
   void inorder(node<Tkey,Tval> *x,
                std::vector<node<Tkey,Tval> *> &vec) {
      if(x == nullptr) return;
      inorder(x->left, vec);
      vec.push_back(x);
      inorder(x->right, vec);
   }

   /* Recursive post-order traversal of all nodes.          *
    * @param x   - root node of current sub-tree            *
    * @param vec - output vec to populate nodes @ level     */
   void postorder(node<Tkey,Tval> *x,
                  std::vector<node<Tkey,Tval> *> &vec) {
      if(x == nullptr) return;
      postorder(x->left, vec);
      postorder(x->right, vec);
      vec.push_back(x);
   }

   /* Recursive Level Order traversal - Given a level get   *
    * all nodes in that level.                              *
    * @param rt  - root node of current sub-tree            *
    * @param vec - output vec to populate nodes @ level     *
    * @param level - 1-based level number                   */
   void levelorder(node<Tkey,Tval> *rt, std::vector<node<Tkey,Tval> *>
                   &vec, unsigned level) {
      if(rt == nullptr || level < 1) return;
      else if(level == 1) vec.push_back(rt);
      else {
         levelorder(rt->left, vec, level-1);
         levelorder(rt->right, vec, level-1);
      }
   }

   /* Iterative BFS (level-order) traversal of all the      *
    * nodes and returns all the node pointers in a vector.  *
    * Note: Using a head and tail index, we can avoid the   *
    * queue, but in interest of keeping code readable, use q*/
   void bfs(node<Tkey,Tval> *rt, std::vector<node<Tkey, Tval> *> &vec) {
      /* Temporary queue to go over all elements           */
      std::queue<node<Tkey, Tval> *> q;
      /* max# nodes = 2^h - 1 (h = 1 based height)         */
      //unsigned max_nodes = std::pow(2, calc_height(rt)) - 1;
      if(rt == nullptr) return;
      q.push(rt);
      while(q.empty() == false) { /* Visit each element once */
         auto x = q.front();  /* BFS = Queue traversal    */
         q.pop();
         /* If leaf element, dont go any further          */
         if(x && is_leaf(x) == false) {
            q.push(x->left);
            q.push(x->right);
         }
         /* After adding all children to q, x -> output   */
         vec.push_back(x);
      }
   }

   /* Iterative spiral-order traversal of all nodes with    *
    * the help of two stacks. This function returns all     *
    * node pointers in a vector                             *
    * Time Complexity = O(n)                                *
    * Space Complexity = O(2^h) (h = height(0 based))       *
    * space complexity is to accomodate  max # nodes that   *
    * each stack would have to hold = maximum possible      *
    * number of leaf nodes                                  */
   void spiralorder(node<Tkey,Tval> *rt,
                    std::vector<node<Tkey,Tval> *> &vec) {
      /* Temporary stack to go over L2R and R2L elements   */
      std::stack<node<Tkey, Tval> *> l2r, r2l, *q1, *q2;
      if(rt == nullptr) return;
      l2r.push(rt);
      q1 = &l2r;
      q2 = &r2l;
      /* Visit each element once and use 2 stacks and LIFO *
       * ordering to change direction across levels        */
      while(l2r.size() != 0 || r2l.size() != 0) {
         while(q1->empty() == false) {
            auto x = q1->top();
            q1->pop();
            if(x == nullptr) continue;
            /* If leaf element, dont go any further      */
            if(is_leaf(x) == false) {
               if(q1 == &l2r) {
                  q2->push(x->right); q2->push(x->left);
               }
               else {
                  q2->push(x->left);  q2->push(x->right);
               }
            }
            /* After adding all children to q, x->output */
            vec.push_back(x);
         }
         /* Toggle queues after iterating over each queue */
         if(q1 == &l2r) { q1 = &r2l; q2 = &l2r; }
         else           { q1 = &l2r; q2 = &r2l; }
      }
   }

   /* Recursive bottom-up order traversal of all nodes.     *
    * This function returns all node pointers in a vector   */
   void bottomuporder(node<Tkey,Tval> *rt,
                      std::vector<node<Tkey,Tval> *> &vec) {
      auto nlevels = height();
      /* Go from last level to first level, get all nodes  */
      for (int level = nlevels; level >= 1; level--)
         levelorder(rt, vec, level);
   }
		
   /* Given a traversal order, traverse nodes and get keys  */
   std::vector<Tkey> key_traversal(Traversal t) {
      std::vector<Tkey> keys;
      std::vector<node<Tkey, Tval> *> nodes;
      if     (t == Traversal::PREORDER)      preorder(root, nodes);
      else if(t == Traversal::INORDER)       inorder(root, nodes);
      else if(t == Traversal::POSTORDER)     postorder(root, nodes);
      else if(t == Traversal::BFS)           bfs(root, nodes);
      else if(t == Traversal::SPIRALORDER)   spiralorder(root, nodes);
      else if(t == Traversal::BOTTOMUPORDER) bottomuporder(root, nodes);
      for (auto x : nodes) {
         if(x)                               keys.push_back(x->key);
         else                                keys.push_back(-1);
      }
      return keys;
   }

   /* Pretty print BT. Time Complexity = O(n lg n)          *
    * Straightforward logic:                                *
    *    = Row #: Depth of node                             *
    *    = Col #: In-order Traversal idx                    *
    * Output can be made more "pretty"/aligned by tweaking  *
    * In-order traversal to keep track of ghost nodes (i.e) *
    * if left node is present & right node absent, account  *
    * right node in column number calculation               */
   void pretty_print(unsigned width=4) {
      int print_row = 0, print_col = 0; 
      if(root == nullptr) return;
      
      std::vector<node<Tkey, Tval> *> inorder_nodes, bfs_nodes;
      /* 1) Do BFS traversal to get row#                   */
      bfs(root, bfs_nodes);
      for(auto x: bfs_nodes)
         if(x) x->loc.first = depth(x);
      
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

   /* BT_ONLY - Find first node that has the key.           */
   node<Tkey,Tval> *find(node<Tkey,Tval> *rt, Tkey key) {
      auto x = rt;
      if(x == nullptr || x->key == key)     return x;
      else if((x = find(rt->left, key)))    return x;
      else if((x = find(rt->right, key)))   return x;
      else                                  return nullptr;
   }

   /* BT_ONLY - Recursive find all keys implementation.     *
    * Returns bool to indicate success/fail and also        *
    * populates a vector of values                          */
   bool find(node<Tkey,Tval> *x, Tkey key, std::vector<Tval> *valvec) {
      bool ret = false;
      if(x == nullptr)                             return ret;
      if(x->key == key)  {
         if(valvec) valvec->push_back(x->val);
         ret = true;
      }
      ret |= find(x->left, key, valvec);
      ret |= find(x->right, key, valvec);
      return ret;
   }

   /* BT_ONLY - Find lowest common parent given 2 nodes     *
    * Two possible cases:                                   *
    * - If a is parent of b, return a. This is accomplished *
    *   by returning a as soon as we find it and no other   *
    *   node will reply back.                               *
    * - If a and b occur in two different branches, then the*
    *   first node that has both left and right sub-tree set*
    *   is the LCP. All other nodes are parent nodes are    *
    *   ancestors, they will just pass on LCP result        */
   node<Tkey,Tval> *find_lcp(node<Tkey,Tval> *cur, node<Tkey,Tval> *a,
                             node<Tkey,Tval> *b) {
      if(cur == nullptr)            return nullptr;
      else if(cur == a || cur == b) return cur;
      
      /* Search for a and b in both left & right sub-tree  */
      auto left  = find_lcp(cur->left, a, b);
      auto right = find_lcp(cur->right, a, b);
      
      /* If both left & right trees have a, b, then this   *
       * node is the LCP. Return this node                 */
      if(left && right)             return cur;
		
      /* If both left and right are not set, either a, b   *
       * do not occur in subtree or this node is ancestor  *
       * in either case, pass on result from left/right    */
      else if(left)                 return left;
      else                          return right;
   }

   /* BT_ONLY - Get Parent node of given node 'x'           */
   node<Tkey,Tval> *get_parent_node(node<Tkey,Tval> *parent,
                                    node<Tkey,Tval> *x) {
      if(parent == nullptr)                        return parent;
      else if(parent->left==x || parent->right==x) return parent;
      auto y = get_parent_node(parent->left, x);
      if(y == nullptr)
         y = get_parent_node(parent->right, x);
      return y;
   }

   /* BT_ONLY - Insert while trying to maintain a perfect BT*/
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

   /* BT_ONLY - Delete **all** occurences of this key       *
    * Follow Hibbard deletion condition to del current node *
    * 3 possibile cases:                                    *
    * 0 child: Set parent link to null and update cnts      *
    * 1 child: Set parent link to other child + update cnts *
    * 2 child: Replace current node with another node from  *
    *        : subtree starting at this node + update cnts  *
    *        : For BT chose node from deepest subtree       *
    *        : For BST chose min node from subtree          */
   node<Tkey,Tval> *del(node<Tkey,Tval> *x, Tkey key) {
      if(x == nullptr)        return x;
      x->left  = del(x->left, key);
      x->right = del(x->right, key);
      if(x->key == key) {
         auto old_x = x;
         /* Takes care of 1st 2 cases of Hibbard Deletion */
         if     (x->right == nullptr) x = x->left;
         else if(x->left  == nullptr) x = x->right;
         /* Takes care of 3rd case of Hibbard Deletion    */
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

   /* @brief Uses pre-order traversal to serialize the BT   *
    * @param x   - current node to serialize                *
    * @param ser - String which holds serialized values     *
    * @param tok - inter-value token (optional parameter)   *
    * Note: BT val should be serializable (via sstream) and *
    * should not contain tok.                               */
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

private:
   unsigned ins_cnt;
   unsigned del_cnt;
   unsigned dup_ins_cnt;
   node<Tkey, Tval> *root;
};

template<typename Tkey, typename Tval>
std::ostream& operator<<(std::ostream& os, binary_tree<Tkey, Tval>& bin) {
   bin.pretty_print();
   os << std::endl;
   //os << x.key << ':' << x.val ;
   return os;
}

} //end namespace
