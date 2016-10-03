//g++-5 -O3 -Wall --std=c++11 -g -o algo_design_readn_chars algo_design_readn_chars.cc

/**
 * @file  ReadN characters
 * @brief Given read4 chars implement a readn
 */

// https://leetcode.com/problems/read-n-characters-given-read4/
// https://leetcode.com/problems/read-n-characters-given-read4-ii-call-multiple-times/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::min                     */
#include <vector>            /* std:vector                   */
using namespace std;

// Dummy implementation of the read4 API.
int read4(char *buf) { return 0; }

/**
 * The API: int read4(char *buf) reads 4 characters at a time
 * from a file.
 * The return value is the actual number of characters read.
 * For example, it returns 3 if there is only 3 characters left
 * in the file.
 * By using the read4 API, implement the function int
 * read(char *buf, int n) that reads n characters from the file.
 * Note:
 * The read function will only be called once for each test case.
 */

// https://leetcode.com/problems/read-n-characters-given-read4/

/**
 * @brief - Maintain a local buffer to copy 4 chars at a time*/
int read(char *buf, int n) {
   int i = 0;
   int i4 = 0, n4 = 0; /* Define locally, as state not needed*/
   char tmp[4];       /* Define locally, as state not needed */
   while(i < n) {
      if(i4 == n4) { i4 = 0; n4 = read4(tmp); }
      if(n4 == 0)  break;
      buf[i++] = tmp[i4++];
   }
   return i;       /* Return number of bytes actually copied */
}

/**
 * Same as above
 * Note: The read function maybe called multiple times
 */

// https://leetcode.com/problems/read-n-characters-given-read4-ii-call-multiple-times/

class Solution {
public:
   int read(char *buf, int n) {
      int i = 0;
      while(i < n) {
         if(i4 == n4) { i4 = 0; n4 = read4(tmp); }
         if(n4 == 0)  break;
         buf[i++] = tmp[i4++];
      }
      return i;
   }
private:
   char tmp[4];    /* Re-use tmp across calls to read        */
   int  i4 = 0, n4 = 0; /* Maintain read4 statictics         */
};


int main()
{
   cout << "Info: Manual testcases yet to be written" << endl;
   return 0;
}

