C++ Programs (Algo, DS)
===================

- C++ programs (Algo, DS)
- Note, implementations aim for clarity rather than optimal performance.
  - Some sections may exhibits poor cache locality, perform more comparisons/swaps than necessary.
  - Unless stated otherwise, none of the DS/Algo implementations are MT/Async safe.

----------------------------------------------------------------------------------------
Algo - Dynamic Programming
--------------------------------------------
- Each program in [Dynamic Programming](./dyn_prog) has a brute-force and DP implementation along with a randomized test vector:
|#  | Name                    | Purpose                                                   |
|:--|:-----------------------:|:----------------------------------------------------------|
|1. |  [Subset Sum](./dyn_prog/dyn_subset_sum.cc)  | Given a set of integers and a target sum, find out if there is a subset whose sum equals to the target sum.                       | 
|2. |  [Binary Knapsack](./dyn_prog/dyn_knapsack_01.cc) | Given a bag of items (each item has a weight and value) and a target weight, select items with following 2 restrictions: <br> - Total weight is less than or equal to max weight <br> - Total value is maximized          |

----------------------------------------------------------------------------------------