//g++-5 --std=c++11 -Wall -g -o ds_hash_longest_consecutive_seq ds_hash_longest_consecutive_seq.cc

/**
 * @file  Longest Consecutive Sequence
 * @brief Given unsorted array, find length of longest consecutive sequence
 */

// https://leetcode.com/problems/longest-consecutive-sequence/

/**
 * Given an unsorted array of integers, find the length of the longest
 * consecutive elements sequence.
 * For example,
 * Given [100, 4, 200, 1, 3, 2],
 * The longest consecutive elements sequence is [1, 2, 3, 4].
 * Return its length: 4.
 * Note: Your algorithm should run in O(n) complexity.
 */

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map           */
using namespace std;

/* Use DFS to visit all consecutive numbers of a given val   */
int dfs_consecutive(std::unordered_map<int, int>& mp, int val) {
   int up=val+1, down=val-1;
   while(mp.find(up) != mp.end() || mp.find(down) != mp.end()) {
      auto uit = mp.find(up), dit = mp.find(down);
      if(uit != mp.end()) {mp[val]++; mp.erase(uit); up++;  }
      if(dit != mp.end()) {mp[val]++; mp.erase(dit); down--;}
   }
   return mp[val];
}

/* Use a HashTable to find and track consecutive numbers. Use*
 * DFS to traverse around every given node                   *
 * Time_Complexity=O(n), Space_Complexity=O(n)               */
int longestConsecutive(vector<int>& nums) {
   int ans = 1;
   std::unordered_map<int, int> mp; /* consecutive cnt       */

   /* Initialize unordered_map with vector                   */
   for(auto val : nums) mp[val] = 1;

   /* Pick up any random element and DFS search around it    */
   while( !mp.empty() ) {
      auto it = mp.begin(); /* random first node from Map    */
      int key = it->first;  /* get node's key                */
      /* Current max is either old or current DFS traversal  */
      ans = std::max(ans, dfs_consecutive(mp, key));
      mp.erase(it);  /* Remove current processed node        */
   }
   return ans;
}

struct test_vector {
   std::vector<int> X;
   int exp;
};

const struct test_vector test[2] =  {
   {{9,1,-3,2,4,8,3,-1,6,-2,-4,7}, 4},
   {{100, 4, 200, 1, 3, 2},        4},
};
	
int main()
{
   for(auto tst : test) {
      auto ans = longestConsecutive(tst.X);
      if(ans != tst.exp) {
         cout << "Error:longestConsecutive failed for: ";
         for(auto v : tst.X) cout << v << ",";   cout << endl;
         cout << " exp " << tst.exp << " got " << ans << endl;
         return -1;
      }
   }
   cout << "Info: All manual test-cases passed successfully" << endl;
   return 0;
}
