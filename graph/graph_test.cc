#include <iostream>            /* std::cout                  */
#include <iomanip>             /* std::setw                  */
#include <vector>              /* std::vector                */
#include <cmath>               /* pow, log2                  */
#include <cassert>             /* assert                     */
#include <algorithm>           /* std::max                   */
#include <random>              /* std::default_random_engine */

#include "rand_generator.h"    /* init_rand()                */
#include "graph.h"             /* Undirected/Directed Graphs */
#include "graph_sssp.h"        /* Dijkstra's SSSP            */
#include "print_utils.h"       /* print_table_row            */
using namespace std;
using namespace graph;

bool dijkstra_test() {
   /* ex from http://www.ifp.illinois.edu/~angelia/ge330fall09_dijkstra_l18.pdf    */
   std::vector<std::vector<neighbor_wt>> graph = {
      {},
      {{2, 7}, {3, 9}, {6, 14}},
      {{3, 10}, {4, 15}},
      {{4, 11}, {6, 2}},
      {{5, 6}},
      {},
      {{5, 9}},
   };
   if     (dijkstra_sssp(1, 2, graph) != 7)  return false;
   else if(dijkstra_sssp(1, 6, graph) != 11) return false;
   else if(dijkstra_sssp(1, 4, graph) != 20) return false;
   else                                      return true;
}

int main()
{
   init_rand();
   if(dijkstra_test() == false) return -1;
   cout << "Info: Manual tests passed successfully" << endl;
   return 0;
}
