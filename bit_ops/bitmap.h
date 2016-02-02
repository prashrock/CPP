#ifndef _BITMAP_CPP_
#define _BITMAP_CPP_

#include <algorithm>           /* std::max                   */
#include <cstring>             /* size_t                     */
#include <cstdint>             /* uint64_t                   */
#include <climits>             /* CHAR_BIT                   */
#include <cerrno>              /* CHAR_BIT                   */
static const int u64_bit = (CHAR_BIT * sizeof(uint64_t));

/* Constant size bitmap definition                           *
 * Note: valid entries for bitmap = [0 - N]. N should be     *
 * specified during bitmap creation.                         */
class bitmap
{
public:
	/* Create bitmap based on max capacity [0-max_n]         */
	void init(size_t max_n){
		length = 0;
		if(max_n >= u64_bit) {
			length = (max_n / u64_bit) + 1;
			words  = new uint64_t[length];
		}
		clear();
	}
	/* Reset the bitmap                                      */
	void clear() {
		if(!length) bits = 0;
		else memset(words, 0, length * sizeof(uint64_t));
	}
	/* Set all the bits in the bitmap                        */
	void set_all() {
		if(!length) bits = -1;
		else memset(words, -1, length * sizeof(uint64_t));
	}
	/* Constructor for the bitmap class                      *
	 * @param max_n - maximum value in this static bitmap    */
    bitmap(size_t max_n) : length(0), bits(0) {
		init(max_n);
	}
	/* Destructor for the bitmap class                       */
	~bitmap() {
		if(length && words) delete[] words;
	}
	/* Bitmap class get API                                  *
	 * @param pos - position idx. Can be zero/one based      *
	 * Note: As long as user is consistent with get/set API  *
	 * Bitmap Class does not care if idx is 0 or 1 based     */
	bool get(size_t pos) {
		uint64_t *word = get_word(pos);
		if(!word) return false;
		else      return ((*word & wordmask(pos)) != 0);
	}
	/* Bitmap class get next set position idx                *
	 * @param pos - position idx. Can be zero/one based      *
 	 * @param next_pos - reference variable for next_pos     */
	bool get_next_set_pos(size_t pos, size_t &next_pos) {
		next_pos = pos + 1;
		/* If next pos is not valid, nothing to do           */
		uint64_t *word = get_word(next_pos); /*Get word      */
		if(!word) return false;
		/* If lucky, cur_word has nextsetbit, check cur_word */
		int ffs = bit_ffs(*word >> (next_pos % u64_bit));
		if(ffs >= 0)  {
			next_pos += ffs;
			return true;
		}
		/* Start from next word till length & find_first_bit */
		for(auto i = get_word_idx(next_pos)+1; i < length; ++i) {
			ffs = bit_ffs(words[i]);
			if(ffs >= 0)  {
				next_pos = i * u64_bit + ffs;
				return true;
			}
		}
		return false;
	}
	/* Set Bitmap at specified position                      *
	 * @param pos - position idx. Can be zero/one based      */
	void set(size_t pos)   {set(pos, true);}
	/* Clear/Reset Bitmap at specified position              *
 	 * @param pos - position idx. Can be zero/one based      */
	void reset(size_t pos) {set(pos, false);}
	
private:
	/* Use GCC built-in FFS. Note, returns 1 based idx       */
	int bit_ffs(uint64_t word) {
		return __builtin_ffsll(word) - 1;
	}
		
	/* Clear the Lowest set bit of given word                */
	uint64_t clear_lsb(uint64_t n) {
		return (n & (n - 1));
	}
	/* Get the Lowest set bit of given word(C built-in)      */
	uint64_t get_lsb_word_pos(uint64_t n) {
		return __builtin_ctzll(n);
	}
	/* Given position [0-n], find the 64-bit word index      *
	 * which contains this position.                         *
	 * For 64-bit bitmap, this always returns 0              */
	size_t get_word_idx(size_t pos)
	{
		return (length) ? pos/u64_bit : 0;
	}
	/* Given position [0-n) find 64-bit word with this bit   */
	uint64_t *get_word(size_t pos) {
		if(!length)                    return &bits;
		else if(length > pos/u64_bit)  return &words[pos/u64_bit];
		else                           return nullptr;
	}
	/* Given position, given next word                       */
	uint64_t *get_next_word(size_t pos) {
		if(!length)                return nullptr;
		else {
			size_t next_word       = get_word_idx(pos) + 1;
			if(next_word < length) return &words[next_word];
			else                   return nullptr;
		}
	}
	/* Given a bit position [0-63) create a mask             */
	uint64_t wordmask(size_t bit) {
		return ((uint64_t)1 << (bit % u64_bit));
	}
	/* Given position[0-n), set/clear bit in that position   */
	void set(size_t bit, bool on) {
		size_t bitmap_size = length ? (length * u64_bit) : u64_bit;
		if(bit >= bitmap_size) return;
		uint64_t *word = get_word(bit);
		if(on)
			*word |= wordmask(bit);
		else
			*word &= ~wordmask(bit);
	}
	/* Bitmap class member variables                         */
    size_t length;
    union {
	    uint64_t bits;
	    uint64_t *words;
    };
};

#endif //_BITMAP_CPP_
