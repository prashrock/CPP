//g++-5 -Wall --std=c++11 -g -o ds_linkedlist_plus_one ds_linkedlist_plus_one.cc

/**
 * @file  LinkedList number add one
 * @brief Given a number stored in a list, add 1 to it
 */

// https://leetcode.com/problems/plus-one-linked-list/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */

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
 * Given a non-negative number represented as a singly
 * linked list of digits, plus one to the number.
 * The digits are stored such that the most significant
 * digit is at the head of the list.
 * Example:
 * Input: 1->2->3
 * Output:1->2->4
 */

/** @brief  - Iterative solution                             *
 * First loop: Calculate which nodes to update for add op    *
 * Secnd loop: Update only these nodes and maintain carry    *
 * @param head - Input list head ptr (each node = 1 digit)   *
 * @ret        - Same list with add_val added to it          *
 * Time Complexity = O(n),       Space Complexity = O(n)     */
ListNode* plusOne(ListNode* head, int add_val = 1) {
   std::vector<ListNode *> nodes;
   /* Corner-case : empty linked-list, need to return add_val*/
   if(head == nullptr) {
      head = new ListNode(add_val);
      return head;
   }
   for(auto cur = head ; cur ; cur = cur->next ) {
      /* If no carry-back from cur, clear all prev nodes     */
      if(cur->val < 9)              nodes.clear();
      /* Always add last node in linkedlist for update       */
      if(cur->next == nullptr)      nodes.push_back(cur);
      /* Carry from next elem might have to be stored @ cur  */
      else if(cur->next->val == 9)  nodes.push_back(cur);
      /* Next element can absorb carry, so delete all prev   */
      else if(nodes.size() != 0)    nodes.clear();
   }
   /* Modify all nodes by adding add_val and propagate carry */
   int carry = 0;
   for(int i = nodes.size() - 1; i >= 0; --i)  {
      auto val = nodes[i]->val + add_val;
      nodes[i]->val = val % 10;
      carry    = val / 10;
   }
   /* If there is a carry, we need a new node to be created  */
   if(carry) {
      auto h  = new ListNode(carry);
      h->next = nodes[0];
      if(head == nodes[0]) head = h;
   }
   return head;
}

/* Below is a list of test-cases to include                  */
//[1, 2, 3] == [1, 2, 4]
//[8, 9]    == [9, 0]
//[9]       == [1, 0]
//[9, 9]    == [1, 0, 0]
//[]        == [1]
int main() {
   cout << "Info: Need to write test-cases" << endl;
   return 0;
}
