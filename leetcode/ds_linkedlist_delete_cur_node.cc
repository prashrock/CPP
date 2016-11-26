//g++-5 --std=c++11 -Wall -g -o ds_linkedlist_delete_cur_node ds_linkedlist_delete_cur_node.cc

/**
 * @file  In LinkedList delete a node given only that node
 * @brief Delete a node given access to only that node
 */

// https://leetcode.com/problems/delete-node-in-a-linked-list/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
using namespace std;

/**
 * Write a function to delete a node (except the tail) in a
 * singly linked list, given only access to that node.
 * Supposed the linked list is 1 -> 2 -> 3 -> 4 and you are
 * given the third node with value 3, the linked list should
 * become 1 -> 2 -> 4 after calling your function.
 */

struct ListNode {
   int val;
   ListNode *next;
   ListNode(int x) : val(x), next(NULL) {}
};

/**
 * @brief  Instead of deleting current node, just move all the   *
 * subsequent node values back by one and delete the last node   *
 * @note   this solution does not work if node is the tail node  *
 * because there is no future node we can move back and we cannot*
 * access the previous node to set its next pointer to null      */
void deleteNode(ListNode* node) {
   auto next = node->next;
   /* Handle corner-case where there is only one element         */
   if(next  == nullptr) { free(node); return; }
   /* While next pointer is not tail, move elements back by one  */
   while (next->next) {
      node->val = next->val;
      next = next->next;
      node = node->next;
   }
   /* Last but one node needs to get the last node value         */
   node->val = next->val;
   node->next = nullptr;
   free(next);
}

int main()
{
   cout << "Info: Manual test-cases yet to be created." << endl;
   return 0;
}
