//g++-5 -Wall --std=c++11 -g -o ds_string_reverse_words ds_string_reverse_words.cc

/**
 * @file  Reverse Words in a String
 * @brief Given an input string, reverse the string word by word
 */

// https://leetcode.com/problems/reverse-string/
// https://leetcode.com/problems/reverse-vowels-of-a-string/
// https://leetcode.com/problems/reverse-words-in-a-string/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/* 
 * Write a function that takes a string as input and returns the
 * string reversed.
 * Example: Given s = "hello", return "olleh".
 */
/* @brief, forward and reverse index, iterate till they meet */
string reverseString(std::string& s) {
   for(int i = 0, j = (int)s.size()-1; i < j; ++i, --j)
      std::swap(s[i], s[j]);
   return s;
}


/*
 * Write a function that takes a string as input and reverse only
 * the vowels of a string.
 * Example 1: Given s = "hello", return "holle".
 * Example 2: Given s = "leetcode", return "leotcede".
 */
string reverseVowels(std::string s) {
   const std::string vowels = "aeiouAEIOU";
   for(int i = 0, j = (int)s.size()-1; i < j; ) {
      /* Move the left pointer till we hit a vowel           */
      while(i < j && vowels.find(s[i]) == std::string::npos) i++;
      /* Move the right pointer till we hit a vowel          */
      while(i < j && vowels.find(s[j]) == std::string::npos) j--;
      /* If we reach here and indexes are valid, time to swap*/
      if(i < j) std::swap(s[i++], s[j--]);
   }
   return s;
}

/*
 * Given an input string, reverse the string word by word.
 * For example,
 * Given s = "the sky is blue",
 * return "blue is sky the".
 */

/* @brief: Not the most optimal, but hopefully the simplest  *
 * implementation which breaks it into multiple sub-problems *
 * Note: Refer also to my Github C in-place implementation:  *
 * https://github.com/prashrock/C/blob/master/string/string_api.h#L198 */
void reverseWords(std::string &s) {
   auto fit = s.begin();   /* Define fwd iterator            */
   auto rit = s.rbegin();  /* Define rev iterator            */
   
   /* Handle ltrim and rtrim first in a given string         */
   for(; fit != s.end()  && std::isspace(*fit); ++fit);
   for(; rit != s.rend() && std::isspace(*rit); ++rit);
   if(fit == s.end()) s = "";  /* If string is all blank     */
   else               s = std::string(fit, rit.base());

   if(s.size() == 0)  return; /* base case - string empty    */
   
   /* Next trim extra spaces inbetween words                 */
   for(fit = std::next(s.begin()); fit != s.end(); )
      if(std::isspace(*fit) && *fit == *std::prev(fit)) s.erase(fit);
      else                                              ++fit;
  
  /* Next rotate the entire string char by char              */
  for(fit = s.begin(), rit = s.rbegin(); fit < rit.base(); ++fit, ++rit)
     std::swap(*fit, *rit);
  
  /* Last rotate each word without moving spaces             */
  for(auto fit = s.begin(), sfit = s.begin(); sfit != s.end();
      fit = std::next(sfit)) {
     sfit = std::find(fit, s.end(), ' ');
     std::reverse(fit, sfit);
  }
}

/* Do two reversals. First reversal, blindly reverse entire  *
 * string. Next, for each word, find its end point and copy  *
 * it in reverse fashion                                     *
 * Time Complexity = O(2n) Space Complextiy = O(1)           */
void reverseWords2(std::string &s) {
   /* First - Reverse the entire string including spaces     */
   std::reverse(s.begin(), s.end());
   int cur = 0; /* Currently occupied index                  */
   /* Go over the entire string and maintain cur store ptr   *
    * and the length of the last word (to reverse)           */
   for(int i = 0, len = 0; i < (int)s.size(); ++i, len = 0) {
      /* Push forward anytime we see a space character       */
      if(std::isspace(s[i])) continue; 
      /* Stay within while loop till end of while loop. Move *
       * current word from idx i to idx cur and maintain len */
      while( i < (int)s.size() && !std::isspace(s[i]) ) {
         s[cur++] = s[i++]; /* Move word from i to cur       */
         len++;             /* Book-keeping: len of cur word */
      }
      /* We have a word right now, reverse it and a space    */
      std::reverse(s.begin() + cur - len, s.begin() + cur);
      s[cur++] = ' ';
      
   }
   /* Last word has a space at its end, so don't account it  */
   if(cur) cur--;
   s.erase(s.begin()+cur, s.end());
}
   
struct test_vector {
   std::string inp;
   std::string exp;
};

const struct test_vector test[7] =  {
   { "",    ""},
   { "   ", ""},
   { "the  sky is blue", "blue is sky the"},
   { "   the sky  is blue", "blue is sky the"},
   { "the sky is  blue   ", "blue is sky the"},
   { "   the  sky is  blue   ", "blue is sky the"},
   { "   wazzaaaaap   ", "wazzaaaaap"},
};

int main()
{
   for(auto tst : test) {
      std::string ans1(tst.inp), ans2(tst.inp);
      reverseWords(ans1);
      if(ans1 != tst.exp) {
         cout << "Error:reverseWords failed. Exp '"
              << tst.exp << "' Got '" << ans1
              << "' for '" << tst.inp << "'" << endl;
         return -1;
      }
      reverseWords2(ans2);
      if(ans2 != tst.exp) {
         cout << "Error:reverseWords2 failed. Exp '"
              << tst.exp << "' Got '" << ans2
              << "' for '" << tst.inp << "'" << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
