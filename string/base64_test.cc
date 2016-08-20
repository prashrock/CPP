//g++-5 --std=c++11 -Wall -g -o base64_test base64_test.cc -I../utils/
//taskset -c 1 ./base64_test
#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <string>            /* std::string                  */

#include "rand_generator.h"  /* init_rand()                  */
#include "base64.h"          /* base64_encode                */
#include "print_utils.h"     /* MILLIOn                      */

const int num_iters   = MILLION;
const int str_max_len = 20;

/* Randomly generate strings and verify base64 encode/decode */
bool base64_randomized_test(int max_len = str_max_len) {
   std::cout << "Info: Running " << num_iters
             << " randomized iterations: " << std::endl;
   for(size_t i = 0; i < num_iters; ++i) {
      const int len = get_rand(max_len);
      auto s = get_rand_str(len);
      auto enc = base64_encode(s);
      auto dec = base64_decode(enc);
      if(s != dec) {
         std::cout << "Error: Randomized encode/decode failed for" << std::endl
                   << "Inp: " << s   << std::endl
                   << "Enc: " << enc << std::endl
                   << "Dec: " << dec << std::endl;
         return false;
      }
      if(i % 10000 == 0) { std::cout << "."; std::cout.flush(); }
   }
   std::cout << std::endl;
   return true;
}

int main()
{
   init_rand();
   auto s = "This is a sample text!";
   std::cout << "'" << s << "' in base 64: ";
   auto enc = base64_encode(s);
   std::cout << enc                    << std::endl;

   if(base64_randomized_test())
      std::cout << "Info: All Base64 test-cases passed successfully" << std::endl;
   return 0;
}
