//g++ --std=c++11 -g -Wall -Werror -o ds_string_one_edit_distance ds_string_one_edit_distance.cc

/**
 * @file  One Edit Distance
 * @brief Given two strings S and T, determine if they are both
 * are one edit distance apart.
 */

// https://leetcode.com/problems/one-edit-distance/

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
 * Iterate over both strings and maintain mismatch count     *
 * @param s - First String                                   *
 * @param t - Second String                                  *
 * @return                                                   *
 *   True if s & t differ by 1 edit dist, False if otherwise *
 * Time Complexity = O(n),  n=max(len(s), len(t))            *
 * Space Complexity= O(1)                                    */
bool isOneEditDistance(string s, string t) {
   int cnt = 0, i, j;
   string &big  =  (s.size() > t.size())?  s : t;
   string &small = (s.size() <= t.size())? s : t;
   int b_sz = big.size(), s_sz = small.size();
   //
   /* avoid all checks when sz diff > 1                      */
   if((b_sz - s_sz) > 1) return false;
   for(i = 0, j = 0; i < b_sz && j < s_sz; i++, j++) {
      if(big[i] != small[j]) {
         cnt++;
         /* If this is the 2nd mismatch return               */
         if(cnt > 1) return false;
         else if(i+1 < b_sz  && big[i+1] == small[j])   i++;
         else if(j+1 < s_sz  && big[i]   == small[j+1]) j++;
      }
   }
   return ((((b_sz - i) + (s_sz - j)) + cnt) == 1);
}

int main()
{
   string left, right;

   /* Manual test-cases                                      */
   if(isOneEditDistance("abc", "ab") != true)
      cout << "Error: Manual test - 'abc:ab' returned false" << endl;
   else if(isOneEditDistance("", "x") != true)
      cout << "Error: Manual test - ':x' returned false" << endl;
   else if(isOneEditDistance("abc", "adc") != true)
      cout << "Error: Manual test - 'abc:adc' returned false" << endl;
   else if(isOneEditDistance("this is long", "this is long ") != true)
      cout << "Error: Manual test - 'this is long:this is long '"
           << " returned false" << endl;
   else if(isOneEditDistance("ab", "ba") != false)
      cout << "Error: Manual test - 'ab:ba' returned true" << endl;
   else if(isOneEditDistance("abc", "xyz") != false)
      cout << "Error: Manual test - 'abc:xyz' returned true" << endl;
   else if(isOneEditDistance("", "") != false)
      cout << "Error: Manual test - ':' returned true" << endl;
   else
      cout << "Info: All manual test-cases passed" << endl;
   return 0;
}
