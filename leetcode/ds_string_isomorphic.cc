//g++ -Wall --std=c++11 -g -o ds_string_isomorphic ds_string_isomorphic.cc

/**
 * @file  String Isomorphic
 * @brief Given two strings, check if chars are isomorphic
 */

// https://leetcode.com/problems/isomorphic-strings/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/*
 * Given two strings s & t, determine if they are isomorphic.*
 * Two strings are isomorphic if the characters in 's' can   *
 * be replaced to get 't'.                                   *
 * All occurrences of a character must be replaced with      *
 * another character while preserving the order of           *
 * characters. No two characters may map to the same         *
 * character but a character may map to itself.              *
 * For example,                                              *
 *  - Given "egg", "add", return true.                       *
 *  - Given "foo", "bar", return false.                      *
 *  - Given "paper", "title", return true.                   */



/**
 * Check if there is a 1:1 mapping between characters on     *
 * LHS and chars on RHS.                                     *
 * @param left                                               *
 *   LHS input (str, vec, or any other iteratable container) *
 * @param rights                                             *
 *   RHS input (same container as LHS)                       *
 * @return                                                   *
 *   True if LHS & RHS are isomorphic, False if otherwise    *
 * Time Complexity = O(n),  n=max(len(left), len(right))     *
 * Space Complexity= O(n+m), n=len(left), m=len(right)       *
 * Note: Linear time worst case, sublinear time typical case *
 * Note: avoiding hash and using uint8_t to represent ASCII  *
 * would have made this code more efficient but current      *
 * approach is more generic (can work for other containers)  */
template<typename T1=std::string, typename T2=char>
bool isomorphic_check(T1 left, T1 right)
{
   bool ret = true;
   int val = 0; /* incremental val for each isomorphic pair  */
   auto l_itr = left.begin();      /* LHS iterator           */
   auto r_itr = right.begin();     /* RHS iterator           */
   unordered_map<T2, int> l_hash(left.size()), /* left hash  */
      r_hash(right.size());                  /* right hash   */

   /* Go over 1 elem (left, right) till we run out either    */
   while(l_itr != left.end() && r_itr != right.end())
      {
         auto l_hash_itr = l_hash.find(*l_itr); /* left  int */
         auto r_hash_itr = r_hash.find(*r_itr); /* right int */
		
         /* case 1: new token in both lhs + rhs              */
         if(l_hash_itr == l_hash.end() && r_hash_itr == r_hash.end()) {
            l_hash[*l_itr] = val;
            r_hash[*r_itr] = val;
         }
         /* case 2: check if l/r entry missing or not equal  */
         else if((l_hash_itr == l_hash.end() || r_hash_itr == r_hash.end()) ||
                 (l_hash_itr->second != r_hash_itr->second)) {
            ret = false;
            break;
         }
         /* case 3: Both token and char are old and match    *
          *         nothing to check or do here              */

         /* Get the next token for lhs,rhs + increment val   */
         l_itr++;		r_itr++;		val++;
      }

   /* If we reach here, it could mean one of the following   *
    * 1) Isomorphism failed (ret = false) nothing more to do *
    * 2) run out of tokens in either lhs or rhs. not isomorphic *
    * 3) run out of tokens in both lhs and rhs. isomorphic   */
   if(ret)
      ret = (l_itr == left.end() && r_itr == right.end());

   return ret;
}

int main()
{
   string left, right;

   /* Automated cases                                        */
   if(isomorphic_check<string, char>("egg", "add") != true)
      cout << "Error: Manual test - 'egg:add' returned false" << endl;
   else if(isomorphic_check<string, char>("foo", "bar") != false)
      cout << "Error: Manual test - 'foo:bar' returned true" << endl;
   else if(isomorphic_check<string, char>("paper", "title") != true)
      cout << "Error: Manual test - 'paper:title' returned false" << endl;
   /* Manual case                                            */
   else {
      cout << "Info: Automatic test-cases successful. Manual:" << endl;
      cout << "Enter the left string:"  << endl;
      getline(std::cin, left);
      cout << "Enter the right string:" << endl;
      getline(std::cin, right);
      if(isomorphic_check(left, right))
         cout << "Success: Left & Right are isomorphic" << endl;
   }
   return 0;
}
