#ifndef _MATH_FACT_CPP
#define _MATH_FACT_CPP
#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <cstdint>           /* uint8_t                      */
#include "math_misc.h"       /* bigint_multiply              */
#include "compiler_api.h"    /* STATIC_ASSERT_TYPE_UINT_ULONG*/

namespace math {

/* @brief Calc n! without using recursion (detect overflow)  *
 * Time Complexity = O(n)      Space Complexity = O(1)       */
template<typename T1=int, typename T2=long>
static inline bool factorial(T1 n, T2& res) {
   STATIC_ASSERT_TYPE_UINT_ULONG(T1); /* not handling -ve #s */
   res = 1;
   for(T2 ores = res; n > 0; --n, ores = res) {
      res *= n;
      if(res < ores) return false;
   }
   return true;
}
 
/* Calculate and print large factorial (beyond uint64_t)     */
static inline std::string big_factorial(unsigned n, bool print=false) {
   auto result = bigint(1);
   while(n) bigint_multiply(result, n--);

   auto result_str = bigint_print(result);
   if(print) std::cout << result_str;
   return result_str;
}
 
/** @brief Calculate number of trailing zeros in factorial   *
 * Every trailing zero comes from a multiple of 10 which in  *
 * turn has 2 prime factors (2, 5). Note: In a factorial     *
 * every other number is a multiple of 2, so the number of   *
 * 10's is determined by the #5s = #5's+#25's+#125's+etc     */
static inline int count_trailing_zeros_in_factorial(const int n) {
   int cnt = 0;
   if(n == 5) return 1;
   for(int fpow = 5; (n/fpow >= 1); fpow *= 5) {
      cnt += n/fpow;
   }
   return cnt;
}
 
} //end namespace math
#endif //_MATH_FACT_CPP
