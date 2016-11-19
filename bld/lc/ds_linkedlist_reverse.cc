//g++-5 -Wall --std=c++11 -g -o ds_linkedlist_reverse ds_linkedlist_reverse.cc

/**
 * @file  Reverse LinkedList
 * @brief Reverse a singly linked-list
 */

// https://leetcode.com/problems/reverse-linked-list/
// https://leetcode.com/problems/reverse-linked-list-ii/

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
 * Definition for singly-linked list.
 */
struct ListNode {
   int val;
   ListNode *next;
   ListNode(int x) : val(x), next(NULL) {}
};

/** 
 * Reverse a singly linked list.
 * Hint:
 * A linked list can be reversed either iteratively or recursively. 
 * Could you implement both?
 */

/** @brief - Reverse Linkedlist given first pointer          *
 * @param head - Input list head pointer                     *
 * @ret        - Reversed linked-list                        *
 * Time Complexity = O(n), Space Complexity = O(1)           */
ListNode* reverseList(ListNode* head) {
   ListNode* old = NULL, *next = NULL;
   while(head) {
      next       = head->next;
      head->next = old;
      old        = head;
      head       = next;
   }
   return old;
}

bool reverseListTest() {
   cout << "Info: Need to write test-cases" << endl;
   return true;
}

/**
 * Reverse a linked list from position m to n. 
 * Do it in-place and in one-pass.
 * For example:
 * Given 1->2->3->4->5->NULL, m = 2 and n = 4,
 * return 1->4->3->2->5->NULL.
 * Note:
 * Given m, n satisfy the following condition:
 * 1 ≤ m ≤ n ≤ length of list.
 */
 
ListNode* reverseBetween(ListNode* head, int m, int n) {
   if(m == n) return head;
   ListNode dummy(0);
   ListNode  *pre = &dummy;
   dummy.next = head;
   for(int i = 1; i < m; ++i) pre = pre->next;
  
   ListNode *cur = pre->next, *old = NULL;
   for(int i = m; i <= n; ++i) {
      auto next  = cur->next;
      cur->next  = old;
      old        = cur;
      cur        = next;
   }
   pre->next->next = cur;
   pre->next       = old;
   return dummy.next;
}

bool reverseBetweenTest() {
   ListNode one(1), two(2), three(3);
   one.next = &two; two.next = &three;
   reverseBetween(&one, 2, 3);
   return true;
}

int main()
{
   if(reverseListTest() != true)            return -1;
   else if(reverseBetweenTest() != true)    return -2;
   return 0;
}
