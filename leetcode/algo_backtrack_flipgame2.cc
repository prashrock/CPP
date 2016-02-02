//g++ -Wall --std=c++11 -g -o algo_backtrack_flipgame2 algo_backtrack_flipgame2.cc

/**
 * @file  Flip Game II
 * @brief Alternate moves and play till one player has no move.
 */

//https://leetcode.com/problems/flip-game-ii/

/**
 * You are playing the following Flip Game with your friend: Given
 * a string that contains only these two characters:  + and -,
 * you and your friend take turns to flip two consecutive "++" into "--".
 * The game ends when a person can no longer make a move and therefore
 * the other person will be the winner.
 * Write a function to determine if the starting player can guarantee a win.
 * For example, given s = "++++", return true. The starting player can
 * guarantee a win by flipping the middle "++" to become "+--+".
 */

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

void setPos(string &s, int idx)   { s[idx] = s[idx + 1] = '-'; }
void unsetPos(string &s, int idx) { s[idx] = s[idx + 1] = '+'; }
bool chkPos(string &s, int idx)   {return (s[idx]=='+'&&s[idx+1]=='+');}

/**
 * Backtracking algorithm to calculate if current player can *
 * win. Each recursively loop causes players to alternate    *
 * @param s   Input string as reference (modify in place)    *
 * @ret       true if cur player has atleast 1 winning move  *
 * Time Complexity = O(2^n),  Space Complexity = O(1)        *
 * Note: performance can be improved with memoization by     *
 * calculating results of sub-strings and storing results in *
 * a hash table.                                             *
 */
bool canWinBT(string &s)
{
   bool ret = false; /* I have to move first, assume fail    */
   /* Loop till last but 1 character (check 2 chars at time) */
   for(int i = 0; i < (int)s.size()-1; ++i) {
      /* Chk if we can make valid move at current idx        */
      if(chkPos(s, i)) {
         setPos(s, i);       /* Make move at current idx     */
         /* Each recursion implies other player's move       *
          * So current player's success is tied to other     *
          * player's failure (backtracking algo)             */
         ret = !canWinBT(s);
         unsetPos(s, i);     /* Undo move at current idx     */
         if(ret == true)  break; /* Break if winning move    */
      }
   }
   /* return true if 1 winning move found else return false  */
   return ret;
}

bool canWin(string s) {
   if(s.size() == 0) return false;
   else              return canWinBT(s);
}

bool tester(string s, bool exp_res)
{
   if(canWin(s) != exp_res) {
      cout << "Error: expected " << exp_res << " for " << s << endl;
      return false;
   }
   return true;
}

int main()
{
   if   (tester("++++",  true) == false) {goto end;}
   else if(tester("+",  false) == false) {goto end;}
   else if(tester("--", false) == false) {goto end;}
   else if(tester("", false)   == false) {goto end;}
   else if(tester("+++--++++--++++", true) == false) {goto end;}
   cout << "Info: All manual test cases passed" << endl;
end:
   return 0;
}
