//g++ -Wall --std=c++11 -g -o vector_bounds_example vector_bounds_example.cc -I../utils/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include "print_utils.h"     /* print_table_row              */
using namespace std;

/* Lower bound returns an iterator pointing to the first *
 * element in the range [first,last) that is **not less***
 * than value.                                           *
 * Note: If *it!=num, we have bigger#, so go back        *
 * Upper bound returns an iterator pointing to the first *
 * element in the range [first,last) that is **greater** *
 * than value.                                           *
 */
void lb_ub_print(std::vector<int>& v, int find_val) {
   int lb = std::lower_bound(v.begin(), v.end(), find_val) - v.begin();
   int ub = std::upper_bound(v.begin(), v.end(), find_val) - v.begin();
   cout << find_val << " lb @ "  << lb
                    << ", ub @ " << ub << endl;
}

int main() {
   std::vector<int> v = {1, 1, 2, 3, 4, 5, 6, 6, 6};
   cout << "Below is example vector of length " << v.size() << endl;
   print_table_row<int>("input", v, 2, 3);
   
   lb_ub_print(v, 0);
   lb_ub_print(v, 1);
   lb_ub_print(v, 3);
   lb_ub_print(v, 6);
   lb_ub_print(v, 7);

   return 0;
}
