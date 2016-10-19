#ifndef _MATH_SHUFFLE_CPP
#define _MATH_SHUFFLE_CPP
#include <iostream>          /* std::cout                    */
#include <cmath>             /* pow                          */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <random>            /* std:default_random_engine    */
#include "compiler_api.h"    /* Type check asserts           */
#include "rand_generator.h"  /* get_rand()                   */

namespace math
{

/* @brief Knuth Shuffle implementation to shuffle objects    *
 * Reverse loop + random access = cache inefficient algorithm*
 * @note: There are nPn(n!) permutations (without repetition)*
 * For each iter, if we pick a random number inbetween [0, n)*
 * then algo is incorrect as it gives n^n permutations       *
 * Check Algo (Random) notes for more details                */
template<typename T=int>
static inline void shuffle(std::vector<T>& inp) noexcept {
   if(inp.size() == 0) return;      /* Handle 0 size vectors */
   const size_t N = inp.size();
   for(size_t i = N; i > 1; --i) {  /*consider using uint32_t*/
      const auto j = get_rand(i);      /* 0 <= j < i         */
      std::swap(inp[i - 1], inp[j]);
   }
}

/* Note: Refer to Daniel Lemire's blog for a perf comparison *
 * between STL shuffle and a hand-written version @          *
 * http://lemire.me/blog/2016/10/10/a-case-study-in-the-performance-cost-of-abstraction-cs-stdshuffle/                                                    */
 
} //end namespace
#endif //_MATH_SHUFFLE_CPP
