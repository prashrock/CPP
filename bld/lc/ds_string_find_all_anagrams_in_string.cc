//g++-5 -Wall --std=c++11 -g -o ds_string_find_all_anagrams_in_string ds_string_find_all_anagrams_in_string.cc

/**
 * @file  Find all anagrams in a string
 * @brief Given two strings, find all anagrams of one string in another
 */

// https://leetcode.com/problems/find-all-anagrams-in-a-string/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
#include <vector>            /* std::vector                  */
using namespace std;

/**
 * Given a string s and a non-empty string p, find all the start
 * indices of p's anagrams in s.
 * Strings consists of lowercase English letters only and the
 * length of both strings s and p will not be larger than 20,100.
 * The order of output does not matter.
 * Example:
 * Input:  s: "abab" p: "ab"
 * Output: [0, 1, 2]
 * Explanation:
 * The substring with start index = 0 is "ab", which is an anagram of "ab".
 * The substring with start index = 1 is "ba", which is an anagram of "ab".
 * The substring with start index = 2 is "ab", which is an anagram of "ab".
 */

/* Sliding window approach to cover all substrings in s of length p.size() *
 * Time Complexity = O(s), where s = s.size()                              */
std::vector<int> findAnagrams(std::string s, std::string p) {
   std::vector<int> smap(26, 0), pmap(26, 0); /* since only a-z allowed    */
   std::vector<int> ans;                      /* output vector             */
   /* Handle corner cases first */
   if(s.size() == 0 || p.size() == 0 || s.size() < p.size()) return ans;
   /* Add all chars in p and first p.size() chars of s into a table  */
   for(size_t i = 0; i < p.size(); ++i) {
      pmap[p[i] - 'a']++;
      smap[s[i] - 'a']++;
   }
   /* Sliding window to cover all substrings in s of size p          */
   for(size_t b = 0, e = b + p.size() - 1; e < s.size(); ++b, ++e) {
      if(b != 0) { /* If not first window, remove prev b and add e   */
         smap[s[b-1] - 'a']--;
         smap[s[e]   - 'a']++;
      }
      if(smap == pmap) ans.push_back(b); /* found anagram, add to ans*/
   }
   return ans;
}

struct test_vector {
   std::string s;
   std::string p;
   std::vector<int> exp;
};

const struct test_vector test[4] =  {
   { "",                     "cd",                  {}},
   { "abab",                 "cd",                  {}},
   { "abab",                 "ab",             {0,1,2}},
   { "cbaebabacd",           "abc",             {0, 6}},
};

int main()
{
   for(auto tst : test) {
      auto ans = findAnagrams(tst.s, tst.p);
      if(ans != tst.exp) {
         cout << "Error:find failed for '" << tst.s
              << "' '" << tst.p << "'"     << endl;
         cout << "Expected:";
         for(auto v : tst.exp) cout << v << ","; cout << endl;
         cout << "Got     :";
         for(auto v : ans)     cout << v << ","; cout << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
