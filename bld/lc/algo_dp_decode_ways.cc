//g++-5 --std=c++11 -g -o algo_dp_decode_ways algo_dp_decode_ways.cc
/**
 * @file  Decode ways
 * @brief Find out #distinct ways to decode a string
 */

// https://leetcode.com/problems/decode-ways/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
using namespace std;

/**
 * A message containing letters from A-Z is being encoded to
 * numbers using the following mapping:
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 * Given an encoded message containing digits, determine the
 * total number of ways to decode it.
 * For example,
 * Given encoded message "12", it could be decoded as
 * "AB" (1 2) or "L" (12).
 * The number of ways decoding "12" is 2.
 */

inline bool isValid(char a, char b) {
   return (a == '1' || (a == '2' && b <= '6'));
}
inline bool isValid(char a) { return a != '0'; }

/** Top-Down DP solution (Note: problem similar to 1-2 steps *
 * and fibonacci series)                                     *
 * When n <= 0, the number of ways to decode is 0            *
 * When n = 1, #ways to decode depends on if s[0] is valid   *
 * When n > 2, #ways to decode depends on if s[0] but is     *
 * equal to #ways to reach n-1 + #ways to reach n-2 pos.     *
 * This is because, n-1 and n-2 do not overlap (1 step from  *
 * n-1 to reach n and 2 steps from n-2 to reach n)           *
 * Time Complexity = O(n), Space Complexity = O(n)           */
int numDecodingsTopDown(std::string& s) {
   const int n = s.size();
   if(n == 0) return n;
   else if(n == 1) return isValid(s[0]);
   std::vector<int> dp(s.size() + 1, 0);
   dp[0] = 1;
   dp[1] = isValid(s[0]) ? 1 : 0;
   for(int i = 1, dpi = i + 1; i < n; ++i, ++dpi) {
      if(isValid(s[i]))          dp[dpi] += dp[dpi-1];
      if(isValid(s[i-1], s[i]))  dp[dpi] += dp[dpi-2];
   }
   return dp[n];
}

/** An optimization over the regular top-down approach to not*
 * consume any extra space. O(1) space complexity            */
int numDecodingsTopDownNoSpace(std::string& s) {
   const int n = s.size();
   if(n == 0) return n;
   else if(n == 1) return isValid(s[0]);
   int old = 1, cur = isValid(s[0]) ? 1 : 0;
   for(int i = 1; i < n; ++i) {
      int tmp = 0;
      if(isValid(s[i]))          tmp = cur;
      if(isValid(s[i-1], s[i]))  tmp += old;
      old = cur;
      cur = tmp;
   }
   return cur;
}

/* Bottom-Up DP inspired by                    *
 * https://discuss.leetcode.com/topic/2562/dp-solution-java-for-reference/25 */
int numDecodingsBottomUp(std::string& s) {
   const int n = s.size();
   if(n == 0) return n;
   else if(n == 1) return isValid(s[0]);
   std::vector<int> dp(s.size() + 1, 0);
   dp[n]   = 1;
   dp[n-1] = isValid(s[n-1]) ? 1 : 0;
   for(int i = n-2; i >= 0; --i) {
      if(isValid(s[i]) == false)        continue;
      else if(isValid(s[i], s[i+1]))    dp[i] = dp[i + 1] + dp[i + 2];
      else                              dp[i] = dp[i + 1];
   }
   return dp[0];
}

struct test_vector {
   std::string decode;
   int exp_num_ways;
};

const struct test_vector test[10] =  {
   {"",          0},
   {"0",         0},
   {"9",         1},
   {"10",        1},
   {"211",       3},
   {"1211",      5},
   {"12110",     3},
   {"121100",    0},
   {"11211",     8},
   {"112711",    6},
};

int main()
{
   for(auto tst : test) {
      auto ans = numDecodingsBottomUp(tst.decode);
      if(ans != tst.exp_num_ways) {
         cout << "Error:numDecodingsBottomUp failed for '"
              << tst.decode << "'. Exp: " << tst.exp_num_ways
              << " Got: " << ans << endl;
         return -1;
      }
      ans = numDecodingsTopDown(tst.decode);
      if(ans != tst.exp_num_ways) {
         cout << "Error:numDecodingsTopDown failed for '"
              << tst.decode << "'. Exp: " << tst.exp_num_ways
              << " Got: " << ans << endl;
         return -1;
      }
      ans = numDecodingsTopDownNoSpace(tst.decode);
      if(ans != tst.exp_num_ways) {
         cout << "Error:numDecodingsTopDownNoSpace failed for '"
              << tst.decode << "'. Exp: " << tst.exp_num_ways
              << " Got: " << ans << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}



