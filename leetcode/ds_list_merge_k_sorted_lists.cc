//g++-5 --std=c++11 -Wall -g -o ds_list_merge_k_sorted_lists ds_list_merge_k_sorted_lists.cc

/**
 * @file  Merge K Sorted Lists
 * @brief Given K sorted integer lists, merge them as one sorted list
 */

// https://leetcode.com/problems/merge-k-sorted-lists/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <queue>             /* std::priority_queue          */
using namespace std;

/**
 * Merge k sorted linked lists and return it as one sorted list.
 * Analyze and describe its complexity.
 */

struct ListNode {
   int val;
   ListNode *next;
   ListNode(int x) : val(x), next(NULL) {}
};

struct custom_greater {  /* Custom comparator without classes */
   inline bool operator() (const ListNode *x, const ListNode *y) const {
      return x->val > y->val;
   }
};

/* Use a min-heap to store the k smallest elements (one from *
 * each list). At each iteration pick the lowest and append  *
 * to answer list. Stop the loop when all elements processed *
 * Note: since this approach compares all lists in each iter *
 * it is not cache efficient.                                *
 * Time Complexity = O(nlgk), Space Complexity = O(k)        */
ListNode* mergeKLists(vector<ListNode*>& lists) {
   ListNode *ansb = NULL, *cur = NULL;
   std::priority_queue<ListNode *, std::vector<ListNode *>,
                       custom_greater> min_heap;

   /* From each of the 'k' lists push 1st element into PQ    */
   for(auto node : lists) if(node != NULL) min_heap.push(node);

   /* Now just traverse the priority queue and get all nodes */
   for(; min_heap.size() > 0; ) {
      auto cur_ptr  = min_heap.top();
      min_heap.pop();
      if(cur_ptr->next != NULL)  min_heap.push(cur_ptr->next);
      if(cur == NULL) ansb = cur = cur_ptr; /*Update ans list*/
      else            { cur->next  = cur_ptr; cur = cur_ptr; }
   }
   //if(cur) cur->next = NULL; //last element's next should point to NULL
   return ansb;
}

/* Another approach is to merge 2 lists at a time till there *
 * are no more lists. With this approach, an approach close  *
 * to ./ds_list_merge_sorted_arrays.cc can be used           */

/* Some test-cases which I used in Leetcode                  */
//[[]]   //[]
//[[1]]  //[1]
//[[0, 2, 5]] //[0, 2, 5]
//[[1], [0]] //[0, 1]
//[[2, 5, 6] [0, 3, 5, 6, 7]] //[0, 2, 3, 5, 6, 7]

int main()
{
   cout << "Info: Need to add manual tests for merge k-sorted arrays" << endl;
   return 0;
}
