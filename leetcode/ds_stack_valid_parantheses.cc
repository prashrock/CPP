//g++-5 --std=c++11 -Wall -g -o ds_stack_valid_parantheses ds_stack_valid_parantheses.cc

/**
 * @file  Valid Parantheses (stack test)
 * @brief Given a string match start and end parantheses
 */

// https://leetcode.com/problems/valid-parentheses/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <stack>             /* std::stack                   */
using namespace std;

/**
 * Given a string containing just the characters
 * '(', ')', '{', '}', '[' and ']', determine if the input
 * string is valid.
 *
 * The brackets must close in the correct order, "()" and "()[]{}"
 * are all valid but "(]" and "([)]" are not.
 */

bool isValidEnd(char e)   { return e == ')' || e == '}' || e == ']'; }

bool isValidStart(char e) { return e == '(' || e == '{' || e == '['; }

bool isMatch(char b, char e) {
   if(b == '(')      return e == ')';
   else if(b == '[') return e == ']';
   else if(b == '{') return e == '}';
   else              return false;
}

/* Use stack to store all the forward paranthesis            *
 * Every time we encounter a reverse paranthesis, pop stack  *
 * and validate.                                             *
 * Time Complexity = O(n)    Space Complexity = O(n)         */
bool isValid(string s) {
   std::stack<char> stk; /* Stack of start paran             */

   for(unsigned int i = 0; i < s.size(); ++i) {
      char c = s[i];
      /* Add forward paran to stack                          */
      if(isValidStart(c)) stk.push(c);
      /* When reverse paran is found, pop forward paren      *
       * (note, this will be the latest/last forward paren)  *
       * and validate.                                       */
      else if(isValidEnd(c)) {
         if(stk.size() == 0 || isMatch(stk.top(), c) == false)
            return false;
         stk.pop();
      }
   }

   if(stk.size())  return false;
   else            return true;
}

struct test_vector {
   std::string inp;
   bool exp;
};

const struct test_vector test[4] =  {
   {"()[]{}",         true},
   {"([{}]){}",       true},
   {"()[]{}",         true},
   {"()[){}",        false},
};

int main()
{
   for(auto tst : test) {
      auto ans = isValid(tst.inp);
      if(ans != tst.exp) {
         cout << "Error: isValid failed for " << tst.inp
              << " Expected " << tst.exp << " Got " << ans << endl;
         return -1;
      }
   }
   cout << "Info: All manual test-cases passed." << endl;
   return 0;
}
