//g++-5 --std=c++11 -g -Wall -Werror -o ds_graph_word_break ds_graph_word_break.cc

/**
 * @file Word Break
 * @brief Go from start to end word through dictionary
 */

// https://leetcode.com/problems/word-break/

#include <iostream>          /* std::cout                    */
#include <cmath>             /* pow                          */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include <string>            /* std::string                  */
#include <unordered_set>     /* std::unordered_set container */
using namespace std;

/**
 * Given a string 's' and a dictionary of words dict, determine
 * if 's' can be segmented into a space-separated sequence of
 * one or more dictionary words.
 * For example, given
 * s    = "leetcode",
 * dict = ["leet", "code"].
 * Return true because "leetcode" can be segmented as "leet code".
 */

/** @brief Run a BFS of words over the input string          *
 * @note Dictionary words picked with repetition             */
bool wordBreak(string s, unordered_set<string>& wordDict) {
   if(s.size() == 0)             return true;
   else if(wordDict.size() == 0) return false;
   for(auto word : wordDict) {
      int cnt = 0;
      while(word == s.substr(cnt * word.size(), word.size())) cnt++;
      if(cnt) {
         auto ret = wordBreak(s.substr(cnt * word.size()), wordDict);
         if(ret == true) return ret;
      }
   }
   return false;
}

struct test_vector {
   std::string s;
   std::unordered_set<std::string> dict;
   bool exp;
};

const struct test_vector testv[6] =  {
   {"",         {"leet","code"}, true  },
   {"leetcode", {},              false },
   {"leetcode", {"leet","code"}, true  },
   {"leetcodea",{"leet","code"}, false },
   {"bb",       {"a","b","bbb","bbbb"}, true},
   { "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"}, false },
};

int main() {
   for(auto tst : testv) {
      auto ans = wordBreak(tst.s, tst.dict);
      if(ans != tst.exp) {
         cout << "Error:wordBreak failed. Exp "
              << tst.exp << " Got " << ans << " for string '"
              << tst.s   << "' " << tst.dict.size() << endl;
         return -1;
      }
   }
   cout << "Info: All manual test-cases passed" << endl;	
   return 0;
}
