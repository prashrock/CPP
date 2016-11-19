//g++-5 --std=c++11 -Wall -g -o ds_string_longest_substring_with_atmost_k_distinct_chars ds_string_longest_substring_with_atmost_k_distinct_chars.cc

/**
 * @file  Longest Substring with At Most Two Distinct Characters
 * @brief Given a string find longest substring with atmost 2 unique chars
 */

// https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/
// https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/**
 * Given a string, find the length of the longest substring T
 * that contains at most 2 distinct characters.
 * For example, Given s = .eceba.,
 * T is "ece" which its length is 3.
 */

/* Note - check out Longest Substring without repeating chars problem as well */

/**
 * 2 pointer window based approach. Use map to maintain per  *
 * char cnt. For each char maintain count of chars seen      *
 * Note: can use an array/vector instead of unordered_map    *
 * since we can only have 256 possible options               */
int lengthOfLongestSubstringKDistinct(string s, size_t k) {
   int d = 0;          /* maximum distance with 2 characters */
   std::unordered_map<char, int> map; /* maintaint char cnt  */
   /* Move only the end pointer e in the outer loop.         */
   for(size_t b = 0, e = 0; e < s.size(); ++e) {
      auto c = s[e];
      map[c]++;
      /* Atmost k distinct chars allowed. So if more than k  *
       * distinct chars seen within window move b forward    */
      for(; map.size() > k; ++b) {
         c = s[b];
         if(--map[c] == 0) map.erase(c);
      }
      d = std::max(d, (int)(e - b + 1));
   }
   return d;
}

struct test_vector {
   std::string s;
   int k;
   int exp;
};

const struct test_vector test[6] =  {
   {"",        2,                0 },
   {"e",       0,                0 },
   {"ee",      2,                2 },
   {"eceba",   3,                4 },
   {"aac",     2,                3 },
   {"bacc",    1,                2 },
};

int main()
{
   for(auto tst : test) {
      auto ans = lengthOfLongestSubstringKDistinct(tst.s, tst.k);
      if(ans != tst.exp) {
         cout << "Error:lengthOfLongestSubstringKDistinct failed. Exp "
              << tst.exp  << " Got " << ans
              << " for '" << tst.s   << "' and k=" << tst.k << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
