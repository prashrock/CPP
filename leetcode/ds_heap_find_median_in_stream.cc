//g++ --std=c++11 -g -o ds_heap_find_median_in_stream ds_heap_find_median_in_stream.cc

/**
 * @file  Heap Find Median in Stream
 * @brief Given a stream of integers find the median element
 */

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <queue>             /* std::priority_queue          */
using namespace std;


/**
 * Find Median from Data Stream
 * Median is the middle value in an ordered integer list.
 * If the size of the list is even, there is no middle value.
 * So the median is the mean of the two middle value.
 * Example:
 *   [2,3,4] , the median is 3
 *   [2,3], the median is (2 + 3) / 2 = 2.5
 * Design a data structure that supports the following two operations:
 * void addNum(int num) - Add a integer number from the data stream to DS.
 * double findMedian()  - Return the median of all elements so far.
 * Example:
 *   add(1)
 *   add(2)
 *   findMedian() -> 1.5
 *   add(3)
 *   findMedian() -> 2
 */


/**
 * To find the median, use two Heaps. First heap to maintain *
 * first half of sorted input, Second heap to maintain the   *
 * second half of sorted input.                              */
std::priority_queue<int, std::vector<int>> fh_maxheap;
std::priority_queue<int, std::vector<int>, std::greater<int>> sh_minheap;

/**
 * @brief                                                    *
 *   Add a number to PQ's. Maintain invariant that both PQs  *
 *   are of equal size or differ in size by one              *
 * @param num                                                *
 *   Next number from input stream                           */
void addNum(int num) {
	/* Handle special cases                                  */
	/* 1) The very first number, push it to first-PQ         */
	if(fh_maxheap.size() == 0) fh_maxheap.push(num);
	/* 2) If 2nd number is greater than first number, then   *
	 *    our initial classification was good, just push 2nd *
	 *    number to second-PQ, else move around numbers      */
	else if(sh_minheap.size() == 0) {
		if(num > fh_maxheap.top()) sh_minheap.push(num);
		else { /* First number should be moved to second-PQ  */
			sh_minheap.push(fh_maxheap.top());
			fh_maxheap.pop();
			fh_maxheap.push(num);
		}
	}
	else {
		/* Determine if we Push into first-PQ or second-PQ   */
		if(num > fh_maxheap.top())  sh_minheap.push(num);
		else                        fh_maxheap.push(num);
		
		/* Maintain invariant that both PQ's must be of equal*
		 * size or differ in size by one                     */
		if(sh_minheap.size() > fh_maxheap.size() + 1) {
			fh_maxheap.push(sh_minheap.top());
			sh_minheap.pop();
		}
		else if(fh_maxheap.size() > sh_minheap.size() + 1) {
			sh_minheap.push(fh_maxheap.top());
			fh_maxheap.pop();
		}
	}
}

/**
 * @brief                                                    *
 *   If even #elems, return avg of both PQ top, else return  *
 *   element from the larger PQ                              *
 * @return                                                   *
 *   Median as a double value                                */
double findMedian() {
	auto lm_size = fh_maxheap.size(), gm_size = sh_minheap.size();
	/* If Size==odd, then median is in bigger Priority Queue */
	if((lm_size + gm_size) % 2) {
		if(lm_size > gm_size) return fh_maxheap.top();
		else                  return sh_minheap.top();
	}
	else
		return ((double)fh_maxheap.top() + sh_minheap.top())/2;
}

void printPQs()
{
	auto fh = fh_maxheap;
	auto sh = sh_minheap;
	cout << "FH Size = " << fh.size() << endl;
	while(fh.size()) {
		cout << fh.top() << ",";
		fh.pop();
	}
	cout << endl;

	cout << "SH Size = " << sh.size() << endl;
	while(sh.size()) {
		cout << sh.top() << ",";
		sh.pop();
	}
	cout << endl;
	cout << endl;
}

int main()
{
	cout << "Simple test-case for Find Median of Stream" << endl;
	cout << "insert -1, -2, -3, -4:" << endl;
	addNum(-1);
	cout << "median = " << findMedian() << endl; //-1
	addNum(-2);
	cout << "median = " << findMedian() << endl; //-1.5
	addNum(-3);
	cout << "median = " << findMedian() << endl; //-2
	addNum(-4);
	cout << "median = " << findMedian() << endl; //-2.5
	return 0;
}
