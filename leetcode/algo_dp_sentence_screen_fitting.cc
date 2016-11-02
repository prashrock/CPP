//g++-5 --std=c++11 -g -Wall -o algo_dp_sentence_screen_fitting algo_dp_sentence_screen_fitting.cc

/**
 * @file  Sentence Screen Fitting
 * @brief How many sentences can fit in a window
 */

// https://leetcode.com/problems/sentence-screen-fitting/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include <string>            /* std::string                  */
using namespace std;

/**
 * Given a rows x cols screen and a sentence represented by a list
 * of words, find how many times the given sentence can be fitted
 * on the screen.
 * Note: A word cannot be split into two lines.
 * The order of words in the sentence must remain unchanged.
 * Two consecutive words in a line must be separated by a single space.
 * Total words in the sentence wont exceed 100.
 * Length of each word won't exceed 10.
 * 1 <= rows, cols <= 20,000
 * Note: The character '-' signifies an empty space on the screen.
 * Example 1:
 * Input: rows = 2, cols = 8, sentence = ["hello", "world"]
 * Output: 1
 * Explanation:
 *     hello---
 *     world---
 * Example 2:
 * Input: rows = 3, cols = 6, sentence = ["a", "bcd", "e"]
 * Output: 2
 * Explanation:
 *     a-bcd-
 *     e-a---
 *     bcd-e-
 * Example 3:
 * Input: rows = 4, cols = 5, sentence = ["I", "had", "apple", "pie"]
 * Output: 1
 * Explanation:
 *     I-had
 *     apple
 *     pie-I
 *     had--
 */

/**
 * @brief Greedy solution to pack strings (Note: TLE @ Leet) *
 * Time Complexity = O(rows x cols)   Space Complexity = O(1)*/
int wordsTypingGreedy(vector<string>& sentence, int rows, int cols) {
   if(sentence.empty())  return -1;
   unsigned i = 0;
   int cur_sz = 0, n = sentence.size();
   for(int r = 0; r < rows; ++r) {
      for(int c = 0; c < cols; c++) {
         if(cur_sz == 0) cur_sz = sentence[i % n].size();
         if(c + cur_sz <= cols) { c += cur_sz; cur_sz = 0; i++; }
         else                  break;
      }
      /* If entire string fits in one line, then multiply by *
       * number of rows to get the total # repetitions       */
      if(i % n == 0) { i = i * rows / (r + 1);  break; }
   }
   return i / n;
}

/**
 * @brief DP solution. Store the last seen space at each idx *
 * Go row by row, find the last word to store and maintain a *
 * running count of characters stored so far.                *
 * Time Complexity = O(rows + #chars) Space Complexity = O(chars) *
 * Inspired by https://discuss.leetcode.com/topic/62455/21ms-18-lines-java-solution/5                                                       */
int wordsTypingDP(vector<string>& sentence, int rows, int cols) {
   std::string s; /* concat sentence vector into one string  */
   for(auto& sen : sentence) s += sen + " "; /* add ' ' to s */
   /* Use a DP table (size of sentence) to keep last seen ' '*/
   std::vector<int> dp(s.size(), 0);
   int ccount = 0, len = s.size();
   for(int i = 1; i < (int)dp.size(); ++i) {
      if(s[i] == ' ') dp[i] = 1;
      else            dp[i] = dp[i-1] - 1; /* prev space pos */
   }
   /*for example given given {"abc", "de"} 3 rows and 2 cols *
    * the DP table = [0  -1  -2  1  0  -1  1  ]              */
   for(int i = 0; i < rows; ++i) {
      ccount += cols;  /* Assume all chars can be placed first */
      ccount += dp[ccount % len]; /* Find last seen space    */
   }
   /* #chars that can be stored in outp / #chars in sentence */
   return ccount / len; 
}


struct test_vector {
   std::vector<std::string> sentence;
   int rows;
   int cols;
   int exp;
};

const struct test_vector test[10] =  {
   {{"hello","world"}, 2, 8,                       1},
   {{"I", "had", "apple", "pie"}, 4, 5,            1},
   {{"a", "bcd", "e"}, 3, 6,                       2},
   {{"hello","leetcode"}, 1, 10,                   0},
   {{"a","b","c"}, 3, 1,                           1},
   {{"a"}, 20000, 20000,                           200000000},
   {{"f","p","a"}, 8, 7,                           10},
   {{"try","to","be","better"}, 10000, 9001,       5293333},
   {{"abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r","abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r","abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r","abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r","abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r","abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r","abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r","abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r","abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r","abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r"}, 19948, 19994,       848587},
   {{"tpgl","brqe","wvvquojeh","vehbhsj","nicowu","fejqky","elg","vwpbsm","wsmplm","tijf","gtuujjesu","zatkqbmeq","qerucwer","pevdflxvo","ndagbkbqft","gbm","dqnunyiw","qa","yhumy","qh","nfprt","dpj","bkctxwbbgc","mbqqnkyi","kdn","mzunp","xrgegcu","vxfxmmqf","ruqwclx","bbauvgyaru","djpyxbbt","vmgeld","mwvvspgklq","tmqtq","nubymta","qqzeqg","wh","tul","imawmqasy","ovxoihtuz","c","tvlrtkk","g","mnqp","fscwh","ou","oq","vnghd","zptoo","cl","huhjecx","iurshssq","fijpr","xmusn","stscdep","xoyywgn","sxvgynnb","b","lnlueyomlg","f","j","exn","wltqouopqv","ulo","v","ud","vucvtms","hzkbswn","ix","tovtl","lbrqmx","vg","m","hynilg","juqa","gxrjmxzbc","pcydkl","vqsinyfb","lxcg","kjulwo","pwfpjtiw","cefvbkogi","rjxvcximeo","xxgx","osda","ocvw","aydcul","xmgva","heiuq","a","rlbncaa","kf","i","uwyajpdeb","yqnis","glrhniazyf","ixslvy","neaqh","psxpdzrq","y"}, 20000, 20000,    618181},
};

int main()
{
   for(auto tst : test) {
      auto ans = wordsTypingGreedy(tst.sentence, tst.rows, tst.cols);
      if(ans != tst.exp) {
         cout << "Error:wordsTypingGreedy failed. Exp "
              << tst.exp << " Got " << ans
              << " for rows=" << tst.rows << " cols=" << tst.cols << endl;
         return -1;
      }
      ans = wordsTypingDP(tst.sentence, tst.rows, tst.cols);
      if(ans != tst.exp) {
         cout << "Error:wordsTypingDP failed. Exp "
              << tst.exp << " Got " << ans
              << " for rows=" << tst.rows << " cols=" << tst.cols << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
