//g++-5 -Wall --std=c++11 -g -o math_permutate math_permutate.cc -I../utils/

/**
 * @file  Math Next Permutation
 * @brief Given a vector, return its next incremental permutation
 */

// https://leetcode.com/problems/next-permutation/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include "print_utils.h"     /* print_table_row              */
using namespace std;

/**
 * Implement next permutation, which rearranges numbers into the
 * lexicographically next greater permutation of numbers.
 * If such arrangement is not possible, it must rearrange it as
 * the lowest possible order (ie, sorted in ascending order).
 *
 * The replacement must be in-place, do not allocate extra memory.
 * Here are some examples. Inputs are in the left-hand column and
 * its corresponding outputs are in the right-hand column.
 * 1,2,3 -> 1,3,2
 * 3,2,1 -> 1,2,3
 * 1,1,5 -> 1,5,1
 */

/** @brief Dijkstra's incremental permutation algorithm       *
 * - Incremental algorithm which starts with sorted input seq *
 * - Compute the next permutation without replacement         *
 * - For distinct input string, #permutations = nPn = n!      *
 * - For input string with repetitions, this is an arrangement*
 *   problem with **no repetitions**, i.e.,                   *
 *   #permutations = n!/(n1! n2! n3!) where n1, n2, n3.. are  *
 *   the number of occurences of each digit/character         *
 * @note equivalent to STL std::next_permutation              *
 * @ret returns true if input was permutated.                 */
class Permutate_Dijkstra {
public:
   Permutate_Dijkstra() { }
   /** @brief Sort input vector which we need to permutate    */
   Permutate_Dijkstra(std::vector<int>& n) {
      std::sort(n.begin(), n.end());
   }
   /** @brief Check if any more permutations are possible     *
    * If array is fully sorted (in reverse order) no more perm*/
   bool hasNextPermutation(const std::vector<int>& n) {
      /* check if is_sorted_until returns reverse end of vec  */
      return (is_sorted_until(n.rbegin(), n.rend()) != n.rend());
   }
   /** @brief Get next permutation if one exists else do no-op*
    * Example, given 1342, it will point to 3 (first unsorted *
    * value from Right end). Next, swap with the next highest *
    * value to RHS. In this case swap with 4.                 *
    * Rotate all in-between numbers in range [it, n-1]        */
   bool nextPermutation(std::vector<int>& nums) {
      auto it = nums.rend();
      /* Only if there is one more permutation, fix up array  */
      if(hasNextPermutation(nums)) {
         it = is_sorted_until(nums.rbegin(), nums.rend());
         std::swap(*it, *std::upper_bound(nums.rbegin(), it, *it));
      }
      std::reverse(nums.rbegin(), it);
      return (it != nums.rend());
   }
};

/** @brief Heap permute: Permute input array with repetitions @  *
 * A.Levitin, Introduction to Design&Analysis of Algorithms(179) *
 * Number of permutations (without repetition) = nPn = n!        *
 * Note: Algorithm does not differentiate between strings with   *
 * repeating characters and strings without. Therefore, output   *
 * permutations need not be unique                               *
 * @ret total number of permutations done                        */
unsigned long heapPermutation(std::vector<int>& nums,
                              std::vector<std::vector<int>>& ans,
                              const size_t n) {
   unsigned long tot = 0; /* Tracks the total #permutations      */
   if(n == 1) { ans.push_back(nums); tot = 1; }
   else {
      for(size_t i = 0; i < n; ++i) {
         tot += heapPermutation(nums, ans, n-1);
         if(n % 2 == 1) std::swap(nums[0], nums[n-1]); /* Odd    */
         else           std::swap(nums[i], nums[n-1]); /* Even   */
      }
   }
   return tot;
}

void heapPermutationTest(std::vector<int> nums)
{
   std::vector<std::vector<int>> ans;
   cout << "Heap Permutation, input vector: ";
   print_table_row("", nums);
   auto tot = heapPermutation(nums, ans, nums.size());
   cout << tot << " permutations found: " << endl;
   for(auto v : ans)    print_table_row("  :", v);
}

struct test_vector {
   std::vector<int> nums;
   std::vector<int> next_perm;
};

const struct test_vector test[6] =  {
   {{1},               {1}},
   {{1,2,3},       {1,3,2}},
   {{3,2,1},       {1,2,3}},
   {{1,1,5},       {1,5,1}},
   {{1,3,2},       {2,1,3}},
   {{1,3,4,2},   {1,4,2,3}},
};

int main()
{
   Permutate_Dijkstra pdijkstra;
   for(auto tst : test) {
      auto ans = tst.nums;
      pdijkstra.nextPermutation(ans);
      if(ans != tst.next_perm) {
         cout << "Error:next_perm failed." << endl;
         print_table_row("Exp:", tst.next_perm);
         print_table_row("Got:", ans);
         return -1;
      }
   }

   /* Test heap permutation algorithm with sample vector     */
   heapPermutationTest({1, 2, 3});
   heapPermutationTest({1, 1, 2});
   
   cout << "Info: All manual test-cases passed." << endl;
   return 0;
}
