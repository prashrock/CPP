#ifndef _BITMAP_CPP_
#define _BITMAP_CPP_

#include <algorithm>           /* std::max    */
#include <cstring>             /* size_t      */
#include <cstdint>             /* uint64_t    */
#include <climits>             /* CHAR_BIT    */
#include <cerrno>              /* CHAR_BIT    */

static const int u64_bit = (CHAR_BIT * sizeof(uint64_t));

/* Constant size bitmap. Provides API for     *
 * get/set into bitmap.                       */
class bitmap
{
public:
	/* Create bitmap based on max capacity    */
	void init(size_t capacity){
		length = 0;
		if(capacity >= u64_bit) {
			length = (capacity / u64_bit) + 1;
			words  = new uint64_t[length];
		}
		clear();
	}
	/* Reset the bitmap                       */
	void clear() {
		if(!length) bits = 0;
		else memset(words, 0, length * sizeof(uint64_t));
	}
	/* Constructor for the bitmap class       */
    bitmap(size_t capacity) : length(0), bits(0) {
		init(capacity);
	}
	/* Destructor for the bitmap class        */
	~bitmap() {
		if(length && words) delete[] words;
	}
	/* Bitmap class get API                   */
	bool get(size_t bit) {
		size_t bitmap_size = length ? (length * u64_bit) : u64_bit;
		if(bit >= bitmap_size) return false;
		uint64_t *word = get_word(bit);
		return ((*word & wordmask(bit)) != 0);
	}
	void set(size_t bit)   {set(bit, true);}
	void reset(size_t bit) {set(bit, false);}

private:
	/* Given position [0-n) find 64-bit word with this bit */
	uint64_t *get_word(size_t bit) {
		return (length) ? &words[bit/u64_bit] : &bits;
	}
	/* Given a bit position [0-63) create a mask           */
	uint64_t wordmask(size_t bit) {
		return ((uint64_t)1 << (bit % u64_bit));
	}
	/* Given position[0-n), set/clear bit in that position */
	void set(size_t bit, bool on) {
		size_t bitmap_size = length ? (length * u64_bit) : u64_bit;
		if(bit >= bitmap_size) return;
		uint64_t *word = get_word(bit);
		if(on)
			*word |= wordmask(bit);
		else
			*word &= ~wordmask(bit);
	}
	/* Bitmap class member variables                       */
    size_t length;
    union {
	    uint64_t bits;
	    uint64_t *words;
    };
};

#endif //_BITMAP_CPP_
