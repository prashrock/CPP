//g++ --std=c++11 -g -o math_integer_missing_int math_integer_missing_int.cc

/**
 * @file  Integer Single Number
 * @brief Given an array of pairwise elments find odd one out
 */

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
using namespace std;

//https://leetcode.com/problems/single-number/

/**
 * Given an array of integers, every element appears twice   *
 * except for one. Find that single one.                     *
 * Note:                                                     *
 * Your algorithm should have a linear runtime complexity.   *
 * Could you implement it without using extra memory?        */

/**
 * Given an array of integers, in which exactly 2 elements   *
 * appear only once and all the other elements appear        *
 * exactly twice. Find the two elements that appear only     *
 * once                                                      *
 * For example, given [1, 2, 1, 3, 2, 5] return [3, 5]       *
 * Note:                                                     *
 * Your algorithm should have a linear runtime complexity.   *
 * Could you implement it without using extra memory?        */


/**
 * To find the lone element in an array, leverage the power  *
 * of parity. Since every other number occurs twice, XOR of  *
 * entire array should cancel out all other numbers and give *
 * us the lone number in a silver platter                    *
 * @param nums                                               *
 *   Input vector of elements                                *
 * @return                                                   *
 *   Lone element value                                      *
 * Time Complexity = O(n),  n=size of array                  *
 * Space Complexity= O(1),                                   *
 * Note: This function expects an array with all elements as *
 * duplicate except one element. No checks are done within   *
 * this function to validate this.                           *
 * Note: Using a template so that array can be either a      *
 * signed or unsigned integer of any size                    *
 * Note: Using i = 0; i < nums.size() is faster than this    */
template<typename T=int>
T find_lone_element(vector<T> &nums)
{
   T result = 0;
   for(auto val:nums) result ^= val;
   return result;
}


/**
 * To find two lone elements (A, B) in an array,             *
 * 1) repeat steps from find_lone_element to get XOR of A,B  *
 * 2) each bit in A XOR B implies, that bit is set only in A *
 *    or B and not in both. Use this info to partition the   *
 *    array into two halves. repeat (1) on the two partitions*
 *    but maintain result in two different variables, A, B   *
 *    Similar to (1) all other duplicates will cancel and we *
 *    will be left with only A and B                         *
 * @param nums                                               *
 *   Input vector of elements                                *
 * @return                                                   *
 *   Vector containing two lone element values               *
 * Time Complexity = O(n),  n=size of array                  *
 * Space Complexity= O(1),                                   *
 * Note: This function expects an array with all elements as *
 * duplicate except two elements. No checks are done within  *
 * this function to validate this.                           *
 * Note: Using a template so that array can be either a      *
 * signed or unsigned integer of any size (i8/u8 to i64/u64) */
template<typename T=int>
vector<T> find_two_lone_elements(vector<T> &nums)
{
   vector<T> result(2, 0);
   T a_xor_b = 0;

   /* 1) Repeat find_lone_element ops to get a_xor_b         */
   for(int i = 0; i < nums.size(); i++) a_xor_b ^= nums[i];

   /* 2) get the least set bit, to partition xor result.     *
    * Note: this is the same as bit_get_lsb_val()            */
   T partition_bit = (a_xor_b & -a_xor_b);
   for(int i = 0; i < nums.size(); i++) {
      if(nums[i] & partition_bit)
         result[0] ^= nums[i];
      else
         result[1] ^= nums[i];
   }
   return result;
}



int main()
{
   /* Find lone element test-case                            */
   cout << "Find one missing element in array:" <<endl;
   int arr[] = {1, 2, 3, 4, 5, 1, 3, 2, 4};
   vector<int> vec(arr, arr + sizeof(arr)/sizeof(int));
   cout << find_lone_element(vec) << endl;

   cout << "Find 2 missing elements in array:" <<endl;
   int arr1[] = {1, 2, 1, 3, 2, 5};
   vector<int> vec1(arr1, arr1 + sizeof(arr1)/sizeof(int));
   auto ans1 = find_two_lone_elements(vec1);
   for(auto val:ans1) 	cout << val << endl;
	
   return 0;
}
