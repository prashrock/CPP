//g++-5 -Wall --std=c++11 -g -o math_shuffle math_shuffle.cc

/**
 * @file  Math Shuffle an Array
 * @brief Given a set of numbers without duplicates (shuffle them)
 */

// https://leetcode.com/problems/shuffle-an-array/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
using namespace std;

/**
 * Shuffle a set of numbers without duplicates.
 * Example:
 * // Init an array with set 1, 2, and 3.
 * int[] nums = {1,2,3};
 * Solution solution = new Solution(nums);
 * // Shuffle the array [1,2,3] and return its result.
 * Any permutation of [1,2,3] must equally likely to be returned.
 * solution.shuffle();
 * // Resets the array back to its original configuration [1,2,3].
 * solution.reset();
 * // Returns the random shuffling of array [1,2,3].
 * solution.shuffle();
 */

/**
 * @brief - Minimal Knuth Shuffle implementation.            *
 * Complete implementation @ ../math/math_shuffle.h          */
class Solution {
public:
   Solution(std::vector<int> nums) : val(nums) {
      srand( time(NULL) ^ 100003); /* time XOR prime = seed  */
   }
   
   /** Resets array to original configuration and return it. */
   std::vector<int> reset() { return val; }
   
   /** Returns a random shuffling of the array.              */
   std::vector<int> shuffle() {
      std::vector<int> cpy(val);
      /* Knuth Shuffle main loop (Fisher-Yates Shuffle)      */
      for(size_t i = 1; i < cpy.size(); ++i) {
         const auto j = rand() % (i + 1);  /* 0 <= j <= i    */
         std::swap(cpy[i], cpy[j]);
      }
      return cpy;
   }
private:
   std::vector<int> val;    /* Original unjumbled vector     */
};

int main()
{
   cout << "Info: Manual test-cases yet to be written." << endl;
   return 0;
}
