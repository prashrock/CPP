//g++ --std=c++11 -Wall -g -o ds_stack_math_reverse_polish_notation ds_stack_math_reverse_polish_notation.cc

/**
 * @file  Evaluate Reverse Polish Notation
 * @brief Evaluate value of an arithmetic expr in Reverse Polish Notation
 */

// https://leetcode.com/problems/evaluate-reverse-polish-notation/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <stack>             /* std::stack                   */
using namespace std;

/**
 * Evaluate the value of an arithmetic expression in Reverse Polish
 * Notation.
 * Valid operators are +, -, *, /. Each operand may be an integer
 * or another expression.
 * Some examples:
 *    ["2", "1", "+", "3", "*"]  -> ((2 + 1) * 3)  -> 9
 *    ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
 */


/* Use stack to store each number. Every time we encounter   *
 * an operator, pop 2 elements from stack, evaluate operator *
 * and push back to stack.                                   *
 * Time Complexity = O(n)    Space Complexity = O(n)         */
int evalRPN(vector<string>& tokens) {
   std::stack<int> nums; /* Stack to evaluate in LIFO order  */
   for(auto v : tokens) {
      /* If number, push it to stack (1st or 2nd char is #)  */
      if(std::isdigit(v[0]) || (v[0] == '-' && std::isdigit(v[1])))
         nums.push(std::stoi(v));
      /* Else we have operator-pop 2 numbers, eval and push  */
      else {
         auto a = nums.top(); nums.pop();    /* right element*/
         auto b = nums.top(); nums.pop();    /* left element */
         if     (v == "+") nums.push(b + a);
         else if(v == "-") nums.push(b - a);
         else if(v == "*") nums.push(b * a);
         else if(v == "/") nums.push(b / a);
      }
   }
   /* stack should have 1 elem (ans), else no or wrong input */
   if(nums.size() == 1)    return nums.top();
   else                    return 0;
}

struct test_vector {
   std::vector<string> inp;
   int exp;
};

const struct test_vector test[5] =  {
   {{},                          0},
   {{"2", "1", "+", "3", "*"},   9},
   {{"4", "13", "5", "/", "+"},  6},
   {{"3","-4","+"},             -1},
   {{"4","3","-"},               1},
};

int main()
{
   for(auto tst : test) {
      auto ans = evalRPN(tst.inp);
      if(ans != tst.exp) {
         cout << "Error: isValid failed for " << endl;
         for (auto v : tst.inp) cout << v << ",";
         cout << "  Expected " << tst.exp << " Got " << ans << endl;
         return -1;
      }
   }
   cout << "Info: All manual test-cases passed." << endl;
   return 0;
}
