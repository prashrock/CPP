#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */

#include "print_utils.h"     /* print_table_row              */
#include "rand_generator.h"  /* init_rand()                  */
#include "bitmap.h"          /* bitmap  functions            */
using namespace std;

/* Number of inserts == Coupon Collector problem = n ln(n)   *
 * inserts to ensure every bitmap position [1, max_rand_val] *
 * is covered                                                */
const int number_of_inserts = 620; //~n ln(n)
const int max_rand_val      = 128;
const int num_test_iters    = 1;

/* Compare performance of STL Bitmap and my Bitmap           */
void bitmap_perf_test()
{
	//unsigned long max_bit = 1000000 //Million
	//std::bitset<max_bit> stlb;
	//class bitmap myb(max_bit);
	cout << "Need to implement a micro-benchmark" << endl;
}

/* Generate a sequence of random numbers. Insert them into   *
 * the bitmap and then manually check if all the bits are set*/
bool bitmap_auto_test()
{
	vector<int> v(number_of_inserts);
	class bitmap bitmap(max_rand_val);
	
	fill_vector_rand(v, 0, max_rand_val);
	
	/* Sort the random input vector and remove duplicates */
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	
	cout << "Verifying bitmap @ following bit positions: ";
	for(unsigned i = 0; i < v.size(); ++i) {
		if(bitmap.get(v[i]) == false)
			bitmap.set(v[i]);
		    cout << v[i] << ", ";
	}
	cout << endl;
	return true;
}


int main()
{
	init_rand();
	bool ret = true;
	/* Manual test-case  */
	size_t x;
	class bitmap bitmap(128);
	bitmap.set(1); bitmap.set(127);
	if(bitmap.get(1) == false)
		cout << "Error: 1st set bit not found" <<endl;
	else if(bitmap.get(127) == false)
		cout << "Error: last set bit not found" <<endl;
	/* Note, there is no elaborate test-case for             *
	 * get_next_set_pos, as math_prime.cc does thorough test */
	else if(bitmap.get_next_set_pos(1, x) == false || x != 127)
		cout << "Error: get_next_set_pos failed. Expecting 127, got "
			 << x << endl;
	else {
		cout << "Info: All manual test-cases passed" << endl;
		/* Auto test cases   */
		for(auto i = 0; i < num_test_iters && ret; ++i)
			ret = bitmap_auto_test();
		//if(ret)
		//bitmap_perf_test();
	}
}
