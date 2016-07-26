
C++ Programs (Algo, DS)
===================
- Note, each implementation aims for clarity (for quick reference) rather than optimal performance.
  - Some programs may exhibit poor cache locality, perform more comparisons/swaps than necessary.
  - Unless stated otherwise, implementations are NOT MT/Async safe.
  
Algo - Dynamic Programming
--------------------------------------------
- Each program in [Dynamic Programming](./dyn_prog) has a brute-force and DP implementation along with a randomized test vector

|#  | Name       | Purpose                                      |
|:--|:-----------|:---------------------------------------------|
|1. |  [Subset Sum](./dyn_prog/dyn_subset_sum.cc)  | Given a set of integers and a target sum, find out if there is a subset whose sum equals to the target sum.                                                          | 
|2. |  [Binary Knapsack](./dyn_prog/dyn_knapsack_01.cc) | Given a bag of items (each item has a weight and value) and a target weight, select items with following 2 restrictions: <br> - Total weight is less than or equal to max weight <br> - Total value is maximized  |
|3. |  [Longest Common Subsequence](./dyn_prog/dyn_longest_common_subsequence.cc)  | - Given two sequences (chars/numbers/etc) find the longest common subsequence (subsequence = sequence that appears in same relative order but not necessarily contiguous). <br> - This is similar to [Longest Increasing Subsequence](./leetcode/algo_dp_longest_increasing_subsequence.cc) whose length can be calulated in O(n lg n) time complexity with Patience sort.  <br> - For contiguous length (sub-array instead of subsequence) refer to [Maximum Sum in Subarray(Leetcode)](./leetcode/algo_dp_maximum_sum_product_subarray.cc)            |
|4. |  [Levenstein Minimum edit distance](./dyn_prog/dyn_str_min_edit_distance.cc) | Given two strings, determine minimum number of operations to change 1 string to the other (add, del, sub).                        |

----------------------------------------------------------------------------------------
Data Structures
--------------------------------------------

###Bitmap###
- Simple resizable [Bitmap implementation](./bit_ops/bitmap.h) in under 200 lines using STL Vector as underlying container.
- Supports bitmap resize and get_next_set_bit operation which are not available in STL Bitset.
- Comparable in performance to STL Bitset, simple microbenchmark with 1 Million get/set/clear operations (code-included) shows:

  | Measure                           |  STL Bitset | [Bitmap](./bit_ops/bitmap.h)      |
  |:----------------------------------|:------------|:------------|
  | Total time taken (1 million loop) |  71 ms      | 60 ms       | 
  | Avg #Cycles per loop              |  189 cycles | 162 cycles  |
  - Note: micro-benchmarks were measured on an Ubuntu 16.04 VM running on Intel(R) Xeon(R) CPU X5650 @ 2.67GHz.
- Refer to [C bit_ops header file](../C/bit_ops/bit_ops.h) for BIT manipulation functions (e.g., bit_reverse, bit_propagate_ones_to_right, bit_get_msb, bit_get_lsb, bit_population_cnt, bit_parity, bit_num_leading_zeros, bit_num_trailing_zeros, bit_snoob, bit_log2 (floor, ceil), bit_is_pow2, bit_in_place_permutate)

###LRU###
- STL Based O(1) [LRU Cache implementation](./lru/lru.h) in under 200 lines. Containers used:
  - List to maintain LRU keys in least recently used order (oldest element first)
  - Unordered Map for O(1) LRU Key Lookup. In addition to storing the value, Map also stores the key's pointer in List (for direct access during age refresh).

###Binary Tree###
- Binary Tree implementation

----------------------------------------------------------------------------------------
