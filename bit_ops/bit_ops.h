#ifndef _BITOPS_CPP_
#define _BITOPS_CPP_

#include <algorithm>           /* std::max                   */
#include <vector>              /* std:vector                 */
#include <cstring>             /* memset                     */
#include <climits>             /* CHAR_BIT                   */
#include <bitset>              /* std::bitset (dump)         */
#include <type_traits>         /* std::is_same               */
#include "compiler_api.h"      /* Type check asserts         */

/* Points to remember                                                  *
 * = In C, shift more than BITS_PER_LONG-1 is undefined                *
 * = Below Equality can help calc floor((x+y)/2) without overflow      *
 *   (x + y) == ((x & y) + (x | y)) == ((x ^ y) + 2 * (x & y))         *
 * = Generate 0 on success, -1 on failure (any err# x)                 *
 *   (((int) (x | -x)) >> (WORDBITS - 1))                              *
 * = Generate 0 on success, 1 on failure (any err# x)                  *
 *   (((unsigned int) (x | -x)) >> (WORDBITS - 1))                     *
 * = Implement Bitwise XOR(^) without using the ^ operator             *
 *   (x ^ y) is the same as (~x & y) | (x & ~y)                        *
 * = Given 2's complement int (x,y), find minimum and maximum of both  *
 *   integers, without branch, assuming right shift extends sign bit   *
 *   Min(x, y) => x + ( ((y-x)>>(WORDBITS-1)) & (y-x) )                *
 *   Max(x, y) => x - ( ((x-y)>>(WORDBITS-1)) & (x-y) )                *
 * = Given 2's comp int (x,y), implement ternary condition (?) operator*
 *   without branch, assuming rt shift extends sign (not portable in C)*
 *   (a<b)?x=c:x=d => x = ( ( ((a-b) >> (WORDBITS-1)) & (c^d) ) ^ d)   *
 */

namespace bit_ops
{
   
/* --------------------------------------------------------- */
/* Determine if n is a power of two (return true/false)      */
template<typename T=int>
static inline bool isPow2(const T n) noexcept {
   STATIC_ASSERT_TYPE_INTEGRAL(T);
   return((n != 0) && ((n & (n - 1)) == 0));
}
/* test if x is Even or Odd - Works for all integers (Z)     */
template<typename T=int>
static inline bool isEven(const T n) noexcept {
   STATIC_ASSERT_TYPE_INTEGRAL(T);
   return ((n & 1) == 0);
}
template<typename T=int>
static inline bool isOdd(const T n) noexcept { return !isEven(n); }
/* --------------------------------------------------------- */
/* Following Bit Ops use 0 based bit-position idx            *
 * and work for all integers (Z - scale)                     *
 * If left shift operand causes value bigger than width of   *
 * operand, the operation is undefined (dont do 1 << -1)     */
template<typename T=int>
static inline void bitSet(T& n, uint8_t pos_zb) noexcept {
   STATIC_ASSERT_TYPE_INTEGRAL(T);
   n |= (T)1 << pos_zb;
}
template<typename T=int>
static inline void bitReset(T& n, uint8_t pos_zb) noexcept {
   STATIC_ASSERT_TYPE_INTEGRAL(T);
   n &= ~((T)1 << pos_zb);
}
template<typename T=int>
static inline void bitToggle(T& n, int pos_zb) noexcept {
   STATIC_ASSERT_TYPE_INTEGRAL(T);
   n ^= ((T)1 << pos_zb);
}
 
/* --------------------------------------------------------- */
/* @brief   Calculate the population count of bitstream      *
 * Calc #set 1's (Hamming Weight of bitstream) in const time *
 * The core idea is to do a parallel sum of bits:            *
 * - 1st statement sums up individual 1's with bitmask 0101  *
 * - 2nd sums up 2 bits at a time with bitmask 0011          *
 * - Continue this till total sum is reached == bit-count    *
 * This approach is better than O(lg n) Kernighan approach   *
 * which uses (n &= n - 1) to calculate population count     *
 * @note Works for +/- integers                              */
template<typename T=int>
static inline T bitPopCnt(const T inp) noexcept {
   STATIC_ASSERT_TYPE_INT_UINT(T); /* Do not allow 64-bit int*/
   typedef typename std::make_unsigned<T>::type Tu;
   Tu n = static_cast<Tu> (inp);
   n = (n & 0x55555555) + ((n >> 1) & 0x55555555); //Accumulate 1 bit
   n = (n & 0x33333333) + ((n >> 2) & 0x33333333); //Accumulate 2 bits
   n = (n & 0x0F0F0F0F) + ((n >> 4) & 0x0F0F0F0F); //Accumulate 4 bits
   n = (n & 0x00FF00FF) + ((n >> 8) & 0x00FF00FF); //Accumulate 8 bits
   n = (n & 0x0000FFFF) + ((n >>16) & 0x0000FFFF); //Accumulate 16 bits
   return static_cast<T> (n);
}
/* --------------------------------------------------------- */   
/* @brief Calculate the floor average value without divide   *
 * @note  Gives correct ans even if x + y does not fit in T  *
 * @note  If x > y, then this is equivalent to y + ((x-y)/2) *
 * @return (x + y)/2                                         */
template<typename T=int>
constexpr T avg(const T x, const T y) noexcept {
   STATIC_ASSERT_TYPE_INTEGRAL(T);
   /* Use x+y = carry + sum_without_carry =((x&y)<<1)+(x^y)) */
   return (x & y) + ((x ^ y) >> 1);
}
/* @brief Calculate absolute integer given + or -ve integer  *
 *        abs{x} = !(x) + 1                                  *
 * Use the property that -1 >> n will still be -1            */
template<typename T=int>
static inline typename std::make_unsigned<T>::type abs(T n) noexcept {
   STATIC_ASSERT_TYPE_INTEGRAL(T);
   typedef typename std::make_unsigned<T>::type Tu;
   const Tu nbits = ((sizeof(T) * CHAR_BIT) - 1);
   /* nmask is all 1's if n is -ve or 0 if n is +ve          *
    * nmask is basically -1 (in 2s complement) if n is -ve   *
    * Need a shift to set nmask = -1 to avoid if(-ve) branch */
   const Tu nmask = n >> nbits;
   /* Below applies 2's complement only for -ve numbers      *
    * Use XOR(0xFF..) for NOT operator and -(-1(0xFF..))=+1  */
   return (static_cast<Tu>(n ^ nmask) - nmask);
}
/* --------------------------------------------------------- */
/* @brief Swap adjacent 'WIDTH' bit blocks (from LSB to MSB) *
 * @note  e.g. bit_swap<1>(010011) = 100011                  *
 * @note  Compiler should be able to calc result@compile time*/
template<typename T=int, uint8_t WIDTH=1>
static inline T bitSwap(const T x) noexcept {
   STATIC_ASSERT_TYPE_INT_UINT(T); /* Do not allow 64-bit int*/
   typedef typename std::make_unsigned<T>::type Tu;
   typename std::make_unsigned<T>::type m;
   if(WIDTH == 1)        m = 0x55555555U; /* compile time if */
   else if(WIDTH ==  2)  m = 0x33333333U;
   else if(WIDTH ==  4)  m = 0x0F0F0F0FU;
   else if(WIDTH ==  8)  m = 0x00FF00FFU;
   else if(WIDTH == 16)  m = 0x0000FFFFU;
   else                  m = 0;
   return ((x & m) << WIDTH) | ((Tu)(x & (~m)) >> WIDTH);
}
/* @brief Reverse all bits (rotate all bits) in given number *
 * @note  e.g. bit_reverse(00110111) = 11101100              *
 * @note  reverse operates in byte boundaries                *
 * @note  Compiler should be able to calc result@compile time*/
template<typename T=int, uint8_t WIDTH=32>
static inline T bitReverse(T x) noexcept {
   STATIC_ASSERT_TYPE_INT_UINT(T); /* Do not allow 64-bit int*/
   if(WIDTH > 1) x = bitSwap<T, 1>(x); /* Compile time if    */
   if(WIDTH > 2) x = bitSwap<T, 2>(x);
   if(WIDTH > 4) x = bitSwap<T, 4>(x);
   if(WIDTH > 8) x = bitSwap<T, 8>(x);
   if(WIDTH >16) x = bitSwap<T,16>(x);
   return x;
}
/* --------------------------------------------------------- */   
/* @brief Iterative Binary to Binary-Reflected Gray code impl     *
 * @note                                                          *
 * -Gray codes of consecutive values differ in one bit            *
 * -Gray codes of values that differ by pow of 2 differ in 2 bits *
 * -Gray code of even/odd values have even/odd #bits set resp.    *
 * -Ex: Gray code of {1, 2, 3, 4, 5} = {01, 11, 10, 110, 111}     */
template<typename T=int>
static inline T grayCode(T x) noexcept {
   STATIC_ASSERT_TYPE_INTEGRAL(T);
   return x ^ (x >> 1); /* XOR of x and x/2                  */
}
/* @brief Convert Binary_Reflected Gray to Binary. As Gray code is*
 * bit-wise diff mod 2, compute inverse as bit-wise sum mod 2     *
 * @note                                                          *
 * -For n-bit words, n-fold application of Gray code = orig word  *
 * -Applying the Gray code twice is identical to x^=x>>2 and      *
 * -Applying it four times is x^=x>>4 (for all power of two)      *
 */
template<typename T=int>
static inline T inverseGrayCode(T x) noexcept {
   STATIC_ASSERT_TYPE_INT_UINT(T); /* Do not allow 64-bit int*/
   x ^= x >> 1;      /* Apply Gray code once                 */
   x ^= x >> 2;      /* Apply Gray code twice                */
   x ^= x >> 4;      /* Apply Gray code four times           */
   x ^= x >> 8;      /* Apply Gray code eight times          */
   x ^= x >> 16;     /* Apply Gray code sixteen times        */
   return x;
}
/* @brief Parity of a bitstream is its bit-count modulo 2        *
 * Lowest bit of inverse Gray code of a word contains its parity *
 * @return 0 means even parity and 1 means odd parity            */
template<typename T=int>
static inline int bitParity(T x) noexcept {
  STATIC_ASSERT_TYPE_INT_UINT(T); /* Do not allow 64-bit int*/
  return inverseGrayCode<T>(x) & 1;
}
/* --------------------------------------------------------- */      
} //end namespace

#endif //_BITOPS_CPP_
