//g++ --std=c++11 -g -o algo_sort_meeting_rooms algo_sort_meeting_rooms.cc

/**
 * @file  Meeting Rooms
 * @brief Given array of meetings, can one attend all meetings
 */

/**
 * Given an array of meeting time intervals consisting of start
 * and end times [[s1,e1],[s2,e2],...] (si < ei), determine if
 * a person could attend all meetings.
 * For example - Given [[0, 30],[5, 10],[15, 20]],
 *  return false.
 */

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
using namespace std;

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
 * First in-place custom sorting ranges based on start value *
 * Next, iterate over all elements and check for invariant:  *
 *             arr[i-1].end < arr[i].start                   *
 * Note-1: we do not need to worry about elements before i-1 *
 * because, we have already sorted based on start value      *
 * Note-2: This is a simplified version of other problem -   *
 * algo_sort_merge_overlapping_intervals.cc                  *
 * @param intervals                                          *
 *   Input vector of intervals. This will be sorted in place *
 *   to achieve O(1) space complexity                        *
 * Time Complexity = O(nlgn+n),  n=size of input vector      *
 * Space Complexity= O(1)                                    *
 * Note: this routine assumes that input is valid:           *
 *     meaning for each element, elem.start <= elem.end      */
bool canAttendMeetings(vector<Interval>& intervals) {
	std::sort(intervals.begin(), intervals.end(), less_than_start());
	for(int i = 1; i < intervals.size(); ++i)
		if(intervals[i].start < intervals[i-1].end)      return false;
	return true;
}

int main()
{
	vector<Interval> input 
		= {{0, 30}, {5, 10}, {15, 20}};
		//= {{0, 30}, {31, 40}, {45, 50}};
	bool res = canAttendMeetings(input);
	if(res)
		cout << "For given intervals, can attend all!" << endl;
	else
		cout << "For given intervals, cannot attend all!" << endl;
	return 0;
}
