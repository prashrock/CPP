#ifndef _GRAPH_SSSP_CPP_
#define _GRAPH_SSSP_CPP_

#include <algorithm>           /* std::max                   */
#include <queue>               /* std::queue                 */
#include <vector>              /* std:vector                 */
#include <set>                 /* std:set                    */
#include <stack>               /* std::stack                 */

namespace graph
{

/* Create a custom comparator without using any classes      */
struct less_than_start {

};
   
struct neighbor {
   int to;                      /* Next node (outgoing edge) */
   neighbor(int v) : to(v) {}
};

struct neighbor_wt {
   int to;                      /* Next node (outgoing edge) */
   int wt;
   neighbor_wt(int v, int w) : to(v), wt(w) {}
   inline bool operator <(const neighbor_wt& other) const {
      return (wt < other.wt);
   }
};
   
/** Single Source Shortest Path Algorithms:                  *
 * Given a graph G=(V,E) and source vertex s, find the min   *
 * cost path from s to every vertex in V.                    */

/** BFS for non-weighted graphs.                             */
   
/** Dijkstra Shortest Path Greedy Algo (Heap based approach) *
 * for weighted graphs with non-negative edges               *
 * Below is the algorithm:                                   *
 * - Initialize min_dist for all nodes as MAX_INT (infinite) *
 * - Use an 'active' set(min_heap) of yet to visit nodes     *
 * - Add source node with distance 0 to this list            *
 * - While 'active' set is no empty                          *
 *   - Get the first node in active set (smallest distance)  *
 *   - For each neighbor of this node, calculate new distance*
 *   - If (known dist > new distance) : add to active set    *
 * Time Complexity = O(m lg n), m=#edges, n=#vertices        */
int dijkstra_sssp(int src, int dst,
                  const std::vector<std::vector<neighbor_wt>>& graph) {
   std::vector<int> min_distance(graph.size(),
                                  std::numeric_limits<int>::max());
   min_distance[src] = 0;   /* src can reach src in 0 dist   */
   std::set<neighbor_wt> active_vertices; /* unknown frontier*/
   active_vertices.insert({src, 0}); /* add src to frontier  */

   while(active_vertices.empty() == false) {
      /* Pick the next smallest vertex from unknown frontier */
      int where = active_vertices.begin()->to;
      /* End the search if destination vertex is reached.    *
       * Remove this if to find shortest dist to all vertexes*/
      if(where == dst) return min_distance[dst];
      active_vertices.erase(active_vertices.begin());
      for(auto ed : graph[where]) { /* Visit all neighbors   */
         /* If any neighbor has shorter cost, add to frontier*/
         if(min_distance[ed.to] > min_distance[where] + ed.wt) {
            active_vertices.erase( {ed.to, min_distance[ed.to]} );
            min_distance[ed.to] = min_distance[where] + ed.wt;
            active_vertices.insert( {ed.to, min_distance[ed.to]} );
         }
      }
   }
   /*If shortest path from src->dst does not exceed, ret max */
   return std::numeric_limits<int>::max();
}
   
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
