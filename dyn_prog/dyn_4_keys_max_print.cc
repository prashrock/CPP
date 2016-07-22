#include <iostream>   /* std::cout                           */
#include <iomanip>    /* std::setw                           */
#include <cmath>      /* pow                                 */
#include <cassert>    /* assert                              */
#include <algorithm>  /* std::max                            */
#include "print_utils.h" /* print_table_row                  */
using namespace std;
/*
Imagine you have a special keyboard with the following keys:
Key 1:  Prints 'A' on screen
Key 2: (Ctrl-A): Select screen
Key 3: (Ctrl-C): Copy selection to buffer
Key 4: (Ctrl-V): Print buffer on screen appending it
                 after what has already been printed.
If you can only press the keyboard for N times (with the above four
keys), write a program to produce maximum numbers of A's. That is to
say, the input parameter is N (No. of keys that you can press), the
output is M (No. of As that you can produce).
*/

const int copy_overhead = 2;       /* select + copy          */
const int copy_paste_overhead = 3; /* select + copy + paste  */
const int manual_mode = 6; /*typing A is cheapest till 6 keys*/

/**
 * Dynamic Programming based approach to calculate #m        *
 * @param n                                                  *
 *   Number of keystrokes                                    *
 * Use Dynamic Prog to identify at which character we should *
 * switch from typing A's to one of below two methods:       *
 * Method-1: select, copy once and paste many times          *
 * Method-2: repeat (select, copy, paste)                    *
 * Time complexity = O(n^2). Space Complexity = O(n)         */
void num_keystrokes_calculator(const int n)
{
   std::vector<int> table(n+1);  /* memoize results          */
	
   table[0] = 0;
   for(int i = 1; i <= n; ++i) {
      int cpy_max = 0;
      if(i <= manual_mode) {
         table[i] = i;
         continue;
      }
      /* select, Copy once paste many tried at different offsets */
      /* From which keystroke should we stop typing 'A''s and do *
       * Ctrl+A Ctrl-C --> Ctrl-V, Ctrl-V, Ctrl-V....            */
      for(int j = i-copy_paste_overhead; j >= 1; --j) {
         int num_paste_ops = (i-j+1) - copy_overhead; /* [j, i] */
         int cnt_cpyonce_pstmany = num_paste_ops * table[j];
         cpy_max = std::max(cpy_max, cnt_cpyonce_pstmany);
      }
      /* Is typing better or is copy once paste many better ?   */
      table[i] = std::max(i, cpy_max);
   }
   cout << "Maximum number of 'A's = " << table[n] << endl;
   cout << "Table calculation results: " << endl;
   print_table_row<int>("cpy_once_paste_many", table);
}

int main()
{
   int n;
   cout << "Please enter the number of key strokes: ";
   cin >> n;
   num_keystrokes_calculator(n);
}
