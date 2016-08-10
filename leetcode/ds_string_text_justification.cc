//g++-5 --std=c++11 -g -o ds_string_text_justification ds_string_text_justification.cc

/**
 * @file  Text Justification
 * @brief Given a bunch of words and line size, do center justify
 */

// https://leetcode.com/problems/text-justification/

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
 * Given an array of words and a length L, format the text such
 * that each line has exactly L characters and is fully (left
 * and right) justified.
 * You should pack your words in a greedy approach; that is, pack
 * as many words as you can in each line. Pad extra spaces ' '
 * when necessary so that each line has exactly L characters.
 * Extra spaces between words should be distributed as evenly as
 * possible. If the number of spaces on a line do not divide
 * evenly between words, the empty slots on the left will be
 * assigned more spaces than the slots on the right.
 * For the last line of text, it should be left justified and no
 * extra space is inserted between words.
 * For example,
 * words: ["This", "is", "an", "example", "of", "text", "justification."]
 * L: 16.
 * Return the formatted lines as:
 * [ "This    is    an",
 *   "example  of text",
 *   "justification.  "
 * ]
 * Note: Each word is guaranteed not to exceed L in length.
 */

/* Given a line containing n words and max width, align that *
 * line with appropriate white-spaces to make l/r justified  */
void justify(vector<char>& line, int numWords, int maxWidth) {
   /* 1 word is a special case for padding                   */
   if(numWords == 1) {
      while(line.size() < maxWidth) line.push_back(' ');
   }
   else {
      /* remove last char if it is a whitespace              */
      while(line.back() == ' ') line.erase(std::prev(line.end()));
      int num_space = numWords - 1;
      int pad       = (maxWidth - line.size()) / (num_space);
      int extra_pad = (maxWidth - line.size()) % (num_space);
      /* If total extra padding is less than gaps, add one   *
       * extra pad each time                                 */
      if(extra_pad && extra_pad <= num_space) extra_pad = 1;
      /* Find gap between each word + add appropriate spaces */
      for(int i = 0, cur = 0; i < num_space && cur < maxWidth; ++i) {
         /* If nomore extra padding is reqd, disable extrapad*/
         if( (maxWidth - line.size()) % (num_space - i) == 0) extra_pad = 0;
         /* Cur points to a new word, goto end of this word  */
         while(cur < maxWidth && line[cur] != ' ') cur++;
         /* Add padding. Note padding = pad + extra_pad      */
         for(int j = 0; j < (pad + extra_pad) && line.size() < maxWidth; ++j, ++cur)
            line.insert(line.begin()+cur, ' ');
         /* Find the beginning of the next word              */
         while(cur < maxWidth && line[cur] == ' ') cur++;
      }
   }
}

/* Last line of output must be left-justified. So, trim all  *
 * extra spaces we introduced and force left-alignment       */
void last_line_justify(std::string& line, int maxWidth) {
   if(line.size() == 0) return; /* corner-case               */
   /* Start from second char, if more than one consequtive   *
    * white space found, trim all the white-spaces           */
   for(auto it = std::next(line.begin()); it != line.end(); ) {
      if(*it == ' ' && *std::prev(it) == ' ') line.erase(it);
      else                                    ++it;
   }
   /* After trimming all the extra spaces, add spaced in end */
   while(line.size() < maxWidth) line.push_back(' ');
}

/* Given a line(vector of chars), convert to string + insert */
void push(vector<string>& lines, vector<char>& line, int& numWords) {
   lines.push_back(std::string(line.begin(), line.end()));
   line.clear();
   numWords = 0;
}

/* Hanndle Greedy L/R Justification. Gather as many words as *
 * can fit in a line & pad it with spaces to align to width  */
vector<string> fullJustify(vector<string>& words, int maxWidth) {
   vector<string> lines; /* Final result - vector of strings */
   vector<char> line;    /* Each line - vector of characters */
   int numWords = 0;

   for(auto word : words) {
      /* If existing line is full, format and push this line */
      if(line.size() + word.size() > maxWidth)  {
         justify(line, numWords, maxWidth);
         push(lines, line, numWords);
      }
      for (auto c : word) line.push_back(c);
      if(line.size() == maxWidth)  push(lines, line, numWords);
      else                       { line.push_back(' '); numWords++; }
   }
   /* Handle the last line that was being processed          */
   if(numWords) {
      justify(line, numWords, maxWidth);
      push(lines, line, numWords);
   }
   /* Re-justify the last line of the entire section         */
   last_line_justify(lines.back(), maxWidth);
   return lines;
}

int main()
{
   cout << "Info: Manual test-cases not yet written." << endl;
   return 0;
}
