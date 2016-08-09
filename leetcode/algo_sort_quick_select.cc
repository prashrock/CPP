//g++ -Wall --std=c++11 -g -o algo_sort_quick_select algo_sort_quick_select.cc

/**
 * @file  Kth largest Element (Quick Select)
 * @brief Find the kth largest element in an unsorted array.
 */

// https://leetcode.com/problems/kth-largest-element-in-an-array/

#include <iostream>            /* std::cout                  */
#include <algorithm>           /* std::max                   */
#include <vector>              /* std:vector                 */
#include <random>              /* std::default_random_engine */
using namespace std;

/**
 * Find the kth largest element in an unsorted array. Note that
 * it is the kth largest element in the sorted order, not the kth
 * distinct element.
 * For example,
 * Given [3,2,1,5,6,4] and k = 2, return 5.
 * Note:
 * You may assume k is always valid, 1 . k . array's length.
 */

/* Chose a[0] as pivot and find the sorted pos (0-based) idx *
 * of the pivot. Also, move the pivot to its sorted position *
 * Time Complexity = O(n)      Space Complexity = O(1)       */
int partition(std::vector<int> &a, int left, int right)
{
   int pivot = a[left];  /* chose pivot as the 1st element   */
   int r = right;
   for(int l = left + 1; l <= r; ) {
      if     (a[l] <= pivot) l++; /* Move l if a[l] < pivot  */
      else if(a[r] >= pivot) r--; /* Move r if a[r] > pivot  */
      /* a[l] > pivot and a[r] < pivot, so swap both elems   */
      else                   std::swap(a[l++], a[r--]);
   }
   std::swap(a[left], a[r]); /* Swap pivot to its correct pos*/
   return r;
}

/** QuickSelect algorithm as explained by Robert Sedgewick @ *
 * http://algs4.cs.princeton.edu/23quicksort/Quick.java.html *
 * Rearranges array so that a[k] contains the kth smallest   *
 * key; After this:                                          *
 * - a[0]   through a[k-1] are less than or eq to     a[k]   *
 * - a[k+1] through a[N-1] are greater than or eq to  a[k]   *
 */
int findKthLargest(std::vector<int>& a, int k) {
   if(k < 0 || k > (int)a.size()) return -1; /* corner-cases */

   /* O(n) Shuffle needed for quick-select perf guarantee    */
   std::shuffle(a.begin(), a.end(), std::default_random_engine{});

   /* kth largest, comment this line for kth smallest        */
   k = a.size() - k;
   for(int l = 0, r = a.size() - 1; l <= r; ) {
      int pos = partition(a, l, r);
      if(pos > k)       r = pos - 1;
      else if(pos < k)  l = pos + 1;
      else              return a[pos];
   }
   return -1;
}

struct test_vector {
   std::vector<int> nums;
   int k;
   int exp;
};

const struct test_vector test[4] =  {
   { {1},             1, 1},
   { {3,2,1,5,6,4},   2, 5},
   { {1,2,3,4,5,6},   1, 6},
   { {5,2,4,1,3,6,0}, 2, 5},
};

int main()
{
   for(auto tst : test) {
      auto ans = findKthLargest(tst.nums, tst.k);
      if(ans != tst.exp) {
         cout << "Error:findKthLargest failed. Exp "
              << tst.exp << " Got " << ans << " for ";
         for(auto v: tst.nums) cout  << v << ","; cout << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
