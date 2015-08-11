#ifndef _MATH_PERM_COMB_CPP_
#define _MATH_PERM_COMB_CPP_

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */

/* To generate permutations (lexicographic/heap) refer to    *
 * https://github.com/prashrock/C/blob/master/math/math_permute.h */

/* Calculate #ways to chose k elements from n posibilities   *
 * #ways = nCk   = n!/(r!(n-r)!)                             *
 * @param n      - Number of elements                        *
 * @param k      - Number of choices                         *
 * @param result - nCk value (or zero upon error/overflow)   *
 * Time Complexity = O(k-1)                                  */
template<typename Tret=unsigned, typename T=unsigned>
bool nCk(T n, T k, Tret &result)
{
	if(k > n)  return false;      /* Spl case - Invalid args */
	k = std::min(k, n-k);         /* nCk = nC(n-k)           */
	/* Handle all special cases where we can avoid the loop  */
	if(k == 0)        result = 1; /* nC0 = 1                 */
	else if(k == 1)   result = n; /* nC1 = n                 */
	else              result = n; /* Start with the last #   */

	/* The below for-loop will not be executed for special   *
	 * cases above (k == 0 or 1). For all else, it does      *
	 * result = n!/k!(n-k)! = n*(n-1)*(n-2)*..*(n-k+1)/k!    */
	for(T i = 2; i <= k; ++i)
	{
		Tret overflow_chk = result; /* Handle overflow cases */
		result *= (n - i + 1);   /* Iterative numerator calc */
		result /= i;           /* Iterative denominator calc */
		/* Combination should always grow unless overflow    */
		if(overflow_chk >= result) {
			result = 0;
			return false;
		}
	}
	return true;
}

/* Wrapper to call and use value of nCk directly             */
template<typename Tret=unsigned, typename T=unsigned>
Tret nCk(T n, T k)
{
	Tret result = 0;
	if(nCk(n, k, result)) return result;
	else                  return 0;
}
	
#endif //_MATH_PERM_COMB_CPP_
