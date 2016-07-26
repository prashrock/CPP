#ifndef _BITMAP_CPP_
#define _BITMAP_CPP_

#include <algorithm>           /* std::max                   */
#include <cstring>             /* memset                     */
#include <climits>             /* CHAR_BIT                   */
#include <bitset>              /* std::bitset (dump)         */

/* Simple resizable Bitmap to hold [0, max_n] bits. Uses     *
 * STL Vector as Container and **not thread safe**           *
 * Todo:                                                     *
 * - Feature: For sparse bitmaps, use hierarchical 2D bitmap *
 * - Perf: Avoid divide and modulo operations                *
 * - Perf: Operate with cacheline sized chunks               */
class Bitmap
{
public:
   /* Create bitmap based on max capacity [0-max_n]          *
    * @param max_n - maximum value in this static bitmap     */
    Bitmap(size_t max_n) : n(max_n), bw((n >> u64_shift) + 1 , 0) {}
   ~Bitmap() { }    /* Destructor for the bitmap class       */
   /* Check if a given position is valid within bitmap       */
   inline bool isValid(size_t pos) const {
      return (pos <= n);
   }
   /* Bitmap Set operations (set, set vector, set all)       */
   void set(size_t pos)  {
      set(pos, true);
   }
   void set(const std::vector<size_t>& pv) {
      for(auto p : pv) set(p);
   }
   void setAll() {
      std::fill(bw.begin(), bw.end(), (uint64_t) - 1);
   }
   /* Bitmap Reset operations (reset,reset vector, clear all)*/
   void reset(size_t pos) {
      set(pos, false);
   }
   void reset(const std::vector<size_t>& pv) {
      for(auto p:pv) reset(p);
   }
   void reset() {
      std::fill(bw.begin(), bw.end(),  0);
   }
   /* Bitmap Size ops (container size, #set bits, is empty? */
   inline size_t size()  const {
      return (bw.size() << u64_shift);
   }
   inline size_t count() const {
      return cnt();
   }
   inline bool isEmpty() const {
      return (count() == 0);
   }
   /* Bitmap class get API (get if a bit is set or not)      */
   bool get(size_t pos) const {
      if(isValid(pos) == false) return false;
      else return ((bw[get_word_idx(pos)] & wordmask(pos)) != 0);
   }
   /* Bitmap class get next set position idx                 *
    * @param pos - position idx. Can be zero/one based       *
    * @param next_pos - reference variable for next_pos      */
   bool get_next_set_pos(size_t pos, size_t &next_pos) {
      if(isValid(pos+1) == false) return false; /* not last  */
      uint64_t mask = ~bit_propagate_ones_right(wordmask(pos));
      for(auto i = get_word_idx(pos); i < bw.size(); ++i, mask = -1) {
         int ffs = bit_ffs(bw[i] & mask); /* 1st set bit pos */
         if(ffs >= 0)  { /* If there is a bit,get global idx */
            next_pos = (i << u64_shift) + ffs;
            return true;
         }
      }
      return false;
   }
   inline void resize(size_t new_n) {
      if(new_n < n) /* Clear off all higher bits in last word*/
         bw[get_word_idx(new_n)] &=  bit_propagate_ones_right(wordmask(new_n));
      bw.resize((new_n >> u64_shift) + 1 , 0);
      n = new_n;
   }
   void dump() const {
      for(auto v:bw) cout << std::bitset<u64_bit>(v) << endl;
   }
private:
   /* Bitmap class member variables                          */
   size_t n;             /* specifies #bits in bitmap [0, n] */
   std::vector<uint64_t> bw; /* Underlying bitmap container  */
   const static int u64_bit   = (CHAR_BIT * sizeof(uint64_t));
   const static int u64_shift = 6; /* use 2^6 = 64, no divide*/ 

   /* Use GCC built-in Find First Set (which is 1 based idx) */
   inline int bit_ffs(uint64_t w) const { return __builtin_ffsll(w)-1;   }
   /* Use GCC built-in Population Count                      */
   inline int bit_pop(uint64_t w) const { return __builtin_popcountll(w);}
   /* Clear the Lowest set bit of given word                 */
   inline uint64_t clear_lsb(uint64_t n)        { return (n & (n - 1));  }
   /* Rotate all the bits set (equivalent to calling ntohl   */
   inline uint64_t bit_propagate_ones_right(uint64_t n) const {
      n |= n >> 1;   n |= n >> 2;    n |= n >> 4;
      n |= n >> 8;   n |= n >> 16;   n |= n >> 32;
      return n;
   }
   /* Get the Lowest set bit of given word(C built-in)       */
   inline uint64_t get_lsb_word_pos(uint64_t n) {return __builtin_ctzll(n);}
   /* Given position [0-n], find the 64-bit word index       */
   inline size_t get_word_idx(size_t pos) const { return (pos >> u64_shift);}
   /* Given a bit position [0-63) create a mask              */
   inline uint64_t wordmask(size_t pos) const   {
      return ((uint64_t)1 << (pos % u64_bit));
   }
   /* Given position[0-n), set/clear bit in that position    */
   inline void set(size_t pos, bool on) {
      if(isValid(pos)) {
         if(on)   bw[get_word_idx(pos)] |=  wordmask(pos);
         else     bw[get_word_idx(pos)] &= ~wordmask(pos);
      }
   }
   /* Get a count of # set bits in the Bitmap                */
   inline size_t cnt(size_t n = 0) const {
      for(auto v : bw) n += bit_pop(v);
      return n;
   }
};

#endif //_BITMAP_CPP_
