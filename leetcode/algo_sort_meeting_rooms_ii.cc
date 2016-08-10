//g++-5 --std=c++11 -g -o algo_sort_meeting_rooms_ii algo_sort_meeting_rooms_ii.cc

/**
 * @file  Meeting Rooms II
 * @brief Given array of meetings, how many meeting rooms needed
 */

// https://leetcode.com/problems/meeting-rooms-ii/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <queue>             /* std::priority_queue          */
using namespace std;

/**
 * Given an array of meeting time intervals consisting of start
 * and end times [[s1,e1],[s2,e2],...] (si < ei), find the
 * minimum number of conference rooms required.
 * For example,
 * Given [[0, 30],[5, 10],[15, 20]]  return 2.
 */

/* Create a type for Interval specification                  */
struct Interval {
   int start;
   int end;
   Interval() : start(0), end(0) {}
   Interval(int s, int e) : start(s), end(e) {}
};

/* Create a custom comparator without using any classes      */
struct less_than_start {
   inline bool operator() (const Interval& a, const Interval& b) {
      return (a.start < b.start);
   }
};

/**
 * Sort intervals based on start time. Next, use a Min Heap  *
 * based on end times to track number of rooms required.     *
 * At end of processing all intervals, #entries in min_heap  *
 * is number of rooms required.                              *
 * Time Complexity = O(n lg n) and Space Complexity = O(n)   *
 * Note: Inspired by Interval Partitioning Greedy approach   *
 * (Earliest Start time first) as mentioned here:            *
 * https://www.cs.princeton.edu/~wayne/kleinberg-tardos/pdf/04GreedyAlgorithmsI.pdf *
 */
int minMeetingRooms(vector<Interval>& intervals) {
   if(intervals.size() == 0) return 0;  /* Handle cornercase */
   
   /* Sort intervals based on start time                     */
   std::sort(intervals.begin(), intervals.end(), less_than_start());
   /* Maintain PQ to find out which room is free next        */
   priority_queue<int, vector<int>, std::greater<int>> min_end_pq;

   /* Schedule first interval into the first room-base case  */
   min_end_pq.push(intervals[0].end);
   for(int i = 1; i < intervals.size(); ++i) {
      /* Greedy scheduling: if current interval does not     *
       * overlap with oldest classroom (oldest end-time)     *
       * schedule this interval on that classroom            */
      if(intervals[i].start >= min_end_pq.top())
         min_end_pq.pop(); /* clear up old classroom         */
      /* schedule new interval regardless                    */
      min_end_pq.push(intervals[i].end);
   }
   /* Return number of classrooms                            */
   return min_end_pq.size();
}


int main()
{
   vector<Interval> input = {{0, 30} ,{5, 10}, {15, 20}};
   int ret = minMeetingRooms(input);
   if(ret != 2) {
      cout << "Error: exp 2, got " << ret << " rooms for "
           << "{0, 30} ,{5, 10}, {15, 20}" << endl;
      goto end;
   }
   input = {{9,10}, {4,9}, {4,17}};
   ret = minMeetingRooms(input);
   if(ret != 2) {
      cout << "Error: exp 2, got " << ret << " rooms for "
           << "{9,10}, {4,9}, {4,17}" << endl;
      goto end;
   }
   input = {{2,15},{36,45},{9,29},{16,23},{4,9}};
   ret = minMeetingRooms(input);
   if(ret != 2) {
      cout << "Error: exp 2, got " << ret << " rooms for "
           << "{2,15},{36,45},{9,29},{16,23},{4,9}" << endl;
      goto end;
   }
   cout << "All manual testcases passed" << endl;
 end:
   return 0;
}
