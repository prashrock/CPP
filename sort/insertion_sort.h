#ifndef _INSERTION_SORT_CPP_
#define _INSERTION_SORT_CPP_
#include <iostream>       /* std::cout               */
#include <iomanip>        /* std::setw               */
#include <algorithm>      /* std::vector             */
#include <vector>         /* std:vector              */

namespace sort
{

/* Insertion sort - For each element make sure its greater than prev elem  *
 * + Best case = Array already sorted, n-1 compares and 0 exchanges        *
 * - Worst case = Array in descending order, n^2/2 comps and n^2/2 xchgs   *
 * + For partially sorted arrays, Insertion sort runs in linear time       *
 * Impl inspired by http://hgad.net/posts/stl-algorithms-in-action/        *
 * Time Complexity  = O(n^2)                                               *
 * Space Complexity = O(1)                                                 *
 * Best for         = Partially sorted arrays                              */
template<typename T=int>
static inline void insertion_sort(typename std::vector<T>::iterator begin,
                                  typename std::vector<T>::iterator end) {
   auto&& size = std::distance(begin, end);
   if(size < 2) return;    /* If 0 or 1 elems, don't sort                  */
   /* For each pos find out biggest value in [0, it) swap and move elems   */
   for (auto&& it = std::next(begin); it != end; ++it) {
      auto big_it = std::upper_bound(begin, it, *it); /* big_prev @ [0,it) */
      /* put smaller value (it) in correct place big_it next and move rest *
       * Example of rotate usage                                           *
       * Input = 1   6   3   4   5   2   7 (rotate @ 5 (0-based idx) gives)*
       * Output= 1   2   6   3   4   5   7 (note, higher # is imm after 2) */
      std::rotate(big_it, it, std::next(it)); 
   }
}

#if 0
   for(int i = 0; i < n; i++) {
      for(int j = i; j > 0; j--)  /* if (objs[j] < objs[j-1]) */
         if(cmp(&objs[j], &objs[j - 1]))
            SWAP(objs[j], objs[j - 1]);
         else break;
   }
#endif

}  //end namespace
   
#endif //_INSERTION_SORT_CPP_
