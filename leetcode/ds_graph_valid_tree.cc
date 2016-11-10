//g++-5 --std=c++11 -g -Wall -Werror -o ds_graph_valid_tree ds_graph_valid_tree.cc

/**
 * @file Graph Valid Tree
 * @brief Given an undirected graph, find out if it forms a valid tree
 */

// https://leetcode.com/problems/graph-valid-tree/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include <stack>             /* std::stack                   */
#include <unordered_set>     /* std::unordered_set container */
using namespace std;

/*
 * Given n nodes labeled from 0 to n - 1 and a list of undirected edges
 * (each edge is a pair of nodes), write a function to check whether
 * these edges make up a valid tree.
 * For example:
 * Given n = 5 and edges = [[0, 1], [0, 2], [0, 3], [1, 4]], return true.
 * Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]], return false.
 * Hint:
 * Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], what should your return?
 * Is this case a valid tree?
 * According to the definition of tree on Wikipedia: A tree is an undirected
 * graph in which any two vertices are connected by exactly one path. In other
 * words, any connected graph without simple cycles is a tree..
 * Note: you can assume that no duplicate edges will appear in edges. Since all
 * edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear
 * together in edges.
 */

typedef std::pair<int, int> pii_t;

/* Note: A tree should satisfy the below properties:         *
 * - Has n-1 edges and is connected but acyclic              */
bool validTree(const int n, std::vector<pii_t>& edges) {
   /* Note: Any tree with n nodes has exactly n-1 edges      */
   if((int)edges.size() != (n - 1))   return false;

   /* Build the adjacency list representation of graph       */
   std::vector<std::unordered_set<int>> adjList(n, std::unordered_set<int>());
   for(auto edge : edges) {
      adjList[edge.first ].insert(edge.second);
      adjList[edge.second].insert(edge.first);
   }

   /* Next, check for loops in the graph.                              *
    * Use a bool vector to track list of visited nodes and use stack   *
    * for iterative DFS traversal of the entire graph. To avoid double *
    * visiting a node, remove it from neighbor's adjacency list before *
    * adding neighbor to stack. Alternatively, we can use 3 color and  *
    * recursive approach for Graph DFS traversal.                      */
   std::vector<bool> visited(n, false);
   std::stack<int>   stk;
   stk.push(0); /* Start from any node (need not be the root of tree)  */
   while(!stk.empty()) {
      int x = stk.top(); stk.pop();
      visited[x] = true;
      for(auto neigh : adjList[x]) {
         if(visited[neigh])  return false; /* If loop, cannot be tree  */
         adjList[neigh].erase(x); /* Remove x from neighbor's list     */
         stk.push(neigh);
      }
   }

   /* Lastly, verify if graph is fully connected to qualify as a tree  */
   for(auto v : visited) if(v == false) return false;
   return true;
}

struct test_vector {
   int n;
   std::vector<pii_t> edges;
   bool exp;
};

const struct test_vector test[6] =  {
   {5, {{0,1},{0,2},{2,3},{2,4}},                       true},
   {5, {{0,1},{1,2},{2,3},{1,3},{1,4}},                false},
   {4, {{0,1},{2,3}},                                  false},
   {7, {{0,1},{0,2},{0,3},{4,5},{4,6}},                false},
   {5, {{0,1},{1,2},{3,4}},                            false},
   {4, {{0,1},{2,3},{1,2}},                             true},
};

int main() {
   for(auto tst : test) {
      auto ans = validTree(tst.n, tst.edges);
      if(ans != tst.exp) {
         cout << "Error:validTree failed. Exp "
              << tst.exp << " Got " << ans <<  endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
