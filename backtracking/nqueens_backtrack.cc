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

/* Given an NxN board find a way to place N queens on the    *
 * chessboard so that the queens cannot attack each other    */
const int board_size = 8;    /* 8x8                          */


/* Given an NxN board, dump all the contents - dump (NxN)    */
template<int n>
void board_print(bool (&board)[n][n])
{
   static int sol_cnt;
   cout << "Solution #" << sol_cnt++ << endl;
   for(int i = 0; i < n; ++i) {
      for(int j = 0; j < n; ++j) {
         if(board[i][j]) cout << "Q ";
         else            cout << "X ";
      }
      cout << endl;
   }
   cout << endl;
}

/* Place a chess piece in the given location                 *
 * @param board - NxN 2D boolean array/vector                *
 * @param row   - row index (zero-based)                     *
 * @param col   - col index (zero-based)                     */
template<int N>
void board_place_piece(bool (&board)[N][N], int row, int col)
{
   board[row][col] = true;
}

/* Remove a chess piece from the given location              *
 * @param board - NxN 2D boolean array/vector                *
 * @param row   - row index (zero-based)                     *
 * @param col   - col index (zero-based)                     */
template<int N>
void board_remove_piece(bool (&board)[N][N], int row, int col)
{
   board[row][col] = false;
}

/* Validate current Queen placement in the board.            *
 * Check if another queen exists in the same row or in the   *
 * same column or diagonally (both diagonals)                *
 * check between [0, row) and [0, col) for another queen     *
 * @param board - NxN 2D boolean array/vector                *
 * @param row   - row index (zero-based)                     *
 * @param col   - col index (zero-based)                     */
template<int N>
bool board_validate(bool (&board)[N][N], int row, int col)
{
   int i, j;
   /* Check all previous rows for same column                */
   for(i = 0; i < (int)N; ++i) if(board[i][col]) return false;
   /* Check all previous columns for same row                */
   for(i = 0; i < (int)N; ++i) if(board[row][i]) return false;
   /* Check north-west diagonal                              */
   for(i=row, j=col; (i>=0 && j>=0); i--,j--)
      if(board[i][j])                            return false;
   /* Check south-west diagonal                              */
   for(i=row, j=col; (i<N&&j>=0);  i++,j--)
      if(board[i][j])                            return false;
   return true;
}

/* Backtrack algo for solving an NxN board for placements    *
 * For each column placement(recursive) iterate over all rows*
 * @param board - NxN 2D boolean array/vector                *
 * @param col   - col index (zero-based)                     *
 * @all_sol     - Stop with 1 solution or find all solutions *
 * Time Complexity = O(n!)                                   */
template<int N>
bool board_solver(bool (&board)[N][N], int col, bool all_sol)
{
   if(col >= N) {
      board_print<N>(board);
      return true;
   }
   /* For loop to go row-by-row, and recurse col-by-col      */
   for(int i = 0; i < N; ++i) {
      if(board_validate<N>(board, i, col)) {
         bool res;
         board_place_piece<N>(board, i, col);
         res = board_solver<N>(board, col+1, all_sol);
         /* If res == true, we found one solution already.*
          * If user wants only one sol, stop right here   */
         if(res == true && all_sol == false)
            return true; 
         board_remove_piece<N>(board, i, col);
      }
   }
   return false;
}

int main()
{
   init_rand();
   bool board[board_size][board_size] = {0};
   board_solver<board_size>(board, 0, true);
}
