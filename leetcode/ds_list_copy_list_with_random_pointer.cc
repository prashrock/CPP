//g++ -Wall --std=c++11 -g -o ds_list_copy_list_with_random_pointer ds_list_copy_list_with_random_pointer.cc

/**
 * @file  Copy list with random pointer
 * @brief Copy linked list with pointers to itself.
 */

// https://leetcode.com/problems/copy-list-with-random-pointer/

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
 * A linked list is given such that each node contains an
 * additional random pointer which could point to any node
 * in the list or null.
 * Return a deep copy of the list.
 */

/**
 * Definition for singly-linked list with a random pointer.
 */
struct RandomListNode {
   int label;
   RandomListNode *next, *random;
   RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

/** @brief - Use a Hash table to store all elements in list  *
 * @param head - Input list head pointer                     *
 * @ret        - Deep copied list head pointer               *
 * Time Complexity = O(n), Space Complexity = O(n)           */
RandomListNode *copyRandomList(RandomListNode *head) {
   unordered_map<int, RandomListNode *>map;
   RandomListNode *newhead = NULL, *cit = NULL;

   for(auto it = head; it != NULL; it = it->next) {
      RandomListNode *cur_node = NULL;
      /* If node is already created then use that pointer    */
      if(map.find(it->label) != map.end())
         cur_node = map[it->label];
      else {
         cur_node = new RandomListNode(it->label);
         map[it->label] = cur_node;
      }

      /* If random pointer is present, handle it similar     *
       * to how a new node is usually handled                */
      if(it->random) {
         if(map.find(it->random->label) == map.end()) {
            cur_node->random = new RandomListNode(it->random->label);
            map[it->random->label] = cur_node->random;
         }
         else cur_node->random = map[it->random->label];
      }
      /* If this is the first element, populate head elem    */
      if(newhead == NULL) { cit = newhead = cur_node; }
      else                { cit->next = cur_node; cit = cit->next; }
   }
   return newhead;
}

/**
 * Note: there is another neat solution on Leetcode which uses
 * the original list itself to keep track of random pointers
 * Check out the C++ solution posted in the below link:
 * https://leetcode.com/discuss/22421/solution-constant-space-complexity-linear-time-complexity
 * This approach consists of 3 steps:
 * Iterate the original list and duplicate each node. The duplicate of each node follows its original immediately.
 * Iterate the new list and assign the random pointer for each duplicated node.
 * Restore the original list and extract the duplicated nodes.
 */

int main()
{
   cout << "Info: Need to write test-cases" << endl;
   return 0;
}
