#include <iostream>          /* std::cout        */
#include <iomanip>           /* std::setw        */
#include <cmath>             /* pow              */
#include <cassert>           /* assert           */
#include <algorithm>         /* std::max         */
#include <string>            /* std::string      */

#include "print_utils.h"     /* print_table_row  */
#include "rand_generator.h"  /* init_rand()      */
using namespace std;

const int number_of_iterations = 1;
const int max_set_size         = 5;
const int max_item_value       = 5;
const int max_item_weight      = 10;
const int max_weight           = 10;

int knapsack_01_dp(const int v[], const int wt[],
				   int n, int W)
{
	/* Create a vector of vectors and init to 0  */
	vector<vector<int> > dp(n+1, vector<int> (W+1, 0) );
	vector<vector<bool> > keep(n+1, vector<bool> (W+1, false) );
	//vector<bool> keep(n, false);
	
	/* DP table init */
	for(int i = 0; i <= n; i++) dp[i][0] = 0;
	for(int w = 0; w <= W; w++) dp[0][w] = 0;
	
	for(int i = 1; i <= n; ++i)
	{
		for(int w = 1; w <= W; ++w)
		{
			dp[i][w] = 0;
			if(wt[i-1] <= W &&
			   (v[i-1] + dp[i-1][w - wt[i-1]] > dp[i-1][w]))
			{
				dp[i][w] = v[i-1] + dp[i-1][w-wt[i-1]];
				keep[i][w] = true;
		    }
		    else {
				dp[i][w] = dp[i-1][w];
				keep[i][w] = false;
			}
		}
	}
	cout << "Max achievable value = " << dp[n][W]
		 << " with below elements:" << endl;

	/* Print output table                        */
	vector<int> weights;
	for(int i=0; i <=W; i++) weights.push_back(i);
	print_table_row<int>("\tweights:", weights);
			
	for(int i = 0; i <= n; ++i) {
		std::string name = "\ti=" + std::to_string(i);
			print_table_row<int>(name, dp[i]);
	}

	cout << "----------------------------------" << endl;
	for(int i = n; i > 0; ++i) {
		if(keep[i][W] == true) {
			cout << "\t" << v[i-1] << "\t" << wt[i-1] << endl;
			W -= wt[i-1];
		}
	}

	return dp[n][W];
}

/* Given set size, generate elements randomly    *
 * and call partition set algorithm              */
void knapsack_tester(size_t set_size)
{
	std::vector<int> val(set_size), weights(set_size);
	
	/* Generate vector contents randomly */
	fill_vector_rand(val, 0, max_item_value);
	fill_vector_rand(weights, 0, max_item_weight);
	
	print_table_row<int>("input-values", val);
	print_table_row<int>("input-weights", weights);
	
	knapsack_01_dp(&val[0], &weights[0], set_size,
				   max_weight);
}

int main()
{
	cout << "Running " << number_of_iterations << " iterations "
		 << "each with set size " << max_set_size << endl;
	init_rand();
	for(int i = 1; i <= number_of_iterations; i++)
		knapsack_tester(max_set_size);
}
