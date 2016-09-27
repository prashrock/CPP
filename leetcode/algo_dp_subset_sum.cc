//g++-5 -Wall --std=c++11 -g -o algo_dp_subset_sum algo_dp_subset_sum.cc

/**
 * @file  Coin Change
 * @brief Given denominations and amt find min #coins to make amt
 */

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
using namespace std;

// https://leetcode.com/problems/coin-change/

/**
 * You are given coins of different denominations and a total
 * amount of money amount. Write a function to compute the fewest
 * number of coins that you need to make up that amount. If that
 * amount of money cannot be made up by any combination of the
 * coins, return -1.
 * Example 1:
 * coins = [1, 2, 5], amount = 11
 * return 3 (11 = 5 + 5 + 1)
 * Example 2:
 * coins = [2], amount = 3
 * return -1.
 * Note:
 * You may assume that you have an infinite # of each kind of coin.
 */

/** Bottom-Up DP based solution:                             *
 * Time Complexity = O(amt*coins), Space Complexity = O(amt) */
int coinChangeDP(std::vector<int>& coins, int amt) {
   int maxAmt = amt + 1; /* assume amt != limits<int>::max() */
   /* DP table to store #coins needed to reach current sum   */
   std::vector<int> dp(amt + 1, maxAmt);
   dp[0] = 0;
   /* Actual bottom-up loop to go over all the sums till amt */
   for(int n = 1; n <= amt; ++n) {
      for(auto c : coins)
         if(c <= n) dp[n] = std::min(dp[n], dp[n-c] + 1);
   }
   if(dp[amt] > amt)   return -1;
   else                return dp[amt];
}

/** BFS based solution (Inspired by)::                       *
 * https://discuss.leetcode.com/topic/32589/fast-python-bfs-solution/2 */
int coinChangeBFS(std::vector<int>& coins, int amt) {
   if(amt == 0) return 0;
   /* Maintain a vector to keep track of current BFS amounts */
   std::vector<int>  bfsList = {0};
   /* Keep track of nodes in [1, amt] visited until now      */
   std::vector<bool> visited(amt + 1, false);
   visited[0] = true;
   /* Min #Coins = 1, Keep going till BFS level is empty     */
   for(int nc = 1; bfsList.size() > 0; ++nc) {
      int n = bfsList.size(); /* #amts in current #BFS level */
      for(int i = 0; i < n; ++i) { /* For each cur amt, do:  */
         for(auto c : coins) {     /* Use all possible coins */
            int nextval = bfsList[i] + c;
            if(nextval <= amt) {
               /* Since BFS, as soon as we reach amt, done   */
               if(nextval == amt)     return nc;
               /* If new amt(!visited before) add to BFSlist */
               else if(visited[nextval] == false) {
                  visited[nextval] = true;
                  bfsList.push_back(nextval);
               }
            }

         }
      }
      /* Clear all nodes that were just covered in above loop*/
      bfsList.erase(bfsList.begin(), bfsList.begin() + n);
   }
   return -1;
}

struct test_vector {
   std::vector<int> coins;
   int amt;
   int expNumCoins;
};

const struct test_vector test[7] =  {
   { {1},                   0,  0},
   { {1},                   1,  1},
   { {1},                   2,  2},
   { {2},                   3, -1},
   { {1,2,5},              11,  3},
   { {2147483647},          2, -1},
   { {474,83,404,3},      264,  8},
};

int main()
{
   for(auto tst : test) {
      auto ans = coinChangeDP(tst.coins, tst.amt);
      if(ans != tst.expNumCoins) {
         cout << "Error:coinChangeDP failed. Exp "
              << tst.expNumCoins << " Got "  << ans << " for ";
         for(auto v: tst.coins) cout  << v << ","; cout << endl;
         cout << "amt = " << tst.amt << endl;
         return -1;
      }
      ans = coinChangeBFS(tst.coins, tst.amt);
      if(ans != tst.expNumCoins) {
         cout << "Error:coinChangeBFS failed. Exp "
              << tst.expNumCoins << " Got "  << ans << " for ";
         for(auto v: tst.coins) cout  << v << ","; cout << endl;
         cout << "amt = " << tst.amt << endl;
         return -1;
      }
   }
   cout << "Info: All manual test-cases successful" << endl;
   return 0;
}
