#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <random>            /* std::default_random_engine   */

#include "math_shuffle.h"    /* math::shuffle implementation */
#include "math_fact.h"       /* factorial()                  */
#include "time_api.h"        /* MILLION                      */
using namespace std;

const int num_loops = MILLION;


/* Test small and large factorials (beyond uint64_t)         */
bool factorial_test() {
   std::vector<std::pair<unsigned int, unsigned int>> pass =  {
      {0, 1}, {1, 1}, {2, 2}, {3, 6}, {10, 3628800}, {12, 479001600},  
     };
   std::vector<std::pair<unsigned int, std::string>> pass_big = {
      {0, "1"}, {1, "1"}, {12, "479001600"}, {15, "1307674368000"},
      {20, "2432902008176640000"}, {23, "25852016738884976640000"}, 
   };
   std::vector<std::pair<unsigned int, int>> zeros = {
      {0, 0}, {1, 0}, {3, 0}, {10, 2}, {12, 2}, {15, 3}, {20, 4}, {23, 4},    
   };
   /* Run factorial function for regular unsigned int        */
   for(auto p : pass) {
      unsigned int res;
      if(math::factorial<unsigned int, unsigned int>(p.first, res) == false ||
         res != p.second) {
         cout << "Error: Factorial failed for " << p.first
              << " expected=" << p.second << " got=" << res << endl;
         return false;
      }
   }
   /* Run factorial function for big int                     */
   for(auto p : pass_big) {
      auto res = math::big_factorial(p.first);
      if(res != p.second) {
         cout << "Error: Bigint Factorial failed for " << p.first
              << " expected=" << p.second << " got=" << res << endl;
         return false;
      }
   }
   /* Find number of zeros in n! without computing factorial */
   for(auto p : zeros) {
      auto res = math::count_trailing_zeros_in_factorial(p.first);
      if(res != p.second) {
         cout << "Error: Count zeros in factorial failed for " << p.first
              << " expected=" << p.second << " got=" << res << endl;
         return false;
      }
   }
   return true;
}

int main(){
   init_rand();
   if(factorial_test() == false) return -1;
   cout << "Info: All Math misc tests completed successfully." << endl;
   return 0;
}
