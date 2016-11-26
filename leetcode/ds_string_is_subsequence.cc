//g++-5 -Wall --std=c++11 -g -o ds_string_is_subsequence ds_string_is_subsequence.cc

/**
 * @file  String is subsequence
 * @brief Find out if one string is sub-sequence of another
 */

// https://leetcode.com/problems/is-subsequence/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
using namespace std;

/*
 * Given a string s and a string t, check if s is subsequence of t.
 * You may assume that there is only lower case English letters in
 * both s and t. t is potentially a very long (length ~= 500,000)
 * string, and s is a short string (<=100).
 * A subsequence of a string is a new string which is formed from
 * the original string by deleting some (can be none) of the
 * characters without disturbing the relative positions of the
 * remaining characters. (ie, "ace" is a subsequence of "abcde"
 * while "aec" is not).
 * Example 1:  s = "abc", t = "ahbgdc", Return true.
 * Example 2:  s = "axc", t = "ahbgdc"  Return false.
 * Follow up:
 * If there are lots of incoming S, say S1, S2, ... , Sk
 * where k >= 1B, and you want to check one by one to see if T
 * has its subsequence. In this scenario, how would you change your code?
 */

/** Maintain one idx for t and one for s. Increment sidx only*
 *  upon a match while incrementing tidx through a loop      *
 *  Time Complexity = O(t)       Space Complexity = O(1)     */
bool isSubsequence(string s, string t) {
   if(t.size() < s.size()) return false;
   int si = 0;
   for(int ti = 0; si < (int)s.size() && ti < (int)t.size(); ++ti)
      if(s[si] == t[ti]) si++;
   return (si == (int)s.size());
}

/* To handle multiple S's, two approaches:
 * 1) Maintain first occurence of each char in a map and use as offset
 * 2) Maintain a sorted list of indexes (one per char) and do binary
      search to find the next occurence of s's idx in t
 */

struct test_vector {
   std::string s;
   std::string t;
   bool exp;
};

const struct test_vector tests[2] =   {
   { "abc",              "ahbgdc",    true  },
   { "axc",              "ahbgdc",    false },
};

int main()
{
   for(auto tst : tests) {
      auto ans = isSubsequence(tst.s, tst.t);
      if(ans != tst.exp) {
         cout << "Error: isSubsequence failed for below testcase:" << endl;
         cout << " For '" << tst.s << "," << tst.t << "' expected=" << tst.exp
              << " got=" << ans  << endl;
         return -1;
      }
   }
   cout << "Info: All manual test-cases passed." << endl;
   return 0;
}
