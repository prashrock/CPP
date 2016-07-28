//g++ --std=c++11 -g -o ds_lru_cache ds_lru_cache.cc

/**
 * @file  LRU Cache
 * @brief Design and implement Least Recently Used (LRU) cache DS.
 */

// https://leetcode.com/problems/lru-cache/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <unordered_map>     /* std::unordered_map           */
#include <list>              /* std::list                    */
using namespace std;

/**
 *Design and implement a data structure for Least Recently Used (LRU)
 *cache. It should support the following operations: get and set.
 * - get(key) - Get the value (will always be positive) of the key if
 *       the key exists in the cache, otherwise return -1.
 * - set(key, value) - Set or insert value if the key is not already
 *       present. When cache reached its capacity, invalidate the
 *       least recently used item before inserting a new item.
 */

/* Note: Refer to my extended LRU cache implementation:      *
 * https://github.com/prashrock/CPP/tree/master/lru/lru.h    */

class LRUCache {
   /* Cannot use dequeue as its iterators are invalidated    *
    * upon insert/del and we need iterators to tie to Map    */
public:
   LRUCache(int capacity) : lru_size(capacity) {
      lru_map.reserve(capacity);
   }

   int get(int k) {
      if(lru_map.find(k) == lru_map.end()) return -1;
      promote(k);
      return lru_map[k].first;
   }

   void set(int k, int v) {
      if(lru_map.find(k) != lru_map.end()) { /* key present */
         lru_map[k].first = v;
         promote(k);
      }
      else {
         if(lru_map.size() == lru_size) evict(time_lst.back());
         time_lst.push_front(k);
         lru_map[k] = {v, time_lst.begin()};
      }
   }

private:
   typedef std::pair<int, std::list<int>::iterator> piit_t;
   int                              lru_size;
   std::list<int>                   time_lst; /* newest@front*/
   std::unordered_map<int, piit_t>  lru_map; 

   /* Move element from current time list position to end   */
   inline void promote(int k) {
      time_lst.splice(time_lst.begin(), time_lst, lru_map[k].second);
   }

   /* @brief Evict given **valid** key from LRU (map + list) */
   inline void evict(int k) {
      time_lst.erase(lru_map[k].second);
      lru_map.erase(k);
   }
};

bool lru_manual_test()
{
   /* Manual test-case 1 (test LRU of size 1)                */
   {
      class LRUCache lru(1); /* LRU with single element      */
      lru.set(2, 1);
      if(lru.get(2) != 1) { cout << "Err: Get 2" << endl; return false; }
      lru.set(3, 2);
      if(lru.get(2) != -1) { cout << "Err: Get 2" << endl; return false;}
      if(lru.get(3) != 2)  { cout << "Err: Get 3" << endl; return false;}
      cout << endl;
   };
   /* Manual test-case 1 (test set on same key)              */
   {
      class LRUCache lru(2); /* LRU with two elemenst        */
      lru.set(2,1);
      lru.set(2,2);
      if(lru.get(2) != 2) { cout << "Err: Get 2" << endl; return false; }
      lru.set(1,1);
      lru.set(4,1);
      if(lru.get(2) != -1){cout << "Err: Get 2,-1" <<endl; return false;}
   };
   return true;
}

int main()
{
   if(lru_manual_test() == false) return -1;
   cout << "Info: All manual test-cases passed." << endl;
   return 0;
}
