//g++-5 --std=c++11 -Wall -g -o ds_linkedlist_delete_val ds_linkedlist_delete_val.cc

/**
 * @file  Remove LinkedList elements
 * @brief Delete all nodes that contain a given value in linkedlist
 */

// https://leetcode.com/problems/remove-linked-list-elements/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
using namespace std;

/**
 * Remove all elements from a linked list of integers that have
 * value val.
 * Example
 * Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
 * Return: 1 --> 2 --> 3 --> 4 --> 5
 */

struct ListNode {
   int val;
   ListNode *next;
   ListNode(int x) : val(x), next(NULL) {}
};

/**  @brief  - Approach 1                                    *
 * Maintain 2 pointers, prev and cur. Handle following cases *
 * - Head has val to be deleted (ex: [1,1,2]  and 1)         *
 * - Multiple inbetween nodes have val (ex: [1,2,2,3] and 2) */
ListNode* removeElements1(ListNode* head, int val) {
   /* Maintain 2 nodes cur (first to last node) and prev     *
    * which is always 1 node before cur.                     */
   for(ListNode *cur = head, *prev = nullptr; cur; ) {
      /* If cur has value, do, prev->next = cur->next        */
      if(cur->val == val) {
         /* If prev exists, update pointer to skip cur       */
         if(prev) prev->next = cur->next;
         /* If Linkedlist head is deleted, update head       */
         if(head == cur) head= cur->next;
         auto del = cur;
         cur = cur->next;
         free(del);
      }
      /* If cur node does not have val, update pointers      */
      else {
         if(prev == nullptr) prev = cur;
         else                prev = prev->next;
         cur = cur->next;
      }
   }
   return head;
}

/**  @brief  - Approach 2                                    *
 * Handle head removal first. Next, handle inbetween nodes   */
ListNode* removeElements2(ListNode* head, int val) {
   /* Remove all the head pointers which have val            */
   while(head && head->val == val) head = head->next;
   if(head == nullptr)             return head;
   /* Handle inbetween nodes. Note: be careful about when to *
    * move cur and when to move cur's next pointer           */
   for(auto cur = head; cur && cur->next; ) {
      if(cur->next->val == val) cur->next = cur->next->next;
      else                      cur       = cur->next;
   }
   return head;
}

//[1,2,6,3,4,5,6] //6    [1,2,3,4,5]
//[1,1,1,2,3,4]   //1    [2,3,4]
//[1,2,3,4,6,6,6] //6    [1,2,3,4]
//[]              //1    []

int main()
{
   cout << "Info: Manual test-cases yet to be created." << endl;
   return 0;
}
