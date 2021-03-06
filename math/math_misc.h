#ifndef _MATH_MISC_CPP
#define _MATH_MISC_CPP
#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <cstdint>           /* uint8_t                      */
#include <sstream>           /* std::stringstream            */

namespace math {

/* Calculate (base ^ exp) % modulus; This is based on        *
 * Applied Cryptography by Bruce Schneier (Stackoverflow)    *
 * http://stackoverflow.com/questions/8496182/calculating-powa-b-mod-n *
 * Wiki notes -  http://en.wikipedia.org/wiki/Modular_exponentiation   */
template <typename T1=int, typename T2=unsigned int>
T1 modpow(T1 base, T2 exp, T1 modulus) {
   STATIC_ASSERT_TYPE_UINT_ULONG(T2); /* ensure T2 unsigned  */
   base %= modulus;
   T1 result = 1;
   for(;exp > 0; exp /= 2) {
      if (exp & 1) /* If exp is odd, multiply res with base  */
         result = (result * base) % modulus;
      base = (base * base) % modulus;
   }
   return result;
}
 
/*------------- Big integer multiplication (start) ----------*/
/* In LE Machine order, we need to print in reverse order of *
 * computation.                                              */
template<typename T1=uint8_t>
static inline std::string bigint_print(std::vector<uint8_t> &bigint) {
   std::stringstream ss;
   /* unsigned typecast is required mainly for uint8_t type  */
   for(int i = bigint.size()-1; i >= 0; i--)
      ss << unsigned(bigint[i]);
   return ss.str();
}

/* Multiply a regular integer (unsigned/int/long/etc) to a   *
 * previously stored big-integer. This can even be 1         *
 * The result is stored in the input bigint itself           */
template<typename T1=uint8_t, typename T2=unsigned, unsigned base=10>
static inline void bigint_multiply(std::vector<T1> &res, T2 mul) {
   unsigned i = 0, carry = 0;  /* Initialize carry and loop  */
   for(i = 0; i < res.size(); ++i) {
      T2 prod = res[i] * mul + carry;
      res[i]  = prod % base;  /* Store last # in vector      */
      carry   = prod / base;  /* Update carry accordingly    */
   }
   /* Add Carry to end of result vector                      */
   for(; carry; carry /= base)
      res.push_back(carry % base);
}

/* Create & return a Bigint datatype given a regular integer */
template<typename T1=uint8_t, typename T2=unsigned>
static inline std::vector<T1> bigint(T2 val) {
   std::vector<T1> v {1};
   bigint_multiply(v, val);
   return v;
}
/*------------- Big integer multiplication (start) ----------*/

} //end namespace math

#endif //_MATH_MISC_CPP
