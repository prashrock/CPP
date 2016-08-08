//g++ -Wall --std=c++11 -g -o ds_list_iterator_flatten_nested ds_list_iterator_flatten_nested.cc

/**
 * @file  Flatten Nested List Iterator
 * @brief Implement an iterator to traverse nested list
 */

// https://leetcode.com/problems/flatten-nested-list-iterator/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <stack>             /* std::stack                   */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/**
 * Given a nested list of integers, implement an iterator to flatten it.
 * Each element is either an integer, or a list -- whose elements may
 * also be integers or other lists.
 * Example 1:
 * Given the list [[1,1],2,[1,1]],
 * By calling next repeatedly until hasNext returns false, the order of
 * elements returned by next should be: [1,1,2,1,1].
 * Example 2:
 * Given the list [1,[4,[6]]],
 * By calling next repeatedly until hasNext returns false, the order of
 * elements returned by next should be: [1,4,6].
 */

#if 0
/**
 * Definition for Integer Class.
 */
class NestedInteger {
public:
   // Return true if this NestedInteger holds a single integer, rather than a nested list.
   bool isInteger() const;
   
   // Return the single integer that this NestedInteger holds, if it holds a single integer
   // The result is undefined if this NestedInteger holds a nested list
   int getInteger() const;

   // Return the nested list that this NestedInteger holds, if it holds a nested list
   // The result is undefined if this NestedInteger holds a single integer
   const vector<NestedInteger> &getList() const;
};



/* @brief - Iterator with a stack to avoid recursion         */
class NestedIterator {
public:
   /* Define a new type to hold begin and end for each list  */
   typedef std::pair<std::vector<NestedInteger>::iterator,
                     std::vector<NestedInteger>::iterator> pitit_t;

   NestedIterator(vector<NestedInteger> &nestedList){
      st.push(std::make_pair(nestedList.begin(), nestedList.end()));
   }

   int next() {
      assert(hasNext() == true); /* Confirm list is notempty */
      return (st.top().first++)->getInteger();
   }

   bool hasNext() {
      /* Open lists till we see bare integer or empty stack  */
      while( !st.empty() ) {
         /* If begin() == end(), this list is processed      */
         if(st.top().first == st.top().second) st.pop();
         else {
            auto lst_it = st.top().first; /* cur pos in list */
            if(lst_it->isInteger())        return true;
            /* before pushing, increment top of the stack    */
            st.top().first++;
            st.push(std::make_pair(lst_it->getList().begin(),
                                   lst_it->getList().end()));
         }
      }
      /* If we reach till here, stack is empty and no int    */
      return false;
   }
private:
   std::stack<pitit_t> st; /* LIFO order for recursion       */
};

#endif

int main()
{
   cout << "Note: this code will not compile or run "
        << "because the interface is not implemented here" << endl;
   return 0;
}
