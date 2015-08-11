#ifndef _MATH_PRIME_CPP
#define _MATH_PRIME_CPP
#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */

#include "bitmap.h"          /* bitmap  functions            */

template<size_t N>
void prime_seive_eratosthenes(size_t primes[N],
									  size_t max_rand_val)
{
	int i;
	bitmap seive(max_rand_val);
	seive.set_all(); /* Start with all #'s as valid prime    */
	/* Identify each prime, clear all its multiples          */
	for(size_t i = 2; i < max_rand_val; ++i) {
		if(seive.get(i) == false) continue;
		for(size_t j = i; j <= max_rand_val/i; ++j)
			seive.reset(i * j);
	}

	primes[0] = 2;
	for(i = 1; i < N; ++i)
	{
		size_t x;
		if(seive.get_next_set_pos(primes[i - 1], x))
			primes[i] = x;
		else break;
	}
	std::cout << "Info: Computed " << i << " prime numbers"
			  << " with Seive of Erathosthenes" << std::endl;
}

#endif //_MATH_PRIME_CPP
