#include <iostream>   /* std::cout        */
#include <iomanip>    /* std::setw        */
#include <algorithm>  /* std::max         */
#include <vector>     /* std:vector       */

#include "print_utils.h"
#include "math_sqrt.h"
#include "rand_generator.h"

using namespace std;

int main()
{
	std::vector<int> v(10);
	fill_vector_rand(v, 0, 2);
	print_table_row<int>("rand vector", v);
	cout << "pending" << endl;
}
