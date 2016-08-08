//g++ --std=c++11 -g -o all_distinct_palindromic_substrings all_distinct_palindromic_substrings.cc

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <set>               /* std::set                     */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <string>            /* std::string                  */
#include <unordered_map>     /* std::unordered_map container */

using namespace std;

void print_all_palindromic_substrings(std::string s)
{
   typedef std::pair<char, int> pair_t;
   std::set<pair_t> a_set, b_set, inter;

   /* Populate a_set, b_set with forward/reverse of string   */
   for(auto it = s.begin(); it != s.end(); ++it) {
      if(isspace(*it)) continue; /* ignore spaces in string  */
      else a_set.insert( std::make_pair(*it, (it - s.begin())) );
   }
   for(auto it = s.rbegin(); it != s.rend(); ++it) {
      if(*it == ' ') continue; /* ignore spaces in string    */
      else b_set.insert( std::make_pair(*it, (it - s.rbegin())) );
   }

   /* Create an intersection when fwd/rev char + pos match   */
   std::set_intersection(a_set.begin(), a_set.end(),
                         b_set.begin(), b_set.end(),
                         std::inserter(inter, inter.begin()));

   cout << inter.size() << endl;
   vector<char> results;
   for(int i = 0; i < inter.size();) {
      cout << inter[i].first << endl;
      int n = results.size();
      if(n > 0) {
         if(results[n - 1] != results)
            }
   }
}


int main()
{
   std::string inp = "a bb c";
   //std::vector<char> str(inp.begin(), inp.end());
   print_all_palindromic_substrings(inp);
}
