#ifndef _GRAPH_SSSP_CPP_
#define _GRAPH_SSSP_CPP_

#include <algorithm>           /* std::max                   */
#include <queue>               /* std::queue                 */
#include <vector>              /* std:vector                 */
#include <set>                 /* std:set                    */
#include <stack>               /* std::stack                 */

namespace graph
{

/** Minimum Spanning Tree (MST) Algorithms:                  *
 * Spanning tree is a subset of edges which touches all the  *
 * vertices in a grap (spans the graph). This forms a tree.  *
 * MST is a Spanning Tree with the least total edge cost     *

/** Prim's Algo                                              */


/** Kruskal's Greedy Algo (MST in Undirected Graph)          *
 * Note: If graph is not connected, finds min spanning forest*
 * Algo: Initially, each vertex is in its own tree in forest.*
 * In each iteration, merge 2 components by chosing lightest *
 * cross-over edge (edge crossing the cut).                  */

} //end namespace

#endif //_GRAPH_SSSP_CPP_
