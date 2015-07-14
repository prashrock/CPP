#include <iostream>          /* std::cout        */
#include <iomanip>           /* std::setw        */
#include <cmath>             /* pow              */
#include <cassert>           /* assert           */
#include <algorithm>         /* std::max         */
#include <string>            /* std::string      */
#include <chrono>            /* high_resolution_clock  */
#include <map>               /* std::map container */
#include <unordered_map>     /* std::unordered_map container */

#include "print_utils.h"     /* print_table_row  */
#include "rand_generator.h"  /* init_rand()      */
using namespace std;

const int number_of_iterations = 1000000000;
const int num_of_random_nums = 10000;

template<typename T>
void associative_array_benchmark(T &assoc_array)
{
	std::vector<int> v(10000);
	fill_vector_rand(v, 0, number_of_iterations);

	auto begin = chrono::high_resolution_clock::now();
	for(int i = 0, j = 0; i < number_of_iterations &&
			j < num_of_random_nums; i++, j++)
		assoc_array[v[j]] = v[j];
	auto end =   chrono::high_resolution_clock::now();

	auto elapsed = chrono::duration_cast<chrono::milliseconds>
		(end - begin);
	cout << "time spent = " << elapsed.count() << " ms" << endl;
}

int main()
{
	map<int, int> map_var;
	unordered_map<int, int> unordermap_var;

	init_rand();
	cout << "Micro Benchmark for Map/Unordered Map "
		 << "over 1 Billion iterations:" << endl;
	cout << "Benchmark for Tree based Map, ";
	associative_array_benchmark<map<int, int> >(
		map_var);
	cout << "Benchmark for Hash based Unordered-Map, ";
	associative_array_benchmark<unordered_map<int, int> >(
		unordermap_var);
}
