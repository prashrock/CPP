//g++ -Wall --std=c++11 -g -o vector_bounds_example vector_bounds_example.cc -I../utils/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include "print_utils.h"     /* print_table_row              */
using namespace std;

/* Lower bound returns an iterator pointing to the first     *
 * element in the range [first,last) that is **not less**    *
 * than value.                                               *
 * Note-1: If *it!=num, we have bigger#, so go back          *
 * Note-2: lower_bound offers O(lg n) complexity when working*
 * with a random access iterator (vector iterator)           */

/* Upper bound returns an iterator pointing to the first     *
 * element in the range [first,last) that is **greater**     *
 * than value.                                               */
void lb_ub_print(std::vector<int>& v, int find_val) {
   int lb = std::lower_bound(v.begin(), v.end(), find_val) - v.begin();
   int ub = std::upper_bound(v.begin(), v.end(), find_val) - v.begin();
   cout << find_val << " lb @ "  << lb
                    << ", ub @ " << ub << endl;
}

int main() {
   std::vector<int> v = {1, 1, 2, 3, 4, 8, 9, 9, 9};
   cout << "Below is example vector of length " << v.size() << endl;
   print_table_row<int>("input", v, 2, 3);
   
   lb_ub_print(v, 0);
   lb_ub_print(v, 1);
   lb_ub_print(v, 3);
   lb_ub_print(v, 5);
   lb_ub_print(v, 9);
   lb_ub_print(v, 10);
   
   return 0;
}

/* Gives the below results:
   Below is example vector of length 9
   input:   1   1   2   3   4   8   9   9   9
   0 lb @ 0, ub @ 0
   1 lb @ 0, ub @ 2
   3 lb @ 3, ub @ 4
   5 lb @ 5, ub @ 5
   9 lb @ 6, ub @ 9
   10 lb @ 9, ub @ 9
 */
