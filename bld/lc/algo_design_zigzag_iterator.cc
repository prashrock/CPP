//g++-5 --std=c++11 -Wall -g -o algo_design_zigzag_iterator algo_design_zigzag_iterator.cc -I../utils/

/**
 * @file  Zigzag iterator
 * @brief Given multiple arrays take one from each array
 */

// https://leetcode.com/problems/zigzag-iterator/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include <queue>             /* std::queue                   */
#include "print_utils.h"     /* print_table_row              */
using namespace std;


/**
 * Given two 1d vectors, implement an iterator to return their
 * elements alternately.
 * For example, given two 1d vectors:
 * v1 = [1, 2]
 * v2 = [3, 4, 5, 6]
 * By calling next repeatedly until hasNext returns false, the
 * order of elements returned by next should be: [1,3,2,4,5,6].
 * Follow up: What if you are given k 1d vectors? How well can
 * your code be extended to such cases?
 */

/* Return one value from each input vector                   */
class ZigzagIterator {
   struct itpair { std::vector<int>::iterator b;
                   std::vector<int>::iterator e; };
public:
   ZigzagIterator(std::vector<int>& v1, std::vector<int>& v2) {
      if(v1.begin() != v1.end()) q.push({v1.begin(), v1.end()});
      if(v2.begin() != v2.end()) q.push({v2.begin(), v2.end()});
   }

   inline bool hasNext() { return (q.size() != 0); }

   int next() {
      if(hasNext() == false)  return -1;
      auto itp = q.front();
      q.pop();
      int ret  = *(itp.b++);
      if(itp.b  != itp.e)     q.push(itp);
      return ret;
   }

private:
   std::queue<struct itpair> q;
};

struct test_vector {
   std::vector<int> n1;
   std::vector<int> n2;
   std::vector<int> exp;
};

const struct test_vector test[6] =  {
   {{},              {},               {}},
   {{1,2},           {3},              {1,3,2}},
   {{1,2},           {3,4,5,6},        {1,3,2,4,5,6}},
   {{1,2,3,4},       {},               {1,2,3,4}},
   {{},              {1,2,3,4},        {1,2,3,4}},
   {{1,2,3},         {4,5,6},          {1,4,2,5,3,6}},
};

int main() {
   for(auto tst : test) {
      class ZigzagIterator zig(tst.n1, tst.n2);
      std::vector<int> ans;
      while(zig.hasNext()) ans.push_back(zig.next());
      if(ans != tst.exp) {
         cout << "Error:Zigzag iterator failed." << endl;
         print_table_row("Exp:", tst.exp);
         print_table_row("Got:", ans);
         return -1;
      }
   }
   cout << "Info: All manual test-cases passed." << endl;
   return 0;
}
