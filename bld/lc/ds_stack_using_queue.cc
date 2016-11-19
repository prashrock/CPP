//g++-5 --std=c++11 -Wall -g -o ds_stack_using_queue ds_stack_using_queue.cc

/**
 * @file  Implement a Stack using Queue and vice-versa
 * @brief Use one or more Queues to implement a stack and vice-versa.
 */

// https://leetcode.com/problems/implement-stack-using-queues/
// https://leetcode.com/problems/implement-queue-using-stacks/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
#include <cstring>           /* std::strtok                  */
#include <queue>             /* std::queue                   */
#include <stack>             /* std::stack                   */
using namespace std;


/**
 * Implement the following operations of a stack using queues.
 * push(x) -- Push element x onto stack.
 * pop()   -- Removes the element on top of the stack.
 * top()   -- Get the top element.
 * empty() -- Return whether the stack is empty.
 */

/* Can be achieved with a single queue, by moving elements   *
 * to the back of the queue during a push operation          */
class Stack {
public:
   /* Simulate stack by moving all elements back of latest   *
    * Time Complexity = O(n) -- n-1 operations               */
   void push(int x) {
      q.push(x);
      /* Q is FIFO. Move everything in front of x            *
       * (item just pushed) to behind x everything           */
      for(int i = 0; i < (int)q.size()-1; ++i) {
         q.push(q.front());
         q.pop();
      }
   }

   /* Queue is in LIFO (stack order) so just call pop        */
   void pop() { q.pop(); }

   /* Queue is in LIFO (stack order) so just call front      */
   int top() { return q.front(); }

   bool empty() { return (q.size() == 0); }
private:
   std::queue<int> q;
};


/**
 * Implement the following operations of a queue using stacks.
 * push(x) -- Push element x to the back of queue.
 * pop() -- Removes the element from in front of queue.
 * peek() -- Get the front element.
 * empty() -- Return whether the queue is empty.
 */

/* Maintain 2 stacks. For peek and pop, if output stack is   *
 * empty move elements from the input stack                  */
class Queue {
public:
   /* Insert into the first stack (input stack)              */
   void push(int x) { instk.push(x); }

   /* Move from input stack to output only if output empty   */
   void pop(void) {
      if( outstk.empty() ) migrate();
      outstk.pop();
   }

   /* Move from input stack to output only if output empty   */
   int peek(void) {
      if( outstk.empty() ) migrate();
      return outstk.top();
   }

   // Return whether the queue is empty.
   bool empty(void) {
      return ( instk.empty() && outstk.empty() );
   }
private:
   /* Moving from one stack to another creates queue          */
   std::stack<int> instk, outstk;
   void migrate() {
      while( !instk.empty() ) {
         outstk.push(instk.top());
         instk.pop();
      }
   }
};

int main()
{
   cout << "Info: Manual test-cases not implemented." << endl;
   return 0;
}
