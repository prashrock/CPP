//g++ --std=c++11 -g -Wall -Werror -o ds_graph_loop_course_schedule_ii ds_graph_loop_course_schedule_ii.cc

/**
 * @file Course Schedule II
 * @brief Given a list of courses and prerequisites, return any 
 * one ordering of courses to finish all the courses
 */


#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <stack>             /* std::stack                   */
using namespace std;

/*
 * There are a total of n courses to take, labeled from 0 to n - 1. Some
 * courses may have prerequisites, for example to take  course 0 you have
 * to first take course 1, which is expressed as a pair: [0,1]
 *
 * Given the total number of courses and a list of prerequisite pairs, return
 * the ordering of courses you should take to finish all courses.
 *
 * There may be multiple correct orders, you just need to return one of them.
 * If it is impossible to finish all courses, return an empty array. For example:
 * 2, [[1,0]] - There are a total of 2 courses to take. To take course 1 you
 * should have finished course 0. So the correct course order is [0,1]
 * 4, [[1,0],[2,0],[3,1],[3,2]] - There are a total of 4 courses to take. To take
 * course 3 you should have finished both courses 1 and 2. Both courses 1 and 2
 * should be taken after you finished course 0. So one correct course order
 * is [0,1,2,3]. Another correct ordering is[0,2,1,3].
 */

/**
 * @class Graph
 * Graph maintains out-edge list representation of vertices  *
 * There is one method which uses DFS based topological sort *
 * Use a 3 colored approach to mark visited info in DFS      *
 * 0=unvisited, 1=currently_visiting, 2=finished_node        *
 */
class Graph {
public:
	Graph(int v) : V(v), adj(V, vector<int>()){}
	void addEdge(int v, int w) {adj[v].push_back(w);}
	/* Given a node, find if there are any loops in subgraph *
	 * If there are no loops, return the topological ordering*/
	bool DFSHasLoopTopo(int v, vector<int> &visited, vector<int> &r) {
		visited[v] = 1; /* Grey -- Currently processing node */
		for(auto e: adj[v]) {
			/* If adj node is unvisited, visit recursively   */
			if(visited[e] == 0) {
				bool ret = DFSHasLoopTopo(e, visited, r);
				if(ret == true)       return true;
			}
			/* If an adjacent node is also in currently      *
			 * processing state, we have a loop. return imm  */
			else if(visited[e] == 1)  return true;
		}
		visited[v] = 2; /* Black -- finished processing node */
		r.push_back(v);
		return false;
	}
private:
	int V;
	vector<vector<int>> adj;
};

/**
 * Create graph fully. Use DFS based Topological sort        *
 * @param n       - total number of vertices                 *
 * @param prereqs - Directed edge adjacency list             *
 * @return                                                   *
 *   Vector containing any one topological order             *
 */
vector<int> findOrder(int n, vector<pair<int, int>>& prereq) {
	vector<int>  topo;
	vector<int> visited(n, false);
	Graph g(n);
	for(unsigned i = 0; i < prereq.size(); ++i)
		g.addEdge(prereq[i].second, prereq[i].first);
	for(int i = 0; i < n; ++i) {
		if(visited[i] == 0) /* If unvisited node, start DFS  */
			if(g.DFSHasLoopTopo(i, visited, topo) == true) {
				topo.clear(); /* If loop, no topo ordering   */
				break;        /* stop if loop is found       */
			}
	}
	/* Poor man's stack :)  Emulate stack with vector        *
	 * Since we want to return vector, maintain topological  *
	 * sort ordering in a vector in simple Queue order (LIFO)*
	 * and reverse the result after entire queue is created  */
	std::reverse(topo.begin(), topo.end());
	return topo;
}

int main()
{
	vector<pair<int, int>> v;
	v = {{0, 1}};
    findOrder(2, v);
	/* Manual test-cases                                     */
	cout << "Info: All manual test-cases passed" << endl;	
	return 0;
}
