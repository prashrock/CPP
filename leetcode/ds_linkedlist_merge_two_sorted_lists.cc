//g++-5 -Wall --std=c++11 -g -o ds_linkedlist_merge_two_sorted_lists ds_linkedlist_merge_two_sorted_lists.cc

/**
 * @file  Merge Two sorted LinkedList
 * @brief Given two sorted linkedlists, merge them
 */

// https://leetcode.com/problems/merge-two-sorted-lists/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <algorithm>         /* std::max                     */
using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
   int val;
   ListNode *next;
   ListNode(int x) : val(x), next(NULL) {}
};

/** @brief, move one pointer from l to end of tail           */
void updateOneList(ListNode*& tail, ListNode*& l) {
   if(tail == nullptr) tail = l;
   else              { tail->next = l; tail = tail->next; }
   l = l->next;
}

/** @brief Pick smallest element from each list till one list*
 * is empty. At this point append remaining list to answer   */
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
   ListNode *ans = nullptr;
   ListNode *tail = nullptr;

   while(l1 && l2) { /* Pick min from either of the lists    */
      if(l1->val < l2->val) updateOneList(tail, l1);
      else                  updateOneList(tail, l2);
      /* If this is the first node, update ans (head of LL)  */
      if(ans == nullptr) ans = tail;
   }
   /* Whichever list is left after cycle append it to tail   */
   if(l1)                    updateOneList(tail, l1);
   else if(l2)               updateOneList(tail, l2);
   if(ans == nullptr)        ans = tail;
   return ans;
}

int main() {
   cout << "Info: Need to write test-cases" << endl;
   return 0;
}
