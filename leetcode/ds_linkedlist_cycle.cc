//g++-5 --std=c++11 -Wall -g -o ds_linkedlist_cycle ds_linkedlist_cycle.cc

/**
 * @file  Linkedlist Cycle
 * @brief Detect cycle in a linked list
 */

// https://leetcode.com/problems/linked-list-cycle/
// https://leetcode.com/problems/linked-list-cycle-ii/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */

using namespace std;

struct ListNode {
   int val;
   ListNode *next;
   ListNode(int x) : val(x), next(NULL) {}
};

// https://leetcode.com/problems/linked-list-cycle/
/**
 * Given a linked list, determine if it has a cycle in it.
 * Follow up:
 * Can you solve it without using extra space?
 */

/* Two-pointer (hare-tortoise) approach */
bool hasCycle(ListNode *head) {
   /* base-case: 0 elements */
   if(head == nullptr) return false;
   for(auto slow(head), fast(head);
       fast != nullptr && fast->next != nullptr;) {
      slow = slow->next;
      fast=fast->next->next;
      if(slow == fast) return true;
   }
   return false;
}

//Leetcode test-cases
//[]      //false
//[1]     //false
//[1,2]   //false
//[-21,10,17,8,4,26,5,35,33,-7,-16,27,-12,6,29,-12,5,9,20,14,14,2,13,-24,21,23,-21,5]   //false

// https://leetcode.com/problems/linked-list-cycle-ii/
/**
 * Given a linked list, return the node where the cycle begins.
 * If there is no cycle, return null.
 * Note: Do not modify the linked list.
 * Follow up:
 * Can you solve it without using extra space?
 */

/* Detect loop with same method as before                *
 * Once a loop is detected, start slow from the          *
 * beginning and update both slow, fast till             *
 * they meet again. Math below:                          *
 *  Assume: Length of loop       C = y + z               *
 *  Assume: Distance before loop   = x                   *
 * When slow meets fast (remember, fast is twice as fast as slow): *
 * Slow's total distance,        d = x + y          //1  *
 * Fast's total distance,    2 * d = x + y + z + y  //2  *
 * Substitute (d) from (1) into (2), we get the below:   *
 *    2 * d = x + y + z + y = x + 2y + z //sub (1) in (2)*
 * 2(x + y) = x + 2y + z                                 *
 *  2x + 2y = x + 2y + z                                 *
 *       x  =  z                                    //3  */
ListNode *detectCycle(ListNode *head) {
   /* base-case: 0 elements */
   if(head == nullptr) return nullptr;
   /* Use same logic as before to detect loop */
   auto slow(head), fast(head);
   for(;fast != nullptr && fast->next != nullptr;) {
      slow = slow->next;
      fast = fast->next->next;
      if(slow == fast) break;
   }
   /* If there is no loop, return nullptr     */
   if(fast == nullptr || fast->next == nullptr) return nullptr;
   /* Slow from begin, fast from cur, wait till they meet */
   for(slow = head; slow != fast; slow=slow->next, fast=fast->next);
   return slow;
}

int main()
{
   cout << "Info: Manual test-cases yet to be created." << endl;
   return 0;
}
