C++ Programs (Algo, DS)
===================
- Note, each implementation aims for clarity (for quick reference) rather than optimal performance.
  - Some programs may exhibit poor cache locality, perform more comparisons/swaps than necessary.
  - Unless stated otherwise, implementations are NOT MT/Async safe.
- Any component can be built individually by issuing "make" in the respective directory. Continuous Integration status:
| Branch Name       | Build Status      | Coverity Status             | Grok Access       |
|:------------------|:------------------|:----------------------------|:------------------|
| Master            | [![Build Status](https://travis-ci.org/prashrock/CPP.svg?branch=master)](https://travis-ci.org/prashrock/CPP) | [![Coverity Status](https://scan.coverity.com/projects/2883/badge.svg?flat=1)](https://scan.coverity.com/projects/prashrock-cpp) | [Grokbit](https://grokbit.com/prashrock/CPP/) |

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
###Bit operations###
- **Simple resizable [Bitmap implementation](./bit_ops/bitmap.h)** implemented on STL vectors.
- Almost branchless and type safe [Bit manipulation algorithms](./bit_ops/bit_ops.h):
  - Includes implementation for Population Count, Gray code, Parity Check, Bit reverse, Log2, etc.
  
###LRU###
- STL Based O(1) [LRU Cache implementation](./lru/lru.h) in under 200 lines. Containers used:
  - List to maintain LRU keys in least recently used order (oldest element first)
  - Unordered Map for O(1) LRU Key Lookup. In addition to storing the value, Map also stores the key's pointer in List (for direct access during age refresh).

###Binary Tree###
- Binary Tree implementation

----------------------------------------------------------------------------------------
Math
--------------------------------------------
  | Algo                      | Description                                     |
  |:--------------------------|:------------------------------------------------|
  | **[Shuffle](./math/math_shuffle.h)** | Knuth Shuffle implementation         |

----------------------------------------------------------------------------------------
