#include <algorithm>           /* std::max    */

template<typename Tkey, typename Tval>
class node
{
public:
node(Tkey k, Tval v) :
	key(k), val(v), left(nullptr), right(nullptr), cnt(1){}
	Tkey key;          /* node's key             */
	Tval val;          /* node's val             */
	class node *left;  /* left branch            */
	class node *right; /* right branch           */
	unsigned cnt;      /* number of children + 1 */
};

template<typename Tkey, typename Tval>
std::ostream& operator<<(std::ostream& os, const node<Tkey, Tval>& x)
{
	os << x.key << ':' << x.val ;
	return os;
}


template<typename Tkey, typename Tval>
class binary_tree{
public:
    binary_tree(): ins_cnt(0), del_cnt(0), dup_ins_cnt(0), root(nullptr){}
	unsigned calc_size(){ return calc_size(root);   }
	int calc_height()   { return calc_height(root); }
	node<Tkey, Tval>* get_root() {return root;      }
    /* Get #keys in BT. Time Complexity = O(1)                       */
	unsigned get_size() {
		if(root == nullptr) return 0;
		else   			    return root->cnt;
	}

    /* Calculate #Keys after Insert/Del. Time Complexity = O(1)      */
	unsigned calc_size(node<Tkey, Tval> *x) {
		return (1 + calc_size(x->left) + calc_size(x->right));
	}

    /* Get #Levels in BT(zero-based).  Time Complexity = O(lg n)     */
	int calc_height(node<Tkey, Tval> *x)
	{
		if(x == NULL) return -1;
		else
			return (1 + std::max(bst_height_api(x->left),
								 bst_height_api(x->right)));
	}
	
	/* Check if given node is the root-node                          */
	bool is_root(node<Tkey, Tval> *x)
	{
		if(get_root() && get_root() == x) return true;
		else                              return false;
	}

	bool is_leaf(node<Tkey, Tval> *x)
	{
		if(x->left == nullptr && x->right == nullptr) return true;
		else                                          return false;
	}
private:
	unsigned ins_cnt;
	unsigned del_cnt;
	unsigned dup_ins_cnt;
	node<Tkey, Tval> *root;
};



