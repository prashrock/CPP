//g++-5 --std=c++11 -Wall -g -o algo_design_hit_counter algo_design_hit_counter.cc

/**
 * @file  Design Hit Counter
 * @brief Design counter to cnt #hits received in the past 5 minutes.
 */

// https://leetcode.com/problems/design-hit-counter/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/**
 * Design a hit counter which counts the number of hits received
 * in the past 5 minutes.
 * Each function accepts a timestamp parameter (in seconds granularity)
 * and you may assume that calls are being made to the system in
 * chronological order (ie, the timestamp is monotonically increasing).
 * You may assume that the earliest timestamp starts at 1.
 *
 * It is possible that several hits arrive roughly at the same time.
 * Example:
 * HitCounter counter = new HitCounter();
 * // hit at timestamp 1.
 * counter.hit(1);
 * // hit at timestamp 2.
 * counter.hit(2);
 * // hit at timestamp 3.
 * counter.hit(3);
 * // get hits at timestamp 4, should return 3.
 * counter.getHits(4);
 * // hit at timestamp 300.
 * counter.hit(300);
 * // get hits at timestamp 300, should return 4.
 * counter.getHits(300);
 * // get hits at timestamp 301, should return 3.
 * counter.getHits(301);
 * Follow up: What if the number of hits per second could be very
 * large? Does your design scale?
 */


class HitCounter {
public:
   /** Initialize your data structure here.                  */
   HitCounter() : cnt(0) { }

   /* Record a hit. @param timestamp - cur ts in secs        *
    * Time Complexity =O(1). For each ts store tot cnt sofar */
   void hit(int timestamp) {
      /* If vector empty or new ts, add new elem to vector   */
      if(hits.size() == 0 || hits.rbegin()->first != timestamp)
         hits.push_back({timestamp, ++cnt});
      /* This hit was within last second, just increment cnt */
      else
         hits.rbegin()->second = ++cnt;
   }

   /** Return #hits in past 300 secs. Perform two binary     *
    * search operations. Time Complexity = O(lg n).          */
   int getHits(int timestamp, int duration = 300) {
      return getCnt(timestamp) - getCnt(timestamp - duration);
   }
private:
   typedef std::pair<int, int> pii_t; /* (timestamp, #hits_so_far) */
   int cnt;            /* Total number of hits seen so far   */
   vector<pii_t> hits; /* Maintain hits in a sorted vector   */

   /* Given a timestamp, locate the lower bound hit count    */
   inline int getCnt(int timestamp) {
      /* Use lower_bound to locate ts in the sorted vector   */
      auto it = std::lower_bound(hits.begin(), hits.end(),
                                 std::pair<int, int>{timestamp, 0});
      if(hits.size() == 0) /* Vector empty case              */
         return 0;
      else if(it == hits.begin()) /* If 1st elem, comp ts+ret*/
         return (it->first > timestamp) ? 0 : it->second;
      /* If it==end or next bigger element, go to prev elem  */
      else if(it == hits.end() || it->first > timestamp)
         --it;
      return it->second;
   }
};


int main()
{
   HitCounter ht;
   ht.hit(1);
   cout << "Info: Manual test-cases not yet written." << endl;
   return 0;
}
