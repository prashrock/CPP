//g++ --std=c++11 -Wall -g -o ds_linkedlist_rotate_list ds_linkedlist_rotate_list.cc

/**
 * @file  Rotate Linked List
 * @brief Rotate Given Linked List by k places to the right
 */

// https://leetcode.com/problems/rotate-list/

/**
 * Given a list, rotate the list to the right by k places,
 * where k is non-negative.
 * For example:
 *    Given 1->2->3->4->5->NULL and k = 2,
 *    return 4->5->1->2->3->NULL.
 */

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

struct ListNode {
   int val;
   ListNode *next;
   ListNode(int x) : val(x), next(NULL) {}
};

/* Find rotation point and then loop pointers around         */
ListNode* rotateRight(ListNode* head, int k) {
   /* Find n - number of elements in linked list             */
   int n;
   auto headk = head, last = head;
   for(n = 1; last != NULL && last->next != NULL; last = last->next, ++n);
   if(head == NULL || k == 0 || n == k)
      return head; /* Handle corner cases with no rot        */
   k = (n > k) ? k : k % n; /* if k > n, do k%n rotation     */

   /* Make headk move forward till it points to kth elem     */
   for(int i = 0; i < n-k-1; ++i) headk = headk->next;

   last->next  = head; /* create a loop from rotated to orig */
   head        = headk->next; /* point head to n-kth element */
   headk->next = NULL;  /* complete rotation, break old link */
   return head;
}


int main()
{
   cout << "Info: Manual test-cases yet to be created." << endl;
   return 0;
}

//Below are some manual test-cases to include (from Leet)
//[1, 2, 3, 4, 5]  2  -> [3, 4, 5, 1, 2]
//[1, 2]  2           -> [1, 2]
//[1, 2]  3           -> [2, 1]
//[] 0                -> []
