//g++ -Wall --std=c++11 -g -o ds_string_atoi ds_string_atoi.cc

/**
 * @file  String atoi
 * @brief String to Integer (atoi)
 */

// https://leetcode.com/problems/string-to-integer-atoi/

#include <iostream>          /* std::cout                    */
#include <climits>           /* CHAR_BIT                     */
#include <algorithm>         /* std::max                     */
using namespace std;

/*
 * Implement atoi to convert a string to an integer.
 * - Discards as many whitespace characters as necessary until
 *   the first non-whitespace character is found.
 * - Then, starting from this character, takes an optional initial
 *   plus or minus sign followed by as many numerical digits as
 *   possible, and interprets them as a numerical value.
 * - The string can contain additional characters after those that
 *   form the integral number, which are ignored and have no effect
 *   on the behavior of this function.
 * - If the first sequence of non-whitespace characters in str is not
 *   a valid integral number, or if no such sequence exists because
 *   either str is empty or it contains only whitespace characters,
 *   no conversion is performed.
 * - If no valid conversion could be performed, a zero value is returned.
 * - If the correct value is out of the range of representable values,
 *   INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.
 */


/* String to int implementation which does the following     *
 * - Skip over blank characters first (need to handle \t,\n) *
 * - Find out if +/- sign is specified, if yes, note sign    *
 * - Read all possible number characters (break if not #)    *
 * - Note: Using U64 to catch overflow is much simpler and   *
 *   hopefully faster, but this is an attempt to catch any   *
 *   overflow by using just the output container size        */
int myAtoi(string s) {
   int ans = 0, sign = 1, i = 0, n = s.size();
   /* multiplying by 10 is bigger than left shift by 3 (x8)  *
    * so if before multiplication by 10, check highest 3 bits*/
   const unsigned int longbit = (CHAR_BIT * sizeof(unsigned int)),
      overflow = 1 << (longbit - 1) | 1 << (longbit - 2) | 1 << (longbit - 3);
   for(;i < n && s[i] == ' '; ++i);      /* Skip blanks      */
   if(i<n && (s[i] == '+'||s[i] == '-')) /* Handle +/- sign  */
      sign = (s[i++] == '-' ? -1 : 1);
   for(; i < n && s[i] >= '0' && s[i] <= '9'; ++i) {
      auto old_ans = ans;
      ans = (ans * 10) + s[i] - '0';
      /* Check left most 3 bits and old > new for Overflow   */
      if(old_ans & overflow || (old_ans && ans <= old_ans)) {
         if(sign == 1)  return std::numeric_limits<int>::max();
         else           return std::numeric_limits<int>::min();
      }
   }
   return sign * ans;
}

struct test_vector {
   string num;
   int exp;
};

const struct test_vector tests[16] =   {
   { " +1         ",                1 },
   { "      +-12  ",                0 },
   { "     s-231  ",                0 },
   { "      - 12  ",                0 },
   { "     00000  ",                0 },
   { "    -00000  ",                0 },
   { "        010 ",               10 },
   { "     00023  ",               23 },
   { "     123s   ",              123 },
   { "     -123s  ",             -123 },
   { "     54-12  ",               54 },
   { " -523423423423 ",   -2147483648 },
   { " +523423423423 ",    2147483647 },
   { "    10522545459",    2147483647 },
   { "    2147483648 ",    2147483647 },
   { "   -2147483648 ",   -2147483648 },
};

int main()
{
   for(auto tst : tests) {
      auto ans = myAtoi(tst.num);
      if(ans != tst.exp) {
         cout << "Error: myAtoi failed for below testcase:" << endl;
         cout << " For " << tst.num << " expected=" << tst.exp << " got=" << ans  << endl;
         return -1;
      }
   }
   cout << "Info: All manual test-cases passed for myAtoi" << endl;
   return 0;
}
