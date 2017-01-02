//g++-5 --std=c++11 -Wall  -g -o ds_list_find_all_duplicates_in_array ds_list_find_all_duplicates_in_array.cc

/**
 * @file  Find all Duplicates in an array
 * @brief Find all Duplicates in an array
 */

// https://leetcode.com/problems/find-all-duplicates-in-an-array/
// https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
using namespace std;

// https://leetcode.com/problems/find-all-duplicates-in-an-array/
/**
 * Given an array of integers, 1 <= a[i] <= n (n = size of array),
 * some elements appear twice and others appear once.
 * Find all the elements that appear twice in this array.
 * Could you do it without extra space and in O(n) runtime?
 * Example:
 * Input: [4,3,2,7,8,2,3,1]     Output: [2,3]
 */

/* @note: Need a bitmap of size n to track 2nd occurence. Since  *
 * input is all +ve, to get O(1) space, instead of using a       *
 * separate bitmap, toggle respective index to -ve when we find  *
 * an element. All indexes which are -ve are duplicate           */
vector<int> findDuplicates(vector<int>& nums) {
   std::vector<int> ans;
   for(size_t i = 0; i < nums.size(); ++i) {
      int idx  = std::abs(nums[i]) - 1;
      /* If num is +ve, seeing it first time, so toggle to -ve   */
      if(nums[idx] > 0)   nums[idx]= -std::abs(nums[idx]);
      /* If num is -ve, this is 2nd time we are seeing this #    */
      else                ans.push_back(idx+1);
   }
   return ans;
}

// https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
/**
 * Given an array of integers where 1 <= a[i] <= n (n = size of array),
 * some elements appear twice and others appear once.
 * Find all the elements of [1, n] inclusive that do not appear in this array.
 * Could you do it without extra space and in O(n) runtime?
 * You may assume the returned list does not count as extra space.
 * Example:
 * Input: [4,3,2,7,8,2,3,1]     Output: [5,6]
 */

/* @note: Need a bitmap of size n to track duplicates in [1,n)   *
 * Since input is all +ve, to get O(1) space, instead of using a *
 * separate bitmap, toggle respective index to -ve when we find  *
 * an element. All indexes which are +ve are missing             *
 * Inspired by https://discuss.leetcode.com/topic/65738/java-accepted-simple-solution */
std::vector<int> findDisappearedNumbers(std::vector<int>& nums) {
   std::vector<int> ans;
   for(size_t i = 0; i < nums.size(); ++i) {
      int idx  = std::abs(nums[i]) - 1;
      nums[idx]= -std::abs(nums[idx]);  /* Avoid if -ve check    */
   }
   for(size_t i = 0; i < nums.size(); ++i)
      if(nums[i] > 0) ans.push_back(i + 1);
   return ans;
}

struct test_vector {
   std::vector<int> nums;
   std::vector<int> exp;
};

const struct test_vector test_duplicates[4] =  {
   { {},                      {} },
   { {1},                     {} },
   { {1,1},                  {1} },
   { {4,3,2,7,8,2,3,1},    {2,3} },
};

const struct test_vector test_disappeared[4] =  {
   { {},                       {} },
   { {1},                      {} },
   { {2,3,3},                 {1} },
   { {4,3,2,7,8,2,3,1},     {5,6} },
};

int main()
{
   for(auto tst : test_duplicates) {
      auto ans = findDuplicates(tst.nums);
      if(ans != tst.exp) {
         cout << "Error: findDuplicates failed. " << endl << "Exp: ";
         for(auto v: tst.exp)  cout << v << ","; cout << endl;
         cout << "Got: ";
         for(auto v: ans)      cout << v << ","; cout << endl;
         cout << "For: ";
         for(auto v: tst.nums) cout << v << ","; cout << endl;
         return -1;
      }
   }
   for(auto tst : test_disappeared) {
      auto ans = findDisappearedNumbers(tst.nums);
      if(ans != tst.exp) {
         cout << "Error: findDisappearedNumbers failed. " << endl << "Exp: ";
         for(auto v: tst.exp)  cout << v << ","; cout << endl;
         cout << "Got: ";
         for(auto v: ans)      cout << v << ","; cout << endl;
         cout << "For: ";
         for(auto v: tst.nums) cout << v << ","; cout << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
