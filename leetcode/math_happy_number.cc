//g++-5 --std=c++11 -Wall -g -o math_happy_number math_happy_number.cc

/**
 * @file  Math Happy Number
 * @brief Given a positive integer find if sum of digit squares is 1
 */

// https://leetcode.com/problems/happy-number/

/**
 * Write an algorithm to determine if a number is "happy".
 * A happy number is a number defined by the following process:
 * Starting with any positive integer, replace the number by the sum
 * of the squares of its digits, and repeat the process until the number
 * equals 1 (where it will stay), or it loops endlessly in a cycle which
 * does not include 1. Those numbers for which this process ends in 1 are
 * happy numbers.
 * Example: 19 is a happy number
 * 12 + 92 = 82
 * 82 + 22 = 68
 * 62 + 82 = 100
 * 12 + 02 + 02 = 1
 */


#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow, tgamma(factorial)       */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
#include <unordered_set>     /* std::unordered_set           */
using namespace std;

/* Given a number n calculate sum of its digits squared      *
 * Example: Given 12, return 1^2 + 2^2 = 5                   */
int next(int n) {
   int sum = 0;
   for(auto i = n; i; i /= 10) sum += std::pow(i % 10, 2);
   return sum;
}
/* Given n continue finding sum of all digit squared until   *
 * there is a cycle or we reach 1. To detect a cycle store   *
 * all numbers seen so far from start in a set               */
bool isHappyMap(int n) {
   std::unordered_set<int> loop; /* to detect a loop         */
   while(1) {
      n = next(n);
      /* If n reaches 1, this number is a happy number       */
      if(n == 1)                          return true;
      /* If n is already in loop, then there is a cycle      */
      else if(loop.find(n) != loop.end()) return false;
      /* No cycle yet, so add n to hash and continue         */
      else                                loop.insert(n);
   }
}

/* Use Linked List cycle detection algorithm for O(1) space  *
 * - Credit: Tortoise & Hair algo (Don. Knuth, Floyd)        */
bool isHappyCycle(int n) {
   int slow = n, fast = n;
   while(1) {
      slow = next(slow);       /* slow moves by 1 each loop  */
      fast = next(next(fast)); /* fast moves by 2 each loop  */
      if(slow == 1 || fast == 1)  return true;
      else if(slow == fast)       return false;
   }
}

struct test_vector {
   int X;
   bool exp;
};

const struct test_vector test[4] =  {
   {  4,  false },
   {  5,  false },
   { 19,  true  },
   { 25,  false },
};

int main()
{
   for(auto tst : test) {
      auto ans = isHappyMap(tst.X);
      if(ans != tst.exp) {
         cout << "Error:isHappyMap failed for " << tst.X 
              << " exp " << tst.exp << " got " << ans << endl;
         return -1;
      }
      ans = isHappyCycle(tst.X);
      if(ans != tst.exp) {
         cout << "Error:isHappyCycle failed for " << tst.X 
              << " exp " << tst.exp << " got " << ans << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
