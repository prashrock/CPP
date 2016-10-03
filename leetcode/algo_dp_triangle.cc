//g++-5 --std=c++11 -g -Wall -o algo_dp_triangle algo_dp_triangle.cc

/**
 * @file  Minimum path sum from top to bottom
 * @brief Given a triangle find min path from top to bottom
 */

// https://leetcode.com/problems/triangle/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
using namespace std;

/**
 * Given a triangle, find the minimum path sum from top to bottom.
 * Each step you may move to adjacent numbers on the row below.
 * For example, given the following triangle
 * [      [2],
 *       [3,4],
 *      [6,5,7],
 *     [4,1,8,3]  ]
 * The minimum path sum from top to bottom is 11
 * (i.e., 2 + 3 + 5 + 1 = 11).
 * Note: Bonus point if you are able to do this using only O(n)
 * extra space, where n is the total number of rows in the triangle.
 */

/**
 * @brief Use bottom up DP to iteratively from bottom to top *
 * at each stage maintain min possible path sum upto current *
 * level in the node itself                                  * 
 */
int minimumTotalBottomUp(std::vector<std::vector<int>>& triangle) {
   if(triangle.size() == 0) return 0;
   for(int i = triangle.size() - 2; i >= 0; --i) {
      for(int col = 0; col < (int)triangle[i].size(); ++col) {
         if(col + 1 < (int)triangle[i+1].size())
            triangle[i][col] += std::min(triangle[i+1][col], triangle[i+1][col+1]);
         else
            triangle[i][col] += triangle[i+1][col];
      }
   }
   return triangle[0][0];
}

/* With O(n) space, we can avoid modifying the input triangle*
 * Refer to this solution along with Top-Down solution @     *
 * https://discuss.leetcode.com/topic/29834/c-top-down-and-bottom-up-solutions */

struct test_vector {
   std::vector<std::vector<int>> nums;
   int exp;
};

const struct test_vector test[3] =  {
   { {}                                ,          0 },
   { {{-10}}                           ,        -10 },
   { { {2}, {3,4}, {6,5,7}, {4,1,8,3} },         11 },
};

int main()
{
   for(auto tst : test) {
      auto nums1 = tst.nums;
      auto ans = minimumTotalBottomUp(nums1);
      if(ans != tst.exp) {
         cout << "Error:minimumTotalBottomUp failed. Exp "
              << tst.exp << " Got " << ans << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
