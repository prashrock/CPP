//g++-5 -Wall --std=c++11 -g -o ds_string_int_to_roman_numerals ds_string_int_to_roman_numerals.cc

/**
 * @file  Integer to Roman Numerals
 * @brief Given an integer, convert it to a roman numeral.
 */

// https://leetcode.com/problems/integer-to-roman/

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

/**
 * Given an integer, convert it to a roman numeral.
 * Input is guaranteed to be within the range from 1 to 3999.
 * Gotchas:
 * A smaller number in front of a larger number means subtraction, all
 * else means addition. For example, IV means 4, VI means 6.
 * You would not put more than one smaller number in front of a larger
 * number to subtract. For example, IIV would not mean 3.
 * You must separate ones, tens, hundreds, and thousands as separate items.
 * That means that 99 is XCIX, 90 + 9, but never should be written as IC.
 * Similarly, 999 cannot be IM and 1999 cannot be MIM.
 * Few more rules:
 * A letter repeats its value that many times (XXX = 30, CC = 200, etc.).
 * A letter can only be repeated three times.
 * If one or more letters are placed after another letter of greater value,
 * add that amount.
 * If a letter is placed before another letter of greater value, subtract
 * that amount.
 * Several rules apply for subtracting amounts from Roman numerals:
 *  - a. Only subtract powers of ten (I, X, or C, but not V or L)
 *  - b. Only subtract one number from another.
 *  - c. Do not subtract a number from one that is more than 10 times greater
 * (that is, you can subtract 1 from 10 [IX] but not 1 from 20.there is no
 * such number as IXX.)
 * A bar placed on top of a letter or string of letters increases the
 * numeral's value by 1,000 times.
 */

typedef std::pair<int, std::string> pis_t;
const vector<pis_t> numerals  = {{1,    "I"},
                                 {4,   "IV"}, {5,    "V"},
                                 {9,   "IX"}, {10,   "X"},
                                 {40,  "XL"}, {50,   "L"},
                                 {90,  "XC"}, {100,  "C"},
                                 {400, "CD"}, {500,  "D"},
                                 {900, "CM"}, {1000, "M"}};

	
string intToRoman(int num) {
   string ans;
   const int max_numeral = numerals[numerals.size() - 1].first;
   while(num) {
      /* Returns an iterator pointing to first element in    *
       * range [first, last) that is greater/equal to value  */
      auto it = std::lower_bound(numerals.begin(), numerals.end(),
                                 std::make_pair(num, string(" ")));
      /* If number is bigger than max, lowerbound corner case*/
      if(max_numeral < num)            it = std::prev(it, 1);
      /* If lower bound could not be found, we are done here */
      else if(it == numerals.end())    break;
      /* Lower bound returns an iter pointing to the first   *
       * element in range [first,last) that is **not less**  *
       * than value. If *it!=num, we have bigger#,so go back */
      else if(it->first != num)        it = std::prev(it, 1);
      //cout << "lower bound got " << it->first << " "
      //     << it->second << " for " << num << endl;
      ans += it->second;
      num -= it->first;
   }
   return ans;
}

struct test_vector {
   int X;
   std::string exp;
};

const struct test_vector test[7] =  {
   {   5,    "V"},
   {   1,    "I"},
   {   3,  "III"},
   {  90,   "XC"},
   {  99, "XCIX"},
   { 101,   "CI"},
   {1001,   "MI"},
};

int main()
{
   for(auto tst : test) {
      auto ans = intToRoman(tst.X);
      if(ans != tst.exp) {
         cout << "Error:intToRoman failed for " << tst.X 
              << " expected '"    << tst.exp
              << "' got '" << ans << "'" << endl;
         return -1;
      }
   }
   cout << "Info: Int2Roman talks Roman numbers well :)" << endl;	
   return 0;
}
