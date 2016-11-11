//g++-5 --std=c++11 -g -Wall -Werror -o ds_string_sort_chars_by_frequency ds_string_sort_chars_by_frequency.cc

/**
 * @file  Sort characters by frequency
 * @brief Given a string, sort it in descending order based on freq of chars
 */

// https://leetcode.com/problems/sort-characters-by-frequency/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
#include <queue>             /* std::priority_queue          */
using namespace std;

/*
 * Given a string, sort it in decreasing order based on the frequency
 * of characters.
 * Example 1:
 * Input:  "tree"
 * Output: "eert"
 * Explanation: 'e' appears twice while 'r' and 't' both appear once.
 *  So 'e' must appear before both 'r' and 't'. Therefore "eetr" is
 * also a valid answer.
 * Example 2:
 * Input:  "cccaaa"
 * Output: "cccaaa"
 * Explanation: Both 'c' and 'a' appear three times, so "aaaccc" is
 * also a valid answer. Note that "cacaca" is incorrect, as the same
 * characters must be together.
 * Example 3:
 * Input:  "Aabb"
 * Output: "bbAa"
 * Explanation: "bbaA" is also a valid answer, but "Aabb" is incorrect.
 * Note that 'A' and 'a' are treated as two different characters.
 */

/* Approach 1 - Hash-table + Sort + Freq Table               */ 
/* Use a hash-table + custom sort lambda expression          *
 * Time complexity = O(nlgn) Space complexity = O(m) m chars */
std::string frequencySort1(std::string s) {
   std::vector<int> freqTable(128, 0);
   /* Maintain a freq table to maintain count of each char   */
   for(auto c : s) freqTable[c]++;
   /* Implement custom sort with a lambda expression         */
   std::sort(s.begin(), s.end(), [&](const char a, const char b) {
         return ( (freqTable[a] > freqTable[b]) ||
                  ((freqTable[a] == freqTable[b]) && a > b));
      });
   return s;
}

/* Approach 2 - Priority Queue + Freq Table                  *
 * Time Complexity = O(nlgn) Space Complexity = O(n)         *
 * Although worst-case complexity is bad,this performs better*
 * when there are a lot of repetitions in the input string   */
typedef std::pair<int, unsigned char> piu_t;

std::string frequencySort2(std::string s) {
   std::vector<int> freqTable(128, 0);
   std::priority_queue<piu_t, std::vector<piu_t>, std::less<piu_t>> max_heap;
   std::string ans;
   for(auto c : s) freqTable[c]++;
   /* For all characters ' ','0-9','A-Z','a-z', if it occurs *
    * in the input string add it to the priority queue       */
   for(unsigned char i = ' '; i <= 'z'; ++i)
      if(freqTable[i]) max_heap.push({freqTable[i], i});
   for(; !max_heap.empty(); max_heap.pop()) {
      auto piu = max_heap.top();
      /* Add as many occurences as found in input to output  */
      for(int i = 0; i < piu.first; ++i) ans.push_back(piu.second);
   }
   return ans;
}

struct test_vector {
   std::string s;
   std::string exp;
};

const struct test_vector test[5] =  {
   {"",                                               ""},
   {"tree",                                       "eetr"},
   {"cccaaa",                                   "cccaaa"},
   {"Aabb",                                       "bbaA"},
   {"his s he a ha he  ha ae", "        hhhhhaaaaeeessi"},
};

int main()
{
   for(auto tst : test) {
      auto ans = frequencySort1(tst.s);
      if(ans != tst.exp) {
         cout << "Error:frequencySort1 failed for "
              << tst.s << " "
              << " Exp:" << tst.exp
              << " Got:" << ans << endl; 
         return -1;
      }
      ans = frequencySort2(tst.s);
      if(ans != tst.exp) {
         cout << "Error:frequencySort2 failed for "
              << tst.s << " "
              << " Exp:" << tst.exp
              << " Got:" << ans << endl; 
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
