//g++-5 --std=c++11 -Wall -g -o ds_list_range_addition ds_list_range_addition.cc

/**
 * @file  Range Addition
 * @brief k update operations onto array
 */

// https://leetcode.com/problems/range-addition/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/**
 * Assume you have an array of length n initialized with all 0's
 * and are given k update operations.
 * Each operation is represented as a triplet: [startIndex,endIndex,inc]
 * which increments each element of subarray A[startIndex...endIndex]
 * (startIndex and endIndex inclusive) with inc.
 * Return the modified array after all k operations were executed.
 * Example:
 * Given:
 * length = 5,
 * updates = [ [1,  3,  2],
 *             [2,  4,  3],
 *             [0,  2, -2] ]
 * Output:  [-2, 0, 3, 5, 3]
 * Hints:
 * - Thinking of using advanced data structures? Not needed.
 * - For each update, should you update all elements inbetween ?
 * - Update only the first and end element is sufficient.
 * - The optimal time complexity is O(k + n) & uses O(1) space.
 */

/* Brute-force:                                              *
 * Apply each update immediately                             */
vector<int> getModifiedArrayBrute(int len, vector<vector<int>>& updates) {
   vector<int> ans(len, 0);
   for(auto &up: updates)
      for(int i = up[0]; i <= up[1]; ++i) ans[i] += up[2];
   return ans;
}


/* Optimal-approach:                                         *
 * Update only first and last indexes and use a carry to     *
 * propagate the updates:                                    *
 * - For each update in k, do the following:                 *
 *   - Update ans[b]   += k_val (include in carry after b    *
 *   - Update ans[e+1] -= k_val (exclude in carry from e  )  *
 * - Sweep through array while updating carry @ each elem    *
 * Time Complexity  = O(n + k) n elements and k updates      *
 * Space Complexity = O(1)                                   */ 
vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
   std::vector<int> ans(length, 0);
   /* Update start and end indexes with increment in update  */
   for(auto &up: updates) {
      int b = up[0], e = up[1] + 1, val = up[2];
      if(b < (int)ans.size()) ans[b] += val;
      if(e < (int)ans.size()) ans[e] -= val;
   }

   /* Go over entire arr once to fill in the gaps with carry */
   for(int i = 0, carry = 0; i < (int)ans.size(); ++i) {
      auto t  = ans[i];  /* scratch pad to store cur carry   */
      ans[i] += carry;   /* Update cur idx with prev-carry   */
      carry  += t;       /* Update carry from scratch pad    */
   }
   return ans;
}

////5   //[[1,3,2],[2,4,3],[0,2,-2]]  //[-2, 0, 3, 5, 3 ]

int main()
{
   cout << "Info: Need to add manual tests for Range Addition" << endl;
   return 0;
}
