//g++-5 --std=c++11 -Wall -g -o ds_hash_ins_del_get_random ds_hash_ins_del_get_random.cc

/**
 * @file  Insert Delete GetRandom O(1)
 * @brief Design DS to achieve constant time ins, del, get_rand
 */

// https://leetcode.com/problems/insert-delete-getrandom-o1/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map           */
using namespace std;

/**
 * Design a data structure that supports all following
 * operations in average O(1) time.
 * insert(val): Inserts an item val to set if not already present.
 * remove(val): Removes an item val from the set if present.
 * getRandom: Returns a random element from current set of elements.
 *    Each element must have the same probability of being returned.
 * Example:
 * // Init an empty set.
 * RandomizedSet randomSet = new RandomizedSet();
 * // Inserts 1 to the set. Returns true as 1 was inserted successfully.
 * randomSet.insert(1);
 * // Returns false as 2 does not exist in the set.
 * randomSet.remove(2);
 * // Inserts 2 to the set, returns true. Set now contains [1,2].
 * randomSet.insert(2);
 * // getRandom should return either 1 or 2 randomly.
 * randomSet.getRandom();
 * // Removes 1 from the set, returns true. Set now contains [2].
 * randomSet.remove(1);
 * // 2 was already in the set, so return false.
 * randomSet.insert(2);
 * // Since 1 is the only number in the set, getRandom always return 1.
 * randomSet.getRandom();
 */

/**
 * @brief: RandomizedSet is a HashTable pointing to a vector *
 * HashTable maps given number to a vector index which holds *
 * the actual number                                         *
 * O(1) insert by inserting to end of vector and mapping hash*
 * O(1) randget by directly getting rand index in vector     *
 * O(1) delete by swapping with last vector elem and del last*
 * Time Complexity = O(1), Space Complexity ~ O(2n)          */
class RandomizedSet {
public:
   RandomizedSet() : rand_gen(19) { }

   /** Inserts a value to the set. Returns true if the set   *
    * did not already contain the specified element.         */
   bool insert(int val) {
      /* return false if the element already exists in map   */
      if(val_ht.find(val) != val_ht.end())  return false;
      auto it     = val_vec.insert(val_vec.end(), val);
      val_ht[val] = std::distance(val_vec.begin(), it);
      return true;
   }

   /* Removes a value from the set. Returns true if the set  *
    * contained the specified element.                       */
   bool remove(int val) {
      /* return false if the element does not exists in map  */
      if(val_ht.find(val) == val_ht.end())  return false;
      /* Move val to the end of vector (if more than 1 elem) */
      if(val_vec.size() > 1) {
         int last_val         = *val_vec.rbegin();
         /* Update hash to vector ref for last vector element*/
         val_ht[last_val] = val_ht[val];
         val_vec[val_ht[val]] = last_val;
      }
      /* Erase val from hash_table and from end of vector    */
      val_ht.erase(val);        val_vec.pop_back();
      return true;
   }

   /** Get a random element from the set.                    */
   int getRandom() {
      const int N = val_vec.size();
      int rand_pos = std::uniform_int_distribution<int> {0, N-1}(rand_gen);
      return val_vec[rand_pos];
   }
private:
   std::unordered_map<int, int> val_ht; /* map[num]=vec_idx  */
   std::vector<int> val_vec;           /* val_vec[idx] = num */
   std::default_random_engine rand_gen{std::random_device{}()};
};

	
int main()
{
   cout << "Info: Manual tests yet to be written." << endl;
   return 0;
}
