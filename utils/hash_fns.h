#ifndef _HASH_FNS_CPP_
#define _HASH_FNS_CPP_

/* Simple Rolling Hash function.                             *
 * Uses Horner's method (Linear time method to evaluate poly)*
 * @param inp   - Input vector/string whose hash to calculate*
 * @param radix - Base (10 for integer, 256 for extd ASCII)  *
 * @param prime - Prime number(hash range = [0, prime])      */
template<typename T=std::string, typename Tret=unsigned long>
static inline Tret rolling_hash(T inp, unsigned radix=256, Tret prime=1009)
{
   Tret h = 0;
   for(size_t i = 0; i < inp.size(); ++i)
      h = (h * radix + inp[i]) % prime;
   return h;
}

#endif //_HASH_FNS_CPP_
