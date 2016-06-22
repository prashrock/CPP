#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
#include <unordered_map>     /* std::unordered_map container */

#include "print_utils.h"     /* print_table_row              */
#include "rand_generator.h"  /* init_rand()                  */
using namespace std;

/* Find the length of the longest substring without          *
 * repeating characters - NonRepeating Char Substring (NRCS) */

const int number_of_iterations = 1;
const int string_length        = 10;

/* Keep it generic. Input maybe ASCII (8-bit), unicode or    *
 * maybe even numbers. Not re-entrant safe - Input           *
 * contents and size assumed to be constant                  *
 * assumed to be constant.                                   *
 * Time Complexity  = O(n)                                   *
 * Space Complexity = O(m) m=if alphabets this = 26          */
template<typename T>
int longest_unique_substring(const std::vector<T>& inp)
{
   int max_len = 0, cur_len = 0;
   int max_start_idx = 0, cur_start_idx = 0;
   unordered_map<T, int> map;
   for(int i = 0; i <= inp.size(); ++i) {
      /* Book-keeping. Update max_len if required first      */
      if(max_len < cur_len) {
         max_len = cur_len;
         max_start_idx = cur_start_idx;
      }
      /* Above book-keeping will get missed out after last   *
       * character. Instead of redoing bookkeeping outside   *
       * loop, just enter loop 1 more time and then break    */
      if(i == inp.size()) break;

      T val = inp[i];
		
      /* 1st option - in current substring, we have 1 more   *
       * unique element. Add it to cur_len and continue      */
      if(map.find(val) == map.end())
         cur_len++;
	
      /* We found a repeat character in our current window   *
       * There are 2 cases:                                  *
       * Case 1 - Older occurence outside current window     *
       *        - safe, continue with current substring      *
       * Case 2 - Older occurence within current window      *
       *        - shift window to start after prev occur     */
      else {
         /* case 1: Outside current window, no action        */
         if(map[val] < cur_start_idx)
            cur_len++;
         /* case 2: Within current window, shift window      */
         else {
            cur_start_idx = map[val] + 1;
            cur_len = i - cur_start_idx + 1;
         }
      }
      map[val] = i;  /* Mark where cur inp was fnd           */
   }
   cout << "Longest Unique Substring starts @ " << max_start_idx
        << " with length = " << max_len << endl;
   return max_len;
}

void longest_unique_substring_test()
{
   for(int i = 0; i < number_of_iterations; ++i)
      {
         std::vector<char> str(string_length);
         fill_vector_rand<char>(str, 'A', 'D');
         print_table_row<char>("input", str);
         longest_unique_substring<char>(str);
      }
}

int main()
{
   init_rand();
   longest_unique_substring_test();
   /* Manual test cases */
   //std::string inp = "BCBCDB";
   //std::vector<char> str(inp.begin(), inp.end());
   //longest_unique_substring<char>(str);
}
