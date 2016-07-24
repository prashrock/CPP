//g++ --std=c++11 -g -Wall -o algo_dp_perfect_squares algo_dp_perfect_squares.cc

/**
 * @file  Perfect Squares
 * @brief Given positive integer, find least # perfect squares which sum to n
 */

// https://leetcode.com/problems/perfect-squares/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
//#include "../utils/print_utils.h" /* print_table_row       */
using namespace std;

/**
 * Given a positive integer n, find least number of perfect  *
 * square numbers (for example, 1, 4, 9, 16, ...) which sum  *
 * to n.                                                     *
 * For example, given n = 12, return 3 because 12 = 4+4+4;   *
 * given n = 13, return 2 because 13 = 4 + 9.                */

/**
 * @brief Iterative DP table solutn to calculate #perfect sqs*
 * @param positive integer, n                                *
 * @ret   min number of perfect numbers to sum to get n      *
 * Time Complexity = O(nm) Space Complexity = O(nm)          *
 */
int numSquaresDPTable(int n) {
   vector<int> sqr; 
   for(int i = 0; i * i <= n; ++i) sqr.push_back(i*i);
   int m = sqr.size();
   
   /* DP Subset sum starts here. Initialize DP table to max  */
   std::vector<std::vector<int>>
      dp(n+1, vector<int>(m+1, std::numeric_limits<int>::max()-1));
   for(auto v : sqr)     dp[v][0] = 1;  /* Init DP table     */
   for(int i = 1; i <= n; ++i) {
      for(int j = 1; j <= m; ++j) {
         int ej = j-1;
         if(i > sqr[ej]) dp[i][j] = std::min(dp[i][j-1], dp[i-sqr[ej]][j] + 1);
         else            dp[i][j] = dp[i][j-1];
      }
   }
   /* Dump the entire DP table for analysis                  */
   //print_table_row<int>("\t elems:", elems);
   //for(int i = 0; i <= n; ++i)
   //print_table_row<int>("\t "+to_string(i)+":", dp[i]);
   return dp[n][m];
}

/**
 * @brief Iterative DP solution to calculate #perfect sqs    *
 * @param positive integer, n                                *
 * @ret   min number of perfect numbers to sum to get n      *
 * Time Complexity = O(nm) Space Complexity = O(n)           *
 */
int numSquaresDP(int n) {
   /* burn 1 element to avoid offseting indexes              */
   vector<int> dp_table(n+1, std::numeric_limits<int>::max());
   
   dp_table[0] = 0; /* Base case, no cost to reach here      */
   for(int i = 1; i <= n; ++i)
      for(int j = 1; j*j <= i; ++j)
         dp_table[i] = std::min(dp_table[i], dp_table[i - j*j] + 1);

   return dp_table[n];
}

/* There is also a mathematical solution that I really liked *
 * when trying to understand why my 2nd solution does not    *
 * have best performance, this soln uses following properties*
 * Fermat's Theorem : an odd prime (p)  can be expressed as  *
 * a sum of two squares (x, y), i.e., p = x2 + y2            *
 * iff, p mod 4 = 1                                          *
 * Lagrange's Four Square Theorem: Any natural number can be *
 * represented as the sum of four integer squares:           *
 * i.e., p = a2 + b2 + c2 + d2                               *
 * https://leetcode.com/discuss/58056/summary-of-different-solutions-bfs-static-and-mathematics
 * https://leetcode.com/discuss/56982/o-sqrt-n-in-ruby-c-c   */
struct test_vector {
   int n;
   int exp;
};

const struct test_vector test[6] =  {
   { 1,      1},
   { 3,      3},
   {13,      2},
   {1535,    4},
   {1729,    3}, //Ramanujan Number
   {8609,    2},
};
   
int main()
{
   for(auto tst : test) {
      auto ans = numSquaresDPTable(tst.n);
      if(ans != tst.exp) {
         cout << "Error:numSquaresDPTable failed. Exp "
              << tst.exp << " Got " << ans << " for "
              << tst.n   << endl;
         return -1;
      }
      ans = numSquaresDP(tst.n);
      if(ans != tst.exp) {
         cout << "Error:numSquaresDP failed. Exp "
              << tst.exp << " Got " << ans << " for "
              << tst.n   << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
