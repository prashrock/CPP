#ifndef _GRAPH_SSSP_CPP_
#define _GRAPH_SSSP_CPP_

#include <algorithm>           /* std::max                   */
#include <queue>               /* std::queue                 */
#include <vector>              /* std:vector                 */
#include <set>                 /* std:set                    */
#include <stack>               /* std::stack                 */

namespace graph
{

/** Single Source Shortest Path Algorithms:                  *
 * Given a graph G=(V,E) and source vertex s, find the min   *
 * cost path from s to every vertex in V.                    */

/** BFS for non-weighted graphs.                             */
   
/** Dijkstra Shortest Path Greedy Algo (Heap based approach) *
 * for weighted graphs with non-negative edges.              *
 * Time Complexity = O(m lg n), m=#edges, n=#vertices        */

/** Floyd-Warshall All path shortest-pair Algo               *
 * Note - find shortest path from all sources to all targets *
 * Note - can also find the connectivity (transitive closure)*
 * Algo is below:                                            *
 * for k = 1:n                                               *
 *   for i = 1:n                                             *
 *      for j = 1:n                                          *
 *         adj[i][j]=min(adj[i][j], adj[i][k] + adj[k][j]);  */
   
} //end namespace

#endif //_GRAPH_SSSP_CPP_
