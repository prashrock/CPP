//g++ -Wall --std=c++11 -g -o ds_string_easy_valid_palindrome ds_string_easy_valid_palindrome.cc

/**
 * @file  Valid Palindrome
 * @brief Given a string, determine if it forms a valid palindrome
 */

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

//https://leetcode.com/problems/valid-palindrome/
/**
 * Given a string, determine if it is a palindrome, considering
 * only alphanumeric characters and ignoring cases.
 * For example,
 * "A man, a plan, a canal: Panama" is a palindrome.
 * "race a car" is not a palindrome.
 * Note: Have you consider that the string might be empty?
 * This is a good question to ask during an interview.
 * For this problem, we define empty string as valid palindrome.
 */


/**
 * Maintain two iterators, l->r and r->l, and advance both   *
 * iterators till l < r (since we are incrementing from both *
 * directions, if string is odd size, l can go beyond r) and *
 * check for valid palindrome. If not, return immediately    *
 * @param s - input string to check for palindrome           *
 * @return                                                   *
 *   True if string is a palindrome, False if otherwise      *
 * Time Complexity = O(n),  Space Complexity= O(1)           */
bool isPalindrome(string s) {
   if(s.size() == 0) return true; /* Spl case, 0 length str  */
   auto fit = s.begin(); auto rit = s.rbegin();
   /* Invariant is, f_it should always be less than r_it     */
   while(fit < rit.base()) {
      if     (isalnum(*fit) == 0)  ++fit;
      else if(isalnum(*rit) == 0)  ++rit;
      else if(tolower(*fit) != tolower(*rit))  return false;
      else                        { ++fit; ++rit;    }
   }
   return true;
}

int main()
{
   string s;
   s = "A man, a plan, a canal: Panama";
   if(isPalindrome(s) == false) goto ErrMain;

   s = "race a car";
   if(isPalindrome(s) == true) goto ErrMain;
	cout << "Info: All manual test-cases passed successfully" << endl;
	return 0;
ErrMain:
   cout << "Error: isPalindrome failed for " << s << endl;
   return -1;
}
