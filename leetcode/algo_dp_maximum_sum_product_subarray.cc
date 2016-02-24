//g++ -Wall --std=c++11 -g -o algo_dp_maximum_sum_product_subarray algo_dp_maximum_sum_product_subarray.cc

/**
 * @file  Maximum Sum & Product Subarray
 * @brief Find contiguous subarray with largest sum and product
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

// https://leetcode.com/problems/maximum-subarray/

/**
 * Find the contiguous subarray within an array (containing at least
 * one number) which has the largest sum.
 * For example, given the array [.2,1,.3,4,.1,2,1,.5,4],
 * the contiguous subarray [4,.1,2,1] has the largest sum = 6.
 */

/**
 * DP based solution:                                        *
 * At each iteration compute the maximum sum. Keep two cntrs *
 * one for current positive sum and other for current total  *
 * sum (including event -ve numbers as long as sum > 0)      *
 * Time Complexity = O(n), Space Complexity = O(1)           */
int maxSubArray_firstimplementation(vector<int>& nums) {
   /* Corner-case where input array is empty.               */
   if(nums.size() == 0) return 0;
   int locSum = 0, glbSum = 0, ans = nums[0];
   for(int i = 0, n = nums.size(); i < n; ++i) {
      if(nums[i] < 0) {
	 if(glbSum + nums[i] > 0) glbSum += nums[i];
	 else                     glbSum  = nums[i];
	 locSum = nums[i];
      }
      else {
	 locSum = locSum < 0 ? nums[i] : locSum + nums[i];
	 glbSum = glbSum < 0 ? nums[i] : glbSum + nums[i];
      }
      ans = std::max(ans, std::max(locSum, glbSum));
   }
   return ans;
}

/**
 * Another DP based solution after refining above code:      *
 * mergeing locSum and glbSum into just 1 variable.          *
 * Time Complexity = O(n), Space Complexity = O(1)           */
int maxSubArray_secondimplementation(vector<int>& nums) {
   int ans = nums[0], sum = nums[0];
   for(int i = 1, n = nums.size(); i < n; ++i) {
      sum = std::max(sum + nums[i], nums[i]);
      ans = std::max(ans, sum);
   }
   return ans;
}

/**
 * Divide and Conquer approach based on Programming Pearls   *
 * Algorithm Design Techniques (page 73).                    *
 * Time Complexity = O(n lg n), Space Complexity = O(1)      */
int maxSubArray(vector<int>& nums, int l, int u) {
   if     (l  > u) return 0;
   else if(l == u) return nums[l];
   else {
      /* Select the middle element of the array. So maximum  *
       * subarray may contain that middle element or not.    *
       * If the maximum subarray does not contain middle elem*
       * recurse to left and right sub-arrays                *
       * If the maximum subarray does contain the middle elem*
       * result will be max left_prefix and max right_prefix */ 
      int m = l + (u - l)/2;
      int max_left = nums[m], max_right = nums[m+1];
      for(int i = m, sum = 0; i >= l; --i) {
	 sum += nums[i];
	 max_left = std::max(sum, max_left);
      }
      for(int i = m + 1, sum = 0; i <= u; ++i) {
	 sum += nums[i];
	 max_right = std::max(sum, max_right);
      }
      int max_center  = max_left + max_right;
      int max_lsubarr = maxSubArray(nums, l,   m);
      int max_rsubarr = maxSubArray(nums, m+1, u);
      return std::max(max_center, std::max(max_lsubarr, max_rsubarr));
   }
}

bool maxSum_test() {
   int ans1, ans2, exp;
   vector<int> nums;
   nums = {2,3,-2,4}; exp = 7;
   ans1 = maxSubArray_firstimplementation(nums);
   ans2 = maxSubArray_secondimplementation(nums);
   if(ans1 != exp || ans2 != exp)  goto ErrMaxSum;
   nums = {2,3,-2,4,-2}; exp = 7;
   ans1 = maxSubArray_firstimplementation(nums);
   ans2 = maxSubArray_secondimplementation(nums);
   if(ans1 != exp || ans2 != exp)  goto ErrMaxSum;
   nums = {-4, -3}; exp = -3;
   ans1 = maxSubArray_firstimplementation(nums);
   ans2 = maxSubArray_secondimplementation(nums);
   if(ans1 != exp || ans2 != exp)  goto ErrMaxSum;	
   nums = {-2, 0, -1}; exp = 0;
   ans1 = maxSubArray_firstimplementation(nums);
   ans2 = maxSubArray_secondimplementation(nums);
   if(ans1 != exp || ans2 != exp)  goto ErrMaxSum;
   nums = {-4, -3, -2}; exp = -2;
   ans1 = maxSubArray_firstimplementation(nums);
   ans2 = maxSubArray_secondimplementation(nums);
   if(ans1 != exp || ans2 != exp)  goto ErrMaxSum;
   nums = {-2, 3, 1, 3}; exp = 7;
   ans1 = maxSubArray_firstimplementation(nums);
   ans2 = maxSubArray_secondimplementation(nums);
   if(ans1 != exp || ans2 != exp)  goto ErrMaxSum;
   nums = {2,-5,-2,-4,3}; exp = 3;
   ans1 = maxSubArray_firstimplementation(nums);
   ans2 = maxSubArray_secondimplementation(nums);
   if(ans1 != exp || ans2 != exp)  goto ErrMaxSum;
   nums = {-2}; exp = -2;
   ans1 = maxSubArray_firstimplementation(nums);
   ans2 = maxSubArray_secondimplementation(nums);
   if(ans1 != exp || ans2 != exp)  goto ErrMaxSum;
   nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};  exp = 6;
   ans1 = maxSubArray_firstimplementation(nums);
   ans2 = maxSubArray_secondimplementation(nums);
   if(ans1 != exp || ans2 != exp)  goto ErrMaxSum;
   cout << "Info: All MaxSum manual test-cases passed" << endl;
   return true;
ErrMaxSum:
   cout << "Error: Failed for the below case:" << endl;
   for(auto e : nums) cout << e << " ,";
   cout << "    Expected = " << exp
        << " ans1 got = " << ans1
        << " ans2 got = " << ans2 << endl;
   return false;
}
	
// https://leetcode.com/problems/maximum-product-subarray/

/**
 * Find the contiguous subarray within an array (containing at
 * least one number) which has the largest product.
 * For example, given the array [2,3,-2,4],
 * the contiguous subarray [2,3] has the largest product = 6.
 */

/**
 * DP based solution:                                        *
 * Inspired by solution @ Leetcode                           *
 * https://leetcode.com/discuss/14235/possibly-simplest-solution-with-o-n-time-complexity                                                   *
 * Time Complexity = O(n), Space Complexity = O(1)           */
int maxProduct(vector<int>& nums) {
   int pProd, nProd, ans;
   /* Corner-case where input array is empty.               */
   if(nums.size() == 0) return 0;
   ans = pProd = nProd = nums[0];
   for(int i = 1; i < (int) nums.size(); ++i) {
      if(nums[i] < 0) std::swap(pProd, nProd);
      pProd = std::max(pProd * nums[i], nums[i]);
      nProd = std::min(nProd * nums[i], nums[i]);
      /* Note: max should compare prev max && current pmax */
      ans   = std::max(ans, pProd);
   }
   return ans;
}

bool maxProduct_test() {
   int ans, exp;
   vector<int> nums;
   nums = {2,3,-2,4};
   ans = maxProduct(nums); exp = 6;
   if(ans != exp)  goto ErrMaxProduct;
   nums = {2,3,-2,4,-2};
   ans = maxProduct(nums); exp = 96;
   if(ans != exp) goto ErrMaxProduct;
   nums = {-4, -3};
   ans = maxProduct(nums); exp = 12;
   if(ans != exp) goto ErrMaxProduct;
   nums = {-2, 0, -1};
   ans = maxProduct(nums); exp = 0;
   if(ans != exp)  goto ErrMaxProduct;
   nums = {-4, -3, -2};
   ans = maxProduct(nums); exp = 12;
   if(ans != exp)  goto ErrMaxProduct;
   nums = {2,-5,-2,-4,3};
   ans = maxProduct(nums); exp = 24;
   if(ans != exp)  goto ErrMaxProduct;
   nums = {-2};
   ans = maxProduct(nums); exp = -2;
   if(ans != exp)  goto ErrMaxProduct;
   cout << "Info: All MaxProduct manual test-cases successful" << endl;
   return true;
ErrMaxProduct:
   cout << "Error: Failed for the below case:" << endl;
   for(auto e : nums) cout << e << " ,";
   cout << "    Expected = " << exp << " got = " << ans << endl;
   return false;
}

int main()
{
   if(maxSum_test() == false)          return -1;
   else if(maxProduct_test() == false) return -1;
   return 0;
}
