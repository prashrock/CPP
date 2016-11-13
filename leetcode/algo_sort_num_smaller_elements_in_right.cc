//g++-5 -Wall --std=c++11 -g -o algo_sort_num_smaller_elements_in_right algo_sort_num_smaller_elements_in_right.cc

/**
 * @file  Count number of smaller elements to right
 */

// https://leetcode.com/problems/count-of-smaller-numbers-after-self/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <set>               /* std::multiset                */
using namespace std;


/**
 * You are given an integer array nums and you have to return a new counts
 * array. The counts array has the property where counts[i] is the number
 * of smaller elements to the right of nums[i].
 * Example:
 * Given nums = [5, 2, 6, 1]
 * To the right of 5 there are 2 smaller elements (2 and 1).
 * To the right of 2 there is only 1 smaller element (1).
 * To the right of 6 there is 1 smaller element (1).
 * To the right of 1 there is 0 smaller element.
 * Return the array [2, 1, 1, 0].
 */

/* --------------------Approach:1--------------------------- */
/** STL BST based approach using STL Multiset (duplicates)   *
 * Time Complexity = O(n^2).   Space Complexity = O(n)       *
 * Note: Multiset's iterators aren't random access iterators *
 * causing std::distance to be O(n) complexity               */
vector<int> countSmaller1(vector<int>& nums) {
   multiset<int> ms;
   vector<int> ans(nums.size(), 0);
   /*insert each number, calculate distance & store it in ans*/
   for(int i = nums.size()-1; i >= 0; i--) {
      auto it = std::lower_bound(ms.begin(), ms.end(), nums[i]);
      ans[i] = std::distance(ms.begin(), it);
      ms.insert(nums[i]);
   }
   return ans;
}

/* --------------------Approach:2--------------------------- */
/** Insertion sort based approach with STL vectors           *
 * Time Complexity = O(n^2). Space Complexity = O(n)         *
 * Note: worst case complexity of insertion sort is O(n^2)   *
 * but average case is O(n lg n), so this is acceptable      *
 * Note: Distance in random access iterator is O(1)          */
vector<int> countSmaller2(vector<int>& nums) {
   vector<int> ans(nums.size(), 0), sorted;
   for(int i = nums.size()-1; i >= 0; i--) {
      auto it = std::lower_bound(sorted.begin(), sorted.end(), nums[i]);
      ans[i] = std::distance(sorted.begin(), it);
      sorted.insert(it, nums[i]);
   }
   return ans;
}


/* Approach 3 - BST + Rank after each insert                 */
/* https://discuss.leetcode.com/topic/43595/c-36ms-bst-solution */

/* Approach 4 - Merge sort + Count-inversions at each index  */
/** Recursive Merge sort approach with inversion counting    *
 * Time Complexity = O(n lg n).   Space Complexity = O(n)    */
struct vi {int idx; int val;}; /* Hold value and original pos*/

/* Pre-condition: nums[b:mid] and nums[mid+1:e] are sorted   */
void merge(std::vector<vi>& nums,   std::vector<vi>& tmp,
           std::vector<int>& invcnt,int b, int mid, int e) {
   for(int i = b, j = mid + 1, k = b, inverted = 0; k <= e; ++k) {
      if(i <= mid && j <= e) {
         if(nums[j].val < nums[i].val) { tmp[k] = nums[j++]; inverted++; }
         else     { invcnt[nums[i].idx] += inverted; tmp[k] = nums[i++]; }
      }
      else if(i <= mid) {invcnt[nums[i].idx] += inverted; tmp[k]=nums[i++];}
      else               tmp[k] = nums[j++];
   }
}

void mergeSortInvCnt(std::vector<vi>& nums, std::vector<vi>& tmp,
                     std::vector<int>& invcnt, int b, int e) {
   if(e <= b) return;            /* base-case of merge-sort  */
   int mid = b + (e - b) / 2;
   mergeSortInvCnt(tmp, nums, invcnt, b,     mid);
   mergeSortInvCnt(tmp, nums, invcnt, mid+1, e);
   merge(tmp, nums, invcnt, b, mid, e);
}

std::vector<int> countSmaller4(std::vector<int>& vals) {
   std::vector<int> invcnt(vals.size(), 0);
   std::vector<vi>  nums(vals.size()), tmp(vals.size());
   for(int i = 0; i < (int)vals.size(); ++i)
      nums[i] = tmp[i] = {i, vals[i]};
   mergeSortInvCnt(nums, tmp, invcnt, 0, nums.size()-1);
   return invcnt;
}


struct test_vector {
   std::vector<int> nums;
   std::vector<int> exp;
};

const struct test_vector test[3] =  {
   {{2, 0, 1},            {2, 0, 0}},
   {{5, 2, 6, 1},      {2, 1, 1, 0}},
   {{-1, -1},                {0, 0}},
};

void dump(const vector<int> &a) {
   for(auto val: a) cout << val << ", "; cout << endl;
}

bool match(const vector<int> &a, const vector<int> &b) {
   return std::equal(a.begin(), a.end(), b.begin());
}

void error_dump(const std::string name, const vector<int> &a,
                const vector<int> &ans, const vector<int> &expected) {
   cout << "Error: Failed at " << name;
   cout << " for input: "; dump(a);
   cout << "       Expected: "; dump(expected);
   cout << "       Got: ";      dump(ans);
}

int main()
{
   for(auto tst : test) {
      auto nums = tst.nums;
      auto ans = countSmaller1(nums);
      if(match(ans, tst.exp) == false) {
         error_dump("countSmaller1", tst.nums, ans, tst.exp);
         return -1;
      }
      nums = tst.nums;
      ans = countSmaller2(nums);
      if(match(ans, tst.exp) == false) {
         error_dump("countSmaller2", tst.nums, ans, tst.exp);
         return -1;
      }
      nums = tst.nums;
      ans = countSmaller4(nums);
      if(match(ans, tst.exp) == false) {
         error_dump("countSmaller4", tst.nums, ans, tst.exp);
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
