//g++-5 --std=c++11 -Wall -g -o ds_list_flatten_2D_list ds_list_flatten_2D_list.cc  -I../utils/

/**
 * @file  Flatten 2D list
 * @brief Given N integer vectors, write a merged iterator class
 */

// https://leetcode.com/problems/flatten-2d-vector/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include "print_utils.h"     /* print_table_row              */
using namespace std;

/**
 * Implement an iterator to flatten a 2d vector.
 * For example, Given 2d vector =
 * [ [1,2],
 *   [3],
 *   [4,5,6] ]
 * By calling next repeatedly until hasNext returns false, the
 * order of elements returned by next should be: [1,2,3,4,5,6].
 */

/* Maintain 2 sets of iterators. First set to track outer    *
 * vector. Second to track any one inner vector. Handle all  *
 * iterator updates and checks in hasNext                    */
class Vector2D {
public:
   /* Init all the 4 iterators that we need for this problem */
   Vector2D(std::vector<std::vector<int>>& vec2d) {
      if(vec2d.size()) {
         vb = vec2d.begin();
         ve = vec2d.end();
         b  = e = vec2d[0].begin();
      }
   }
   /* HasNext should have setup inner iterators. So just pick*
    * up the next value from inner vector begin iterator     */
   int next() { return *(b++); }
   /* Update inner and outer iterators as required           */
   bool hasNext() {
      /* First check if current vector has more elements     */
      if(b != e) return true;
      /* Find next vector with elements and update inner its */
      for(; vb != ve; ++vb) {
         if((*vb).size())  { /* We found next inner vector   */
            b = (*vb).begin();
            e = (*vb).end();
            vb++;           /* Move the outer iterators      */
            return true;
         }
      }
      return false;  /* No more inner vectors with data found*/
   }
private:
   std::vector<std::vector<int>>::iterator vb, ve;
   std::vector<int>::iterator b, e;
};

/* Refer to leetcode for another solution with row/col idx
 * instead of using iterators:
 * https://discuss.leetcode.com/topic/21738/2-short-c-solution */

struct test_vector {
   std::vector<std::vector<int>> nums;
   std::vector<int> exp;
};

const struct test_vector test[4] =  {
   {  {},                              {}  },
   {  {{}},                            {}  },
   {  {{},{},{1,2,3},{}},         {1,2,3}  },
   {  {{1,2},{3},{4,5,6}},  {1,2,3,4,5,6}  },
};

int main()
{
   for(auto tst : test) {
      Vector2D i(tst.nums);
      std::vector<int> ans;
      while (i.hasNext()) ans.push_back(i.next());
      if(ans != tst.exp) {
         cout << "Error:Flatten2D failed:" << endl;
         print_table_row("Exp:", tst.exp);
         print_table_row("Got:", ans);
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
