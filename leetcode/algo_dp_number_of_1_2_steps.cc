//g++-5 --std=c++11 -g -o algo_dp_number_of_1_2_steps algo_dp_number_of_1_2_steps.cc

/**
 * @file  Climbing stairs
 * @brief Find out #distinct ways to climb n steps, 1-2 at a time
 */

// https://leetcode.com/problems/climbing-stairs/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
using namespace std;

/**
 * You are climbing a stair case. It takes n steps to reach to the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways
 * can you climb to the top ?
 */

/* Quick Recursive factorial implementation.                 */
static int fact(int n)
{
   return (n == 1 || n == 0) ? 1 : n * fact(n - 1);
}

/**
 * DP based solution:                                        *
 * This question alludes to Fibonacci series expansion       *
 * When n <= 0 the number of ways we can climb is 0          *
 * When n = 1, there is exactly 1 way to climb the stairs    *
 * When n = 2, there are exactly 2 ways to climb the stairs  *
 * When n > 2, the number of ways to reach n, is the number  *
 * of ways to reach n-1 + number of ways to reach n-2 pos.   *
 * This is because, n-1 and n-2 do not overlap (1 step from  *
 * n-1 to reach n and 2 steps from n-2 to reach n)           *
 * Time Complexity = O(n), Space Complexity = O(1)           */
int climbStairsFibonacci(int n) {
   int n_1 = 1;
   int n_2 = 0, fib = 0;
   
   /* Calculate n from n-1 and n-2 values                    */
   for(int i = 0; i < n ; i++) {
      fib = n_1 + n_2; /* #ways to reach here = n-1 + n-2    */
      n_2 = n_1;       /* n-2 takes pprevious cycle value    */
      n_1 = fib;       /* get n-1 ready for next cycle       */
   }
   return fib;
}

/**
 * Permutation Calculation Solution:                         *
 * Calculate the number of 2's and number of 1's in set (n)  *
 * and then total the sum of all possible arrangements with  *
 * summation_over_all_two_cnt ( (n!)/(one_cnt! * two_cnt!) ) *
 * Note, factorial grows fast, so above calc might overflow  */
int climbStairsPermutation(int n) {
   int num_twos = 0, res = 0;

   if(n == 0 || n == 1 || n == 2) return n;
   for(int i = n; i >= 2; i-= 2, num_twos++); /* #2's in inp */
   res = 1;             /* Cnt all one outcome separately.   */
	
   /* Loop over all other outcomes varying #2s to get to next*
    * outcome & calculate the #arrangements of each outcome  */
   for(int i = 1; i <= num_twos; i++) {
      int twos = i;               /* #2s in this outcome     */
      int ones = n - (twos * 2);  /* remaining #1s in outcome*/
      int num_arrange;
      
      /* Calculate #arrangements of this outcome with formua *
       * =  (#1+#2)! / (#1! #2!)                             */
      num_arrange = (fact(twos+ones) / (fact(twos) * fact(ones)));
      res += num_arrange;
   }
   return res;
}

const int staircase_size = 12;

int main()
{
   for(int i = 0; i <= staircase_size; ++i) {
      auto ans_fib  = climbStairsFibonacci(i);
      auto ans_perm = climbStairsPermutation(i);
      if(ans_fib != ans_perm) {
         cout << "Error: for i = " << i
              << " Fib mode = "    << ans_fib
              << " Perm mode = "   << ans_perm << endl;
         return -1;
      }
      else
         cout << "#ways to climb " << i << " stairs = "
              << ans_fib << endl;
   }
   return 0;
}
