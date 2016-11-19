//g++-5 --std=c++11 -g -o algo_dp_wildcard_match algo_dp_wildcard_match.cc
/**
 * @file  Wildcard Match
 * @brief Match a string with pattern containing ? and *
 */

// https://leetcode.com/problems/wildcard-matching/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
using namespace std;

/**
 * Implement wildcard pattern matching with support for '?' and '*'.
 * A wildcard * can match 0 or more occurences OF ANYTHING
 *  '?' Matches any single character.
 * '*' Matches any sequence of characters (including the empty sequence).
 * The matching should cover the entire input string (not partial).
 * The function prototype should be:
 * bool isMatch(const char *s, const char *p)
 * Some examples:
 *  isMatch("aa","a") . false
 *  isMatch("aa","aa") . true
 *  isMatch("aaa","aa") . false
 *  isMatch("aa", "*") . true
 *  isMatch("aa", "a*") . true
 *  isMatch("ab", "?*") . true
 *  isMatch("aab", "c*a*b") . false
 */
/* The key difference between this and regex match is that * *
 * is a wildcard which can match 0 or more chars of ANYTHING */

inline bool isCharMatch(char s, char p) { return (s == p || p == '?'); }

/*  If there are 2+ stars adjacent, prune the 1st n-1 ones   */
void trimstar(string &p) {
   if(p.size() < 2) return;
   for(auto it = std::next(p.begin()); it != p.end();) {
      if(*it == *std::prev(it) && *it == '*') p.erase(it);
      else                                    it++;
   }
}

/* Approach 1 - Backtracking based approach                  */
bool isMatchBT(string s, string p) {
   /* Match p and s till there is failure or 1 string is over*/
   while(s.size() && p.size() && isCharMatch(s[0], p[0])) {
      p = p.substr(1);  s = s.substr(1);
   }
   /* If string p is over, check if s is also over           */
   if(p.empty())          return s.empty();
   /* Else if string s is over, prune all *s in the end of p */
   else if(s.empty())     while(p.size() && p[0] == '*') p = p.substr(1);
   /* Else if we are faced with *, prune extra * and BT      */
   else if(p[0] == '*')   {
      /* Backtrack 3 possible cases when faced with *        */
      if(isMatchBT(s.substr(1), p.substr(1))) return true;
      else if(isMatchBT(s, p.substr(1)))      return true;
      else if(isMatchBT(s.substr(1), p))      return true;
      else                                    return false;
   }
   return p.empty();
}

/* Approach 2 - DP based approach                            */
bool isMatchDP(string s, string p) {
   int n = s.size(), m = p.size();
   std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(m + 1, false));
   dp[0][0] = true; /* Zero-length string + pattern = true   */
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
         else if(p[pidx] == '*') {
            dp[i][j] = dp[i][j-1] || dp[i-1][j] || dp[i-1][j-1];
         }
      }
   }
   return dp[n][m];
}

/* State machine based approach. When * is encountered, save *
 * indexes of s and p so that if there is a mismatch later on*
 * we can come back to idx + 1 of p and s                    *
 * Inspired by Yu's blogpost @                               *
 * http://yucoding.blogspot.com/2013/02/leetcode-question-123-wildcard-matching.html */
bool isMatchState(string s, string p) {
   size_t si = 0, pi = 0;
   size_t si_prev = 0, pi_prev = 0;
   bool star = false;
   for(; si < s.size(); ) {
      if(isCharMatch(s[si], p[pi])) { ++si; ++pi; }
      /* Save current p and s indexes to return in the future*
       * Note: only p should be advanced now...              */
      else if(p[pi] == '*') {
         pi_prev = pi++; /* Save pi to pi_prev and move p    */
         si_prev = si;   /* If match fails later return here */
         star = true;
      }
      /* If no match, but star was encountered before, use it*/
      else if(star) {
         pi = pi_prev + 1;   /* Start matching p after star  */
         si = ++si_prev;     /* Continue s from last saved s */
      }
      /* If no star found and cur s and p dont' match, stop  */
      else   return false;
   }
   /* If p is not over, skip over all '*'s from current p idx*/
   while(p[pi] == '*' && pi < p.size()) pi++;
   /* Make sure all the characters in p are covered.         */
   return (pi == p.size());
}
   
struct test_vector {
   std::string s;
   std::string pat;
   bool exp;
};

const struct test_vector test[13] =  {
   { "ab", "*a",       false },
   { "b",  "*?*?*",    false },
   { "aa", "*",         true },
   { "aa","a",         false },
   { "aa","aa",         true },
   { "aaa","aa",       false },
   { "aa", "a*",        true },
   { "ab", "?*",        true },
   { "aab", "c*a*b",   false },
   { "c",  "*?*",       true },
   { "abefcdgiescdfimde", "ab*cd?i*de", true },
   { "babaaababaabababbbbbbaabaabbabababbaababbaaabbbaaab", "***bba**a*bbba**aab**b", false },
   { "",   "*",         true },
};


int main()
{
   for(auto tst : test) {
      auto p = tst.pat;
      trimstar(p);
      auto ans = isMatchBT(tst.s, p);
      if(ans != tst.exp) {
         cout << "Error:isMatchBT failed for '"
              << tst.s << "', '" << tst.pat
              << "'. Exp: " << tst.exp << endl;
         return -1;
      }
#if 0      
      ans = isMatchDP(tst.s, p);
      if(ans != tst.exp) {
         cout << "Error:isMatchDP failed for '"
              << tst.s << "', '" << tst.pat
              << "'. Exp: " << tst.exp << endl;
         return -1;
      }
#endif
      ans = isMatchState(tst.s, p);
      if(ans != tst.exp) {
         cout << "Error:isMatchState failed for '"
              << tst.s << "', '" << tst.pat
              << "'. Exp: " << tst.exp << endl;
         return -1;
      }
   }
   cout << "Info: Need to implement DP algo " << endl;
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
