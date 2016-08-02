//g++ --std=c++11 -Wall -g -o algo_dc_guess_number algo_dc_guess_number.cc

/**
 * @file  Guess given number
 * @brief Given a range [1-n] and number x, guess the number
 */

// https://leetcode.com/problems/guess-number-higher-or-lower/
// https://leetcode.com/problems/guess-number-higher-or-lower-ii/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/**
 * We are playing the Guess Game. The game is as follows:
 * I pick a number from 1 to n. You have to guess which number I picked.
 * Every time you guess wrong, I'll tell you whether the number is higher
 * or lower.
 * You call a pre-defined API guess(x) which returns 3 possible results
 * -1 : My number is lower
 *  1 : My number is higher
 *  0 : Congrats! You got it!
 */
int guess(int num) {return 0;} /* Not implemented yet        */

/**
 * @brief: Simple Binary Search implementation               *
 * @note:  There are no test-cases for this function yet     *
 * Time Complexity = O(lg n).   Space Complexity = O(1)      */
int guessNumber(int n) {
   for(int lo = 1, hi = n; lo <= hi;) {
      auto mid = lo + (hi - lo)/2;
      auto res = guess(mid);
      if     (res == -1) hi = mid-1;
      else if(res ==  1) lo = mid+1;
      else               return mid;
   }
   return -1;
}

   
int main()
{
   cout << "Info: Test-cases yet to be written." << endl;
   return 0;
}
