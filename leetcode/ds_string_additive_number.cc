//g++-5 --std=c++11 -g -o ds_string_additive_number ds_string_additive_number.cc

/**
 * @file  String Additive Number
 * @brief Given string, check if it forms additive sequence
 */

// https://leetcode.com/problems/additive-number/

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
 * Additive number is a string whose digits can form additive sequence.
 * A valid additive sequence should contain at least three numbers. Except
 * for the first two numbers, each subsequent number in the sequence must
 * be the sum of the preceding two.
 * For example:
 * "112358" is an additive number because the digits can form an additive
 * sequence: 1, 1, 2, 3, 5, 8.
 * 1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
 * "199100199" is also an additive number, the additive sequence
 * is: 1, 99, 100, 199.
 * 1 + 99 = 100, 99 + 100 = 199
 * Note: Numbers in the additive sequence cannot have leading zeros, so
 * sequence 1, 2, 03 or 1, 02, 3 is invalid.
 * Given a string containing only digits '0'-'9', write a function to
 * determine if it's an additive number.
 * Follow up: How would you handle overflow for very large input integers?
 */

/* Check additive number for the remaining elements in seq   */
bool check_remaining_string(string num, unsigned n1, unsigned n2) {
   for(int i = 0; i < num.size();) {
      unsigned n3 = n1 + n2;
      string s = std::to_string(n3);
      if(num.find(s, i) != i)        return false;
      i += s.size();
      n1 = n2;
      n2 = n3;
   }
   return true;
}

/* Check if the given string is additive sequence            */
bool isAdditiveNumber(string num) {
   for(int l1 = 1; l1 <= num.size(); ++l1) {
      if(num[0] == '0' && l1 != 1) break;
      /* There is no limit on 2nd num size, so start from 1  */
      for(int l2 = 1; l1 + l2 <= num.size() - std::max(l1, l2); ++l2) {
         if(num[l1] == '0' && l2 != 1) break;
         unsigned n1 = stoul(num.substr(0, l1));  /* substr(pos, len) */
         unsigned n2 = stoul(num.substr(l1, l2)); /* substr(pos, len) */
         if(check_remaining_string(num.substr(l1 + l2), n1, n2) == true)
            return true;
      }
   }
   return false;
}

struct test_vector {
   std::string X;
   bool exp;
};

const struct test_vector test[4] =  {
   { "120122436",   false },
   { "12012122436", true  },
   { "101",         true  },
   { "221474836472147483649",  true },
};

int main()
{
   for(auto tst : test) {
      auto ans = isAdditiveNumber(tst.X);
      if(ans != tst.exp) {
         cout << "Error: AdditiveNumber failed for "
              << tst.X   << " exp " << tst.exp
              << " got " << ans << endl;
         return -1;
      }
   }
   cout << "Info: All manual test-cases passed" << endl;
   return 0;
}
