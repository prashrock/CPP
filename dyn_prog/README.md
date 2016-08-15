Dynamic Programming
===================

----------------------------------------------------------------------------------------
Implementations
--------------------------------------------
- Each [Dynamic Programming](./) solution has a brute-force and DP implementation.
- Most programs include a backtrack approach to get the optimum solution along with a randomized test vector.

|#  | Name       | Purpose                                      |
|:--|:-----------|:---------------------------------------------|
|1. |  [Subset Sum](./dyn_subset_sum.cc)  | Given a set of integers and a target sum, find out if there is a subset whose sum equals to the target sum.                                                          | 
|2. |  [Binary Knapsack](./dyn_knapsack_01.cc) | Given a bag of items (each item has a weight and value) and a target weight, select items with following 2 restrictions: <br> - Total weight is less than or equal to max weight <br> - Total value is maximized  |
|3. |  [Longest Common Subsequence](./dyn_longest_common_subsequence.cc)  | - Given two sequences (chars/numbers/etc) find the longest common subsequence (subsequence = sequence that appears in same relative order but not necessarily contiguous). <br> - This is similar to [Longest Increasing Subsequence](./leetcode/algo_dp_longest_increasing_subsequence.cc) whose length can be calulated in O(n lg n) time complexity with Patience sort.  <br> - For contiguous length (sub-array instead of subsequence) refer to [Maximum Sum in Subarray(Leetcode)](./leetcode/algo_dp_maximum_sum_product_subarray.cc)            |
|4. |  [Levenstein Minimum edit distance](./dyn_str_min_edit_distance.cc) | Given two strings, determine minimum number of operations to change 1 string to the other (add, del, sub).                        |

----------------------------------------------------------------------------------------






