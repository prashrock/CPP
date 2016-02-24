//g++ --std=c++11 -g -o ds_string_multiply_strings ds_string_multiply_strings.cc

/**
 * @file  Multiply Strings
 * @brief Given two numbers in String return multiplication of numbers
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

// https://leetcode.com/problems/multiply-strings/

/**
 * Given two numbers represented as strings, return multiplication
 * of the numbers as a string.
 * Note: The numbers can be arbitrarily large and are non-negative.
 */

/*-------------------- Approach 1 ---------------------------*/
/**
 * Given 2 # as strings, add them to get another string      */
string add(string num1, string num2, int base=10) {
   string ans;
   /* Go from right to left for both #s and maintain carry   */
   for(int i = num1.size() - 1, j = num2.size() - 1, c = 0;
       i >= 0 || j >= 0 || c;) {
      c  += (i >= 0) ? num1[i--] - '0' : 0;
      c  += (j >= 0) ? num2[j--] - '0' : 0;
      ans = char((c % base) + '0') + ans;
      c  /= base;
   }
   return ans;
}
/* Multiply a string and a number and return another string  */
string multiply(string num1, int num2, int base=10) {
   string ans;
   for(int i = num1.size() - 1, c = 0; i >= 0 || c;) {
      c = ((i >= 0) ? num1[i--] - '0' : 0) * num2 + c;
      ans = char((c % base) + '0') + ans;
      c  /= base;
   }
   return ans;
}
/* Use above two helper functions and distributive rule to   *
 * multiply two numbers given as strings. For example        *
 * 456 * 123 = (456 * 3) + (456 * 20) + (456 * 100)          */
string multiply1(string num1, string num2, int mlen = 8) {
   string &big   = (num1.size() >  num2.size())  ? num1 : num2;
   string &small = (num1.size() <= num2.size())  ? num1 : num2;
   string ans = "0";
   int nzeros = 0;
   /* Instead of extracting 1 digit at a time from num2, use *
    * min(mlen, num2_cur_len) as current length              */
   while(small.size() && small != "0") {
      /* len is the number of characters extracted from num2 */
      int len   = ((int)small.size() - mlen) > 0 ? mlen : small.size();
      int n     = std::stoi(small.substr(small.size() - len));
      small     = small.substr(0, small.size() - len);
      string m  = multiply(big, n);
      for(int i = 0; i < nzeros; ++i) m += "0";
      ans       = add(ans, m);
      nzeros   += len;
   }
   return ans;
}


/*-------------------- Approach 2 ---------------------------*/
/**
 * Given 2 # as strings, multiply them to get another string *
 * @param num1 - number as a string                          *
 * @param num2 - number as a string                          *
 * @return     - num1 * num2 as a string                     *
 * From leet - https://leetcode.com/discuss/26602/brief-c-solution-using-only-strings-and-without-reversal                                  */
string multiply2(string num1, string num2) {
   string sum(num1.size() + num2.size(), '0');

   for (int i = num1.size() - 1; i >= 0; --i) {
      int carry = 0;
      for (int j = num2.size() - 1; j >= 0; --j) {
	 int tmp = (sum[i + j + 1] - '0')
	    + (num1[i] - '0') * (num2[j] - '0') + carry;
	 sum[i + j + 1] = tmp % 10 + '0';
	 carry = tmp / 10;
      }
      sum[i] += carry;
   }

   size_t startpos = sum.find_first_not_of("0");
   if (string::npos != startpos) {
      return sum.substr(startpos);
   }
   return "0";
}


int main()
{
   string num1, num2, ans1, ans2, exp;
   num1 = "0"; num2 = "5"; exp = "0";
   ans1 = multiply1(num1, num2);
   ans2 = multiply2(num1, num2);
   if(ans1 != exp) goto ErrMain1;
   if(ans2 != exp) goto ErrMain2;

   num1 = "9133"; num2 = "0"; exp = "0";
   ans1 = multiply1(num1, num2);
   ans2 = multiply2(num1, num2);
   if(ans1 != exp) goto ErrMain1;
   if(ans2 != exp) goto ErrMain2;


   num1 = "1"; num2 = "5"; exp = "5";
   ans1 = multiply1(num1, num2);
   ans2 = multiply2(num1, num2);
   if(ans1 != exp) goto ErrMain1;
   if(ans2 != exp) goto ErrMain2;

   num1 = "2"; num2 = "4"; exp = "8";
   ans1 = multiply1(num1, num2);
   ans2 = multiply2(num1, num2);
   if(ans1 != exp) goto ErrMain1;
   if(ans2 != exp) goto ErrMain2;
      
   num1 = "2"; num2 = "5"; exp = "10";
   ans1 = multiply1(num1, num2);
   ans2 = multiply2(num1, num2);
   if(ans1 != exp) goto ErrMain1;
   if(ans2 != exp) goto ErrMain2;

   num1 = "123"; num2 = "456"; exp = "56088";
   ans1 = multiply1(num1, num2);
   ans2 = multiply2(num1, num2);
   if(ans1 != exp) goto ErrMain1;
   if(ans2 != exp) goto ErrMain2;
   
   num1 = "12"; num2 = "9999"; exp = "119988";
   ans1 = multiply1(num1, num2);
   ans2 = multiply2(num1, num2);
   if(ans1 != exp) goto ErrMain1;
   if(ans2 != exp) goto ErrMain2;
   
   num1 = "123456"; num2 = "12345"; exp = "1524064320";
   ans1 = multiply1(num1, num2);
   ans2 = multiply2(num1, num2);
   if(ans1 != exp) goto ErrMain1;
   if(ans2 != exp) goto ErrMain2;
   
   cout << "Info: All manual test-cases passed" << endl;
   return 0;
ErrMain1:
   cout << "Error: Multiply1 failed for " << num1 << " x " << num2
	<< " -- " << "Expected " << exp << " Got " << ans1 << endl;
   return -1;
ErrMain2:
   cout << "Error: Multiply2 failed for " << num1 << " x " << num2
	<< " -- " << "Expected " << exp << " Got " << ans2 << endl;
   return -2;
}
