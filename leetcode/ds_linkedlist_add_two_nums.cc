//g++-5 --std=c++11 -Wall -g -o ds_linkedlist_add_two_nums ds_linkedlist_add_two_nums.cc

/**
 * @file  Add two positive numbers
 * @brief Given 2 LinkedList of non-neg numbers, add them both
 */

// https://leetcode.com/problems/add-two-numbers/

/**
 * You are given two linked lists representing two non-negative numbers.
 * The digits are stored in reverse order and each of their nodes contain
 * a single digit. Add the two numbers and return it as a linked list.
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
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

/* Maintain carry and iterate over both lists simultaneously *
 * note, since both numbers are stored in right to left order*
 * it is just a simple forward traversal of linked-lists     */
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
   ListNode *ans  = NULL; /* ans is a new linked-list        */
   int carry = 0;
   /* Be in loop till either lists is non-empty or carry     */
   for(ListNode *cur = ans; l1 || l2 || carry; carry /= 10) {
      if(l1) {carry += l1->val; l1 = l1->next; }
      if(l2) {carry += l2->val; l2 = l2->next; }
      /* carry can be between [0, 18], so use modulo         */
      auto nxt  = new ListNode(carry % 10);
      if(ans == NULL)   cur = ans = nxt; /* 1st elem in ans  */
      else            { cur->next = nxt; cur = cur->next; }
   }
   return ans;
}

int main()
{
   cout << "Info: Manual test-cases yet to be created." << endl;
   return 0;
}
