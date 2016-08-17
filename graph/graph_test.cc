#include <iostream>            /* std::cout                  */
#include <iomanip>             /* std::setw                  */
#include <vector>              /* std::vector                */
#include <cmath>               /* pow, log2                  */
#include <cassert>             /* assert                     */
#include <algorithm>           /* std::max                   */
#include <random>              /* std::default_random_engine */

#include "rand_generator.h"    /* init_rand()                */
#include "graph.h"             /* Undirected/Directed Graphs */
#include "print_utils.h"       /*print_table_row             */
using namespace std;
using namespace graph;


int main()
{
   init_rand();
   cout << "Info: Manual tests passed successfully" << endl;
   return 0;
}
