String Related Algorithms
===================

----------------------------------------------------------------------------------------
Substring Search
--------------------------------------------
- Basic implementation of different [substring search algorithms](./substring.h):

  | Algorithm           | Explanation                             | #Cycles per iteration   | Time taken for 1M iteartions (seconds) |
  |:-------------------:|:----------------------------------------|:------------------------|:---------------------------------------|
  | STL Find            |                                         | 166K cycles | 6.25 s |
  | [Brute Force](https://github.com/prashrock/CPP/blob/master/string/substring.h#L26) | For every position in the text consider it as a starting point and check for match (2 loops) |  164K cycles | 6.17s |
  | [Brute Force Optimized](https://github.com/prashrock/CPP/blob/master/string/substring.h#L52) | Use a single loop and backtrack text and pattern when there is a mismatch   | 151K cycles | 5.68s  |
  | [KMP Algo](https://github.com/prashrock/CPP/blob/master/string/substring.h#L138) | - Uses a Discrete Finite State Machine (DFA) to create a prefix table for searching (longest prefix which is also a suffix). <br> - Best for **long text and pattern with short radix** (e.g. DNA sequence)  | 156K cycles | 5.86s |
  | [Booyer Moore](https://github.com/prashrock/CPP/blob/master/string/substring.h#L174) | - Scan pattern characters from right to left and skip as many as M characters whenever there is a mismatch. <br> - Best for longer patterns with a bigger radix. | 212K cycles | 7.96s |
  | [Rabin Karp (Monte-Carlo Approach)](https://github.com/prashrock/CPP/blob/master/string/substring.h#L221) | - Use a rolling hash to compare the pattern hash for each position in the text. <br> - Monte-Carlo approach tolerates hash false-positives (do not manually check substring with text) | 378K cycles | 14.19 s |

- Note:
  - Micro-benchmarks were measured on an Ubuntu 16.04 VM running on Intel(R) Xeon(R) CPU X5650 @ 2.67GHz with GCC 5.4.0 with C++11 and OPT flags(-O3 -Os, -march=native)
  - The above data was obtained with [1M randomized test strings](./substr_match.cc) with a text size of 100K characters and a pattern size of 100.

----------------------------------------------------------------------------------------
