//g++-5 --std=c++11 -Wall -g -o algo_greedy_local_minimum_candy algo_greedy_local_minimum_candy.cc

/**
 * @file  Candy
 * @brief Find Minimum number of candies to give to N children
 */

// https://leetcode.com/problems/candy/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <numeric>           /* std:accumulate               */
using namespace std;

/**
 * There are N children standing in a line. Each child is
 * assigned a rating value.
 * You are giving candies to these children subjected to the
 * following requirements:
 * Each child must have at least one candy.
 * Children with a higher rating get more candies than their neighbors.
 * What is the minimum candies you must give?
 * Note: If two neighboring children have same rating, 2nd child
 * need not get the same #candies as the first.
 * ex[1, 2, 2] = 1 + 2 + 1 = 4 candies.
 * Without this constraint the problem is trivial to solve.
 */

/**
 * @brief: To identify all local minima, do a two-pass algo  *
 * In forward pass, [1, n-1], compare each child to prev     *
 * In reverse pass, [n-2, 0], compare each child to next     *
 * Chose the maximum #candies needed across both passes      *
 * Time Complexity = O(n).   Space Complexity = O(n)         */
int candy(vector<int>& r) {
   int n = r.size();
   if(n < 2) return n;                         /* base-case  */
   std::vector<int> candies(n, 1);
   /* Forward pass (2nd element to last element)             */
   for(int i = 1; i < n; ++i)
      if(r[i] > r[i-1]) candies[i] = candies[i-1] + 1;
   /* Reverse pass (2nd to last element to first element)    */
   for(int i = n-2; i >= 0; --i)
      if(r[i] > r[i+1]) candies[i] = std::max(candies[i], candies[i+1] + 1);
   return std::accumulate(candies.begin(),candies.end(), 0);
}

/* Note: There is an interesting single pass algorithm with  *
 * O(1) space complexity at leetcode:                        *
 * https://discuss.leetcode.com/topic/17722/two-c-solutions-given-with-explanation-both-with-o-n-time-one-with-o-1-space-the-other-with-o-n-space         */

struct test_vector {
   std::vector<int> num;
   int exp;
};

const struct test_vector test[10] =  {
   {{},                                0},
   {{0},                               1},
   {{1,2},                             3},
   {{2,2},                             2},
   {{5,10,15},                         6},
   {{1, 7, 9},                         6},
   {{1, 2, 2},                         4},
   {{1, 2, 3, 4, 1, 2},               13},
   {{1, 2, 3, 4, 3, 4},               13},
   {{1, 2, 3, 4, 3, 2},               13},
};
   
int main()
{
   for(auto tst : test) {
      auto ans = candy(tst.num);
      if(ans != tst.exp) {
         cout << "Error:candy failed. Input ";
         for(auto val : tst.num) cout << val << ",";
         cout <<  "Exp: " << tst.exp << " Got: " << ans;
         cout << endl;
         return -1;
      }
   }
   cout << "Info: All manual test-cases passed." << endl;
   return 0;
}
