//g++ --std=c++11 -g -Wall -Werror -o ds_graph_loop_course_schedule ds_graph_loop_course_schedule.cc

/**
 * @file Course Schedule
 * @brief Given a list of courses and prerequisites, can you 
 * finish all the courses
 */

// https://leetcode.com/problems/course-schedule/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/*
 * There are a total of n courses to take, labeled from 0 to n - 1.
 * Some courses may have prerequisites, for example to take
 * course 0 you have to first take course 1, which is expressed
 * as a pair: [0,1]
 * Given the total number of courses and a list of prerequisite
 * pairs, is it possible for you to finish all courses?
 * For example:
 * 2, [[1,0]]
 * There are a total of 2 courses to take. To take course 1 you
 * should have finished course 0. So it is possible.
 * 2, [[1,0],[0,1]]
 * There are a total of 2 courses to take. To take course 1 you
 * should have finished course 0, and to take course 0 you should
 * also have finished course 1. So it is impossible.
 */

/**
 * @class Graph
 * Graph maintains out-edge list representation of vertices  *
 * There is one method which uses DFS to find a loop in graph*
 * Use a 3 colored approach to mark visited info in DFS      *
 * 0=unvisited, 1=currently_visiting, 2=finished_node        *
 */
class Graph {
public:
   Graph(int v) : V(v), adj(V, vector<int>()){}
   void addEdge(int v, int w) {adj[v].push_back(w);}
   /* Given a node, find if there are any loops in subgraph  */
   bool DFSHasLoop(int v, vector<int> &visited) {
      visited[v] = 1; /* Grey -- Currently processing node   */
      for(auto e: adj[v]) {
         /* If an adjacent node is also in currently         *
          * processing state, we have a loop. return imm     */
         if(visited[e] == 1)       return true;
         /* If we've already seen adjacent, nothing todo     */
         else if(visited[e] == 2)  continue;
         /* If adj node is unvisited, visit recursively      */
         else {
            bool ret = DFSHasLoop(e, visited);
            if(ret == true)       return true;
         }
      }
      visited[v] = 2; /* Black -- finished processing node   */
      return false;
   }
private:
   int V;
   vector<vector<int>> adj;
};

/**
 * Create graph fully. Use DFS to search for loops.          *
 * @param numCourses   - total number of vertices            *
 * @param prerequisite - edge lists                          *
 * @return                                                   *
 *   True if there is no loop in the graph                   *
 */
bool canFinish(int numCourses, vector<pair<int, int>>& prereq) {
   Graph g(numCourses);
   /* 0=unvisited, 1=currently_visiting, 2=finished_node    */
   vector<int> visited(numCourses, 0);
   for(unsigned i = 0; i < prereq.size(); ++i)
      g.addEdge(prereq[i].first, prereq[i].second);
   for(int i = 0; i < numCourses; ++i) {
      if(visited[i] == 0) /* If unvisited node, start DFS    */
         if(g.DFSHasLoop(i, visited) == true)
            return false;
   }
   return true;
}


int main()
{
   vector<pair<int, int>> v;
   /* Manual test-cases                                     */
   if(canFinish(2, v = {{0, 1}}) != true)
      cout << "Error: 1st Manual test failed" << endl;
   else if(canFinish(2, v = {{1, 0}, {0, 1}}) != false)
      cout << "Error: 2nd Manual test failed" << endl;
   else if(canFinish(3, v = {{1, 0}, {0, 2}, {2, 1}}) != false)
      cout << "Error: 3rd Manual test failed" << endl;
   else if(canFinish(4, v = {{0, 1}, {1, 2}, {2, 3}}) != true)
      cout << "Error: 4th Manual test failed" << endl;
   else
      cout << "Info: All manual test-cases passed" << endl;	
   return 0;
}
