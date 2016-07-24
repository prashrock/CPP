
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
|1. |  [Subset Sum](./dyn_prog/dyn_subset_sum.cc)  | Given a set of integers and a target sum, find out if there is a subset whose sum equals to the target sum.                       | 
|2. |  [Binary Knapsack](./dyn_prog/dyn_knapsack_01.cc) | Given a bag of items (each item has a weight and value) and a target weight, select items with following 2 restrictions: <br> - Total weight is less than or equal to max weight <br> - Total value is maximized  |
|3. |  [Longest Common Subsequence](./dyn_prog/dyn_longest_common_subsequence.cc) | - Given two sequences (chars/numbers/etc) find the length of longest common subsequence (subsequence is a sequence that appears in same relative order but not necessarily contiguous). <br> - This is similar to [Longest Increasing Subsequence](./leetcode/algo_dp_longest_increasing_subsequence.cc) which can be implemented in O(n lg n) time complexity with Patience sort.       |
|4. |  [Levenstein Minimum edit distance](./dyn_prog/dyn_str_min_edit_distance.cc) | Given two strings, determine minimum number of operations to change 1 string to the other (add, del, sub). |

----------------------------------------------------------------------------------------
