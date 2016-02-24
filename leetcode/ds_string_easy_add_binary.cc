//g++ -Wall --std=c++11 -g -o ds_string_easy_add_binary ds_string_easy_add_binary.cc

/**
 * @file  Add Binary
 * @brief Given two binary strings, return their sum (also binary string).
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

//https://leetcode.com/problems/add-binary/
/**
 * For example,
 * a = "11"
 * b = "1"
 * Return "100".
*/

/**
 * Go from right-most bit to left-most bit of big-string and *
 * maintain a carry-bit along.                               *
 * @param a - First string                                   *
 * @param b - Second string                                  *
 * @return  - Binary sum of a and b                          *
 * Time Complexity = O(n), n=max(len(a), len(b))             *
 * Space Complexity= O(n), n=max(len(a), len(b))             */
string addBinary(string a, string b) {
   /* Create references for small and big string             */
   string &small = a.size() <  b.size() ? a : b;
   string &big   = a.size() >= b.size() ? a : b;
   char    carry = '0';
   /* For-loop to go over the bigger string                  */
   for(auto it = big.rbegin(), sm_it = small.rbegin();
       it != big.rend(); ++it)
   {
      char small_char = '0';
      /* If we still have a char from small string, take it  */
      if( sm_it != small.rend()) {small_char = *sm_it; ++sm_it; }
      /* val=big[i]+small[j]+carry. val is between [0, 3]    */
      int val = *it - '0' + small_char - '0' + carry - '0';
      if (val > 1) { carry = '1'; *it = '0' + (char)(val & 1);  }
      else         { carry = '0'; *it = '0' + (char)(val    );  }
   }
   /* After going over big string, if carry, prepend it      */
   if(carry == '1') return "1" + big;
   else             return big;
}




int main()
{
   string a, b, ans, exp;

   a = "1"; b = "1"; exp = "10";
   ans = addBinary(a, b);
   if(ans != exp) goto ErrMain;

   a = "0"; b = "0"; exp = "0";
   ans = addBinary(a, b);
   if(ans != exp) goto ErrMain;
   
   a = "11"; b = "1"; exp = "100";
   ans = addBinary(a, b);
   if(ans != exp) goto ErrMain;

   a = "0"; b = "1"; exp = "1";
   ans = addBinary(a, b);
   if(ans != exp) goto ErrMain;
   cout << "Info: All manual test-cases for AddBinary passed." << endl;
   return 0;
ErrMain:
   cout << "Error: "   << a << " + " << b << " failed."
	<< "expected " << exp << " got " << ans << endl;
   return -1;
}
