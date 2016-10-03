#ifndef _BINARY_INDEXED_TREE_DS_
#define _BINARY_INDEXED_TREE_DS_
#include <algorithm>           /* std::max                   */
#include <vector>              /* std:vector                 */

/* Defines a Binary Indexed Tree (BIT) aka Fenwick Tree      *
 * A BIT only stores meta information for each index of the  *
 * original dataset. With this meta information following ops*
 * can be performed in O(log n) instead of O(1)/O(n) time:   *
 * - Point Update  : e.g., add value 'v' at position 'idx'   *
 * - Point GetVal  : e.g., get value 'v' at position 'idx'   *
 * - Cumul GetSum  : e.g., sum of nodes in range [0, e]      *
 * - Range GetSum  : e.g., sum of nodes in range [b, e]      *
 * Note:                                                     *
 * - Not Multi-Thread safe and cannot change size dynamically*
 * - Need to implement Range update (need 2 index trees)     *
 * - Inspired by http://codesay.blogspot.com/2014/03/fenwick-trees-bit-index-tree-easy-way.html
 * - Inspired by https://www.youtube.com/watch?v=CWDQJGaN1gY */

template<typename Tval=int>
class bin_idx_tree {
public:
   /* Two constructors - BIT(size), BIT(val_vector)          */
   bin_idx_tree(size_t sz): n(sz), tree(n + 1, 0) { }
   bin_idx_tree(std::vector<Tval> v): bin_idx_tree(v.size()) {
      for(size_t i = 0; i < n; ++i) update(i, v[i]);
   }
   /** @brief Returns the number of elements in BIT          *
    *  Time Complexity = O(1)                                */
   size_t size() const { return n; }
   /** @brief Update/Add value(val) at single position(idx)  *
    * @param idx = 0-based tree index, val = value to store  *
    * Time Complexity = O(lg n)                              */
   inline void update(size_t idx, Tval val) {
      for(idx += 1; idx <= n; idx += lsb(idx))
         tree[idx] += val; /* Add val to current node in BIT */
   }
   /** @brief Calculate cumulative sum of nodes in [0, idx]  *
    * @param idx = 0-based tree index                        *
    * Time Complexity = O(lg n)                              */
   inline Tval getSum(size_t idx) {
      Tval sum = 0;
      for(idx += 1; idx > 0; idx -= lsb(idx))
         sum += tree[idx]; /* Add current val to sum         */
      return sum;
   }
   /** @brief Calculate cumulative sum of nodes in [b, e]    *
    * @param b, e = 0-based indexes                          *
    * Time Complexity = O(2 * lg n)                          */
   inline Tval getSum(size_t b, size_t e) {
      return (getSum(e) - getSum(b - 1));
   }
   /** @brief Get point value stored at idx (not cumulative) *
    * @param idx = 0-based tree index                        *
    * Time Complexity = O(2 * lg n)                          */
   inline Tval getVal(size_t idx) {
      return (getSum(idx) - getSum(idx - 1));
   }
   friend std::ostream& operator<<(std::ostream& os, bin_idx_tree<Tval>& b) {
      os << std::setw(6) << "IDX"     << "   ";
      os << std::setw(6) << "VAL"     << "   ";
      os << std::setw(6) << "BIT_SUM" << "   " << std::endl;
      for(size_t i = 0; i < b.n; ++i) {
         os << std::setw(6) << i            << "   ";
         os << std::setw(6) << b.getVal(i)  << "   ";
         os << std::setw(6) << b.getSum(i)  << "   ";
         os << std::endl;
      }
      os << std::setw(0) << std::endl;
      return os;
   }
private:
   size_t n;
   std::vector<Tval> tree; /* internally use 1 based idx     */
   /* Get the LSB value of a given number n                  */
   inline size_t lsb(size_t n) {return (n & -(n)); }
};


#endif //_BINARY_INDEXED_TREE_DS_
