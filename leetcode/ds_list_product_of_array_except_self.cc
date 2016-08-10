//g++-5 --std=c++11 -Wall -g -o ds_list_product_of_array_except_self ds_list_product_of_array_except_self.cc

/**
 * @file  Product of Array Except Self
 * @brief Given array compute product of all numbers except self at each index
 */

// https://leetcode.com/problems/product-of-array-except-self/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/**
 * Given an array of n integers where n > 1, nums, return an array output such
 * that output[i] is equal to the product of all the elements of nums except nums[i].
 * Solve it without division and in O(n).
 * For example, given [1,2,3,4], return [24,12,8,6].
 * Follow up:
 * Could you solve it with constant space complexity? (Note: The output array does not
 * count as extra space for the purpose of space complexity analysis.)
 */

/* Two pointers in opposite direction approach.              */
vector<int> productExceptSelf(vector<int>& nums) {
   int size = nums.size();
   vector<int> result(nums.size(), 1);
   for(int i = 0, j=nums.size()-1, fwd=1, rev=1; i < size; ++i, --j) {
      result[i] *= fwd;
      fwd       *= nums[i];
      result[j] *= rev;
      rev       *= nums[j];
   }
   return result;
}

int main()
{
   vector<int> nums, result, exp;

   nums = { 1, 2, 3, 4 };
   exp  = {24, 12, 8, 6};
   result = productExceptSelf(nums);
   if(result != exp) goto Errmain;
   
   nums = { 1, 2, 3, 4, 5 };
   exp  = { 120, 60, 40, 30, 24};
   result = productExceptSelf(nums);
   if(result != exp) goto Errmain;

   nums = { 1, 2, 0, 4, 5 };
   exp  = { 0, 0, 40,0, 0};
   result = productExceptSelf(nums);
   if(result != exp) goto Errmain;
   cout << "All test-cases passed." << endl;
   return 0;
 Errmain:
   cout << "Error: Product Except Self returned failed for - ";
   for(auto val: nums) cout << val << ", "; cout << endl;
   cout << "Expected - "; 	for(auto val: exp)    cout << val << ", "; cout << endl;
   cout << "Got      - "; 	for(auto val: result) cout << val << ", "; cout << endl;
   return -1;
}
