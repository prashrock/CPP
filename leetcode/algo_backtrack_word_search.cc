//g++-5 --std=c++11 -Wall -g -o algo_backtrack_word_search algo_backtrack_word_search.cc

/**
 * @file  Word Search
 * @brief Find word from 2D board
 */

//https://leetcode.com/problems/word-search/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/**
 * Given a 2D board and a word, find if the word exists in the grid.
 * The word can be constructed from letters of sequentially adjacent cell,
 * where "adjacent" cells are those horizontally or vertically neighboring.
 * The same letter cell may not be used more than once.
 * For example, Given board =
 *  [['A','B','C','E'],
 *   ['S','F','C','S'],
 *   ['A','D','E','E']]
 * word = "ABCCED", -> returns true,
 * word = "SEE",    -> returns true,
 * word = "ABCB",   -> returns false.
 */


/*------------------- Backtrack Algo ------------------------*/
int m, n; /* row, col size of the given board                */
/**
 * Backtracking algorithm to explore all 4 directions given  *
 * a starting position                                       *
 * @param board - 2D Input board                             *
 * @param word  - String that has to be searched             *
 * @param idx   - current index being processed in word      *
 * @param i,j   - 0-based row,col pos to look for word[idx]  *
 */
bool existBT(vector<vector<char>> &board, string &word, int idx,
	     int i, int j)
{
   /* Basecase - Reached end of backtracking             */
   if((int)word.size() == idx)                              return true;
   if(i<0 || j<0 || i==m || j==n || board[i][j]!=word[idx]) return false;
   board[i][j] = '\0';
   /* Try north, south, west, east for next char match   */
   bool ret = existBT(board, word, idx+1, i-1, j)   ||
	existBT(board, word, idx+1, i+1, j)   ||
	existBT(board, word, idx+1, i,   j-1) ||
	existBT(board, word, idx+1, i,   j+1);
   board[i][j] = word[idx];
   return ret;
}

bool exist(vector<vector<char>> &board, string word) {
   if     (word.size()  == 0)  return true;
   else if(board.size() == 0)  return false;
   m = board.size();
   n = board[0].size();

   /* For every occurence of 1st char scan the table   */
   for(int i = 0; i < m; ++i)
      for(int j = 0; j < n; ++j)
	 if(board[i][j] == word[0] && existBT(board, word, 0, i, j))
	    return true;
   return false;
}

int main(){
   vector<vector<char>> board;
   string word;
   bool exp, ans;
   board = {{'A','B','C','E'},
	    {'S','F','C','S'},
	    {'A','D','E','E'}};
   word = "ABCCED"; exp = true;
   ans = exist(board, word);
   if(ans != exp) goto ErrMain;
      
   board = {{'a', 'a'}};
   word = "aaa"; exp = false;
   ans = exist(board, word);
   if(ans != exp) goto ErrMain;
   
   board = {{'C','A','A'},{'A','A','A'},{'B','C','D'}};
   word = "AAB"; exp = true;
   ans = exist(board, word);
   if(ans != exp) goto ErrMain;
   
   cout << "Info: All manual test cases passed" << endl;
   return 0;
ErrMain:
   cout << "Error: Failed to finding '" << word << "' in board" << endl;
   return -1;
}
