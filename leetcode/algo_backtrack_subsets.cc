//g++-5 --std=c++11 -Wall -g -o algo_backtrack_subsets algo_backtrack_subsets.cc

/**
 * @file  Subsets
 * @brief Return all possible subsets of the given input
 */

//https://leetcode.com/problems/subsets/

/**
 * Given set of distinct ints, return all possible subsets.  *
 * Note:                                                     *
 * Elements in a subset must be in non-descending order.     *
 * The solution set must not contain duplicate subsets.      *
 * For example, If nums = [1,2,3], a solution is:            *
 * [ [3], [1], [2], [1,2,3], [1,3], [2,3], [1,2], [] ]       *
 */


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
 *-----------------------------------------------------------*
 * Note, there are 3 possible implementations below:         *
 * - backtracking, iterative and bitmap based approach       *
 * Number of subsets = 2^num_elems (including null set)      *
 * For example, number of subsets in {1, 2, 3} = 2^3 = 8     *
 *-----------------------------------------------------------*/
/*------------------- Backtrack Algo ------------------------*/
/**
 * Backtracking algorithm to create all possible subsets of  *
 * a given size.                                             *
 * @param nums - input integer vector whose subset we need   *
 * @param result - output vector of vector containing subsets*
 * @param len  - Subset size                                 *
 * @param cur  - next subset in creation                     *
 * @param idx  - current idx in nums that is being processed *
 */
void permutate_specific_len(vector<int>& nums,
                            vector<vector<int>>& result,
                            vector<int>& cur, int idx, int len)
{
   /* Start from current idx and go till end of input array  *
    * at each step, if current subset length = len, add the  *
    * subset to result, else backtrack from this point       */
   for(int i = idx; i < (int)nums.size(); ++i) {
      cur.push_back(nums[i]); /* Add num[i] to cur subset    */
      if(idx + 1 == len)      /* If current subset is full   */
         result.push_back(cur); /* add it to result          */
      /* check if we can continue moving forward from idx    */
      else if(nums.size() - i + 1  >= len - cur.size())
         permutate_specific_len(nums, result, cur, i+1, len);
      cur.pop_back(); /* Remove num[i] from cur subset       */
   }
}

vector<vector<int>> subsets_backtrack(vector<int>& nums) {
   vector<vector<int> > result(1, vector<int>());
   std::sort(nums.begin(), nums.end()); /* sort input vec    */
   /* For each length generate all possible subsets          */
   for(int l = 1; l <= (int)nums.size(); ++l) {
      vector<int> cur;
      permutate_specific_len(nums, result, cur, 0, l);
   }
   return result;
}

/*--------------- Backtrack Algo End ------------------------*/
/*------------------- Iterative Algo ------------------------*/
/**
 * Iterative algorithm to create all possible subsets of     *
 * given input set. Note, this implementation is inspired by *
 * a posted solution @ Leetcode:                             *
 * Initially: [[]]                                           *
 * Adding the first number to all the existed subsets:       *
 *    [[], [1]];                                             *
 * Adding the second number to all the existed subsets:      *
 *    [[], [1], [2], [1, 2]];                                *
 * Adding the third number to all the existed subsets:       *
 *    [[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]] *
 */
vector<vector<int>> subsets_iterative(vector<int>& nums) {
   vector<vector<int>> result(1, vector<int>());
   std::sort(nums.begin(), nums.end()); /* sort input vec    */
   /* Go over the entire input array                         */
   for(int i = 0; i < (int)nums.size(); ++i) {
      int n = result.size();
      for(int j = 0; j < n; ++j) {
         result.push_back(result[j]);
         result.back().push_back(nums[i]);
      }
   }
   return result;
}
/*--------------- Iterative Algo End ------------------------*/
/*--------------------- Bitmap Algo -------------------------*/
/**
 * Bitmap algorithm to create all possible subsets of given  *
 * input set. Note, this implementation is inspired by       *
 * a posted solution @ Leetcode:                             *
 * Lets assign bits to each outcome:                         *
 *  - First bit to 1 , Second bit to 2 and third bit to 3    *
 * Also, let Take = 1 and No_take = 0                        *
 * 0) 0 0 0  -> No_take 3 , No_take 2 , No_take 1 = { }      *
 * 1) 0 0 1  -> No_take 3 , No_take 2 ,    take 1 = {1}      *
 * 2) 0 1 0  -> No_take 3 ,    take 2 , No_take 1 = {2}      *
 * 3) 0 1 1  -> No_take 3 ,    take 2 ,    take 1 = {1,2}    *
 * 4) 1 0 0  ->    take 3 , No_take 2 , No_take 1 = {3}      *
 * 5) 1 0 1  ->    take 3 , No_take 2 ,    take 1 = {1,3}    *
 * 6) 1 1 0  ->    take 3 ,    take 2 , No_take 1 = {2,3}    *
 * 7) 1 1 1  ->    take 3 ,    take 2 ,    take 1 = {1,2,3}  *
 * In the above logic ,Insert S[i] only                      *
 * if (j>>i) & 1 == true where  { j E { 0,1,2,3,4,5,6,7 }    *
 * and i = ith element in the input array                    *
 * Time Complexity = O(n * 2^n) Space Complexity = O(1)      *
 */
vector<vector<int>> subsets_bitmap(vector<int>& nums) {
   int n = std::pow(2, nums.size());
   vector<vector<int> > result(n, vector<int>());
   std::sort(nums.begin(), nums.end()); /* sort input vec    */
   /* Go over the entire solution space, fill all elems      */
   for(int i = 0; i < n; ++i) {
      for(int j = 0; j < (int)nums.size(); ++j) {
         if((i >> j) & 1)
            result[i].push_back(nums[j]);
      }
   }
   return result;
}
/*----------------- Bitmap Algo End -------------------------*/

void output_vec(vector<int>& v) {
   cout << "[";
   for (auto elem : v) cout << elem << ", ";
   cout << "]" << endl;
}

bool tester(vector<int>& inp, int num_perm) {
   bool ret;
   auto res1 = subsets_backtrack(inp);
   auto res2 = subsets_iterative(inp);
   auto res3 = subsets_bitmap(inp);
   if(res1.size() != res2.size() ||
      res1.size() != res3.size() ||
      res1.size() != (size_t)num_perm)     {
      cout << "Error: Iterative and Recursive results"
           << " dont match expected num sets!" << endl;
      cout << "Iterative result: " << endl;
      for(auto v : res1) output_vec(v);
      cout << "Recursive result: " << endl;
      for(auto v : res2) output_vec(v);
      cout << "Bitmap result: " << endl;
      for(auto v : res3) output_vec(v);
      ret = false;
   }
   else ret = true;
   return ret;
}

int main() {
   vector<int> v = {0};
   if(tester(v,  2) == false) {goto end;}
   v = {1, 2};
   if(tester(v,  4) == false) {goto end;}
   v = {4, 1, 0};
   if(tester(v,  8) == false) {goto end;}
   v = {5, 6, 7, 8};
   if(tester(v,  16) == false) {goto end;}
   cout << "Info: All manual test cases passed" << endl;
 end:
   return 0;
}
