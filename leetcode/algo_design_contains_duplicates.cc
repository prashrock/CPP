//g++-5 --std=c++11 -Wall -g -o algo_design_contains_duplicates algo_design_contains_duplicates.cc

/**
 * @file  Sliding Window - Contains duplicates
 * @brief Find out if there are duplicates within a range
 */

// https://leetcode.com/problems/contains-duplicate/
// https://leetcode.com/problems/contains-duplicate-ii/
// https://leetcode.com/problems/contains-duplicate-iii/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include <set>               /* std::set container           */
#include <unordered_set>     /* std::unordered_set container */
using namespace std;

// https://leetcode.com/problems/contains-duplicate/
/**
 * Given an array of integers, find if the array contains any
 * duplicates. Your function should return true if any value
 * appears at least twice in the array, and it should return
 * false if every element is distinct.
 */
/* Use an unordered_set as a hash_table to find duplicates    */
bool containsDuplicate(vector<int>& nums) {
   std::unordered_set<int> num_set;
   for(auto num : nums) {
      if(num_set.find(num) == num_set.end()) num_set.insert(num);
      else                                   return true;
   }
   return false;
}

// https://leetcode.com/problems/contains-duplicate-ii/
/**
 * Given an array of integers and an integer k, find out
 * whether there are two distinct indices i and j in the
 * array such that nums[i] = nums[j] and the difference
 * between i and j is at most k.
 */
/* Use unordered set with simple sliding window              */
bool containsNearbyDuplicate(vector<int>& nums, int k) {
   if (k <= 0)                      return false;
   else if (k >= (int)nums.size())  k = nums.size() - 1;
   std::unordered_set<int> ns;
   for(int i = 0; i < (int)nums.size(); ++i) {
      if(i > k) ns.erase(nums[i - k - 1]);
      if(ns.find(nums[i]) == ns.end()) ns.insert(nums[i]);
      else                          return true;
   }
   return false;
}

// https://leetcode.com/problems/contains-duplicate-iii/
/**
 * Given an array of integers, find out whether there are
 * two distinct indices i and j in the array such that the
 * difference between nums[i] and nums[j] is at most t and
 * the difference between i and j is at most k.
 */
/* Sliding Window with an extra condition. Need to use a     *
 * set since we need order within sliding window             */
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
   if (k <= 0)                          return false;
   else if (k >= (int)nums.size())      k = nums.size() - 1;
   std::set<int> window;
   for(int i = 0; i < (int)nums.size(); ++i) {
      /* First constraint - retain only atmost k elements    */
      if(i > k) window.erase(nums[i - k - 1]);
      auto it = window.lower_bound(nums[i] - t);
      /* Find out if there are no matching elements inside   *
       * the sliding window first before inserting new elem  */
      if(it == window.end() || std::abs(nums[i] - *it) > t)
         window.insert(nums[i]);
      else return true;
   }
   return false;
}

/* Test-case vectors   */
struct test_dup {
   std::vector<int> nums;
   bool exp;
};

const struct test_dup testI[3] = {
   { {},               false  },
   { {1, 2},           false  },
   { {1, 1, 2},        true   },
};

struct test_nearbydups {
   std::vector<int> nums;
   int k;
   bool exp;
};

const struct test_nearbydups testII[2] = {
   { {},        0,        false  },
   { {-1, -1},  1,        true   },
};

struct test_nearbyalmostdups {
   std::vector<int> nums;
   int k;
   int t;
   bool exp;
};

const struct test_nearbyalmostdups testIII[3] = {
   { {},             0,      0,        false},
   { {-1, -1},       1,     -1,        false},
   { {-5, 2, 5},     2,      3,        true},
};

int main()
{
   for(auto tst : testI) {
      auto ans = containsDuplicate(tst.nums);
      if(ans != tst.exp) {
         cout << "Error:containsDuplicates failed for: ";
         for(auto v : tst.nums) cout << v << ",";
         cout << endl;
         return false;
      }
   }
   for(auto tst : testII) {
      auto ans = containsNearbyDuplicate(tst.nums, tst.k);
      if(ans != tst.exp) {
         cout << "Error:containsNearbyDuplicate failed for: ";
         for(auto v : tst.nums) cout << v << ",";
         cout << endl;
         return false;
      }
   }
   for(auto tst : testIII) {
      auto ans = containsNearbyAlmostDuplicate(tst.nums, tst.k, tst.t);
      if(ans != tst.exp) {
         cout << "Error:containsNearbyAlmostDuplicate failed for: ";
         for(auto v : tst.nums) cout << v << ",";
         cout << endl;
         return false;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
