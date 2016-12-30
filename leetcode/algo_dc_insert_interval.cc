//g++-5 --std=c++11 -Wall -g -o algo_dc_insert_interval algo_dc_insert_interval.cc

/**
 * @file  Insert Interval
 * @brief Given non-overlapping intervals insert new interval
 */

// https://leetcode.com/problems/insert-interval/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max, std::lower_bound   */
#include <vector>            /* std::vector                  */
using namespace std;

/**
 * Given a set of non-overlapping intervals, insert a new interval
 * into the intervals (merge if necessary).
 * You may assume that the intervals were initially sorted according
 * to their start times.
 * Example 1:
 * Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
 * Example 2:
 * Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9]
 * in as [1,2],[3,10],[12,16].
 * This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
 */

struct Interval {
   int start;
   int end;
   Interval() : start(0), end(0) {}
   Interval(int s, int e) : start(s), end(e) {}
   bool operator==(Interval other) const{
      if(other.start == start && other.end == end) return true;
      else                                         return false;
   }
};

struct less_than_start  {
   bool operator() (const Interval& l, const Interval& r)
   { return (l.start <= r.start ); }
};

struct less_than_end  {
   bool operator() (const Interval& l, const Interval& r)
   { return (l.end <= r.end ); }
};

inline bool isOverlap(const Interval &l, const Interval &r)
{ return l.end >= r.start; }

/**
 * @brief: Use Lower_Bound to mark the conflicting region for*
 * a given new interval. Update new interval with conflicting*
 * region, insert it and delete the conflicting region       *
 * Time Complexity = O(n).   Space Complexity = O(1)         */
std::vector<Interval> insert(std::vector<Interval>& ivs, Interval niv) {
   /* Use lower_bound to find beginning and end of overlapping section */
   auto bit = std::lower_bound(ivs.begin(), ivs.end(), niv, less_than_start());
   auto eit = std::lower_bound(bit,         ivs.end(), niv, less_than_end());
   /* If lower bound returns next highest element, move one elem back  */
   if(bit != ivs.begin() && isOverlap(*std::prev(bit), niv))
      bit = std::prev(bit);
   if(eit == ivs.end()   || !isOverlap(niv, *eit))
      eit = std::prev(eit);
   /* If there is an overlap, then adjust start/end in niv & del range */
   if(bit != ivs.end() && eit != ivs.end() && isOverlap(*bit, niv)) {
      niv.start = std::min(niv.start, bit->start);
      niv.end   = std::max(niv.end,   eit->end);
      ivs.erase(bit, eit+1);
   }
   ivs.insert(bit, niv);
   return ivs;
}

struct test_vector {
   std::vector<Interval> ivs;
   Interval niv;
   std::vector<Interval> exp;
};

const struct test_vector test[8] =  {
   { {},                                 {5,7},                {{5, 7}} },
   { {{1,3},{6,9}},                      {2,5},           {{1,5},{6,9}} },
   { {{1,5}},                            {5,7},                {{1, 7}} },
   { {{1,5}},                            {0,0},           {{0,0},{1,5}} },
   { {{1,5}},                            {0,3},                 {{0,5}} },
   { {{1,5}},                            {6,8},           {{1,5},{6,8}} },
   { {{1,5},{6,8}},                      {0,9},                 {{0,9}} },
   { {{1,2},{3,5},{6,7},{8,10},{12,16}}, {4,9},  {{1,2},{3,10},{12,16}} },
};

int main()
{
   for(auto tst : test) {
      auto ans = insert(tst.ivs, tst.niv);
      if(ans != tst.exp) {
         cout << "Error:insertInterval failed. Exp "
              << tst.exp.size() << " elements, got "
              << ans.size() << " elements " << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
