//g++ --std=c++11 -Wall -g -o math_3sum math_3sum.cc

/**
 * @file  3Sum Exact, Smaller, Closest
 * @brief Given an array of unsorted integers, find out all a+b+c<=t
 */

// https://leetcode.com/problems/3sum-smaller/
// https://leetcode.com/problems/3sum/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
using namespace std;

/**
 * Given an array of n integers nums and a target, find the number of index triplets
 * i, j, k with 0 <= i < j < k < n that satisfy the below condition:
 * nums[i] + nums[j] + nums[k] < target.
 * For example, given nums = [-2, 0, 1, 3], and target = 2.
 * Return 2. Because there are two triplets which sums are less than 2:
 * [-2, 0, 1]
 * [-2, 0, 3]
 * Follow up: Could you solve it in O(n^2) runtime?
 */


/**
 * Use a sorted list traversal approach. First sort input.   *
 * Run an index from start to len-2. Let this index mark the *
 * 1st element (i). For each value of (i) keep two more idxs *
 * (j = i+1) and (k = n-1). Adjust both pointers j and k     *
 * to find out all 3 values of i, j, k which satisfy below:  *
 * nums[i] + nums[j] + nums[k] < target                      *
 * @param                                                    *
 *    nums - Input vector of elements                        *
 *  target - The sum to reach                                * 
 * @return                                                   *
 *   count of i,j,k pairs found                              *
 * Time Complexity = O(n^2)   Space Complexity= O(1),        *
 */
int threeSumSmaller(vector<int>& nums, int target) {
   int cnt = 0;

   std::sort(nums.begin(), nums.end());
   for(int i = 0; i < (int)nums.size() - 2; ++i) {
      for(int j = i + 1, k = nums.size() - 1; j < k;) {
         if(nums[i] + nums[j] + nums[k] < target) {
            cnt += k - (j + 1) + 1;
            //for(int l = j+1; l <= k; l++)
            //cout << nums[i] << " " << nums[j] << " " << nums[l] << endl;
            j++;
         }
         else k--;
      }
   }
   return cnt;
}

struct test_vector {
   vector<int> nums;
   int target;
   int exp;
};

const struct test_vector test_3sum_smaller[4] =  {
   {{},     0, 0},   /* no elements test-case                */
   {{1, 2}, 0, 0},   /* 2 elements test-case(need atleast 3) */
   {{1,1,-2},1,1},   /* 3 elements test-case(valid test-case)*/
   {{-2,0,1,3},2,2}, /* 4 elements test-case(valid test-case)*/
};

bool threeSumSmaller_test(){
   for(auto tst : test_3sum_smaller) {
      int ans = threeSumSmaller(tst.nums, tst.target);
      if(ans != tst.exp) {
         cout << "Error: 3Sum smaller failed for below testcase:" << endl;
         for(auto e : tst.nums) cout << e  << " ,"; cout << endl;
         cout << "target = " << tst.target << " expected=" << tst.exp
              << " got="     << ans        << endl;
         return false;
      }
   }
   cout << "Info: All manual test-cases passed for 3Sum smaller." << endl;
   return true;
}

// https://leetcode.com/problems/3sum/
/**
 * Use a sorted list traversal approach. First sort input.   *
 * Run an index from start to len-2. Let this index mark the *
 * 1st element (i). For each value of (i) keep two more idxs *
 * (j = i+1) and (k = n-1). Adjust both pointers j and k     *
 * to find out all 3 values of i, j, k which satisfy below:  *
 * nums[i] + nums[j] + nums[k] == target (0 in this case)    *
 * Note: Wasted a lot of time to handle duplicates. If there *
 * are duplicates, process them normally first time and then *
 * express skip them. Do this in outer and inner loop.       *
 * @param                                                    *
 *    nums - Input vector of elements                        *
 *  target - The sum to reach (0 in this case)               * 
 * @return                                                   *
 *   vector of i,j,k pairs found                             *
 * Time Complexity = O(n^2)   Space Complexity= O(1),        *
 * Note: Further optimizations possible - Update k within    *
 * innerloop by using upper_bound of target-(nums[i]+nums[j])*
 * This opt should improve avg time complexity of inner loop *
 */
vector<vector<int>> threeSum(vector<int>& nums) {
   vector<vector<int>> ans;
   sort(nums.begin(), nums.end());
   /* Outer loop to fix 1st pointer (nums[i])                */
   for(int i = 0; i < (int) nums.size() - 2; ++i) {
      if (i > 0 && nums[i] == nums[i-1]) continue;
      /* When nums[i] == nums[j], process this case only     *
       * once. Return second time (compare i with i-1)       */
      /* Inner loop to calc 2nd/3rd ptr - nums[j], nums[k]   */
      for(int j = i + 1, k = nums.size() - 1; j < k;) {
         int sum = nums[i] + nums[j] + nums[k];
         if     (sum < 0) j++; /* 2nd pointer too low        */
         else if(sum > 0) k--; /* 3rd pointer too high       */
         else {
            //cout<<nums[i]<<" "<<nums[j]<<" "<<nums[k]<<endl;
            ans.push_back({nums[i], nums[j], nums[k]});
            /* Prune duplicates for 2nd/3rd pointers         *
             * The key is to prune after processing once     */
            while(nums[j] == nums[j + 1]) j++;
            while(nums[k] == nums[k - 1]) k--;
            j++; k--; /* Update both 2nd/3rd ptr if match    */
         }
      }
   }
   return ans;
}

const struct test_vector test_3sum[8] =  {
   {{},     0, 0},   /* no elements test-case                */
   {{1, 2}, 0, 0},   /* 2 elements test-case(need atleast 3) */
   {{0,0,0},0, 1},   /* 3 elements valid test-case           */
   {{0,0,0,0},0,1},  /* 4 elements valid test-case           */
   {{-1,-1,2,0},0,1}, /* 4 elements valid test-case          */
   {{-1,0,1,2,-1,-4},0, 2},
   {{-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6}, 0, 6},
   {{7,-1,14,-12,-8,7,2,-15,8,8,-8,-14,-4,-5,7,9,11,-4,-15,-6,1,
     -14,4,3,10,-5,2,1,6,11,2,-2,-5,-7,-6,2,-15,11,-6,8,-4,2,1,
     -1,4,-6,-15,1,5,-15,10,14,9,-8,-6,4,-6,11,12,-15,7,-1,-9,9,
     -1,0,-4,-1,-12,-2,14,-9,7,0,-3,-4,1,-2,12,14,-10,0,5,14,-1,
     14,3,8,10,-8,8,-5,-2,6,-11,12,13,-7,-12,8,6,-13,14,-2,-5,
     -11,1,3,-6}, 0, 119},
};

bool threeSum_test(){
   for(auto tst : test_3sum) {
      auto ans = threeSum(tst.nums);
      if((int)ans.size() != tst.exp) {
         cout << "Error: 3Sum failed for below testcase:" << endl;
         for(auto e : tst.nums) cout << e  << " ,"; cout << endl;
         cout << "target = " << tst.target << " expected=" << tst.exp
              << " got="     << ans.size()        << endl;
         return false;
      }
   }
   cout << "Info: All manual test-cases passed for 3Sum." << endl;
   return true;
}

int main()
{
   if     (threeSumSmaller_test() == false) return -1;
   else if(threeSum_test() == false)        return -1;
   return 0;
}
