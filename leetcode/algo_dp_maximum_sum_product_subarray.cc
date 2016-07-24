//g++ -Wall --std=c++11 -g -o algo_dp_maximum_sum_product_subarray algo_dp_maximum_sum_product_subarray.cc

/**
 * @file  Maximum Sum & Product Subarray
 * @brief Find contiguous subarray with largest sum and product
 */

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
using namespace std;

// https://leetcode.com/problems/maximum-subarray/

/**
 * Find the contiguous subarray within an array (containing at least
 * one number) which has the largest sum.
 * For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
 * the contiguous subarray [4,-1,2,1] has the largest sum = 6.
 */

/**
 * DP based solution:                                        *
 * At each iteration compute the maximum sum. Keep two cntrs *
 * one for current positive sum and other for current total  *
 * sum (including event -ve numbers as long as sum > 0)      *
 * Time Complexity = O(n), Space Complexity = O(1)           */
int maxSubArray_DP1(vector<int>& nums) {
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
      ans = std::max({ans, locSum, glbSum});
   }
   return ans;
}

/**
 * Another DP based solution after refining above code:      *
 * mergeing locSum and glbSum into just 1 variable.          *
 * Time Complexity = O(n), Space Complexity = O(1)           */
int maxSubArray_DP2(vector<int>& nums) {
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
int maxSubArray_DC(std::vector<int>& nums, int l, int u) {
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
      int max_lsubarr = maxSubArray_DC(nums, l,   m);
      int max_rsubarr = maxSubArray_DC(nums, m+1, u);
      return std::max(max_center, std::max(max_lsubarr, max_rsubarr));
   }
}

struct test_vector {
   vector<int> nums;
   int exp;
};

const struct test_vector sum_test[10] =  {
   { {10},                           10},
   { {-2},                           -2},
   { {2,3,-2,4},                      7},
   { {2,3,-2,4,-2},                   7},
   { {-4,-3},                        -3},
   { {-2,0,-1},                       0},
   { {-4,-3,-2},                     -2},
   { {-2,3,1,3},                      7},
   { {2,-5,-2,-4,3},                  3},
   { {-2,1,-3,4,-1,2,1,-5,4},         6},
};

bool maxSum_test() {
   const std::vector<std::string> names = {"DP1", "DP2", "DC"};
   for(auto tst : sum_test) {
      for(size_t i = 0; i < names.size(); ++i) {
         int ans;
         if     (i == 0) ans = maxSubArray_DP1(tst.nums);
         else if(i == 1) ans = maxSubArray_DP2(tst.nums);
         else if(i == 2) ans = maxSubArray_DC(tst.nums, 0, tst.nums.size()-1);
         if(ans != tst.exp) {
            cout << "Error:Max Sum " << names[i] << " failed. Exp "
                 << tst.exp << " Got " << ans << " for ";
            for(auto v: tst.nums) cout  << v << ","; cout << endl;
            return false;
         }        
      }
   }
   cout << "Info: All MaxSum manual test-cases successful" << endl;
   return true;
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
 * https://leetcode.com/discuss/14235/possibly-simplest-solution-with-o-n-time-complexity *
 * Time Complexity = O(n), Space Complexity = O(1)           */
int maxProduct(vector<int>& nums) {
   int pProd, nProd, ans;
   /* Corner-case where input array is empty.                */
   if(nums.size() == 0) return 0;
   ans = pProd = nProd = nums[0];
   for(size_t i = 1; i < nums.size(); ++i) {
      if(nums[i] < 0)    std::swap(pProd, nProd);
      pProd = std::max(pProd * nums[i], nums[i]);
      nProd = std::min(nProd * nums[i], nums[i]);
      /* Note: max should compare prev max && current pmax   */
      ans   = std::max(ans, pProd);
   }
   return ans;
}

const struct test_vector product_test[10] =  {
   { {10},                           10},
   { {-2},                           -2},
   { {2,3,-2,4},                      6},
   { {2,3,-2,4,-2},                  96},   
   { {-4,-3},                        12},
   { {-2,0,-1},                       0},
   { {-4,-3,-2},                     12},
   { {-2,3,2,3},                     18},
   { {2,-5,-2,-4,3},                 24},
   { {-2,1,-3,4,-1,2,1,-5,4},       960},
};

bool maxProduct_test() {
   for(auto tst : product_test) {
      auto ans = maxProduct(tst.nums);
      if(ans != tst.exp) {
         cout << "Error:maxProduct failed. Exp "
              << tst.exp << " Got "  << ans << " for ";
         for(auto v: tst.nums) cout  << v << ","; cout << endl;
         return false;
      }
   }
   cout << "Info: All MaxProduct manual test-cases successful" << endl;
   return true;
}

int main()
{
   if(maxSum_test() == false)          return -1;
   else if(maxProduct_test() == false) return -1;
   return 0;
}
