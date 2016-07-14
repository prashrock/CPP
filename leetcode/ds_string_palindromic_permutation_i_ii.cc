//g++ --std=c++11 -g -o ds_string_palindromic_permutation_i_ii ds_string_palindromic_permutation_i_ii.cc

/**
 * @file  String Palindromic Permutation
 * @brief Given string, determine of permutation can form palindrome
 */

// https://leetcode.com/problems/palindrome-permutation/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
#include <cstring>           /* std::strtok                  */
#include <bitset>            /* bitset                       */
using namespace std;

/*
 * Given a string, determine if a permutation of the string  *
 * could form a palindrome.                                  *
 * For example:                                              *
 * "code" -> False, "aab" -> True, "carerac" -> True.        */

/**
 * Use a bitmap and toggle bitmap for each char found. Count *
 * of bits set is the number of #odd occuring characters     *
 * @param s - input string                                   *
 * @return                                                   *
 *   True if a permutation can form palindrome               *
 * Time Complexity = O(n),  n=len(s)                         *
 * Space Complexity= O(n),  n=len(s)                         */
bool canPermutePalindrome(string s) {
   /* enough space to hold Unicode UTF-8 encoding            */
   std::bitset<256> bits;
   for(auto c : s) bits.flip((unsigned char)c);
   return bits.count() < 2;
}

bool canPermutePalindromeTest() {
   if     (canPermutePalindrome("code") != false)
      cout << "Error: Palindrome chk failed for 'code'" << endl;
   else if(canPermutePalindrome("aab") != true)
      cout << "Error: Palindrome chk failed for 'aab'" << endl;
   else if(canPermutePalindrome("carerac") != true)
      cout << "Error: Palindrome chk failed for 'carerac'" << endl;
   else if(canPermutePalindrome("as") != false)
      cout << "Error: Palindrome chk failed for 'as'" << endl;
   else
      return true;
   return false;
}

int main()
{
   if(canPermutePalindromeTest())
      cout << "Info: All Palindrome Check cases passed" << endl;
   return 0;
}
