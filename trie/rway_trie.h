#ifndef _CPP_TRIE_RWAYTRIE_H_
#define _CPP_TRIE_RWAYTRIE_H_
#include <algorithm>           /* std::max                   */
#include <bitset>              /* std:bitset                 */

/**
 * R-way Trie class is a Trie ST impl of key-value pairs.    *
 * It supports get(),put(),del(),contains(),size() API's.    *
 * This Symbol Table interface does not allow duplicate keys *
 * In the event of duplicates old value gets replaced.       *
 * - For flexibility, this is an n-Way trie (n default=256)  *
 *   and the key and value types are configurable            *
 * - The root node resides in stack while rest of the nodes  *
 *   reside in heap with default vector allocator            *
 * Note: Not multi-thread safe (client responsibility)       */
namespace rw_trie
{

/* R-way Trie Node class (Node management layer)             */
template<typename Tval, unsigned R=256>
class node
{
public:
     node() : bmp(), next(0), hasval(false) {}
    ~node() { next.clear(); }
    size_t get_num_branches() { return bmp.count();  }
    bool has_val()            { return hasval;       }
    /* Insert a child node @ current node. Note, for first   *
	 * insert, next vector needs initialization. Subsequent  *
	 * inserts involve merely setting a bit in the bitmap    *
	 * @param pos - position idx [0, R) for insert           *
	 * @return node - child node @ pos. Useful for traversal */
    node<Tval, R> *put(unsigned pos)
    {
		/* Resize when current node's next vector length = 0 */
	    if(next.size() == 0)  next.resize(R);
		if(pos >= R)    return nullptr;    /* Invalid index  */
		bmp[pos] = true;     /* Bitmap tracks #active paths  */
		return &next[pos];   /* Return node we just put      */
    }
    /* Get the child node given a position (r-way position)  *
	 * @param pos - position idx [0, R) of child node        *
	 * @return node - child node @ pos. Useful for traversal */
    node<Tval, R> *get(unsigned pos)
    {
	    if(pos >= R)   return nullptr;    /* Invalid index   */
    	if(bmp[pos])   return &next[pos]; /* Valid Vector    */
    	else           return nullptr;    /* Invalid Vector  */
    }
    /* Delete child at given position (only at this node)    *
	 * @param pos   - position idx [0, R) of child node      *
	 * @return bool - status of the delete operation         */
    bool del(unsigned pos)
    {
	    if(pos >= R)   return false;      /* Invalid index   */
        /* If child at pos is unused, then nothing to delete */ 
		if(!bmp[pos])  return false; /* Bitmap pos validate  */
		else           bmp[pos] = false;  /* Clear bitmap    */
		/* If there are no other paths, resize the vector    */
		if(!get_num_branches()) next.resize(0);
		return true;
    }
    /* Get the value stored at current node                  *
	 * @param   val - Reference of val from client           *
	 * @return bool - true:cur_node has val, false:otherwise */
    bool get_val(Tval &val){
	    if(hasval)    val = this->val;
    	return hasval;
    }
    /* Store value @ current node (overwrite if required)    *
	 * @param   val - Reference of val from client           */
    void put_val(const Tval &val) {
		this->val = val;
    	hasval   = true;
	}
    /* Delete value @ current node.                          */
    bool del_val() {
		if(hasval) {hasval = false; return true;}
		else         return false;
	}
private:
    Tval val;            /* node's value - only if end-node  */
    std::bitset<R> bmp;  /* track number of active r-ways    */
    std::vector<node<Tval, R>> next; /* r-way key list-heap  */
    bool hasval;         /* indicate if this key has a value */
};

/* R-way Trie class                                          */
template<typename Tkey, typename Tval, unsigned R=256>
class rway_trie
{
public:
    rway_trie(): root(), n(0){} /* RWay Trie Constructor     */
    /* Given a key, find its corresponding value from ST     *
	 * @param   key - Key (string, vector, etc)              *
	 * @param   val - Ref to store val of key (if key found) *
	 * @return bool - true:key found, false:key not found    */
    bool get(Tkey k, Tval &val)
    {
   	    unsigned i;
	    auto *node = &root;
	    /* Run for loop for length of the key or till there  *
	     * is a valid trie node.                             */
  	    for(i = 0; i < k.size() && node->get_num_branches() > 0; ++i)
	    {
	    	unsigned idx = static_cast<unsigned>(k[i]);
		    node = node->get(idx);
		    /* If no node, dead end, return immediately      */
    		if(node == nullptr) goto not_found;
	    }
    	/* If we've covered all elements in key and there is *
	     * a valid value in last node node, key in Trie      */
    	if(i == k.size()) {
	    	return node->get_val(val);
    	}
    not_found:
	    return false;
	}
    /* Store/overwrite val for given key in ST (key=unique)  *
	 * @param   key - Key (string, vector, etc)              *
	 * @param   val - val to store for this particular key   */
    void put(Tkey k, const Tval &val)
    {
		unsigned i;
		auto *node = &root;
		/* Run for loop for length of the key                */
		for(i = 0; i < k.size() && node; ++i) {
			unsigned idx = static_cast<unsigned>(k[i]);
			node = node->put(idx); /* return child node *    */
		}
		node->put_val(val); /* Store value in the last node  */
	}
    bool del(Tkey k, node<Tval, R> *node, unsigned pos)
    {
		bool ret = true;
		if(node == nullptr)   return false;
		unsigned idx        = static_cast<unsigned>(k[pos]);
		auto *child         = node->get(idx);
		if(pos == k.size())   ret = node->del_val();
		else                  ret = del(k, child, pos + 1);
		if(ret && child && child->get_num_branches() == 0 &&
		   node->has_val() == false)
				ret = node->del(idx);
		return ret;
	}
    bool del(Tkey k)   { return del(k, &root, 0); }
    /* Calculate #Active Paths in this Trie DS               */
    size_t calc_size() { return 0; }
private:
    node<Tval, R> root;   /* Root of the trie - in stack     */
    unsigned  n;          /* Number of keys in trie          */
};

/* << operator implemented for class node                    */
template<typename Tkey, typename Tval>
std::ostream& operator<<(std::ostream& os, const node<Tval>& x)
{
	os << x.val ;
	return os;
}


} //Namespace end

#endif //_CPP_TRIE_RWAYTRIE_H_
