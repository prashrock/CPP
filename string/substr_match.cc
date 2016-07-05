#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
#include <unordered_map>     /* std::unordered_map container */

#include "print_utils.h"     /* print_table_row              */
#include "rand_generator.h"  /* init_rand()                  */
#include "substring.h"       /* substring functionality      */
#include "time_api.h"        /* C based time mgmt API        */
using namespace std;

/* Check if pattern occurs in text. If yes return first idx  */
const int number_of_iterations = MILLION/10;
const int text_length          = 3000;
const int pattern_length       = 100;
const size_t RADIX             = 256; /* Extended ASCII      */

/* Maintain a table of substring algo's for test purposes    */
const std::vector<std::string> substr_types = {
   "Brute", "Brute Opt", "KMP", "Boyer-Moore", "Rabin-Karp"
};
const std::vector<int (*)(std::string, std::string)> substr =
{
   substring_brute,
   substring_opt,
   substring_kmp,
   substring_boyer_moore,
   substring_rabin_karp,
};

const int N = substr.size();

/* Randomized test-cases:                                    *
 * For 'number_of_iterations', generate random text and pat  *
 * strings, run them through all the substr algorithms and   *
 * ensure each test-case passes. Brute force is used as the  *
 * correctness benchmark.                                    */
void substring_match_randomized_test()
{
   std::vector<struct time_api_t> time(N);
   std::vector<struct tsc_api_t> tsc(N);
	
   unsigned int num_substr_matches = 0;
   bool pass = true;

   cout << "Info: Running Randomized tests for "
        << number_of_iterations
        << " iterations" << endl;
   for(int i = 0; i < N; ++i) {
      rt_measure_init(&time[i]);
      tsc_measure_init(&tsc[i]);
   }
   for(int i = 0; i < number_of_iterations; ++i) {
      vector<char> text(text_length);
      vector<char> pattern(pattern_length);
      fill_vector_rand<char>(text, 'A', 'B');
      fill_vector_rand<char>(pattern, 'A', 'B');
      string txt_str(text.begin(), text.end());
      string pat_str(pattern.begin(), pattern.end());

      int brute_pos = txt_str.find(pat_str);
      if(brute_pos != -1) num_substr_matches++;
		
      for(int j = 0; j < N; ++j) {
         rt_measure_start(&time[j], true);
         tsc_measure_start(&tsc[j]);
         int pos = substr[j](txt_str, pat_str);
         tsc_measure_end(&tsc[j]);
         rt_measure_end(&time[j], true);
         //Assume brute force is always correct :)
         if(pos != brute_pos) {
            cout << "Error: Auto test failed for "
                 << substr_types[j] << " expected " << brute_pos
                 << " found " << pos << endl;
            print_table_row<char>("text", text);
            print_table_row<char>("pattern", pattern);
            pass = false;
            break;
         }
      }
      if(!pass) break;
   }
   if(pass) {
      cout << "Info: All Auto randomized test-cases passed" << endl;
      cout << "      " << number_of_iterations
           << " iterations with txt_length="<< text_length
           << " and pattern_length="  << pattern_length
           << " (" << num_substr_matches
           << " matches found)." << endl;
      cout << "Statistics for each substring algo: " << endl;
      for(int i = 0; i < N; ++i) {
         time_print_api(&time[i], substr_types[i].c_str());
         time_tsc_statistics_print(number_of_iterations, &time[i], &tsc[i]);
      }
   }
}

/* Manual test-cases:                                        *
 * Run some hand-crafted test-cases against each substring   *
 * algo. This helps Cover known corner-cases for each algo   */
bool substring_match_manual_test()
{
   int j;
   bool pass = false;
   for(j = 0; j < N; ++j) {
      if(substr[j]("ABC", "ABC") != 0)
         cout << "Error: Full string match failed ";
      else if(substr[j]("ABEC", "") != -1)
         cout << "Error: Empty pattern match failed ";
      else if(substr[j]("", "AB") != -1)
         cout << "Error: Empty text match failed ";
      else if(substr[j]("ABEC", "EC") != 2)
         cout << "Error: Pattern at end of text not detected ";
      else if(substr[j]("ABC", "AB") != 0)
         cout << "Error: Pattern at start of text not detected ";
      else if(substr[j]("AADDDDAA", "DDA") != 4)
         cout << "Error: Last Repeating pattern case not detected ";
      else if(substr[j]("AAABCD", "AAB") != 1)
         cout << "Error: First Repeating case not detected ";
      else {
         pass = true;
         continue;
      }
      pass = false;
      break;
   }
   if(pass) cout << "Info: All Manual test-cases passed" << endl;
   else     cout << "for '" << substr_types[j] << "' method." << endl;
   return pass;
}

int main()
{
   init_rand();
   if(substring_match_manual_test())
      substring_match_randomized_test();
}
