//g++-5 -Wall --std=c++11 -g -o math_uniform_rand_sampling math_uniform_rand_sampling.cc

/**
 * @file  Math Uniform random sampling
 * @brief Given a link-list return a random value
 */

// https://leetcode.com/problems/linked-list-random-node/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include <random>            /* std::default_random_engine   */
using namespace std;

/**
 * Given a singly linked list, return a random node's value
 * from the linked list. Each node must have the same
 * probability of being chosen.
 * Follow up:
 * What if the linked list is extremely large and its length is
 * unknown to you?
 * Could you solve this efficiently without using extra space?
 * Example:
 *  // Init a singly linked list [1,2,3].
 *  ListNode head = new ListNode(1);
 *  head.next = new ListNode(2);
 *  head.next.next = new ListNode(3);
 *  Solution solution = new Solution(head);
 * // getRandom() should return either 1, 2, or 3 randomly.
 *   Each element should have equal probability of returning.
 *   solution.getRandom();
 */

struct ListNode {
   int val;
   ListNode *next;
   ListNode(int x) : val(x), next(NULL) {}
};

/**
 * @brief - Reservoir sampling with k = 1        */
class Solution {
   /* KPA */
public:
   /** @param head The linked list's head.
       Note that head is guaranteed to be not null, it has atleast one node. */
   Solution(ListNode* uhead) : head(uhead) { }

   /** Returns a random node's value. For each element in range   *
    * [0, k), include it in the result. For each element in range *
    * [k, n), include in result if rand([0, i]) falls in range of *
    * [0, k).                                                     */
   int getRandom(int k = 1) {
      int res = head->val, i = 1;
      for(auto cur = head->next; cur != nullptr; cur = cur->next, ++i) {
         /* uniform_int_distribution returns a rand # in range [0,i] */
         if(std::uniform_int_distribution<int> {0,i}(rand_gen) < k)
            res = cur->val;
      }
      return res;
   }
private:
   ListNode *head;
   std::default_random_engine rand_gen{std::random_device{}()};
};

int main()
{
   cout << "Info: Manual test-cases yet to be written." << endl;
   return 0;
}
