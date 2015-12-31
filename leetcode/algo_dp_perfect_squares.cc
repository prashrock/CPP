//g++ --std=c++11 -g -Wall -o algo_dp_perfect_squares algo_dp_perfect_squares.cc

/**
 * @file  Perfect Squares
 * @brief Given positive integer, find least # perfect squares which sum to n
 */

/**
 * Given a positive integer n, find least number of perfect  *
 * square numbers (for example, 1, 4, 9, 16, ...) which sum  *
 * to n.                                                     *
 * For example, given n = 12, return 3 because 12 = 4+4+4;   *
 * given n = 13, return 2 because 13 = 4 + 9.                */


#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
//#include "../utils/print_utils.h" /* print_table_row       */
using namespace std;

/**
 * @brief Iterative DP table solutn to calculate #perfect sqs*
 * @param positive integer, n                                *
 * @ret   min number of perfect numbers to sum to get n      *
 * Time Complexity = O(nm) Space Complexity = O(nm)          *
 */
int numSquaresDPTable(int n) {
	vector<int> elems;
	for(int i = 0; i * i <= n; ++i) elems.push_back(i*i);

	/* DP Subset sum starts here. Initialize DP table to max    */
	vector<vector<int>>
		dp(n+1, vector<int>(elems.size()+1,
							std::numeric_limits<int>::max()-1));
	for(auto val : elems) if(val && val <= n) dp[val][0] = 1;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= (int)elems.size(); ++j) {
			int ej = j-1;
			if(i > elems[ej])
				dp[i][j] = std::min(dp[i][j-1], dp[i-elems[ej]][j] + 1);
			else
				dp[i][j] = dp[i][j-1];
		}
	}
	/* Dump the entire DP table for analysis                */
	//print_table_row<int>("\t elems:", elems);
	//for(int i = 0; i <= n; ++i)
	//print_table_row<int>("\t "+to_string(i)+":", dp[i]);
	return dp[n][elems.size()];
}

/**
 * @brief Iterative DP solution to calculate #perfect sqs    *
 * @param positive integer, n                                *
 * @ret   min number of perfect numbers to sum to get n      *
 * Time Complexity = O(nm) Space Complexity = O(n)           *
 */
int numSquaresDP(int n) {
	/* burn 1 element to avoid offseting indexes             */
	vector<int> dp_table(n+1, std::numeric_limits<int>::max());

	dp_table[0] = 0; /* Base case, no cost to reach here     */
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

bool numSquaresTest() {
	int v1, v2;
	v1 = numSquaresDPTable(1);
	v2 = numSquaresDP(1);
	if     (v1 != 1)
	{  cout << "Error: 1 test-case failed v1 " << v1 << endl; return false;}
	else if(v2 != 1)
	{  cout << "Error: 1 test-case failed v2 " << v2 << endl; return false;}

	v1 = numSquaresDPTable(3);
	v2 = numSquaresDP(3);
	if     (v1 != 3)
	{  cout << "Error: 3 test-case failed v1 " << v1 << endl; return false;}
	else if(v2 != 3)
	{  cout << "Error: 3 test-case failed v2 " << v2 << endl; return false;}
	

	v1 = numSquaresDPTable(13);
	v2 = numSquaresDP(13);
	if     (v1 != 2)
	{  cout << "Error: 13 test-case failed v1 " << v1 << endl; return false;}
	else if(v2 != 2)
	{  cout << "Error: 13 test-case failed v2 " << v2 << endl; return false;}
	
	//v = numSquaresDP(8609);
	//v = numSquaresDP(1535);
	cout << "All manual test-cases passed" << endl;
	return true;
}

int main()
{
	numSquaresTest();
}
