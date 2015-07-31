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
		uint64_t *word = get_word(pos); /*  Get current word */
		/* If current pos is not valid, nothing to do        */
		if(!word) return false; 
		bool ret = false;
		/* Get the word index for current position_idx       *
		 * To handle 64-bit bitmap case = do-while construct */
		size_t word_idx = get_word_idx(pos);
		/* Mask with only 1's in left of pos in current_word *
		 * Example: 101100 -> 111000                         */
		uint64_t mask = clear_lsb(~(wordmask(pos) - 1));
		/* Do-While handles case single 64B bitmap case      */
		do
		{
			/* Check if any remaining bits in current word   */
			uint64_t remaining = *word & mask;
			if(!remaining) {
				word_idx++; /* Move to next word             */
				mask = -1;  /*Going to next word, full bitmap*/
				word = &words[word_idx];
			}
			else {
				ret = true; /* We found the next set bit pos */
				next_pos = word_idx * u64_bit
					+ get_lsb_word_pos(remaining);
				break;
			}
		} while(length && word_idx < length);
		return ret;
	}
	/* Set Bitmap at specified position                      *
	 * @param pos - position idx. Can be zero/one based      */
	void set(size_t pos)   {set(pos, true);}
	/* Clear/Reset Bitmap at specified position              *
 	 * @param pos - position idx. Can be zero/one based      */
	void reset(size_t pos) {set(pos, false);}
	
private:
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
