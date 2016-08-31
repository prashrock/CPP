C++ Programs (Algo, DS)
===================
- This is a minimal C++ Library of Algorithms and Data Structures for fun and for practice. Implementations are not production ready (concise/clarity over performance/features)
- Headers only, most implementations are contained in respective headers.
- CI Status:
  
  | Branch Name       | Build Status      | Coverity Status             | Grok Access       |
  |:------------------|:------------------|:----------------------------|:------------------|
  | Master            | [![Build Status](https://travis-ci.org/prashrock/CPP.svg?branch=master)](https://travis-ci.org/prashrock/CPP) | [![Coverity Status](https://scan.coverity.com/projects/2883/badge.svg?flat=1)](https://scan.coverity.com/projects/prashrock-cpp) | [Grokbit](https://grokbit.com/prashrock/CPP/) |

----------------------------------------------------------------------------------------
Leetcode
--------------------------------------------
- A cataloged list of Leetcode solutions can be found [here](./leetcode/README.md)

----------------------------------------------------------------------------------------
Algo
--------------------------------------------
- Below are a list of algorithms categorized by topic. Refer to the per-directory Readme for more details:

  | Topic             | List of algorithms                                                                    |
  |:------------------|:--------------------------------------------------------------------------------------|
  | [Bit manipulation algorithms](./bit_ops/bit_ops.h) | Almost branchless and type safe implementations for: <br> - Population Count, Gray code, Parity Check, Bit reverse, Log2, etc. |
  | [Dynamic Programming](./dyn_prog) | - [Subset Sum](./dyn_prog/dyn_subset_sum.cc),  [Binary Knapsack](./dyn_prog/dyn_knapsack_01.cc) <br> - [Longest Common Subsequence](./dyn_prog/dyn_longest_common_subsequence.cc), [Longest Increasing Subsequence](./leetcode/algo_dp_longest_increasing_subsequence.cc) <br> - [Levenstein Minimum edit distance](./dyn_prog/dyn_str_min_edit_distance.cc) |
  | [String Related](./string/) | - [Substring Search](./string/substring.h) - [Brute Force](./string/substring.h#L52), [KMP](./string/substring.h#L138), [Boyer Moore](./string/substring.h#L174), [Rabin Karp (Monte Carlo approach)](./string/substring.h#L221) <br> - Base64 [Encode / Decode](./string/base64.h)  |
  | [Graph Algorithms](./graph/)| -[Shortest Path](./graph/graph_sssp.h) - [Dijkstra single source shortest path](./graph/graph_sssp.h)       |

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
  | **[Binary index tree/Fenwick Tree](./tree/binary_indexed_tree.h)** | Binary Index Tree implementation. Useful for O(log n) range sum operations.  |

----------------------------------------------------------------------------------------
Math
--------------------------------------------
- All implementations can be found in respective header files: 

  | Algo                      | Description                                     |
  |:--------------------------|:------------------------------------------------|
  | **[Shuffle](./math/math_shuffle.h)** | Knuth Shuffle implementation         |
  | **[Factorial](./math/math_fact.h)**  | [Iterative factorial](./math/math_fact.h#15) [Large factorial(bigger than uint64_t)](./math/math_fact.h#26) [Number of Zeros in factorial](./math/math_fact.h#40)          |

----------------------------------------------------------------------------------------
