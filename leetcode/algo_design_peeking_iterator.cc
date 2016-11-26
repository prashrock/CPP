//g++-5 --std=c++11 -Wall -g -o algo_design_peeking_iterator algo_design_peeking_iterator.cc

/**
 * @file  Peeking iterator
 * @brief Given regular iterator and a list support look-ahead op
 */

// https://leetcode.com/problems/peeking-iterator/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
using namespace std;


/**
 * Given an Iterator class interface with methods: next() and hasNext()
 * design and implement a PeekingIterator that support the peek()
 * operation -- it essentially peek() at the element that will be
 * returned by the next call to next().
 * Here is an example. Assume that the iterator is initialized to the
 * beginning of the list: [1, 2, 3].
 * Call next() gets you 1, the first element in the list.
 * Now you call peek() and it returns 2, the next element.
 * Calling next() after that still return 2.
 * You call next() the final time and it returns 3, the last element.
 * Calling hasNext() after that should return false.
 * Hints:
 * - Think of "looking ahead". You want to cache the next element.
 * - Is one variable sufficient? Why or why not?
 * - Test your design with call order of peek() before next() vs
 *   next() before peek().
 * - For a clean implementation, check out Google's guava library source.
 */

// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
   struct Data;
   Data* data;
public:
   Iterator(const vector<int>& nums);
   Iterator(const Iterator& iter);
   virtual ~Iterator();
   // Returns the next element in the iteration.
   int next();
   // Returns true if the iteration has more elements.
   bool hasNext() const;
};

/* Use a cache variable and flag to store the peeked value   *
 * Another interesting implementation is always using cache  *
 * - https://discuss.leetcode.com/topic/25875/another-c-solution-with-one-line-in-peek-and-hasnext-ac */
class PeekingIterator : public Iterator {
public:
   PeekingIterator(const vector<int>& nums) : Iterator(nums), isNext(false) { }

   // Returns the next element in the iteration without advancing the iterator.
   // Assume hasNext() is true when peek() is called
   int peek() {
      if(isNext == false) {
         vNext  = Iterator::next();
         isNext = true;
      }
      return vNext;
   }

   // hasNext() and next() should behave the same as in the Iterator interface.
   // Override them if needed.
   int next() {
      if(isNext) {
         isNext = false;
         return vNext;
      }
      else return Iterator::next();
   }

   bool hasNext() const {
      return (Iterator::hasNext() || isNext);
   }
private:
   int  vNext;  /* Cache to store the next peeked element    */
   bool isNext; /* Flag to indicate whether vNext is in-use  */
};


int main() {
   //PeekingIterator p({1, 2, 3});
   cout << "Info: Since Iterator interface is not fully implemented,"
        << " this implementation cannot be tested yet." << endl;
   return 0;
}
