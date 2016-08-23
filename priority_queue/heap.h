#ifndef _HEAP_DS_
#define _HEAP_DS_
#include <stdio.h>
#include <stdlib.h>        /* atoi  */
#include <stdbool.h>       /* bool, true, false */
#include <ctype.h>         /* isspace */
#include <string.h>        /* memset */
#include <assert.h>        /* assert */
#include <limits.h>        /* UINT_MAX */
#include <malloc.h>        /* malloc, free */
#include <stdint.h>        /* uintptr_t */
#include "compiler_api.h"  /* likely, MAX, SWAP */
#include "bit_ops.h"       /* bit_align_up_nearest_pow2() */

/* Priority Queue implementation based on auto resizable pow-of-2 Heap.*
 * Heap Usage - Min/Max Heap can be toggled with compile time macro's  *
 * Use one-based array as the underlying DS to simplify calculations   *
 * If an application has a theta bound on the number of keys expected  *
 * this number can be passed on during init. By treating this info as  *
 * the lower bound on the numer of keys, we get:                       *
 * - Potential cache optimization for heap-root accesses.              *
 * - Avoid frequent heap resizing.                                     *
 * Based on Prof. Sedgewick's lecs - http://algs4.cs.princeton.edu/24pq*/

/* Key can be a user defined structure or data-type                    */
#ifndef KEY_TYPE
#define KEY_TYPE int
#endif
#ifndef LESS_CMP  /* For user-defined keys, define a custom comparator */
#define LESS_CMP(_prnt, _child) ((_prnt) < (_child))
#endif
#ifndef MORE_CMP  /* For user-defined keys, define a custom comparator */
#define MORE_CMP(_prnt, _child) ((_prnt) > (_child))
#endif
/* Use compile-time macro's for min and max heaps.                     */
#if defined(MAX_HEAP_IMPL) && defined(MIN_HEAP_IMPL)
#error "Error: Both Max Heap and Min Heap macro's specified\n"
#elif defined(MAX_HEAP_IMPL)
#define HEAP_TYPE_STR "MAX_HEAP"
/*For MAX-Heap's, define the Heap invariant break condition            */
#define CMP(_prnt,_child)  LESS_CMP((_prnt),(_child))
#elif defined(MIN_HEAP_IMPL)
#define HEAP_TYPE_STR "MIN_HEAP"
/*For MIN-Heap's, define the Heap invariant break condition            */
#define CMP(_prnt, _child) MORE_CMP((_prnt),(_child)) /*Heap invariant break*/
#else
#error "Error: Unknown heap type - Specify MAX_HEAP or MIN_HEAP\n"
#endif

/* If not specified by user, defined the resize ratios                */
#ifndef HEAP_USR_RESIZE_RATIO
#define HEAP_USR_RESIZE_RATIO (2)
#endif
/* With Resize ratio, define Heap grow and shrink ratios              *
 *     - Grow   = ratio*size.    Default, grow = 2 * size             *
 *     - Shrink = size/(2*ratio) Default, grow = 1/4 * size           */
#define HEAP_RESIZE_UP_RATIO   (HEAP_USR_RESIZE_RATIO)
#define HEAP_RESIZE_DOWN_RATIO (2 * HEAP_USR_RESIZE_RATIO)

/* Resize statistics                                                  */
typedef struct dy_stats
{
	unsigned resize_up_cnt;
	unsigned resize_down_cnt;
	unsigned resize_up_err_cnt;
	unsigned resize_down_err_cnt;
}dy_stats;

/* Heap statistics                                                    */
typedef struct my_heap_stats
{
	unsigned ins_cnt;
	unsigned del_cnt;
	dy_stats dy;
}heap_stats_t;

typedef struct my_heap
{
	heap_stats_t stats; /* Maintain heap usage statistics             */
	unsigned n;         /* Current number of elements in the Heap     */
	unsigned size;      /* Container size. If n = size-1, need resize */
	KEY_TYPE *keys;     /* Ptr to hold all keys (key-0 unused)        */
	unsigned min_size;  /* Avoid frequent resizing with min #keys     */
}heap_t;

/*----------------------Core Heap functionalities---------------------*/
/* Iteratively compare given key and its parent and swap if heap      *
 * invariant is violated                                              */
static inline void heap_swim(KEY_TYPE keys[], unsigned k)
{
	/* MaxHeap: if(k > 1 && a[k/2] < a[k]) */
	while(k > 1 && CMP(keys[k/2], keys[k])) {
		SWAP(keys[k/2], keys[k]);
		k = k/2;
	}		
}

/* Iteratively compare given key and its children and swap if heap    *
 * invariant is violated                                              */
static inline void heap_sink(KEY_TYPE keys[], unsigned n, unsigned k)
{
	while(2*k <= n) {
		int j = 2*k;
		if(j < n && CMP(keys[j], keys[j+1])) j++;
		if(!CMP(keys[k], keys[j]))           break;
		SWAP(keys[k], keys[j]);
		k = j;
	}
}

/*----------------------Internal Functions(Start)---------------------*/
/* Container size of the heap                                         */
static inline unsigned heap_size_impl(heap_t *hp) {return hp->size;}

/* Number of keys in the heap                                         */
static inline unsigned heap_count_impl(heap_t *hp) {return hp->n;}

static inline bool is_heap_empty_impl(heap_t *hp)
{
	return heap_count_impl(hp) == 0;
}

static inline bool is_heap_full_impl(heap_t *hp)
{
	return (heap_count_impl(hp) + 1 == heap_size_impl(hp));
}

/* Allocate the memory for heap keys immediately after the heap struct *
 * So, if user has a good estimate of capacity, resize will never have *
 * to be done and the 1st few heap keys are hopefully in the same      *
 * cacheline as the heap structure                                     */
static inline heap_t *heap_init_impl(unsigned init_capacity, unsigned min_size)
{
	heap_t *hp = malloc(sizeof(heap_t));
	if(init_capacity == 0 || init_capacity == 1) init_capacity = 2;
	if(min_size == 1) min_size = 2;
	if(init_capacity < min_size) init_capacity = min_size;
	if(hp) {
		memset(hp, 0, sizeof(heap_t));
		hp->keys = malloc(sizeof(KEY_TYPE[init_capacity]));
		if(hp->keys == NULL) {
			free(hp);
			return NULL;
		}
		memset(hp->keys, 0, sizeof(KEY_TYPE[init_capacity]));
		hp->size = init_capacity;
		if(min_size)
			hp->min_size = min_size;
	}
	return hp;
}

/* If Key's dynamic array has ben resized handle free accordingly     */
static inline void heap_destroy_impl(heap_t *hp)
{
	if(!hp) return;
	if(hp->stats.dy.resize_up_cnt || hp->stats.dy.resize_down_cnt)
		free(hp->keys);
	free(hp);
}

static inline bool heap_resize_impl(heap_t *hp, unsigned new_size)
{
	int i;
	KEY_TYPE *new_keys;
	if(new_size == 0)             new_size = 2;
	else if(new_size < hp->min_size) /* Do not resize below min size  */
		return true;
	assert(heap_size_impl(hp) >= heap_count_impl(hp));
	new_keys = malloc(sizeof(KEY_TYPE[new_size]));
	if(new_keys == NULL) return false;
	for(i = 1; i <= heap_count_impl(hp); i++)
		new_keys[i] = hp->keys[i];
	free(hp->keys);
	hp->keys = new_keys;
	hp->size = new_size;
	return true;
}

/* Validate if the subtree arr[1..k] is a valid max/min heap          */
static inline bool heap_validate_impl(heap_t *hp, int k)
{
	int left = 2*k, right = 2*k+1;
	if(k > hp->n) return true;
	if(left <= hp->n  && CMP(hp->keys[k], hp->keys[left])) return false;
	if(right <= hp->n && CMP(hp->keys[k], hp->keys[right])) return false;
	return heap_validate_impl(hp, left) && heap_validate_impl(hp, right);
}

static inline bool heap_heapify_impl(heap_t *hp, KEY_TYPE keys[], int len)
{
	int k;
	/* Sanity check the requested size increase first                 */
	if(is_heap_empty_impl(hp) == false || len + 1 >= heap_size_impl(hp))
		return false;
	memcpy(&hp->keys[hp->n+1], keys, sizeof(KEY_TYPE[len]));
	hp->stats.ins_cnt += len;
	hp->n += len;
	for(k = hp->n/2; k >= 1; k--)
		heap_sink(hp->keys, hp->n, k);
	assert(heap_validate_impl(hp, 1)); /* Assert Heap invariant       */
	return true;
}
/*-----------------------Internal Functions(End)----------------------*/
/*-------------------------API Functions(Start)-----------------------*/
heap_t *heap_init(unsigned init_cap, unsigned min_size)
{
	min_size = bit_align_up_nearest_pow2(min_size);
	return heap_init_impl(bit_align_up_nearest_pow2(init_cap+1), min_size);
}

void heap_destroy(heap_t *hp)           {return heap_destroy_impl(hp);}
unsigned heap_count(heap_t *hp)         {return heap_count_impl(hp);}
unsigned heap_size(heap_t *hp)          {return heap_size_impl(hp);}
bool is_heap_empty(heap_t *hp)          {return is_heap_empty_impl(hp);}
bool is_heap_full(heap_t *hp)           {return is_heap_full_impl(hp);}
bool heap_validate(heap_t *hp)          {return heap_validate_impl(hp, 1);}

bool heap_resize(heap_t *hp, unsigned new_size)
{
	if(new_size != hp->size * HEAP_RESIZE_UP_RATIO &&
	   new_size != hp->size / HEAP_RESIZE_DOWN_RATIO)
		 return false;
	else return heap_resize_impl(hp, new_size);
}

/* Inserts a new key into the correct level of the Heap.              *
 * Time Complexity = O(log n)                                         */
bool heap_insert(heap_t *hp, KEY_TYPE key)
{
	if(is_heap_full(hp)) {
		if(heap_resize(hp, hp->size * HEAP_RESIZE_UP_RATIO) == false){
			hp->stats.dy.resize_up_err_cnt++;
			return false;
		}
		hp->stats.dy.resize_up_cnt++;
	}
	/* Insert new key and percholate it up to maintain heap invariant */
	hp->keys[++hp->n] = key;
	heap_swim(hp->keys, hp->n);
	hp->stats.ins_cnt++;
	assert(heap_validate(hp)); /* Assert Heap invariant               */
	return true;
}

/* Retrieve the root-node of the Heap. This node can be the minimum or*
 * or maximum depending on the type of the heap (MIN-Heap or MAX-Heap)*
 * Time Complexity = O(1)                                             */
bool heap_peak_root(heap_t *hp, KEY_TYPE *key)
{
	if(key && is_heap_empty(hp) == false) {
		*key = hp->keys[1];
		return true;
	}
	return false;
}

/* Delete the root-node of the Heap and return it back                *
 * Time Complexity = O(log n)                                         */
bool heap_delete_root(heap_t *hp, KEY_TYPE *usr_key)
{
	if(is_heap_empty(hp)) return false;
	heap_peak_root(hp, usr_key);
	SWAP(hp->keys[hp->n], hp->keys[1]);
	hp->keys[hp->n--] = 0;
	heap_sink(hp->keys, hp->n, 1);
	if(heap_count(hp) + 1 == heap_size(hp) / HEAP_RESIZE_DOWN_RATIO)
	{
		if(heap_resize(hp, heap_size(hp)/
							HEAP_RESIZE_DOWN_RATIO) == false) {
			hp->stats.dy.resize_down_err_cnt++;
			return false;
		}
		hp->stats.dy.resize_down_cnt++;
	}
	hp->stats.del_cnt++;
	assert(heap_validate(hp)); /* Assert Heap invariant               */
	return true;	
}

/* Initialize the Heap from an array of keys. Follows a sink based    *
 * heap construction approach (start from 1 level above the leaves)   *
 * Time Complexity = O(n) (check Heap notes)                          */
bool heap_heapify(heap_t *hp, KEY_TYPE keys[], unsigned len) {
	if(is_heap_empty(hp) == false) {
		printf("Error: Heapify needs an empty heap\n");
		printf("Info: Empty heap or Use heap_insert() instead\n");
		return false;
	}
	/* Create sufficient space is available to insert the new elements*/
	if(len + 1 >= heap_size(hp)) {
		unsigned new_size = bit_align_up_nearest_pow2(len + 1);
		/* Sanity test the new size */
		if(new_size <= hp->size) return false;
		/* Note,call heap_resize_impl() to avoid validating new_size  */
		if(heap_resize_impl(hp, new_size) == false){
			hp->stats.dy.resize_up_err_cnt++;
			return false;
		}
		hp->stats.dy.resize_up_cnt++;
	}
	return heap_heapify_impl(hp, keys, len);
}

void heap_print(KEY_TYPE keys[], unsigned n)
{
	int k, level = 0;
	for(k = 1; k <= n; k++) {
		if(level != bit_floor_log2(k)){
			level = bit_floor_log2(k);
			printf("\n");
		}
		printf("%d ", keys[k]);	
	}
	printf("\n");
}

/* Sort algorithm based on heap-sort                                  *
 * Note: MAX_HEAP will cause last element to be the highest after sort*
 * Note: 0th index will be ignored                                    *
 * Time Complexity = O(n log n), Space Complexity = O(1)              */
void heap_sort(KEY_TYPE keys[], int n) {
	int k;
	/* First step is to create the heap = O(n) cost                   */
	for(k = n/2; k >= 1; k--)
		heap_sink(keys, n, k);
	/* Next, put each element in its respective place = O(n lg n)cost */
	while(n > 1) {
		SWAP(keys[1], keys[n]);
		n--;
		heap_sink(keys, n, 1);
	}
}

void heap_print_stats(heap_t *hp)
{
	heap_stats_t *st = &hp->stats;
	printf("Heap Usage Statistics:\n");
	printf("Heap Size             = %10u\t", heap_size(hp));
	printf("Heap Count            = %10u\n", heap_count(hp));
	printf("Insert Count          = %10u\t", st->ins_cnt);
	printf("Delete Count          = %10u\n", st->del_cnt);
	printf("Dy_ARR Size UP Count  = %10u\t", st->dy.resize_up_cnt);
	printf("Dy_ARR Size Down Count= %10u\n", st->dy.resize_down_cnt);
	if(st->dy.resize_up_err_cnt || st->dy.resize_down_err_cnt) {
		printf("Dy_ARR Size UP Err    = %10u\t", st->dy.resize_up_err_cnt);
		printf("Dy_ARR Size Down Err  = %10u\n", st->dy.resize_down_err_cnt);
	}
	/* Keep stats as read on clear                                    */
	memset(st, 0, sizeof(heap_stats_t));
}

/*--------------------------API Functions(End)------------------------*/
#endif //_HEAP_DS_
