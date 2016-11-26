//g++-5 --std=c++11 -g -o algo_dp_regex_match algo_dp_regex_match.cc
/**
 * @file  Regex Match
 * @brief Match a string with pattern containing . and *
 */

// https://leetcode.com/problems/regular-expression-matching/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
using namespace std;

/**
 * Implement regular expression matching with support for '.' and '*'.
 * '.' Matches any single character.
 * '*' Matches zero or more of the preceding element.
 * The matching should cover the entire input string (not partial).
 * The function prototype should be:
 * bool isMatch(const char *s, const char *p)
 * Some examples:
 *  isMatch("aa","a") . false
 *  isMatch("aa","aa") . true
 *  isMatch("aaa","aa") . false
 *  isMatch("aa", "a*") . true
 *  isMatch("aa", ".*") . true
 *  isMatch("ab", ".*") . true
 *  isMatch("aab", "c*a*b") . true
 */

/* Note: look at the wildcard matching problem before this   */

inline bool isCharMatch(const char str_c, const char pat_c) {
   return (str_c == pat_c || pat_c == '.');
}

/* Approach 1 - Backtracking based approach                  */
bool isMatchBT1(string s, string p) {
   /* If pattern is over then check if string is also over   */
   if(p.empty())                                  return (s.empty());
   /* If string empty (and pattern is not), pattern might be *
    * full of c*, which can all be ignored, continue match   */
   if(s.empty())
      return (p.size() > 1 && p[1] == '*' && isMatchBT1(s, p.substr(2)));
   /* If this is the last pattern char, or next is not '*'   */
   if(p.size() == 1 || p[1] != '*')
      return isCharMatch(s[0], p[0]) && isMatchBT1(s.substr(1), p.substr(1));
   /* This is a * based pattern. First check for Null pat and*
    * then check each subsequent char of the string s        */
   else
      return (isMatchBT1(s, p.substr(2)) ||
              (isCharMatch(s[0], p[0]) && isMatchBT1(s.substr(1), p)));
   
}

/* Approach 2 - Backtracking based approach                  */
bool isMatchBT2(string s, string p) {
   /* If pattern is over then check if string is also over   */
   if(p.empty())                                  return (s.empty());
   /* If this is the last pattern char, or next is not '*'   */
   if(p.size() == 1 || p[1] != '*') {
      if(s.empty() || !isCharMatch(s[0], p[0]))   return false;
      else            return isMatchBT2(s.substr(1), p.substr(1));
   }
   /* Next pat char is a *, so accomodate for '.*' or 'c*'   */
   while(s.size() && isCharMatch(s[0], p[0])) {
      /* Since s is pruned in the while loop, only need to   *
       * check for zero-length match case (next char in pat) */
      if(isMatchBT2(s, p.substr(2)))               return true;
      s = s.substr(1); /* prune s (move s forward by 1)      */
   }
   /* If we are here, then we just finished a match c* match *
    * and have not updated 'p' yet. Instead of updating p and*
    * manually checking, use recursion to check the remaining*
    * chars in s                                             */
   return isMatchBT2(s, p.substr(2));
}

/* Approach 3 - Dynammic Programming based approach          */
bool isMatchDP(std::string s, std::string p) {
   int n = s.size(), m = p.size();
   std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(m + 1, false));
   dp[0][0] = true; /* Zero-length string + pattern = true   */
   /* Propagate pattern *'s for a zero-length string 's'     */
   for(int j = 2; j <= m; ++j) {
      int pidx = j - 1; /* pidx is the index into string p   */
      if(p[pidx] == '*') dp[0][j] = dp[0][j-2];
   }
   for(int i = 1; i <= n; ++i) {
      for(int j = 1; j <= m; ++j) {
         int sidx = i - 1, pidx = j - 1;
         /* If current char in s and p match, then move on   */
         if(isCharMatch(s[sidx], p[pidx])) dp[i][j] = dp[i-1][j-1];
         /* If current char in p is '*', then two cases:     *
          * 1) If pat char before * does not match s char    *
          *    then try for 0-length pattern match OR        *
          * 2) If previous pattern char matches current s    *
          *    check if that answer works as well            */
         else if(p[pidx] == '*' && pidx > 0) {
            dp[i][j] = dp[i][j-2] |
                       (isCharMatch(s[sidx], p[pidx-1]) & dp[i-1][j]);
         }
      }
   }
   return dp[n][m];
}
   
struct test_vector {
   std::string s;
   std::string pat;
   bool exp;
};

const struct test_vector test[13] =  {
   {  "aa",     "a",        false },
   {  "aa",    "aa",         true },
   { "aaa",    "aa",        false },
   {  "aa",    ".*",         true },
   {  "aa",    "a*",         true },
   {  "ab",    ".*",         true },
   {  "ab",    ".*",         true },
   { "aab", "c*a*b",         true },
   {   "a", ".*..a*",       false },
   {"abcd",    "d*",        false },
   {   "a",   "ab*",         true },
   { "aaa",   "ab*a*c*a",    true },
   { "aasdfasdfasdfasdfas", "aasdf.*asdf.*asdf.*asdf.*s", true },
};


int main()
{
   for(auto tst : test) {
      auto ans = isMatchBT1(tst.s, tst.pat);
      if(ans != tst.exp) {
         cout << "Error:isMatchBT1 failed for '"
              << tst.s << ", '" << tst.pat
              << "'. Exp: " << tst.exp << endl;
         return -1;
      }
      ans = isMatchBT2(tst.s, tst.pat);
      if(ans != tst.exp) {
         cout << "Error:isMatchBT2 failed for '"
              << tst.s << ", '" << tst.pat
              << "'. Exp: " << tst.exp << endl;
         return -1;
      }
      ans = isMatchDP(tst.s, tst.pat);
      if(ans != tst.exp) {
         cout << "Error:isMatchDP failed for '"
              << tst.s << ", '" << tst.pat
              << "'. Exp: " << tst.exp << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
