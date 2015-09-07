//g++ -std=c++11 -o least_k_numbers least_k_numbers.cc
/* Find out the least k numbers out of n numbers. For        *
 * example, if given the 8 numbers 4, 5, 1, 6, 2, 7, 3 and 8,*
 * please return the least 4 numbers 1, 2, 3 and 4.          */

#include <iostream>          /* std::cout        */
#include <iomanip>           /* std::setw        */
#include <cmath>             /* pow              */
#include <algorithm>         /* std::sort        */
#include <set>               /* std::multiset    */
#include "../utils/print_utils.h"     /* print_table_row  */
#include "../utils/rand_generator.h"  /* init_rand()      */
using namespace std;

const int num_iterations       = 1000000;
const int vect_length          = 10;
const int least_k_length       = vect_length/4;
const int max_item_value       = 100;

/* Brute force, sort based extract least k items impl        *
 * This approach takes O(n lg n) time                        */
template<typename T=int>
std::vector<T> least_k_brute_force(std::vector<T> input, int k)
{
	std::vector<T> result(0);
	if(k < 1 || k > input.size()) return result;

	/* Sort entire input and extract first k elements        */
	std::sort(input.begin(), input.end());
	result.assign(input.begin(), input.begin() + k);
	return result;
}

/* For a quick implementation, use multiset(BST) to maintain *
 * the smallest k numbers. This approach takes O(n lg k)     *
 * time complexity.                                          *
 * Ideally a maxheap of size k would be preferred but using  *
 * STL for quicker prototyping.                              */
template<typename T=int>
std::vector<T> least_k_multiset(std::vector<T> input, int k)
{
	std::vector<T> result(0);
	if(k < 1 || k > input.size()) return result;
	/* Create the BST based Multi-Set                        */
	std::multiset<T, greater<T>> result_set;

	for(auto val : input) /* For each elem in input vector   */
	{
		if(result_set.size() < k)    /* if size(set) < k     */
			result_set.insert(val);  /* Add element directly */
        /* Once set is full, if greatest(set) > input[i],    *
		 * then replace greatest(set) with input[i]          */
		else {
			auto iter = result_set.begin(); /* greatest #    */
			if(val < *iter){
				result_set.erase(iter);  /* erase greatest # */
				result_set.insert(val);  /* insert input[i]  */
			}
		}
	}
	result.assign(result_set.begin(), result_set.end());
	/* Sort result to match brute force algo output          */
	std::sort(result.begin(), result.end());
	return result;
}

/* Generate random numbers and test brute + multiset impls   */
bool least_k_test()
{
	vector<int> input(vect_length);
	fill_vector_rand<int>(input, 0, max_item_value);
	auto brute_rs = least_k_brute_force(input, least_k_length);
	auto set_rs = least_k_multiset(input, least_k_length);
	if(brute_rs != set_rs) {
		print_table_row<int>("input", input);
		print_table_row<int>("brute result", brute_rs);
		print_table_row<int>("multiset result", set_rs);
		return false;
	}
	return true;
}

int main()
{
	init_rand();
	auto n = num_iterations;
	cout << "Running " << num_iterations << " test iterations:" << endl;
	while(n--)
		if(least_k_test() == false) break;
	if(n == -1)                     cout << "Successful" << endl;
}
