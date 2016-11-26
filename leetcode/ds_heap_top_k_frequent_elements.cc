//g++-5 --std=c++11 -g -o ds_heap_top_k_frequent_elements ds_heap_top_k_frequent_elements.cc

/**
 * @file  Top K Frequent Elements
 * @brief Given non-empty array, return the k most frequent elements.
 */

// https://leetcode.com/problems/top-k-frequent-elements/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <queue>             /* std::priority_queue          */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/**
 * Given a non-empty array of integers, return the k most frequent elements.
 *
 * For example,
 * Given [1,1,1,2,2,3] and k = 2, return [1,2].
 * Note:
 * - You may assume k is always valid, 1 . k . number of unique elements.
 * - Your algorithm's time complexity must be better than O(n log n), where
 * n is the array's size.
 */


/**
 * @brief                                                    *
 * Create Hash_table to maintain all the occurence frequency *
 * Next, create a MaxHeap to sort based on frequency         */
typedef std::pair<int, int> pii_t;
vector<int> topKFrequent(vector<int>& nums, int k) {
   std::unordered_map<int, int> mp;
   std::priority_queue<pii_t, std::vector<pii_t>> maxheap;
   vector<int> result(k, 0);

   /* First update Hash-Table for element in nums.           */
   //http://stackoverflow.com/questions/12889496/does-stl-map-auto-initialize-values
   for (auto val : nums)  ++mp[val];
   /* Create a max-heap with all the elements                */
   for(auto mval : mp)  maxheap.push(std::make_pair(mval.second, mval.first));
   /* We are told that there are atleast k distinct elements */
   assert(maxheap.size() >= k);
   /* Copy from priorityqueue to vector                      */
   for(auto i=0; i<k; ++i, maxheap.pop()) result[i] = maxheap.top().second;
   return result;
}

/**
 * @brief                                                    *
 * Create Hash_table to maintain occurence frequency. Update *
 * Maxheap and result vector simultaneously                  */
typedef std::pair<int, int> pii_t;
vector<int> topKFrequent1(vector<int>& nums, int k) {
   std::unordered_map<int, int> mp;
   std::priority_queue<pii_t, std::vector<pii_t>> maxheap;
   vector<int> result;

   /* First update Hash-Table for element in nums.           */
   //http://stackoverflow.com/questions/12889496/does-stl-map-auto-initialize-values
   for (auto val : nums)  ++mp[val];

   /* Create a max-heap with all the elements */
   for(auto mval : mp) {
      maxheap.push(std::make_pair(mval.second, mval.first));
      /* If there are less than k elements in Map then we    *
       * can start moving elements to answer array           */
      if(maxheap.size() > mp.size() - k) {
         result.push_back(maxheap.top().second);
         maxheap.pop();
      }
   }
   return result;
}

struct test_vector {
   std::vector<int> nums;
   int target;
   std::vector<int> exp;
};

const struct test_vector test[2] =  {
   { {1,1,1,2,2,3}, 2, {1,2} },
   { {3,0,1,0}, 1, {0}       },
};

void dump_error(struct test_vector tst, std::vector<int> ans)
{
   for(auto e : tst.nums) cout << e << ","; cout << endl;
   cout << "Target = " << tst.target << endl;
   cout << "Expected ans: ";
   for(auto e : tst.exp) cout << e << ","; cout << endl;
   cout << " Got ans: ";
   for(auto e : ans) cout << e << ","; cout << endl;
}

int main()
{
   int ans;
   for(auto tst : test) {
      auto ans = topKFrequent(tst.nums, tst.target);
      if(ans != tst.exp) {
         cout << "Error: topK frequent test failed: ";
         dump_error(tst, ans);
         return -1;
      }
      ans = topKFrequent1(tst.nums, tst.target);
      std::sort(ans.begin(), ans.end());
      if(ans != tst.exp) {
         cout << "Error: topK frequent opt test failed: ";
         dump_error(tst, ans);
         return -1;
      }
   }
   cout << "Info: All manual tests passed successfully." << endl;
   return 0;
}
