//g++ --std=c++11 -Wall  -g -o ds_list_find_the_celebrity ds_list_find_the_celebrity.cc

/**
 * @file  Find the celebrity
 * @brief Special majority element problem
 */

// https://leetcode.com/problems/find-the-celebrity/

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
 * Suppose you are at a party with n people (labeled from 0 to n - 1)
 * and among them, there may exist one celebrity. The definition of
 * a celebrity is that all the other n - 1 people know him/her but
 * he/she does not know any of them.
 *
 * Now you want to find out who the celebrity is or verify that there
 * is not one. The only thing you are allowed to do is to ask questions
 * like: "Hi, A. Do you know B?" to get information of whether A knows B.
 * You need to find out the celebrity (or verify there is not one) by
 * asking as few questions as possible (in the asymptotic sense).
 *
 * You are given a helper function bool knows(a, b) which tells you
 * whether A knows B. Implement a function int findCelebrity(n), your
 * function should minimize the number of calls to knows.
 *
 * Note: There will be exactly one celebrity if he/she is in the party.
 * Return the celebrity's label if there is a celebrity in the party.
 * If there is no celebrity, return -1.
 */

/* Given helper function to return true if a knows b         */
bool knows(int a, int b) {return true;}

/* Since every element should know celebrity except the      *
 * celebrity himself, just go over the list once to find out *
 * potential celebrity. Next, validate if it is correct      */
int findCelebrity(int n) {
   int candidate = 0;
   /* calculate the candidate (celebrity) first in a loop.   */
   for(int i = 1; i < n; ++i)
      if (knows(candidate, i)) candidate = i;

   /* Everyone other than celebrity must know celebrity      *
    * Celebrity should not know any of the others            */
   for(int i = 0; i < n; ++i) {
      if(i == candidate)                                    continue;
      else if(!knows(i, candidate) || knows(candidate, i))  return -1;
   }
   return candidate;
}

/* Note, if this question did not deal with celebrity, but   *
 * instead with majority elements, use Boyer Moore Algorithm */

/* This is a distributed election count algo which will      *
 * find the majority element (element occuring > half times) *
 * Since this problem doesnt make this claim, cant use this  */
int booyerMooreMethod(vector<int>& nums) {
   int candidate, cnt = 0;
   for(int i = 0; i < (int)nums.size(); ++i) {
      if(cnt == 0)              candidate = nums[i];
      if(candidate == nums[i])  cnt++;
      else                      cnt--;
   }
   int verify_cnt = 0;
   for(int i = 0; i < (int)nums.size(); ++i)
      if(candidate == nums[i]) verify_cnt++;
   
   if(verify_cnt >= (int)(nums.size()+1)/2) return candidate;
   else                                     return -1;
}

int main()
{
   cout << "Info: No test-cases implemented yet." << endl;
   return 0;
}
