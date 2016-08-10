#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <algorithm>         /* std::max                     */
#include <vector>              /* std:vector                 */
#include <string>            /* std::string                  */
#include "print_utils.h"     /* print_table_row              */
#include "rand_generator.h"  /* init_rand()                  */
using namespace std;

/* Given two strings, determine minimum number of operations *
 * (insert, del, substitute) to change 1 string to other     *
 * Use Levenshtein distance, ins,del cost = 1, sub cost = 1  */

const int number_of_iterations = 100;
const int max_set_size         =  10;

/* DP Bottom-Up Memoization Approach for Levenstein Distance *
 * M[i][j] =  (M[i-1][j]   + 1  --Add/Delete                 *
 *         min(M[i][j-1]   + 1  --Add/Delete                 *
 *            (M[i-1][j-1] + 1 (if str[i]!=str[j]) -- Subst  *
 *            (            + 0 (if str[i]==str[j]) -- Subst  *
 * Time Complexity = O(m*n)    Space Complexity= O(m*n)      */
template<typename T>
int min_edit_dp(const T s1[], size_t m, const T s2[], size_t n,
                int add_cost=1, int del_cost=1, int sub_cost=1,
                bool print_dp_table=false)
{
   /* Store #substitutions at cur index in dp_table          */
   vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

   /* First row/col, pre-init with add cost of s1, s2 alone  */
   for(size_t i = 0; i <= m; i++) dp[i][0] = i;
   for(size_t j = 0; j <= n; j++) dp[0][j] = j;
   
   for(size_t i = 1; i <= m; ++i) {
      for(size_t j = 1; j <= n; ++j) {
         /* a) If elements are equal, no-cost at all         */
         if(s1[i-1] == s2[j-1]) dp[i][j] = dp[i-1][j-1];
         /* Else, use min of add/del/substitute costs        */
         else {
            dp[i][j] = std::min(dp[i-1][j]+add_cost,   dp[i][j-1]+del_cost);
            dp[i][j] = std::min(dp[i-1][j-1]+sub_cost, dp[i][j]);
         }
      }
   }
   
   int min_edit_cost = dp[m][n];
   /* Core DP Logic done, now deduce min-edit dist and print */
   if(print_dp_table) {
      std::vector<T> s1v(s1, s1 + m), s2v(s2, s2 + n);
      print_table_row<T>("s1", s1v);
      print_table_row<T>("s2", s2v);
      cout << "Min Edit Distance = " << min_edit_cost << endl;
      cout << "DP Table:" << endl;
      cout << "Rows = S1 | Columns = S2 (table stores #edits)" << endl;
      for (size_t j = 0; j <= n; ++j) {
         if(j == 0)  printf("--- |[-] ");
         else        std::cout << std::left         << std::setw(3)
                               << std::setfill(' ') << s2[j-1];
      }
      cout << endl << "--------------------------------------------" << endl;
      for (size_t i = 0; i <= m; ++i) {
         if(i == 0)  printf("[-] | ");
         else        std::cout << std::left         << std::setw(3)
                               << std::setfill(' ') << s1[i-1] << " | ";
         for (size_t j = 0; j <= n; ++j)
            std::cout << std::left         << std::setw(3)
                      << std::setfill(' ') << dp[i][j];
         cout << endl;
      }
      cout << endl;
      std::cout.copyfmt(std::ios(NULL)); /* Restore cout     */
   }
   return min_edit_cost;
}

template<typename T>
int min_edit_brute(const T s1[], int m, const T s2[], int n, int i, int j,
                   int add_cost=1, int del_cost=1, int sub_cost=1)
{
   /* Handle the base case of recursion */
   if     (i == n)         return m - j; /* s1 is empty, count s2 remain */
   else if(j == m)         return n - i; /* s2 is empty, count s1 remain */
   else if(s1[i] == s2[j]) return min_edit_brute(s1, m, s2, n, i+1, j+1);
   else
      return std::min({add_cost + min_edit_brute(s1, m, s2, n, i,   j+1),
                       del_cost + min_edit_brute(s1, m, s2, n, i+1, j),
                       sub_cost + min_edit_brute(s1, m, s2, n, i+1, j+1)});
}

/* Given String size, generate elements randomly and call    *
 * Min Edit Distance Brute and DP algorithms                 */
bool min_edit_tester(size_t set_size)
{
   std::vector<char> s1(set_size), s2(set_size);
	
   /* Generate vector contents randomly from A-Z */
   fill_vector_rand(s1, 'A', 'F');
   fill_vector_rand(s2, 'A', 'F');
   
   auto dp_res = min_edit_dp(&s1[0], s1.size(), &s2[0], s2.size());
   auto brute_res = min_edit_brute(&s1[0], s1.size(), &s2[0], s2.size(), 0, 0); 
   
   if(dp_res != brute_res) {
      cout << "Error: Min_edit failed for given input "
           << "DP = " << dp_res << " Brute = " << brute_res << endl;
      cout << "Below is the DP table result:"  << endl;
      min_edit_dp(&s1[0], s1.size(), &s2[0], s2.size(), 1, 1, 1, true);
      return false;
   }
   return true;
}

int main()
{   
   cout << "Running " << number_of_iterations << " iterations "
        << "each with set size " << max_set_size << endl;
   init_rand();
   for(int i = 1; i <= number_of_iterations; i++)
      if(min_edit_tester(max_set_size) == false) return -1;
   cout << "Info: All Min-edit test-cases completed successfully " << endl;
   return 0;
}
