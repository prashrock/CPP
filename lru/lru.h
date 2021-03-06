#ifndef _LRU_CPP_
#define _LRU_CPP_

#include <algorithm>           /* std::max                   */
#include <unordered_map>       /* std::unordered_map         */
#include <list>                /* std::list                  */

/**
 * @class LRU
 * @brief STL based Least Recently Used Cache implementation
 *        Evicts items with the greatest "idle time"
 * @note  Inspired by Tim Day(http://timday.bitbucket.org/lru.html)
 * @note  Minimal leetcode implementation  @
 *        https://github.com/prashrock/CPP/tree/master/leetcode/ds_lru_cache.cc
 
 * This class uses 2 STL containers (List + Unordered_MAP) and
 * implements a basic O(1) LRU container.
 */
template<typename Tkey=int, typename Tval=int>
class lru
{
 public:
   explicit lru(size_t size) : sz_(size), map_(size)  {    }
   ~lru()                       { clear();                 }

  /**
   * @brief Returns the key list (as constant)               */
   const std::list<Tkey>& get_keys() const { return list_; }
   /**
    * @brief Get #entries currently present in LRU           */
    size_t count() const       { return map_.size();       }
   /**
    * @brief Get LRU Container size (max #entries)           */
    size_t size() const        { return sz_;               }
   /**
    * @brief Check if LRU is full                            */
    bool isFull() const        { return count() == size(); }
   /**
    * @brief Check if LRU is empty                           */
    bool isEmpty() const       { return count() == 0;      }
   /**
    * @brief Manually remove a key and value from LRU        *
    * @note  Time Complexity = O(1)                          */
    void remove(Tkey k)        { if(exist(k))   evict(k);  }
   /**
    * @brief Peek at the oldest key in LRU                   */
    bool peekOldest(Tkey &k) const {
       if(isEmpty())  return false;
       else {
          k = list_.front();
          return true;
       }
    }
   /**
    * @brief Peek at the newest key in LRU                   */
    bool peekNewest(Tkey &k) const {
       if(isEmpty())  return false;
       else {
          k = list_.back();
          return true;
       }
    }
   /**
    * @brief Clear the contents of the LRU (clear keys+vals) */
    void clear() {
       list_.clear();  /* Clear the list of keys             */
       map_.clear();   /* Clear unordered_map of val+itr     */
    }
   /**
    * @brief Check if a given key exists in LRU              *
    * @note  Time Complexity = O(1) (bcoz of unordered_map)  */
    bool exist(Tkey k) const {
       if(map_.find(k) != map_.end()) return true;
       else                           return false;
    }
   /**
    * @brief Inserts a Key + Value Pair                      *
    * @note  Time Complexity = O(1) (bcoz of unordered_map)  */
    bool insert(Tkey k, Tval val) {
       /* This key is already present                       */
       if(exist(k))   map_[k].first = val;
       else   	       lru_insert(k, val);
       promote(k); /* Bump up this key in the LRU list      */
       return true;
    }
   /**
    * @brief Get the value for a key (also refresh age)      *
    * @note  Time Complexity = O(1) (bcoz of unordered_map)  */
    bool get(Tkey k, Tval &val) {
       if(exist(k) == false)  return false;
       else {
          val = map_[k].first; /* Map contains val+list itr  */
          promote(k); /* Bump up this key in the LRU list    */
          return true;
       }
    }
   /**
    * @brief Get the value for a key (no age refresh)        *
    * @note  This API asserts that key is valid. So do not   *
    *        call this API if key might not be present       */
    const Tval &get(Tkey k) const {
       assert(exist(k));
       return map_.at(k).first; /* [] as it is not const op  */
    }
   /**
    * @brief Get the value for a key (also refresh age)      *
    * @note  This API asserts that key is valid. So do not   *
    *        call this API if key might not be present       */
    const Tval &get(Tkey k) {
       /* Use c to refer to overloaded const function        */
       const auto *const_this = this;
       assert(exist(k));
       promote(k);
       return const_this->get(k);
    }
private:
    /* Map should be indexed by key & should hold two things:*
     * val and location of val in list (an iterator)         */
    typedef std::unordered_map< Tkey, std::pair<Tval,
            typename std::list<Tkey>::iterator> > lru_map_t;
    size_t sz_;             /**< Container Size              */
    std::list<Tkey> list_;  /**< List to maintain ins order  */
    lru_map_t map_;         /**< Map to locate Key in O(1)   */

   /**
    * @brief Refresh the age of the given key.               *
    * @note  Expects a valid key (i.e., key present in map)  */
    void promote(Tkey k) {
       /* Move element from current list position to end     */
       list_.splice(list_.end(), list_, map_[k].second);
    }
   /**
    * @brief Evict given key from LRU (map + list)           *
    * @note  Expects a valid key (key present in map + list) */
    void evict(Tkey k) {
       list_.erase(map_[k].second);
       map_.erase(k);
    }
   /**
    * @brief Insert key+val into the LRU                     */
    void lru_insert(Tkey k, Tval val) {
       if(isFull()) { /* If full, evict oldest (first) elem */
          Tkey oldest_key = list_.front();
          evict(oldest_key);
       }
       auto it = list_.insert(list_.end(), k);
       map_[k] = std::make_pair(val, it);
    }
};

/**
 * @fn lru::operator<<() const
 * @brief Outputs all elements in LRU based on age ( newest to oldest)
 * @return ostream
 */
template<typename Tkey, typename Tval>
std::ostream& operator<<(std::ostream& os, const lru<Tkey, Tval>& x)
{
   os << "key  : val (oldest to newest)" << std::endl;
   auto key_list = x.get_keys();
   for(auto k : key_list) {
      Tval v = x.get(k);
      os << k << ":" << v << std::endl;
   }
   return os;
}

#endif //_LRU_CPP_
