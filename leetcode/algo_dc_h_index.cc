//g++ --std=c++11 -Wall -g -o algo_dc_h_index algo_dc_h_index.cc

/**
 * @file  H-Index
 * @brief Find index H-index (atleast H numbers greater than H)
 */

// https://leetcode.com/problems/h-index/

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
 * Given an array of citations (each citation is a non-negative integer)
 * of a researcher, write a function to compute the researcher's h-index.
 * According to the definition of h-index on Wikipedia: "A scientist has
 * index h if h of his/her N papers have at least h citations each, and
 * the other N . h papers have no more than h citations each."
 * For example, given citations = [3, 0, 6, 1, 5], which means the
 * researcher has 5 papers in total and each of them had received
 * 3, 0, 6, 1, 5 citations respectively. Since the researcher has 3
 * papers with at least 3 citations each and the remaining two with no
 * more than 3 citations each, his h-index is 3.
 * Note: If there are several possible values for h, the maximum one is
 * taken as the h-index.
 * Hint:
 * An easy approach is to sort the array first.
 * What are the possible values of h-index?
 * A faster approach is to use extra space.
 */

/**
 * @brief: Implement Binary Search to calculate H-Index      *
 * Time Complexity = O(lg n).   Space Complexity = O(1)      */
int hIndex(vector<int>& citations) {
   int ans = 0;
   if(citations.size() == 0)      return ans;
   std::sort(citations.begin(), citations.end());
   /* Loop invariant: first <= last. Each time, list size is *
    * reduced into half and we search only 1 half            */
   for(int n = citations.size(), first = 0, last = n-1; first <= last;) {
      /* if n is even, mid will point to smaller mid element */
      int mid = first + (last - first) / 2;
      if(citations[mid] >= n-mid) ans   = n - mid;
      if(citations[mid] < n-mid)  first = mid + 1;
      else                        last  = mid - 1;
   }
   return ans;
}

int main()
{
   vector<int> nums;
   int exp, ans;
   /* Craft a bunch of manual test-cases for this prob  */
   nums = {}; exp = 0;
   ans  = hIndex(nums);
   if(ans != exp) goto Errmain;

   nums = {0}; exp = 0;
   ans  = hIndex(nums);
   if(ans != exp) goto Errmain;
   
   nums = {1}; exp = 1;
   ans  = hIndex(nums);
   if(ans != exp) goto Errmain;

   nums = {100}; exp = 1;
   ans  = hIndex(nums);
   if(ans != exp) goto Errmain;

   nums = {0, 1}; exp = 1;
   ans  = hIndex(nums);
   if(ans != exp) goto Errmain;
   
   nums = {3, 0, 6, 1, 5}; exp = 3;
   ans  = hIndex(nums);
   if(ans != exp) goto Errmain;

   nums = {4,1,2,7,5,3,1}; exp = 3;
   ans  = hIndex(nums);
   if(ans != exp) goto Errmain;
   
   cout << "Info: All manual test-cases passed." << endl;
   return 0;
 Errmain:
   cout << "Error: hIndex failed for input: ";
   for(auto e : nums) cout << e << ","; cout << endl;
   cout << " Expected = " << exp << " Got = " << ans << endl;
   return -1;
}
