//g++ -Wall --std=c++11 -g -o ds_string_int_to_words ds_string_int_to_words.cc

/**
 * @file  Integer to English Words
 * @brief Convert a non-negative integer to its english words representation.
 *        Given input is guaranteed to be less than 231 - 1.
 */

// https://leetcode.com/problems/integer-to-english-words/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/**
 * For example,
 * 123 -> "One Hundred Twenty Three"
 * 12345 -> "Twelve Thousand Three Hundred Forty Five"
 * 1234567 -> "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
 */

const vector<string> suffix    = {"", " Thousand", " Million", " Billion"};
const vector<string> below_10  = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
const vector<string> below_20  = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
const vector<string> below_100 = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
const int ZERO = 0, TEN = 10, TWENTY = 20, HUNDRED = 100, THOUSAND = 1000, MILLION = 1000000, BILLION = 1000000000;

/** Approach 1                                               *
 * Almost iterative/modular approach to convert num to str   */
string StringifyIntHundred(int num) {
   if(num < 10)      return below_10[num];
   else if(num < 20) return below_20[num-10];
   else if(num % 10) return below_100[num/10] + " " + below_10[num % 10];
   else              return below_100[num/10];
}
string StringifyIntThousand(int num) {
   string ans = "";
   if(num >= 100) ans += below_10[num/100] + " Hundred";
   num %= 100;
   if(num) {
      if(ans.size()) ans += " ";
      ans += StringifyIntHundred(num);
   }
   return ans;
}
string numberToWords2(int num) {
   if(num == 0) return "Zero";
   string ans;
	
   for(int i = 0; num; num/=THOUSAND, ++i) {
      int part = num % THOUSAND;
      if(ans.size() && ans[0] != ' ')  ans = " " + ans;
      if(part) ans = StringifyIntThousand(part) + suffix[i] + ans;
   }
   return ans;
}


/** Approach 2                                               *
 * Recursive approach to convert number to string            */
string numToWordsRec(int num) {
   if     (num >= BILLION)
      return numToWordsRec(num/BILLION) + " Billion" + numToWordsRec(num%BILLION);
   else if(num >= MILLION)
      return numToWordsRec(num/MILLION) + " Million" + numToWordsRec(num%MILLION);
   else if(num >= THOUSAND)
      return numToWordsRec(num/THOUSAND) + " Thousand" + numToWordsRec(num%THOUSAND);
   else if(num >= HUNDRED)
      return numToWordsRec(num/HUNDRED) + " Hundred" + numToWordsRec(num%HUNDRED);
   else if(num >= TWENTY)
      return " " + below_100[num/TEN] +  numToWordsRec(num%TEN);
   else if(num >= TEN)
      return " " + below_20[num-TEN];
   else if(num > ZERO)
      return " " + below_10[num];
   else
      return "";
}
string numberToWords(int num) {
   if(num == 0) return "Zero";
   else         return  numToWordsRec(num).substr(1);
}

struct test_vector {
   int X;
   std::string exp;
};

const struct test_vector test[12] =  {
   {123, "One Hundred Twenty Three"},
   {12345, "Twelve Thousand Three Hundred Forty Five"},
   {1234567, "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"},
   {1234567891, "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"},
   {0, "Zero"},
   {10, "Ten"},
   {20, "Twenty"},
   {21, "Twenty One"},
   {200, "Two Hundred"},
   {1000, "One Thousand"},
   {10000, "Ten Thousand"},
   {1000010, "One Million Ten"},
};

int main()
{
   for(auto tst : test) {
      auto ans = numberToWords(tst.X);
      if(ans != tst.exp) {
         cout << "Error:numberToWords failed for " << tst.X 
              << " exp " << tst.exp << " got "     << ans << endl;
         return -1;
      }
      ans = numberToWords2(tst.X);
      if(ans != tst.exp) {
         cout << "Error:numberToWords2 failed for " << tst.X 
              << " exp " << tst.exp << " got "      << ans << endl;
         return -1;
      }
   }
   cout << "Success: Program talks English numbers well :)" << endl;	
   return 0;
   
}
