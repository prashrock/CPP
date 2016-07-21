#include <iostream>          /* std::cout        */
#include <algorithm>         /* std::max         */
#include "print_utils.h"     /* print_table_row  */
#include "rand_generator.h"  /* init_rand()      */
using namespace std;

const int number_of_iterations    =   10;
const int number_of_items_in_iter =   20; /* input vector sz */
const int max_item_value          =   10;
const int max_sum                 =  100; /* expected sum    */

/* DP Bottom-Up Memoization approach to calculate Subset Sum *
 * Can handle Duplicates and 0 in set.                       */
bool subset_sum(const std::vector<int>& set, const int sum,
                bool print_dp_table=false, bool print_backtrace=false)
{
   int n = set.size();
   bool result = false;
    /* Row is the constraint to solve (in this case sum)     *
     * Column is input values (in this case set[])           */
   std::vector<std::vector<bool>> dp(sum+1, vector<bool> (n+1, false));
   /* First row, pre-initialize lookup row for (sum-set[i])  */
   for(int j = 0; j <= n; j++)    dp[0][j] = true;
   /* First column, pre-init for empty set[], except row 0   */
   for(int i = 1; i <= sum; i++)  dp[i][0] = false;
   
   /* Calculate all dp indexes with Dynamic Programming      */
   for   (int s = 1; s <= sum; s++) {
      for(int j = 1; j <= n; j++) {
         int set_idx = j-1;
         if(set[set_idx] > s) /* Skip out of bounds subset   */
            dp[s][j] = dp[s][j-1];
         else
            dp[s][j] = dp[s][j-1] || dp[s-set[set_idx]][j-1];
      }
   }
   
   /* Final ans - Can we reach sum from any of the numbers ? */
   if(dp[sum][n]) result = true;

   /* Check if we should print DP Table or Result Backtrace  */
   if(print_dp_table) {
      print_table_row<int>("input-values", set);
         
      /* Print the DP Matrix                                 */
      printf("Rows = Sums and Columns = n\n");
      for (int j = 0; j <= n; j++) {
         if(j == 0)  printf("--- | --- ");
         else	     printf("%3d ",set[j-1]);
      }
      printf("\n--------------------------------------------\n");
      for (int i = 0; i <= sum; i++) {
         if(i == 0)  printf("--- | ");
         else        printf("%3d | ", i);
         for (int j = 0; j <= n; j++)
            printf ("%3d ", (dp[i][j] == true) ? 1 : 0);
         printf("\n");
      }
   }
   /* Check if we should print the result backtrace          */
   if(result && print_backtrace) {
      cout << "Numbers:";
      /* Start from last row, find out which column was first*
       * set in the DP table. This is O(n lg n) algorithm    */
      for(int i = sum; i > 0;) {
         auto it = std::lower_bound(dp[i].begin(), dp[i].end(), true);
         if(*it == true) {
            int idx = it - dp[i].begin() - 1;
            i -= set[idx];
            cout << set[idx] << ",";
         }
      }
      cout << endl;
   }
   return result;
}

/* Can handle duplicates and negative numbers                */
bool subset_sum_brute(const std::vector<int>& set, int n, int sum)
{
   int idx = n-1;         /* idx is 0 based                  */
   if(sum == 0)           return true;
   if(n == 0 && sum != 0) return false;
   /* Skip out of bounds subset                              */
   if(set[idx] > sum)
      return subset_sum_brute(set, n-1, sum);
   /* 2 cases in dynamic programming:                        *
    * a) Don't include last element in calculating sum       *
    * b) Include last element in calculating sum             */
   return ( subset_sum_brute(set, n-1, sum) ||
            subset_sum_brute(set, n-1, sum - set[idx]) );
}

/* Given set size, generate elements randomly and then call  *
 * Subset sum Brute and DP algorithms                        */
bool subsetsum_tester(size_t set_size, int sum, int &cnt)
{
   std::vector<int> val(set_size);
   
   /* Generate vector contents randomly                      */
   fill_vector_rand(val, 0, max_item_value);
   
   auto dp_res    = subset_sum(val, sum);
   auto brute_res = subset_sum_brute(val, val.size(), sum);

   if(dp_res != brute_res) {
      cout << "Error: Subset failed for given input "
           << "DP = " << dp_res << " Brute = " << brute_res << endl;
      cout << "Below is the DP table result:"  << endl;
      subset_sum(val, sum, true, true);
      return false;
   }
   if(dp_res == true) cnt++;
   return true;
}

int main()
{
   int cnt = 0; /* Number of successful Subsetsum runs       */
   cout << "Running " << number_of_iterations << " iterations "
        << "each with " << number_of_items_in_iter << " items "
        << "and with max_sum=" << max_sum          << endl;
   init_rand();
   for(int i = 1; i <= number_of_iterations; i++)
      if(subsetsum_tester(number_of_items_in_iter, max_sum, cnt) == false)
         return -1;
   
   cout << "Info: All Subset sum test-cases completed successfully "
        << cnt << " subsets had subset's with sum " << max_sum << endl;
   return 0;
}
