//g++ -Wall --std=c++11 -g -o algo_sort_merge_overlapping_intervals algo_sort_merge_overlapping_intervals.cc

/**
 * @file  Merge Overlapping Intervals
 * @brief Given a vector of overlapping intervals, merge intervals.
 */

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
using namespace std;

/* Create a type for the pair {left, right}                  */
typedef std::pair<int, int> range_t;

/* Create a custom comparator without using any classes      */
struct less_than_range_val
{
   inline bool operator() (const range_t& a, const range_t& b)
   {
      return (a.first < b.first);
   }
};

/**
 * Merge intervals in-place after custom sort                *
 * First custom sorting the ranges based on 'left' value     *
 * and then iterate over all the elements in place  and merge*
 * whenever possible.                                        *
 * @param inp                                                *
 *   Input vector of ranges. This will be sorted and merged  *
 *   in place to achieve O(1) space complexity               *
 * Time Complexity = O(nlgn),  n=size of input vector        *
 * Space Complexity= O(1)                                    *
 * Note: this routine assumes that input is valid:           *
 *     meaning for each pair, p.left <= p.right              */
void mergeIntervals(vector<range_t> &inp)
{
   int midx = 0; /* Index to maintain the merged result      */
	
   /* sort input range in ascending value of 'left' value    *
    * This O(nlgn) step can be avoided if we had sorted inp  */
   std::sort(inp.begin(), inp.end(), less_than_range_val());

   /* Iterate over entire list and merge in place            */
   for(int i = 1; i < inp.size(); ++i) {
      /* If current indx is out of merge range, then the     *
       * this has to be a new range (prev range is over)     */
      if(inp[midx].second < inp[i].first) inp[++midx] = inp[i];
      /* If within old range, update 'right' value           */
      else inp[midx].second = std::max(inp[midx].second, inp[i].second);
   }
   /* If we've merged everything to 1 range, set #merged = 1 */
   if(midx == 0) midx = 1;
   /* Reset the vector size to reflect merged result size    */
   inp.resize(midx);
}

int main()
{
   vector<range_t> input // = {{3, 6}, {1, 5}};
      = {{6,8}, {1,9}, {2,4}, {4,7}};
   mergeIntervals(input);
   cout << "Output size = " << input.size() << endl;
   for(auto val : input)
      cout << val.first << ',' << val.second << endl;
   return 0;
}
