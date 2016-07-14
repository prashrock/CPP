//g++ --std=c++11 -g -o ds_string_encode_decode ds_string_encode_decode.cc

/**
 * @file  String Encode Decode
 * @brief Given a list of strings serialize and de-serialize them
 */

// https://leetcode.com/problems/encode-and-decode-strings/

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
 * Design an algorithm to encode a list of strings to a string. The
 * encoded string is then sent over the network and is decoded back
 * to the original list of strings.
 * Machine 1 (sender) has the function:
 * string encode(vector<string> strs) { return encoded_string; }
 * Machine 2 (receiver) has the function:
 * vector<string> decode(string s)    { return strs;           }
 * Implement the encode and decode methods.
 * The string may contain any possible characters out of 256 valid
 * ascii characters. Your algorithm should be generalized enough to
 * work on any possible characters.
 */

/**
 * Just like malloc metadata at beginning of buffer, maintain*
 * additional info containing num and size of each string    *
 * @param strs - vector of strings to encode                 *
 * @return                                                   *
 * A single encoded string which holds all strings from str  *
 */
string encode(vector<string>& strs) {
   string ans = std::to_string(strs.size()) + "#";
   for(auto &val : strs)
      ans += std::to_string(val.size()) + "#" + val;
   return ans;
}

vector<string> decode(string s) {
   int e, n;
   vector<string> ans;
   //cout << "decode " << s << endl;
   /* First get the # strings in encoded string              */
   e = s.find_first_of('#');
   n = std::stoi(s.substr(0, e));
   ans.resize(n);
   /* For each string we have sz#string, extract in order    */
   for(int i = 0, b = e + 1; i < ans.size(); ++i, b += n) {
      e = s.find_first_of('#', b); 
      n = std::stoi(s.substr(b, e)); /* n is size of string  */
      b = e + 1;
      ans[i] = s.substr(b, n); /* Extract the actual string  */
   }
   return ans;
}

int main()
{
   vector<string> inp, exp, ans;

   inp = {"", ""};
   exp = {"", ""};
   ans = decode(encode(inp));
   if (ans != exp) goto ErrMain;
   
   inp = {"hello", ""};
   exp = {"hello", ""};
   ans = decode(encode(inp));
   if (ans != exp) goto ErrMain;
   
   inp = {"", "world"};
   exp = {"", "world"};
   ans = decode(encode(inp));
   if (ans != exp) goto ErrMain;
   
   inp = {"hello", "world"};
   exp = {"hello", "world"};
   ans = decode(encode(inp));
   if (ans != exp) goto ErrMain;

   cout << "Info: All manual test-cases passed for encode-decode" << endl;
   return 0;
 ErrMain:
   cout << "Error: Failed for input: " << endl;
   for(auto val : inp) cout << val << ","; cout << endl;
   for(auto val : ans) cout << val << ","; cout << endl;
   return 0;
}
