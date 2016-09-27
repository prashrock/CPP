//g++-5 -Wall --std=c++11 -g -o ds_string_length_of_last_word ds_string_length_of_last_word.cc

/**
 * @file  String length of last word
 * @brief Return length of the last word in the string
 */

// https://leetcode.com/problems/length-of-last-word/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
using namespace std;

/*
 * Given a string s consists of upper/lower-case alphabets and
 * empty space characters ' ', return the length of last word
 * in the string.
 * If the last word does not exist, return 0.
 * Note: A word is defined as a character sequence consists of
 * non-space characters only.
 * For example,
 * Given s = "Hello World", return 5.
 */

/** Go from the last char. First, skip all the spaces        *
 * Next, find the length of the first word                   */
int lengthOfLastWord_Iterator(string s) {
   /* Start from the last character in the string s          */
   auto rit_b = s.rbegin();
   /* Loop to skip all the spaces.                           */
   for(; rit_b != s.rend() && *rit_b == ' '; ++rit_b) ;
   if(rit_b == s.rend()) return 0; /* If no more char, ret 0 */
   /* Start from the next char, and proceed till next space  */
   auto rit_e = rit_b + 1;
   for(; rit_e != s.rend() && *rit_e != ' '; ++rit_e) ;
   return std::distance(rit_b, rit_e); /* length = distance  */
}

/** Go from the last char. Maintain a length counter only if *
 *  a non-space char is encountered. Stop after 1 full word  */
int lengthOfLastWord_manual(string s) {
   int lastlen = 0;
   /* Go from last char of string till 1 word or first char  */
   for(int i = s.size() - 1; i >= 0; --i) {
      /* If space, check if its after 1st word to break      */
      if(std::isspace(s[i])) { if(lastlen) break; }
      /* Else means non-space char, this must be the 1st word*/
      else                                 lastlen++;
   }
   return lastlen;
}

struct test_vector {
   std::string str;
   int exp_length;
};

const struct test_vector tests[6] =   {
   {"",                                0},
   {"     ",                           0},
   {"a",                               1},
   {"a ",                              1},
   {"Hello World",                     5},
   {"well this is a very long ",       4},
};

int main()
{
   for(auto tst : tests) {
      auto ans = lengthOfLastWord_Iterator(tst.str);
      if(ans != tst.exp_length) {
         cout << "Error: lengthOfLastWord_Iterator failed for below testcase:" << endl;
         cout << " For '" << tst.str << "' expected=" << tst.exp_length
              << " got=" << ans  << endl;
         return -1;
      }
      ans = lengthOfLastWord_manual(tst.str);
      if(ans != tst.exp_length) {
         cout << "Error: lengthOfLastWord_manual failed for below testcase:" << endl;
         cout << " For '" << tst.str << "' expected=" << tst.exp_length
              << " got=" << ans  << endl;
         return -1;
      }
   }
   cout << "Info: All manual test-cases passed." << endl;
   return 0;
}
