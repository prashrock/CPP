//g++-5 --std=c++11 -Wall -g -o ds_string_longest_substring_without_repeating_chars ds_string_longest_substring_without_repeating_chars.cc

/**
 * @file  Longest Substring without repeating characters
 * @brief Given a string find longest substring with all unique chars
 */

// https://leetcode.com/problems/longest-substring-without-repeating-characters/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/**
 * Given a string, find the length of the longest substring without
 * repeating characters.
 * Examples:
 * Given "abcabcbb", the answer is "abc", which the length is 3.
 * Given "bbbbb", the answer is "b", with the length of 1.
 * Given "pwwkew", the answer is "wke", with the length of 3.
 * Note that the answer must be a substring, "pwke" is a subsequence
 * and not a substring.
 */

/** Approach - 1 - 2 pointer window based approach.          *
 * Use map to maintain per char cnt. For each char maintain  *
 * count of chars seen                                       *
 * Note: can use an array/vector instead of unordered_map    *
 * since we can only have 256 possible options               */
/* A char is duplicate if its seen more than once            */
int lengthOfLongestSubstring(string s) {
   int d = 0; /* longest unique substring seen so far */
   std::unordered_map<char, int> map; /* keeps count of each char seen */
   for(int b = 0, e = 0; e < (int)s.size(); ++e) {
      map[s[e]]++;               /* Add to window  */
      /* If we've found a duplicate move b forward till no duplicate   */
      for(; map[s[e]] > 1; ++b) --map[s[b]];
      /* If we reach here, there is no duplicate, record substr length */
      d = std::max(d, e - b + 1);
   }
   return d;
}

/* DP based approach to find length of longest substring     */
int lengthOfLongestSubstringDP(string s) {
   std::unordered_map<char, int> map; /* Holds last position of char */
   int begin = 0, maxlen = 0;
   for(int i = 0; i < (int)s.size(); ++i) {
      auto c = s[i];
      /* If char is already seen and is beyond our last begin */
      if(map.find(c) != map.end())
         begin = std::max(begin, map[c] + 1);
      map[c] = i;
      maxlen = std::max(maxlen, i - begin + 1);
   }
   return maxlen;
}
   
struct test_vector {
   std::string s;
   int exp;
};

const struct test_vector test[4] =  {
   { "c",                       1},
   { "abcabcbb",                3},
   { "bbbbb",                   1},
   { "pwwkew",                  3},
};

int main()
{
   for(auto tst : test) {
      auto ans = lengthOfLongestSubstring(tst.s);
      if(ans != tst.exp) {
         cout << "Error:lengthOfLongestSubstring failed. Exp "
              << tst.exp  << " Got " << ans
              << " for '" << tst.s   << "'" << endl;
         return -1;
      }
      ans = lengthOfLongestSubstringDP(tst.s);
      if(ans != tst.exp) {
         cout << "Error:lengthOfLongestSubstringDP failed. Exp "
              << tst.exp  << " Got " << ans
              << " for '" << tst.s   << "'" << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
