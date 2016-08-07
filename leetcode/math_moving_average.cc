//g++ -O3 -Wall --std=c++11 -g -o math_moving_average math_moving_average.cc

/**
 * @file  Moving Average from Data Stream
 * @brief Given stream + window size, calculate moving average
 */

// https://leetcode.com/problems/moving-average-from-data-stream/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::min                     */
using namespace std;

/**
 * Given a stream of integers and a window size, calculate the
 * moving average of all integers in the sliding window.
 * For example,
 *  MovingAverage m = new MovingAverage(3);
 *  m.next(1)  = 1 / 1            = 1
 *  m.next(10) = (1 + 10) / 2     = 5.50000
 *  m.next(3)  = (1 + 10 + 3) / 3 = 4.66667
 *  m.next(5)  = (10 + 3 + 5) / 3 = 6.00000
 */

/**
 * @brief - Maintain a circular array for the window and     *
 * maintain the sum of all elements within the window.       *
 * Time Complexity = O(1)                                    *
 * Space Complexity = O(n) where n is the window size        */
class MovingAverage {
public:
   /** Initialize your data structure here. */
   MovingAverage(int size) : nums(size, 0), idx(0), sum(0) { }

   double next(int val) {
      auto cidx  = idx++ % nums.size(); /* calc circular idx */
      sum       += (val  - nums[cidx]); /* adjust window sum */
      nums[cidx] = val;         /* stick new val into window */
      return ((double)sum)/std::min(idx, (unsigned int)nums.size());
   }
private:
   std::vector<int> nums;  /* to hold all elements in window */
   unsigned int idx;       /* rolling counter of total #ins  */
   long sum;               /* sum of all items within window */
};

struct test_vector {
   int window_size;
   std::vector<int> num;
   std::vector<double> avgs;
};

const struct test_vector test[1] =  {
   {3, {1, 10, 3, 5}, {1, 5.50000, 4.66666666666666666, 6.00000}},
};

int main()
{
   for(auto tst : test) {
      MovingAverage m(tst.window_size);
      for(int i = 0; i < (int)tst.num.size(); ++i) {
         auto ans = m.next(tst.num[i]);
         if(ans != tst.avgs[i]) {
            cout << "Error: Moving Average failed for input:" << endl;
            for(auto e : tst.num) cout << e << ",";
            cout << endl << "failed at idx " << i
                 << " expected=" << tst.avgs[i]
                 << " got="      << ans << endl;
            return -1;
         }
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}

