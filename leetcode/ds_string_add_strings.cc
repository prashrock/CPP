//g++-5 --std=c++11 -Wall -g -o ds_string_add_strings ds_string_add_strings.cc

/**
 * @file  Add Strings
 * @brief Given two integer strings, return their sum (also string).
 */

// https://leetcode.com/problems/add-strings/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
using namespace std;

/**
 * Given two non-negative numbers num1 and num2 represented as
 * string, return the sum of num1 and num2.
 * Note:
 * The length of both num1 and num2 is < 5100.
 * Both num1 and num2 contains only digits 0-9.
 * Both num1 and num2 does not contain any leading zero.
 * You must not use any built-in BigInteger library or convert
 * the inputs to integer directly.
 */

/**
 * With iterators and extra storage to hold the ans          *
 * @param num1 - First string                                *
 * @param num2 - Second string                               *
 * @return     - Sum of num1 and num2                        *
 * Time Complexity = O(n), n=max(len(a), len(b))             *
 * Space Complexity= O(n), n=max(len(a), len(b))             */
std::string addStrings1(std::string& num1, std::string& num2) {
   string ans;
   int carry = 0;
   for(auto rit1 = num1.rbegin(), rit2 = num2.rbegin();
       rit1 != num1.rend() || rit2 != num2.rend() || carry;
       carry /= 10) {
      if(rit1 != num1.rend()) carry += ( *(rit1++) - '0');
      if(rit2 != num2.rend()) carry += ( *(rit2++) - '0');
      ans.insert(ans.begin(), (carry % 10) + '0');
   }
   return ans;
}

/** Without  extra storage to hold the ans                   */
std::string addStrings2(std::string& num1, std::string& num2) {
   if(num1.size() < num2.size())          return addStrings2(num2, num1);
   else if(num1.empty() || num2.empty())  return num1 + num2;
   int carry = 0;
   for(int i=num1.size()-1, j=num2.size()-1; i >= 0; carry /= 10) {
      if(i >= 0)  carry += num1[i]  - '0';
      if(j >= 0)  carry += num2[j--]- '0';
      num1[i--] = carry % 10 + '0';
   }
   if(carry) num1.insert(num1.begin(), carry + '0');
   return num1;
}

struct test_vector {
   std::string num1;
   std::string num2;
   std::string exp;
};

const struct test_vector test[4] =  {
   {        "0",               "0",                "0"},
   {        "5",               "5",               "10"},
   {       "15",             "115",              "130"},
   {"999999999", "999999999999999", "1000000999999998"},
};

int main()
{
   for(auto tst : test) {
      auto num1 = tst.num1;
      auto ans = addStrings1(num1, tst.num2);
      if(ans != tst.exp) {
         cout << "Error:addStrings1 failed. Exp "
              << tst.exp << " Got " << ans
              << " for num1=" << tst.num1
              << " and num2=" << tst.num2 << endl;
         return -1;
      }
      num1 = tst.num1;
      ans = addStrings2(num1, tst.num2);
      if(ans != tst.exp) {
         cout << "Error:addStrings2 failed. Exp "
              << tst.exp << " Got " << ans
              << " for num1=" << tst.num1
              << " and num2=" << tst.num2 << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
