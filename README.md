C++ Programs (Algo, DS)
===================
- Note, this project is mainly for learning purposes. Most implementation aim for clarity rather than optimal performance.
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
  | [Bit manipulation algorithms](./bit_ops/bit_ops.h) | Almost branchless and type safe implementations for: <br> - Population Count, Gray code, Parity Check, Bit reverse, Log2, etc. |
  | [Dynamic Programming](./dyn_prog) | - [Subset Sum](./dyn_prog/dyn_subset_sum.cc),  [Binary Knapsack](./dyn_prog/dyn_knapsack_01.cc) <br> - [Longest Common Subsequence](./dyn_prog/dyn_longest_common_subsequence.cc), [Longest Increasing Subsequence](./leetcode/algo_dp_longest_increasing_subsequence.cc) <br> - [Levenstein Minimum edit distance](./dyn_prog/dyn_str_min_edit_distance.cc) |
  | [String Related](./string/) | - [Substring Search](./string/substring.h) - [Brute Force](./string/substring.h#L52), [KMP](./string/substring.h#L138), [Boyer Moore](./string/substring.h#L173), [Rabin Karp (Monte Carlo approach)](./string/substring.h#L220) <br> - Base64 [Encode / Decode](./string/base64.h) |

----------------------------------------------------------------------------------------
Utils and Micro-Benchmarks
--------------------------------------------
- Time and #cycle measurement API.
- Micro-benchmarks:
  - Measure cost of [gettid system-call](./micro_benchmarks/bench_sys_call.cc) which does not have [glibc vDSO wrapper](http://man7.org/linux/man-pages/man2/gettid.2.html)
  - Compare [rdtsc, clock_gettime and gettimeofday](./micro_benchmarks/bench_gettime.cc)
  - Compare [basic spinlock with pthread_lock](./micro_benchmarks/bench_lock.cc)

----------------------------------------------------------------------------------------
Data Structures
--------------------------------------------
- Below are a list of data structure implementations. Refer to the per-directory Readme for more details:
 
  | Data Structure    | Implementation Details                                                                     |
  |:------------------|:-------------------------------------------------------------------------------------------|
  | **[Bitmap](./bit_ops/bitmap.h)** | Simple, template based, resizable bitmap implementation using STL Vector    |
  | **[LRU Cache](./lru/lru.h)**     | O(1) Least Recently Used Cache implementation (STL Unordered Map + List)    |
  | **[Binary Tree](./tree/binary_tree.h)** | Binary Tree implementation with below [tree traversal operations](./tree/binary_tree_traversal.h) <br> - BFS, Pre/In/Post DFS Order, Spiral Order, Bottom-up Order.    |

----------------------------------------------------------------------------------------
Math
--------------------------------------------
- All implementations can be found in respective header files: 

  | Algo                      | Description                                     |
  |:--------------------------|:------------------------------------------------|
  | **[Shuffle](./math/math_shuffle.h)** | Knuth Shuffle implementation         |

----------------------------------------------------------------------------------------
