#include <iostream>          /* std::cout        */
#include <iomanip>           /* std::setw        */
#include <cmath>             /* pow              */
#include <cassert>           /* assert           */
#include <algorithm>         /* std::max         */
#include <string>            /* std::string      */

#include "print_utils.h"     /* print_table_row  */
#include "rand_generator.h"  /* init_rand()      */
using namespace std;

/* Determine whether given Set can be partitioned*
 * into two subsets such that the sum of elements*
 * in both subsets is same.                      */


const int number_of_iterations = 20;
const int max_set_size         = 10;
const int max_random_number    = 10;


/* DP Approach                                   *
 * If sum is odd, then we cannot partition       *
 * If sum is even, then do a DP approach with    *
 * following Recursion                           *
 *               - table[i][j-1]                 *
 * table[i][j] = |                               *
 *               - table[i-val][j-1]             *
 * Time Complexity = O(sum*n)                    *
 * Space Complexity= O(sum*n)                    */
template<typename T>
bool partition_set_dp(const T v[], size_t n)
{
	unsigned total = 0;
	for(int i = 0; i < n; i++) total += v[i];
	unsigned partition_sum = total / 2;
	/*C++11 create 2D vector and initialize to 0*/
	vector<vector<bool> > table(partition_sum+1, vector<bool>(n+1, 0));
	/* Sum must be capable of being split into   *
	 * two equal parts for partitioning          */
	if(total % 2 != 0){
		cout << "\tSum is odd. Cannot partition set." << endl;
		return false;
	}

	/* Initialize DP table                       */
	for(int i = 0; i <= partition_sum; ++i) table[i][0] = false;
	for(int j = 0; j <= n; ++j)     		table[0][j] = true;

	for(int sum = 1; sum <= partition_sum; ++sum) {
		for(int j = 1; j <= n; ++j) {
			int val = v[j-1];
			/* If previous column is set, then set here as well */
			table[sum][j] = table[sum][j-1];
			/* If previous column is set, then set here as well *
			 * Note: table[sum-val][j-1], has j-1 and not j  to *
			 * find if [sum-val] can be reached without using j */
			if(val <= sum)
				table[sum][j] = table[sum][j] |
					table[sum - val][j-1];
		}
	}

	/* Can partition succesfully                 */
	if(table[partition_sum][n] == true)
		return true;
	
	/* Print output table                        */
	cout << "\tSUM = " << total << endl;
	vector<T> inp(1);
	for(int i=0; i <n; i++) inp.push_back(v[i]);
	print_table_row<T>("\tinput", inp);
			
	for(int sum = 0; sum <= partition_sum; ++sum) {
		std::string name = "\tsum:" + std::to_string(sum);
			print_table_row<bool>(name, table[sum]);
	}
	cout << "\tPartition failed" << endl;
	return table[partition_sum][n];
}

/* Given set size, generate elements randomly    *
 * and call partition set algorithm              */
void partition_set_tester(size_t set_size)
{
	std::vector<int> v(set_size);
	
	/* Generate vector contents randomly */
	fill_vector_rand(v, 0, max_random_number);
	print_table_row<int>("input", v);
	partition_set_dp(&v[0], v.size());
}


int main()
{
	cout << "Running " << number_of_iterations << " iterations "
		 << "each with set size " << max_set_size << endl;
	init_rand();
	for(int i = 1; i <= number_of_iterations; i++)
		partition_set_tester(max_set_size);
}
