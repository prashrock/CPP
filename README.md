C++ Programs (Algo, DS)
===================
- Note, each implementation aims for clarity (for quick reference) rather than optimal performance.
  - Some programs may exhibit poor cache locality, perform more comparisons/swaps than necessary.
  - Unless stated otherwise, implementations are NOT MT/Async safe.
- Any component can be built individually by issuing "make" in the respective directory. Continuous Integration status:
  
  | Branch Name       | Build Status      | Coverity Status             | Grok Access       |
  |:------------------|:------------------|:----------------------------|:------------------|
  | Master            | [![Build Status](https://travis-ci.org/prashrock/CPP.svg?branch=master)](https://travis-ci.org/prashrock/CPP) | [![Coverity Status](https://scan.coverity.com/projects/2883/badge.svg?flat=1)](https://scan.coverity.com/projects/prashrock-cpp) | [Grokbit](https://grokbit.com/prashrock/CPP/) |

Algo
--------------------------------------------
- Below are a list of algorithms categorized by topic. Refer to the per-directory Readme for more details:

  | Topic             | List of algorithms                                                                    |
  |:------------------|:--------------------------------------------------------------------------------------|
  | [Dynamic Programming](./dyn_prog) | [Subset Sum](./dyn_prog/dyn_subset_sum.cc),  [Binary Knapsack](./dyn_prog/dyn_knapsack_01.cc), [Longest Common Subsequence](./dyn_prog/dyn_longest_common_subsequence.cc), [Longest Increasing Subsequence](./leetcode/algo_dp_longest_increasing_subsequence.cc), [Levenstein Minimum edit distance](./dyn_prog/dyn_str_min_edit_distance.cc) |
  | [Substring Search](./string/substring.h) | [Brute Force](./string/substring.h#L52), [KMP](./string/substring.h#L138), [Boyer Moore](./string/substring.h#L173), [Rabin Karp (Monte Carlo approach)](./string/substring.h#L220) |

----------------------------------------------------------------------------------------
Data Structures
--------------------------------------------
###Bit operations###
- **Simple resizable [Bitmap implementation](./bit_ops/bitmap.h)** implemented on STL vectors.
- Almost branchless and type safe [Bit manipulation algorithms](./bit_ops/bit_ops.h):
  - Includes implementation for Population Count, Gray code, Parity Check, Bit reverse, Log2, etc.
  
###LRU###
- STL Based O(1) [LRU Cache implementation](./lru/lru.h) in under 200 lines.

###Binary Tree###
- Binary Tree implementation

----------------------------------------------------------------------------------------
Math
--------------------------------------------
- All implementations can be found in respective header files: 

  | Algo                      | Description                                     |
  |:--------------------------|:------------------------------------------------|
  | **[Shuffle](./math/math_shuffle.h)** | Knuth Shuffle implementation         |

----------------------------------------------------------------------------------------
