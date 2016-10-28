//g++-5 --std=c++11 -Wall -g -o ds_hash_group_anagrams ds_hash_group_anagrams.cc

/**
 * @file  Group Anagrams
 * @brief Given a list of strings, group them into anagrams
 */

// https://leetcode.com/problems/anagrams/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <unordered_map>     /* std::unordered_map           */
using namespace std;

/*
 * Given an array of strings, group anagrams together.
 * For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
 * Return:
 * [ ["ate", "eat","tea"],
 *   ["nat","tan"],
 *   ["bat"] ]
 * Note: All inputs will be in lower-case.
 */


/** @brief: Use a hash-table to store each group of anagrams.*
 * The key to hash-table must be unique for all members of   *
 * the group. Use sorted string as the key.                  */
vector<vector<string>> groupAnagrams(vector<string>& strs) {
   std::unordered_map<string, std::vector<string>> map;
   for(auto s : strs) {
      auto key = s; /* Cannot sort input string, make a copy */
      std::sort(key.begin(), key.end());
      if(map.find(key) == map.end()) map[key] = {s};
      else                           map[key].push_back(s);
   }
   /* All anagrams are grouped. Just go over hash-table and   *
    * create the result vector.                               */
   std::vector<std::vector<string>> ans;
   for(auto it = map.begin(); it != map.end(); ++it)
      ans.push_back(it->second);
   return ans;
}

struct test_vector {
   std::vector<std::string> s;
   std::vector<std::vector<std::string>> exp;
};

const struct test_vector test[2] =  {
   { {""},         {{""}} },
   { {"eat", "tea", "tan", "ate", "nat", "bat"},
     {{"bat"}, {"tan","nat"}, {"eat", "tea", "ate"}} },
};
   
int main()
{
   for(auto tst : test) {
      auto ans = groupAnagrams(tst.s);
      if(ans != tst.exp) {
         cout << "Error:groupAnagrams failed for ";
         for(auto s : tst.s) cout << s << ",";
         cout << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
