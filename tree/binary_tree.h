#include <algorithm>           /* std::max                   */

namespace bt
{
	
template<typename Tkey=int, typename Tval=int>
class node
{
public:
node(Tkey k, Tval v) :
	key(k), val(v), left(nullptr), right(nullptr), cnt(1){}
~node() { //kp_cnt++; //std::cout << "del " << key << std::endl;
		  left = nullptr; right = nullptr; key = 0;}
	Tkey key;          /* node's key                         */
	Tval val;          /* node's val                         */
	class node *left;  /* left branch                        */
	class node *right; /* right branch                       */
	unsigned cnt;      /* number of children + 1             */
};

template<typename Tkey, typename Tval>
std::ostream& operator<<(std::ostream& os, const node<Tkey, Tval>& x)
{
	os << x.key << ':' << x.val ;
	return os;
}

template<typename Tkey=int, typename Tval=int>
class binary_tree{
public:
    binary_tree(): ins_cnt(0),del_cnt(0),dup_ins_cnt(0),root(nullptr){}
    unsigned size()     { return get_size(root);    }
    unsigned height()   { return calc_height(root); } /* 1-based */
	node<Tkey, Tval>* get_root() {return root;      }
    void ins(Tkey key, Tval val) { root = ins(root, key, val); }
    void del(Tkey key)           { root = del(root, key); }

	/* Check if given node is the root-node                  */
	bool is_root(node<Tkey, Tval> *x)
	{
		if(get_root() && get_root() == x) return true;
		else                              return false;
	}

	/* Check if given node's left and right child is null    */
	bool is_leaf(node<Tkey, Tval> *x)
	{
		if(x->left == nullptr && x->right == nullptr) return true;
		else                                          return false;
	}

    /* Get #keys in BT. Time Complexity = O(1)               */
	unsigned get_size(node<Tkey, Tval> *x) {
		if(x == nullptr) return 0;
		else   			 return x->cnt;
	}

    /* Calculate #Keys after Ins/Del. Time Complexity = O(1) */
	unsigned calc_size(node<Tkey, Tval> *x) {
		if(is_leaf(x))   return 1;
		else return (1 + get_size(x->left) + get_size(x->right));
	}

    /* Get #Levels in BT(zero-based). Time Complexity=O(lg n)*
	 * This logic can be slightly modified to achieve tail   *
	 * recursion, but keeping as such for easy readability   */
	int calc_height(node<Tkey, Tval> *x)
	{
		if(x == nullptr) return 0;
		else
			return (1 + std::max(calc_height(x->left),
								 calc_height(x->right)));
	}
	
    /* Get the deepest leaf node in the entire Binary Tree   *
	 * This is an attempt to keep a check on height of BT    */
    node<Tkey,Tval> *get_deepest_leaf_node(node<Tkey,Tval> *x)
    {
		if(x == nullptr || is_leaf(x)) return x;
		else if(x->left == nullptr)
			return get_deepest_leaf_node(x->right);
		else
			return get_deepest_leaf_node(x->left);
	}

    /* BT_ONLY - Get Parent node of given node 'x'           */
    node<Tkey,Tval> *get_parent_node(node<Tkey,Tval> *parent,
									 node<Tkey,Tval> *x)
    {
		if(parent == nullptr)                        return parent;
		else if(parent->left==x || parent->right==x) return parent;
		auto y = get_parent_node(parent->left, x);
		if(y == nullptr)
			 y = get_parent_node(parent->right, x);
		return y;
	}

    /* BT_ONLY - Insert while trying to maintain a perfect BT*/
    node<Tkey,Tval> *ins(node<Tkey,Tval> *x, Tkey key, Tval val)
    {
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
										 node<Tkey,Tval> *del)
    {
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
    node<Tkey,Tval> *del(node<Tkey,Tval> *x, Tkey key)
    {
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

private:
	unsigned ins_cnt;
	unsigned del_cnt;
	unsigned dup_ins_cnt;
	node<Tkey, Tval> *root;
};

} //end namespace
