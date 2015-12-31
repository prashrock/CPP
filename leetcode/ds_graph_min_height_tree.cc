//g++ --std=c++11 -g -Wall -Werror -o ds_graph_min_height_tree ds_graph_min_height_tree.cc

/* NOTE THIS IS IMPLEMENTATION IS NOT COMPLETE */

/**
 * @file Minimum Height Tree
 * @brief Given an undirected graph, amongst all possible rooted trees, find min-height tree
 */


#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_set>     /* std::unordered_set container */
using namespace std;

/*
 */

/**
 * @class Graph
 * Graph maintains out-edge list representation of vertices  *
 */
class Graph {
public:
	Graph(int v) : V(v), adj(V, unordered_set<int>()){}
	void addEdge(int v, int w) { adj[v].insert(w);    }
	void delEdge(int v, int w) { adj[v].erase(w);     }
	unordered_set<int> getneighb(int v){return adj[v];} 
	bool isLeaf(int v) { return  adj[v].size() == 1;  }
	unsigned getNumVertices()  { return V;            }
	void delVertex(int v) {
		if(adj[v].size()) { adj[v].clear(); V--; }
	}
	vector<int> getLeafVertices() {
        vector<int> leaves;
        for(unsigned i = 0; i < adj.size(); ++i)
            if(isLeaf(i)) leaves.push_back(i);
        return leaves;
	}
private:
	int V;
	vector<unordered_set<int>> adj;
};

/**
 * Create graph fully. keep deleting leaves layer-by-layer,  *
 * until reach the root.                                     *
 * @param n     - total number of vertices                   *
 * @param edges - edge lists                                 *
 * @return                                                   *
 *   a vector containing 1-2 nodes (potential MHT roots)     *
 */
// vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
// 	Graph g(n);
// 	vector<int> leaves;
// 	for(unsigned i = 0; i < edges.size(); ++i) {
// 		g.addEdge(edges[i].first, edges[i].second);
// 		g.addEdge(edges[i].second, edges[i].first);
// 	}
// 	while(g.getNumVertices() != 1 || g.getNumVertices() != 2) {
// 		leaves = g.getLeafVertices();
// 		for(auto leaf : leaves) {
// 			auto neighbor_set = g.getneighb(leaf);
// 			for (auto neighbor : neighbor_set)
// 				g.delEdge(neighbor, leaf);
// 			g.delVertex(leaf);
// 		}
// 		if(g.getNumVertices() == leaves.size()) break;
// 	}
// 	leaves = g.getLeafVertices();
// 	if(leaves.size()) {
// 		cout << "Printing Leaves: ";
// 		for(auto i : leaves) cout << i << ",";
// 		cout << endl;
// 	}
// 	else
// 		cout << "Error: No such tree found !" << endl;
	
//     return leaves;
// }


int main()
{
	vector<pair<int, int>> v;
	/* Manual test-cases                                     */
	if(findMinHeightTrees(4, v = {{1, 0}, {1, 2}, {1, 3}}) != (vector<int>){1})
		cout << "Error: 1st Manual test failed" << endl;
	else
		cout << "Info: All manual test-cases passed" << endl;	
	return 0;
}
