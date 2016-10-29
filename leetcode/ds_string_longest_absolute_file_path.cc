//g++-5 --std=c++11 -g -o ds_string_longest_absolute_file_path ds_string_longest_absolute_file_path.cc

/**
 * @file  Longest Absolute File Path
 * @brief Find a file within sub-dir with longest path.
 */

// https://leetcode.com/problems/longest-absolute-file-path/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
#include <cstring>           /* std::strtok                  */
using namespace std;

/**
 * Suppose we abstract our file system by a string in the following
 * manner:
 * The string "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" represents:
 *   dir
 *      subdir1
 *      subdir2
 *         file.ext
 * The directory dir contains an empty sub-directory subdir1 and a
 * sub-directory subdir2 containing a file file.ext.
 * The string "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
 * represents:
 *   dir
 *      subdir1
 *         file1.ext
 *         subsubdir1
 *      subdir2
 *         subsubdir2
 *            file2.ext
 * The directory dir contains two sub-directories subdir1 and subdir2.
 * subdir1 contains a file file1.ext and an empty second-level sub-
 * directory subsubdir1. subdir2 contains a second-level sub-directory
 * subsubdir2 containing a file file2.ext.
 * We are interested in finding the longest (number of characters)
 * absolute path to a file within our file system. For example, in the
 * second example above, the longest absolute path is
 * "dir/subdir2/subsubdir2/file2.ext", and its length is 32 (not
 * including the double quotes).
 * Given a string representing the file system in the above format,
 * return the length of the longest absolute path to file in the
 * abstracted file system. If there is no file in the system, return 0.
 * Note: The name of a file contains at least a . and an extension.
 *       The name of a directory or sub-directory will not contain a ..
 * Time complexity required: O(n) where n is the size of the input string.
 * Notice that a/aa/aaa/file1.txt is not the longest file path, if there
 * is another path aaaaaaaaaaaaaaaaaaaaa/sth.png
 */

/* Use the #'\t' to find the file/dir level and return the   *
 * size of the token (without \t's)                          */
inline int find_level(const char *tok, int& lev) {
   while(tok[lev] == '\t')    lev++;/*  each \t means 1 level*/
   return (strlen(tok) - lev);      /* Leave \t for len calc */
}

/** @brief Maintain the longest word seen till this point    */
int lengthLongestPath(string input) {
   int size = 0;  /* Holds the maximum path length so far    */
   auto *tok = strtok((char *)input.c_str(), "\n");
   /* Treat like a stack to hold cumulative path lens till this point. */
   std::vector<int> cur_len;
   /* Split input into tokens (use '\n' as the separator)    */
   for(; tok != nullptr; tok = strtok(nullptr, "\n")) {
      int lev = 0;   /* 0-based current file/directory level */
      int toklen = find_level(tok, lev); /* Cur token length */
      /* Stack should have cur directory, update accordingly */
      if(lev == cur_len.size()) cur_len.push_back(toklen);
      else                      cur_len[lev] = toklen;
      /* Include parent dir len and '\' in cur dir len calc  */
      if(lev > 0) cur_len[lev] += cur_len[lev - 1] + 1;
      /* If this is a file, then see if this is a max-len    */
      if(strchr(tok, '.') != nullptr) size = std::max(size, cur_len[lev]);
      /* For debugging, print cur-level, file/dir name & size*/
      //cout << lev << ") " << tok << "(" << cur_len[lev] << ")" << endl;
   }
   return size;
}

struct test_vector {
   std::string s;
   int exp;
};

const struct test_vector test[5] =  {
{"a",                                        0},
{"dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext", 20},
{"dir\n\tsubdir1\n\tsubdir2\n\t\t.ext",     16},
{"dir\n\tsubdir1\n\t\tfile.ext\n\tsubdir2", 20},
{"dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext", 32},
};

int main()
{
   for(auto tst : test) {
      auto ans = lengthLongestPath(tst.s);
      if(ans != tst.exp) {
         cout << "Error:lengthLongestPath failed. Exp "
              << tst.exp << " Got " << ans
              << " for " << tst.s   << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}

