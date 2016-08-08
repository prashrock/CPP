//g++ --std=c++11 -Wall -g -o math_geometry_max_2Dpoints_line math_geometry_max_2Dpoints_line.cc

/**
 * @file  Max Points on a Line
 * @brief Find maximum number of points that lie on the same straight line
 */

// https://leetcode.com/problems/max-points-on-a-line/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <unordered_map>     /* std::unordered_map           */
using namespace std;

/**
 * Given n points on a 2D plane, find the maximum number of
 * points that lie on the same straight line
 */

/* Definition for a point. */
struct Point {
   int x;
   int y;
   Point() : x(0), y(0) {}
   Point(int a, int b) : x(a), y(b) {}
};

/* First attempt - only worry about lines parallel to        *
 * X-Axis, Y-Axis or lie on one of the two diagonals(45 deg) */
typedef std::pair<int, int> pii_t;
struct piit_hash {
   std::size_t operator()(const pii_t &x) const {
      return std::hash<int>()(x.first) ^ std::hash<int>()(x.second);
   }
};

/* Go over each point and project it onto 4 possible lines   *
 * - Line parallel to X-Axis                                 *
 * - Line parallel to Y-Axis                                 *
 * - Left Diagonal Line (45^o) increasing form left to right *
 * - Right Diagonal Line(45^o) decreasing form left to right *
 * Time Complexity = O(n)                                    */
int maxPoints_Restricted(vector<Point>& points) {
   /* maintain map foreach line X, Y, left-diag, right-diag  */
   std::unordered_map<pii_t, int, piit_hash> hor, vert, ld, rd;
   int ans = 0;
   for(const auto &p : points) {
      ans = std::max(ans, ++hor[{p.x, 0}]);    /* X-axis line*/
      ans = std::max(ans, ++vert[{0, p.y}]);   /* Y-axis line*/
      ans = std::max(ans, ++ld[{p.x-p.y, 0}]); /* left-diag  */
      ans = std::max(ans, ++rd[{p.x+p.y, 0}]); /* right-diag */
   }
   return ans;
}

/* Use equation of a line to calculate slope with 2 points   *
 * slope = rise/run = (y2 - y1)/(x2 - x1)                    *
 * Use property - If two lines have same slope and share a   *
 * common point then the two lines must be the same one      *
 * Time Complexity = O(n^2)                                  */
int maxPoints(vector<Point>& p) {
   if(p.size() <= 2) return p.size(); /* base-cases          */
   int ans = 0;
   /* For each point find all other points which are the same*
    * or have the same slope as this point                   */
   for(int i = 0; i < (int)p.size(); ++i) {
      std::unordered_map<float, int> slope_map; /* #points   */
      int h_pts = 0, slope_pts = 0, same_pts = 1;
      for(int j = i + 1; j < (int)p.size(); ++j) {
         if(p[i].x == p[j].x) { /* same/horizontal points    */
            if(p[i].y == p[j].y) ++same_pts;
            else                 ++h_pts;
         }
         else {
            float slope = ((float)(p[j].y-p[i].y))/(p[j].x-p[i].x);
            slope_pts   = std::max(slope_pts, ++slope_map[slope]);
         }
      }
      ans = std::max(ans, (std::max(slope_pts, h_pts) + same_pts));
   }
   return ans;
}

struct test_vector {
   std::vector<struct Point> points;
   int exp;
};

const struct test_vector tests[6] =  {
   { {},                          0},
   { {{0,0}},                     1},
   { {{0,0}, {1, 1}, {1, 2}},     2},
   { {{1,1}, {1, 1}, {2, 3}},     3},
   { {{0,0}, {-1,-1},{2, 2}},     3},
   { {{0,0}, {1, 1}, {1,-1}},     2},
};

int main()
{
   for(auto tst : tests) {
      auto ans = maxPoints(tst.points);
      if(ans != tst.exp) {
         cout << "Error: maxPoints failed for below testcase:" << endl;
         for(auto e : tst.points) cout << e.x  << ", " << e.y  << endl;
         cout << " expected=" << tst.exp << " got="    << ans  << endl;
         return -1;
      }
   }
   cout << "Info: All manual test-cases passed for 2D points on line." << endl;
   return 0;
}
