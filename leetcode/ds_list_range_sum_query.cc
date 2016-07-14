//g++ --std=c++11 -Wall -g -o ds_list_range_sum_query ds_list_range_sum_query.cc

/**
 * @file  Range Sum Query (Immutable and Muttable)
 * @brief Given integer array, find sum of elements between indices
 */

// https://leetcode.com/problems/range-sum-query-immutable/
// https://leetcode.com/problems/range-sum-query-mutable/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/**
 * Immutable Range Sum Query (easy)
 * Given an integer array nums, find the sum of the elements between
 * indices i and j (i . j), inclusive.
 * Example:
 * Given nums = [-2, 0, 3, -5, 2, -1]
 * sumRange(0, 2) -> 1
 * sumRange(2, 5) -> -1
 * sumRange(0, 5) -> -3
 * Note:
 * - You may assume that the array does not change in immutable version.
 * - There are many calls to sumRange function.
 */
class ImmutableNumArray {
public:
   ImmutableNumArray(vector<int> &nums) {
      /* Waste 0th index to avoid if condition in sumRange   */
      sums.resize(nums.size() + 1);
      /* Calculate a rolling sum [0, i] foreach i (0<=i<n)   */
      for(int i = 0, rolling_sum = 0; i < (int)nums.size(); ++i) {
         rolling_sum += nums[i];
         sums[i + 1] = rolling_sum;
      }
   }

   /* Given index (i, j), perform the below operation        *
    * result = rolling_sum[j] - rolling_sum[i-1]             *
    * Note: the above formula needs sanity checks for i-1>0  *
    * therefore, waste 0th index in rolling_sum to avoid if  */
   int sumRange(int i, int j)  {
      return sums[j + 1] - sums[i];
   }
private:
   vector<int> sums; /* Stores rolling sum upto index        */
};

/**
 * Mutable Range Sum Query (Medium)
 * Given an integer array nums, find the sum of the elements between
 * indices i and j (i . j), inclusive.
 * The update(i, val) function modifies nums by updating the element
 * at index i to val.
 * Example:
 * Given nums = [1, 3, 5]
 * sumRange(0, 2) -> 9
 * update(1, 2)
 * sumRange(0, 2) -> 8
 * Note:
 * - The array is only modifiable by the update function.
 * - You may assume the number of calls to update and sumRange function
 *   is distributed evenly.
 */
/* Note: this is a Binary Indexed Tree based implementation  *
 * Refer to my BIT C implementation to understand the layout *
 * of this tree and its supported operations:                *
 * https://github.com/prashrock/C/blob/master/tree/binary_indexed_tree.h */
class MutableNumArray {
public:
   MutableNumArray(vector<int> &lnums) : nums(lnums) {
      bit_sums.resize(nums.size() + 1);
      for(int i = 0; i < (int)nums.size(); ++i)
         bit_update(i+1, nums[i]);
   }

   void update(int i, int val) {
      /* Calculate diff which needs to be propagated         */
      int diff_val = val - nums[i];
      nums[i] = val;
      if(diff_val != 0) bit_update(i+1, diff_val);
   }

   int sumRange(int i, int j) {
      return bit_getsum(j+1) - bit_getsum(i);
   }

private:
   vector<int> nums;       /* Actual number range            */
   vector<int> bit_sums;   /* Holds the Binary Indexed Tree  */

   /* Traverse the BIT and update value through tree         *
    * Time Complexity = O(lg n)                              */
   __attribute__((always_inline)) void bit_update(int i, int val) {
      while(i <= (int)nums.size()) {
         bit_sums[i] += val;
         i += i & (-i); /* ADD LSB */
      }
   }

   /* Traverse the BIT and compute sum upto this node        *
    * Time Complexity = O(lg n)                              */
   __attribute__((always_inline)) int bit_getsum(int i) {
      int val = 0;
      while(i > 0) {
         val += bit_sums[i];
         i -= i & (-i); /* SUB LSB */
      }
      return val;
   }
};


bool immutable_rangesumquery_test()
{
   std::vector<int> input = {-2, 0, 3, -5, 2, -1};
   class ImmutableNumArray imm_na = ImmutableNumArray(input);
   int result;
   if     ((result = imm_na.sumRange(0, 2)) != 1)
      cout << "Error: Immutable Sum 0, 2 returned " << result << endl;
   else if((result = imm_na.sumRange(2, 5)) != -1) 
      cout << "Error: Immutable Sum 2, 5 returned " << result << endl;
   else if((result = imm_na.sumRange(0, 5)) != -3) 
      cout << "Error: Immutable Sum 0, 5 returned " << result << endl;
   else
      return true;
   return false;
}

bool mutable_rangesumquery_test()
{
   std::vector<int> input = {1, 3, 5};
   class MutableNumArray mu_na = MutableNumArray(input);
   int result;
   if((result = mu_na.sumRange(0, 2)) != 9) {
      cout << "Error: Immutable Sum 0, 2 returned " << result << endl;
      return false;
   }

   mu_na.update(1, 2); /* Replace 3 (2nd element) with 2     */
   if((result = mu_na.sumRange(0, 2)) != 8) {
      cout << "Error: Immutable Sum 0, 2 returned " << result << endl;
      return false;
   }
   return true;
}

int main()
{
   if(immutable_rangesumquery_test() && mutable_rangesumquery_test())
      cout << "Info: All manual test-cases passed." << endl;
   return 0;
}
