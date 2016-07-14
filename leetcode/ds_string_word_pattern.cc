//g++ --std=c++11 -g -o ds_string_word_pattern ds_string_word_pattern.cc

/**
 * @file  String Word Pattern
 * @brief Given a pattern and a STring find if String follows same pattern
 */

// https://leetcode.com/problems/word-pattern/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_set>     /* std::unordered_set container */
using namespace std;

/*
 * Given a pattern and a string str, find if str follows the same pattern.
 * Here follow means a full match, such that there is a bijection between
 * a letter in pattern and a non-empty word in str.
 * Examples:
 *  pattern = "abba", str = "dog cat cat dog" should return true.
 *  pattern = "abba", str = "dog cat cat fish" should return false.
 *  pattern = "aaaa", str = "dog cat cat dog" should return false.
 *  pattern = "abba", str = "dog dog dog dog" should return false.
 * Notes:
 *  You may assume pattern contains only lowercase letters, and str
 *  contains lowercase letters separated by a single space.
 */

/**
 * Check if there is a 1:1 mapping between characters on     *
 * LHS and words on RHS.                                     *
 * @param leftc                                              *
 *   Template = a single word containing characters          *
 * @param rights                                             *
 *   Line = a list of words seperated by "delim"             *
 * @return                                                   *
 *   True if there is Bijection, False if otherwise          *
 * Time Complexity = O(n),  n=max(len(leftc), len(rights))   *
 * Space Complexity= O(2n), n=len(leftc)                     *
 * Note: Linear time worst case, sublinear time typical case */
bool bijection_check(string leftc, string rights, string delim=" ")
{
   /* Init variables  */
   bool ret = true;
   unordered_set<char> lset(leftc.size());  /* leftc hash   */
   unordered_set<string> rset(leftc.size()); /* rights hash */
   auto t_it = leftc.begin(); /* Iter over leftc char-char  */
   auto *tok = strtok((char *)rights.c_str(), (char *)delim.c_str());

   /* Ideally we could have checked if the                  *
    * cardinality(leftc) == cardinality(rights), but        *
    * getting cardinality of rights would mean iterating    *
    * over all the tokens one more time.                    */

   /* Go over each token + char, till we run out of either  */
   while(tok != NULL && t_it != leftc.end()) {
      auto lfind = lset.find(*t_it);
      auto rfind = rset.find(tok);
		
      /* case 1: New token and char                        */
      if(lfind == lset.end() && rfind == rset.end()) {
         lset.insert(*t_it);
         rset.insert(tok);
      }
      /* case 2: check if left/right entry missing         */
      else if((lfind == lset.end() || rfind == rset.end()) || 
              (*lfind != *t_it     || *rfind != tok)) {
         ret = false;
         break;
      }
      /* case 3: Both token and char are old and match     *
       *         nothing to check or do here               */
		
		
      /* Get the next word and next token from template    */
      tok = strtok(NULL, (char *)delim.c_str());
      t_it++;
   }

   /* If we reach here, it could mean one of the following  *
    * 1) bijection false (ret == false) nothing more to do  *
    * 2) run out of words in str or char in templ. If we've *
    *    run out of only one of the above two, return false *
    * 3) words and char over, (1) not true, so return true  */
   if(ret)
      ret = ((tok == NULL) && t_it == leftc.end());
	
   return ret;
}

int main()
{
   string rights, leftc;

   /* Standard cases                                        */
   if(bijection_check("abba", "dog cat cat dog") != true)
      cout << "Error: Manual test - 'abba:dog cat cat dog'" << endl;
   else if(bijection_check("abba", "dog cat cat fish") != false)
      cout << "Error: Manual test - 'abba:dog cat cat fish'" << endl;
   else if(bijection_check("aaaa", "dog cat cat dog") != false)
      cout << "Error: Manual test - 'aaaa:dog cat cat dog'" << endl;
   else if(bijection_check("abba", "dog dog dog dog") != false)
      cout << "Error: Manual test - 'abba:dog dog dog dog'" << endl;

   /* Manual case                                           */
   cout << "Enter the string:" << endl;
   getline(std::cin, rights);
   cout << "Enter the template:" << endl;
   getline(std::cin, leftc);
   if(bijection_check(leftc, rights))
      cout << "Bijection found between left and right" << endl;
	
   return 0;
}
