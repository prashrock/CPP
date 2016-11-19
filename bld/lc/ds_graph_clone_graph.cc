//g++-5 --std=c++11 -g -Wall -Werror -o ds_graph_clone_graph ds_graph_clone_graph.cc

/**
 * @file Clone Graph
 * @brief Given an undirected graph, clone (deep copy) it
 */

// https://leetcode.com/problems/clone-graph/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/*
 * Clone an undirected graph. Each node in the graph contains
 * a label and a list of its neighbors.
 * OJ's undirected graph serialization:
 * Nodes are labeled uniquely.
 * We use # as a separator for each node, and , as a separator
 * for node label and each neighbor of the node.
 * As an example, consider the serialized graph {0,1,2#1,2#2,2}.
 * The graph has a total of three nodes, and therefore contains
 * three parts as separated by #.
 * First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
 * Second node is labeled as 1. Connect node 1 to node 2.
 * Third node is labeled as 2. Connect node 2 to node 2 (itself),
 * thus forming a self-cycle. Visually, the graph looks like the following:
 *
 *           1
 *          / \
 *         /   \
 *        0 --- 2
 *             / \
 *             \_/
 */

struct UndirectedGraphNode {
   int label;
   vector<UndirectedGraphNode *> neighbors;
   UndirectedGraphNode(int x) : label(x) {};
};

std::unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> clones;

/* DFS based recursive approach to clone an undirected graph */
UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
   if(node == nullptr) return nullptr;
   /* If we have not seen this node before, explore all neighbors */
   if(clones.find(node) == clones.end()) {
      auto cln = clones[node] = new UndirectedGraphNode(node->label);
      for(auto x : node->neighbors) {
         cln->neighbors.push_back(cloneGraph(x));
      }
   }
   return clones[node];
}

int main() {
   cout << "Info: Test cases yet to be implemented." << endl;
   return 0;
}
