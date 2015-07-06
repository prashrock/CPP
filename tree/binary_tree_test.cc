#include <iostream>            /* std::cout     */
#include <iomanip>             /* std::setw     */
#include <vector>              /* std::vector   */
#include <cmath>               /* pow           */
#include <cassert>             /* assert        */
#include <algorithm>           /* std::max      */

#include "rand_generator.h"    /* init_rand()   */
#include "binary_tree.h"       /* BT API        */
using namespace std;

const int num_inserts = 10;
const int min_key     =  0;
const int max_key     = 20;


int main()
{
	init_rand();
	std::vector<int> v(num_inserts);
    /* Generate vector contents randomly */
    fill_vector_rand(v, min_key, max_key);
	for(int i = 0; i < num_inserts; ++i)
	{
		node<int, int> n(v[i], v[i]);
		cout << n << endl;
	}
}
