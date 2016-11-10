//g++-5 --std=c++11 -g -Wall -Werror -o ds_uf_number_connected_components ds_uf_number_connected_components.cc

/**
 * @file Number of Connected Components
 * @brief Given an undirected graph return the number of connected components
 */

// https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include <stack>             /* std::stack                   */
#include <unordered_set>     /* std::unordered_set container */
using namespace std;

/*
 * Given n nodes labeled from 0 to n - 1 and a list of undirected
 * edges (each edge is a pair of nodes), write a function to find
 * the number of connected components in an undirected graph.
 * Example 1:
 *    0          3
 *    |          |
 *    1 --- 2    4
 * Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], return 2.
 * Example 2:
 *    0           4
 *    |           |
 *    1 --- 2 --- 3
 * Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [3, 4]], return 1.
 * Note:
 * You can assume that no duplicate edges will appear in edges. Since
 * all edges are undirected, [0, 1] is the same as [1, 0] and thus will
 * not appear together in edges.
 */

typedef std::pair<int, int> pii_t;

/* Approach 1 - Explore the entire graph using DFS           */
/* DFS based approach similar to Graph Valid Tree problem    */
int countComponentsDFS(int n, std::vector<pii_t>& edges) {
   /* First, build adjacency list representation of graph    */
   std::vector<std::unordered_set<int>> adjList(n, unordered_set<int>());
   for(auto edge : edges) {
      adjList[edge.first ].insert(edge.second);
      adjList[edge.second].insert(edge.first);
   }
   /* Second, do a DFS traversal to track all visited nodes  */
   std::vector<bool> visited(n, false);
   std::stack<int>   stk;
   int cc_cnt = 0;
   /* Start from each unvisited node and perform a DFS       */
   for(int i = 0; i < n; ++i) {
      if(visited[i]) continue; /* If already visited, skip node */
      stk.push(i);             /* Enter this element to process */
      cc_cnt++;                /* This is part of a new component */
      while(!stk.empty()) {    /* DFS loop, similar to Graph Valid Tree */
         auto x = stk.top(); stk.pop();
         visited[x] = true;
         for(auto neigh : adjList[x]) {
            if(visited[neigh])  continue;    /* Ignore loops */
            adjList[neigh].erase(x); /* Remove x from neighbor */
            stk.push(neigh);         /* Visit neighbor next  */
         }
      }
   }
   return cc_cnt;
}

/* Approach 2 - Find the #components with Union-Find DS      */

/* Static Union-find data structure with path-compression.   *
 * Note: for weighted quick-union with rank check notes @    *
 * https://github.com/prashrock/C/blob/master/union_find/union_find.h *
 * @note  DS does not grow dynamically - id's expected to be *
 *        in the range [0, n). No checks done                */
class unionFind {
public:
   unionFind(int n) : ufID(n) {
      std::iota (ufID.begin(), ufID.end(), 0); /* Initialize ID's [0, n) */
   }
   inline void Union(int id1, int id2) {
      ufID[id1] = id2;
   }
   /* Use Path Compression by Halving during find when id's  *
    * don't match expects id to be valid                     */
   inline int Find(int id) {
      while(ufID[id] != id) id = ufID[id] = ufID[ufID[id]];
      return id;
   }
private:
   std::vector<int> ufID;   
};

/* Use Union-Find with Path Compression                      */
int countComponentsUF(int n, std::vector<pii_t>& edges) {
   int num_components = n; /* Each vertex is a component in beginning */
   class unionFind uf(n);
   for(auto edge : edges) {
      auto e1 = uf.Find(edge.first);
      auto e2 = uf.Find(edge.second);
      /* If edge is connecting two components, call union and reduce  *
       * number of unique components seen so far                      */
      if(e1 != e2) {
         uf.Union(e1, e2);
         num_components--; /* With every union num_comp goes down by 1*/
      }
   }
   return num_components;
}

struct test_vector {
   int n;
   std::vector<pii_t> edges;
   int exp_num_components;
};

const struct test_vector test[2] =  {
   {5,      {{0,1},{1,2},{3,4}},                             2},
   {5,      {{0,1},{1,2},{2,3},{3,4}},                       1},
};

int main() {
   for(auto tst : test) {
      auto ans = countComponentsDFS(tst.n, tst.edges);
      if(ans != tst.exp_num_components) {
         cout << "Error:countComponentsDFS failed. Exp "
              << tst.exp_num_components << " Got " << ans <<  endl;
         return -1;
      }
      ans = countComponentsUF(tst.n, tst.edges);
      if(ans != tst.exp_num_components) {
         cout << "Error:countComponentsUF failed. Exp "
              << tst.exp_num_components << " Got " << ans <<  endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
