#include <iostream>          /* std::cout        */
#include <iomanip>           /* std::setw        */
#include <cmath>             /* pow              */
#include <cassert>           /* assert           */
#include <algorithm>         /* std::max         */
#include <string>            /* std::string      */

#include "print_utils.h"     /* print_table_row  */
#include "rand_generator.h"  /* init_rand()      */
using namespace std;

const int number_of_iterations = 100;
const int max_set_size         =  50;
const int max_item_value       =  50;
const int max_item_weight      =  20;
const int max_weight           = 100;

/* DP Bottom-Up Memoization approach to find knapsack value  *
 * Sum of wts of input elements is the constraint (DP rows)  *
 * Sum of values of input elements is to maximize (DP value) *
 * Note: This algo can handle duplicates in wt and value, but*
 * currently only +ve values allowed. To support negative    *
 * values, init dp table with std::numeric_limits<int>::min()*/
int knapsack_01_dp(const std::vector<int>& v, const std::vector<int>& wt,
                   int max_wt,
                   bool print_dp_table=false, bool print_backtrace=false)
{
   /* Create a vector of vectors and init to 0               */
   int n = v.size(), W = max_wt;
   /* Store value in dp_table (subset sum stored true/false) */
   vector<vector<int>>  dp(W+1, vector<int> (n+1, 0));
   /* Burn O(nW) space for O(n) time to calc selected elems  */
   vector<vector<bool>> keep(W+1, vector<bool> (n+1, false));
	
   for(int w = 1; w <= W; ++w) {
      for(int j = 1; j <= n; ++j) {
         if(wt[j-1] > w)   /* Skip out of bounds weight      */
            dp[w][j]   = dp[w][j-1];
         /* If including current wt, beats prev value, use it*/
         else if(v[j-1] + dp[w - wt[j-1]][j-1] > dp[w][j-1]) {
            dp[w][j]   = v[j-1] + dp[w-wt[j-1]][j-1];
            keep[w][j] = true;
         }
         else /* if current weight is not picked, use prev   */
            dp[w][j]   = dp[w][j-1];
      }
   }
   /* Core DP Logic done, now book-keeping and printing      */
   /* Check if we should print DP Table or Result Backtrace  */
   if(print_dp_table || print_backtrace) {
      cout << "Max achievable value = " << dp[W][n]
           << " with below elements:" << endl;
      print_table_row<int>("input-values ", v);
      print_table_row<int>("input-weights", wt);
   }
   if(print_dp_table) {
      /* Print the DP Matrix                                 */
      printf("Rows = Sum_of_weights and Columns = input_elements\n");
      for (int j = 0; j <= n; j++) {
         if(j == 0)  printf("--- | [-] ");
         else	     printf("%3d ", j);
      }
      printf("\n--------------------------------------------\n");
      for (int w = 0; w <= W; w++) {
         if(w == 0)  printf("  0 | ");
         else        printf("%3d | ", w);
         for (int j = 0; j <= n; j++)
            printf ("%3d ", dp[w][j]);
         printf("\n");
      }
   }
   /* Check if we should print the result backtrace          */
   if(print_backtrace) {
      vector<int> sel_weights, sel_values;
      /* For each weight we know selected knapsack items     *
       * Start from max weight and pick items in O(n) time   */
      for(int i = n, w = W; i > 0; --i) {
         if(keep[w][i] == true) {
            sel_weights.push_back(wt[i-1]);
            sel_values.push_back(v[i-1]);
            w -= wt[i-1];
         }
      }
      cout << "DP Selected weights:" << endl;
      print_table_row<int>("sel-values ", sel_values);
      print_table_row<int>("sel-weights", sel_weights);
   }
   return dp[W][n];
}

/* Can handle duplicates.                                    */
int knapsack_01_brute(const std::vector<int>& v, const std::vector<int>& wt,
                       int n, int max_wt, int cur_val)
{
   int idx = n-1;                 /* idx is 0 based          */
   /* no more elems, or we've reached the max weight budget  */
   if(n == 0 || max_wt == 0) return cur_val;
   /* Skip index if its weight is out of bounds              */
   else if(wt[idx] > max_wt)
      return knapsack_01_brute(v, wt, n-1, max_wt, cur_val);
   /* 2 cases in dynamic programming:                        *
    * a) Don't include last element in calculation           *
    * b) Include last element in calculation                 */
   auto val_a = knapsack_01_brute(v, wt, n-1, max_wt, cur_val);
   auto val_b = knapsack_01_brute(v, wt, n-1, max_wt - wt[idx],
                                  cur_val + v[idx]);
   return std::max(val_a, val_b);
}

/* Given set size, generate elements randomly and then call  *
 * Knapsack Brute and DP algorithms                          */
bool knapsack_tester(size_t set_size, int max_wt, int max_val)
{
   std::vector<int> v(set_size), wt(set_size);
	
   /* Generate vector contents randomly                      */
   fill_vector_rand(v,  1, max_val);
   fill_vector_rand(wt, 1, max_wt);
   
   auto dp_res    = knapsack_01_dp(v, wt, max_wt);
   auto brute_res = knapsack_01_brute(v, wt, set_size, max_wt, 0); 
   
   if(dp_res != brute_res) {
      cout << "Error: Knapsack_01 failed for given input "
           << "DP = " << dp_res << " Brute = " << brute_res << endl;
      cout << "Below is the DP table result:"  << endl;
      knapsack_01_dp(v, wt, max_wt, true, true);
      return false;
   }
   return true;
}

int main()
{
   cout << "Running " << number_of_iterations << " iterations "
        << "each with set size " << max_set_size
        << " and max weight as " << max_item_weight
        << " and max value as "  << max_item_value << endl;
   init_rand();
   for(int i = 1; i <= number_of_iterations; i++)
      if(knapsack_tester(max_set_size, max_item_weight, max_item_value) == false)
         return -1;
   cout << "Info: All Knapsack test-cases completed successfully " << endl;
   return 0;
}
