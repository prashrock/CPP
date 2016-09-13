//g++-5 -Wall --std=c++11 -g -o ds_string_zigzag_conversion ds_string_zigzag_conversion.cc

/**
 * @file  String Zigzag traversal
 * @brief Given string return its zigzag traversal.
 */

// https://leetcode.com/problems/zigzag-conversion/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
#include <vector>            /* std:vector                   */
using namespace std;

/*
 * The string "PAYPALISHIRING" is written in a zigzag pattern
 * on a given number of rows like this: (you may want to display
 * this pattern in a fixed font for better legibility)
 *  P   A   H   N
 *  A P L S I I G
 *  Y   I   R
 * And then read line by line: "PAHNAPLSIIGYIR"
 * Write the code that will take a string and make this conversion
 * given a number of rows:
 * string convert(string text, int nRows);
 * convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
 */



/** @brief use a row idx to decide which row should the next *
 * char be inserted into. For example, given ABCDEFGHIJ, 4   *
 * A     G     M                                             *
 * B   F H   L N                                             *
 * C E   I K   O                                             *
 * D     J     P                                             */
string convert(string s, size_t numRows) {
   int rowadd = 1;
   /* Corner case: If #rows < 2, this function is a no-op    */
   if(numRows < 2)       return s;
   /* 2-D vector holding characters one row at a time        */
   std::vector<std::vector<char>> srows(numRows, std::vector<char>(0));
   /* i tracks the input char sequence, i in [0, n)          *
    * row holds row idx to insert the cur char [0, numRows)  */
   for(size_t i = 0, row = 0; i < s.size(); ++i, row += rowadd) {
      srows[row].push_back(s[i]);  /* Push cur into cur row  */
      if(row == numRows - 1) rowadd = -1; /* in last row     */
      else if(row == 0)      rowadd =  1; /* in first row    */
   }
   string ans;
   for(auto v : srows)  ans += std::string(v.begin(), v.end());
   return ans;
}

struct test_vector {
   std::string inp;
   size_t nrows;
   std::string exp;
};

const struct test_vector test[5] =  {
   { "",                    5, ""},
   { "ABC",                 1, "ABC"},
   { "PAYPALISHIRING",      3, "PAHNAPLSIIGYIR"},
   { "PAYPALISHIRING",      4, "PINALSIGYAHRPI"},
   { "1234567890123456789", 5, "1972806837159462453"},
};

int main() {
   for(auto tst : test) {
      auto ans = convert(tst.inp, tst.nrows);
      if(ans != tst.exp) {
         cout << "Error:convert failed. Exp "
              << tst.exp << " Got " << ans
              << " for " << tst.nrows << " rows" << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
