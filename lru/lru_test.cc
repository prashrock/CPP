#include <iostream>            /* std::cout                  */
#include <iomanip>             /* std::setw                  */
#include <vector>              /* std::vector                */
#include <cmath>               /* pow, log2                  */
#include <cassert>             /* assert                     */
#include <algorithm>           /* std::max                   */

#include "rand_generator.h"    /* init_rand()                */
#include "lru.h"               /* LRU API                    */
#include "print_utils.h"       /*print_table_row             */
using namespace std;
using namespace lru_space;

const int num_inserts =  10;
const int lru_size    =   5;
const int min_key     =   0;
const int max_key     =  10;

/* Walk through BT creation and deletion process             */
void lru_walkthrough()
{
	std::vector<int> vec(num_inserts);
    lru<int, int>    lru(lru_size);

    fill_vector_rand(vec, min_key, max_key);
	print_table_row<int>("Insert order", vec);
	
	cout << "Walkthrough of LRU operations:" << endl;
	cout << "Current LRU Size is: " << lru.size() << endl;
	cout << "Inserting " << vec.size() << " elements" << endl;
	for(auto key : vec) {
		lru.insert(key, key);
		cout <<   "elem = " << key
			 << " size  = " << lru.size() << endl;
	}

	cout << "Dumping the LRU cache before any remove:" << endl;
	cout << lru;
	
	std::shuffle(vec.begin(), vec.end(),
				 std::default_random_engine(get_rand(max_key)));

	print_table_row<int>("Del order", vec);
	for(auto key : vec) {
		lru.remove(key);
		cout << "size   = " << lru.size() << endl;
	}
	cout << "-----------------------" << endl << endl;
}

int main()
{
	init_rand();
	lru_walkthrough();
}
