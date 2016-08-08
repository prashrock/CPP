#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <algorithm>         /* std::max                     */
#include <vector>              /* std:vector                 */
#include <string>            /* std::string                  */
#include "print_utils.h"     /* print_table_row              */
#include "rand_generator.h"  /* init_rand()                  */
using namespace std;

/* Given 2 sequences, find the length of longest subsequence *
 * present in both of them. A subsequence is a sequence that *
 * appears in the same relative order, but not necessarily   *
 * contiguous.                                               *
 * Ex: LCS for ABCDGH and AEDFHR = ADH (len = 3)             *
 * Ex: LCS for AGGTAB and GXTXAYB = GTAB(len = 4)            */

const int number_of_iterations = 100;
const int max_set_size         = 20;

/* DP Bottom-Up Memoization Approach to calculate LCS        *
 * if(s1[idx1]   == s2[idx2])                                *
 *    table[i][j] = table[i-1][j-1] + 1                      *
 * else                                                      *
 *                      - table[i][j-1]                      *
 *    table[i][j] = max |                                    *
 *                      - table[i-1][j]                      *
 * Time Complexity = O(m*n)    Space Complexity= O(m*n)      */
template<typename T>
int lcs_dp(const T s1[], size_t m, const T s2[], size_t n,
           bool print_dp_table=false, bool print_backtrace=false)
{
   /* Store #matches at cur index in dp_table                */
   vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
   
   for(size_t i = 1; i <= m; ++i) {
      for(size_t j = 1; j <= n; ++j) {
         /* a) If elements are equal, we have a match        */
         if(s1[i-1] == s2[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
         /* Else, use max of either previous row or column   */
         else	dp[i][j] = std::max(dp[i][j-1], dp[i-1][j]);
      }
   }
   int lcs_len = dp[m][n];
   /* Core DP Logic done, now deduce LCS length and print    */
   if(print_dp_table || print_backtrace) {
      std::vector<T> s1v(s1, s1 + m), s2v(s2, s2 + n);
      print_table_row<T>("s1", s1v);
      print_table_row<T>("s2", s2v);
      cout << "Length of Longest common subsequence = " << lcs_len << endl;
   }
   if(print_dp_table) {
      cout << "DP Table:" << endl;
      cout << "Rows = S1 | Columns = S2 (table stores #common)" << endl;
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
   }
   /* Check if we should print the result backtrace          */
   if(print_backtrace) {
      vector<T> lcs_output;
      /* Traverse DP table from last element all the way back*/
      for(int i = m, j = n; i > 0 && j > 0;) {
         /* If elements are equal, then we have a match      */
         if(s1[i-1] == s2[j-1]) {
            lcs_output.insert(lcs_output.begin(), s1[i-1]);
            i--; j--;
         }
         /* Chose which side to go. Remember this has to be  *
          * consistent. Pick greater idx for traversing      */
         else if(dp[i][j-1] > dp[i-1][j]) j--;
         else                             i--;
      }
      cout << "LCS of length " << lcs_len
           << " found between two inputs" << endl;
      print_table_row<T>("LCS result", lcs_output);
      cout << endl;
   }   
   return lcs_len;
}

template<typename T>
int lcs_brute(const T s1[], int m, const T s2[], int n)
{   
   if(m == 0 || n == 0) return 0; /* base case of recursion  */
   int ans = 0;
   for(int i = 1; i <= m; ++i) {
      for(int j = 1; j <= n; ++j) {
         if(s1[i-1] == s2[j-1])
            ans = std::max(ans, 1 + lcs_brute(&s1[i], m-i, &s2[j], n-j));
      }
   }
   return ans;
}

/* Given String size, generate elements randomly and call    *
 * LCS  Brute and DP algorithms                              */
bool lcs_tester(size_t set_size)
{
   std::vector<char> s1(set_size), s2(set_size);
	
   /* Generate vector contents randomly from A-Z */
   fill_vector_rand(s1, 'A', 'G');
   fill_vector_rand(s2, 'A', 'G');
   
   auto dp_res = lcs_dp(&s1[0], s1.size(), &s2[0], s2.size());
   auto brute_res = lcs_brute(&s1[0], s1.size(), &s2[0], s2.size()); 
   
   if(dp_res != brute_res) {
      cout << "Error: LCS failed for given input "
           << "DP = " << dp_res << " Brute = " << brute_res << endl;
      cout << "Below is the DP table result:"  << endl;
      lcs_dp(&s1[0], s1.size(), &s2[0], s2.size(), true, true);
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
      if(lcs_tester(max_set_size) == false) return -1;
   cout << "Info: All LCS test-cases completed successfully " << endl;
   return 0;
}
