#include <iostream>          /* std::cout        */
#include <iomanip>           /* std::setw        */
#include <cmath>             /* pow              */
#include <cassert>           /* assert           */
#include <algorithm>         /* std::max         */
#include <string>            /* std::string      */

#include "print_utils.h"     /* print_table_row  */
#include "rand_generator.h"  /* init_rand()      */
using namespace std;


/* Given 2 sequences, find the length of longest *
 * subsequence present in both of them. A        *
 * subsequence is a sequence that appears in the *
 * same relative order, but not necessarily      *
 *contiguous.                                    *
 * Ex: LCS for ABCDGH and AEDFHR = ADH (len = 3) *
 * Ex: LCS for AGGTAB and GXTXAYB = GTAB(len = 4)*/

const int number_of_iterations = 1;
const int max_set_size         = 5;

/* DP Approach                                   *
 * Build a DP table with the following Recursion *
 * if(s1[idx1] == s2[idx2])                      *
 *    table[i][j] = table[i-1][j-1] + 1          *
 * else                                          *
 *                      - table[i][j-1]          *
 *    table[i][j] = max |                        *
 *                      - table[i-1][j]          *
 * Time Complexity = O(m*n)                      *
 * Space Complexity= O(m*n)                      */
template<typename T>
int lcs_dp(const T s1[], size_t m,
           const T s2[], size_t n)
{
   /*C++11 create 2D vector and initialize to 0*/
   vector<vector<int> > table(m+1, vector<int>(n+1, 0));

   for(size_t    i = 0; i <= m; ++i) {
      for(size_t j = 0; j <= n; ++j) {
         /* Initialize DP table               */
         if(i == 0 || j == 0)
            table[i][j] = 0;
         /* If elements are equal             */
         else if(s1[i - 1] == s2[j - 1])
            table[i][j] = table[i-1][j-1] + 1;
         /* Else, use max of previous row/col */
         else				
            table[i][j] = std::max(table[i][j-1],
                                   table[i-1][j]);
      }
   }
   /* After DP completes, we can deduce LCS len */
   int lcs_len = table[m][n];
	
   /* LCS Backtracking                          */
   vector<T> lcs_output;
   for(int i = m, j = n; i > 0 && j > 0;) {
      /* If elements are equal                 */
      if(s1[i - 1] == s2[j - 1]) {
         lcs_output.insert(lcs_output.begin(),
                           s1[i - 1]);
         i--; j--;
      }
      /* Chose which side to go. Remember this *
       * has to be consistent. Pick the idx    *
       * which is greater for traversing       */
      else if(table[i][j - 1] > table[i - 1][j]) j--;
      else                                       i--;
   }
	
   /* Print output table                        */
   cout << "DP Table:" << endl;
   for(size_t i = 0; i <= m; ++i)
      print_table_row<int>("dp", table[i]);
   cout << "LCS of length " << lcs_len
        << " found between two inputs" << endl;
   print_table_row<T>("LCS result", lcs_output);
   cout << endl;
   return lcs_len;
	
}


/* Given String size, generate two random strings*
 * call LCS on both strings and print longest    *
 * subsequence with backtracking                 */
void lcs_tester(size_t set_size)
{
   std::vector<char> s1(set_size), s2(set_size);
	
   /* Generate vector contents randomly from A-Z */
   fill_vector_rand(s1, 'A', 'D');
   fill_vector_rand(s2, 'A', 'D');

   print_table_row<char>("s1", s1);
   print_table_row<char>("s2", s2);
	
   lcs_dp(&s1[0], s1.size(),
          &s2[0], s2.size());

}

int main()
{
   cout << "Running " << number_of_iterations << " iterations "
        << "each with set size " << max_set_size << endl;
   init_rand();
   for(int i = 1; i <= number_of_iterations; i++)
      lcs_tester(max_set_size);
}
