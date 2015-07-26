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

/* Generate a sequence of random numbers. Insert them into   *
 * the bitmap and then manually check if all the bits are set*/
void bitmap_auto_test()
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
	for(unsigned i = 0; i < v.size(); ++i) {
		if(bitmap.get(v[i]) == false)
			cout << "Error: Bit " << v[i] << " not set"
				 << endl;
		bitmap.reset(v[i]);
	}
}


int main()
{
	init_rand();

	/* Auto test cases   */
	for(auto i = 0; i < num_test_iters; ++i)
		bitmap_auto_test();
}
