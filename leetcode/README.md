Leetcode Programs
===================
This is a collection of my [117 Leetcode solutions](./) with comments. Most programs have test-cases and a few even have performance benchmarks. I've tried to put each problem into a broad category for quick reference.

Note: Solutions inspired from Leetcode discussions have explicit comments and links.

Algorithm based
--------------------------------------------
###Backtracking###
|#  | Difficulty | Problem and Solution                         |
|:--|:-----------|:---------------------------------------------|
|1. | Medium     | [Number of 2D Islands](https://leetcode.com/problems/number-of-islands/) ([solution](./algo_backtrack_2D_number_of_islands.cc))                                                                                |
|2. | Medium     | [Flip Game II](https://leetcode.com/problems/flip-game-ii/) ([solution](./algo_backtrack_flipgame2.cc))            |
|3. | Medium     | [Subsets](https://leetcode.com/problems/subsets/) ([solution](./algo_backtrack_subsets.cc))                        |
|4. | Medium     | [Word Search](https://leetcode.com/problems/word-search/) ([solution](./algo_backtrack_word_search.cc))            |

###Divide and Conquer###
|#  | Difficulty | Problem and Solution                         |
|:--|:-----------|:---------------------------------------------|
|1. | Easy       | Find Duplicate([solution](./algo_dc_elem_appear_once_in_sorted_arr.cc))                                            |
|2. | Medium     | [Equal Range](https://leetcode.com/problems/search-for-a-range/) ([solution](./algo_dc_equal_range.cc))            |
|3. | Medium     | [H-Index](https://leetcode.com/problems/h-index/) ([solution](./algo_dc_h_index.cc))           |
|3. | Medium     | [Guess number higher or lower](https://leetcode.com/problems/guess-number-higher-or-lower/) ([solution](./algo_dc_guess_number.cc))       |
|5. | Medium     | Search a 2D Matrix [I](https://leetcode.com/problems/search-a-2d-matrix/),  [II](https://leetcode.com/problems/search-a-2d-matrix-ii/) ([solution](./algo_dc_search_2D_matrix_i_ii.cc))                           |
|6. | Medium     | [Search insert position](https://leetcode.com/problems/search-insert-position/) ([solution](./algo_dc_search_insert_position.cc))                                      |7. | Hard       | [Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/) <br> [Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/) ([solution](./algo_dc_rotated_array_search.cc))  |                         |

###Design###
|#  | Difficulty | Problem and Solution                         |
|:--|:-----------|:---------------------------------------------|
|1. | Easy       | [Moving Average from Data Stream](https://leetcode.com/problems/moving-average-from-data-stream/) ([soln](./algo_design_moving_average.cc))   |
|2. | Medium     | [Hit counter](https://leetcode.com/problems/design-hit-counter/) ([solution](./algo_design_hit_counter.cc))                                   |

###Dynamic Programming###
|#  | Difficulty | Problem and Solution                         |
|:--|:-----------|:---------------------------------------------|
|1. | Easy       | [House Robber](https://leetcode.com/problems/house-robber/) ([solution](./algo_dp_easy_house_robber.cc))           |
|2. | Easy       | [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) ([solution](./algo_dp_number_of_1_2_steps.cc))   |
|3. | Medium     | [Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/) ([solution](./algo_dp_longest_increasing_subsequence.cc))    |
|4. | Medium     | [Maximum Subarray Sum](https://leetcode.com/problems/maximum-subarray/) ([solution](./algo_dp_maximum_sum_product_subarray.cc)) <br> [Maximum Subarray Product](https://leetcode.com/problems/maximum-product-subarray/) ([solution](./algo_dp_maximum_sum_product_subarray.cc))                                                   |
|5. | Medium     | [Paint House](https://leetcode.com/problems/paint-house/) ([solution](./algo_dp_medium_paint_house.cc))            |
|6. | Medium     | [Perfect Squares](https://leetcode.com/problems/perfect-squares/) ([solution](./algo_dp_perfect_squares.cc))       |
|7. | Medium     | [Structurally Unique BST](https://leetcode.com/problems/unique-binary-search-trees/) ([solution](./algo_dp_unique_binary_search_trees.cc))         |

###Sort###
|#  | Difficulty | Problem and Solution                         |
|:--|:-----------|:---------------------------------------------|
|1. | Easy       | [Meeting Rooms](https://leetcode.com/problems/meeting-rooms/) ([solution](./algo_sort_meeting_rooms.cc))           |
|2. | Medium     | [Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii/) ([solution](./algo_sort_meeting_rooms_ii.cc))  |
|3. | Medium     | Merge Overlapping Intervals ([solution](./algo_sort_merge_overlapping_intervals.cc))                               |
|4. | Medium     | [Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/) ([solution](./algo_sort_quick_select.cc))                            |
|5. | Hard       | [Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/) ([solution](./algo_sort_num_smaller_elements_in_right.cc))   |

###Greedy###
|#  | Difficulty | Problem and Solution                         |
|:--|:-----------|:---------------------------------------------|
|1. | Hard       | [Candy - Local Minima counter](https://leetcode.com/problems/candy/) ([solution](./algo_greedy_local_minimum_candy.cc)) | |

----------------------------------------------------------------------------------------
Data Structure based
--------------------------------------------
###Graph###
|#  | Difficulty | Problem and Solution                          |
|:--|:-----------|:---------------------------------------------|
|1. | Medium     | [Course Schedule](https://leetcode.com/problems/course-schedule/) ([solution](./ds_graph_loop_course_schedule.cc)) |
|2. | Medium     | [Course Schedule II](https://leetcode.com/problems/course-schedule-ii/) ([solution](./ds_graph_loop_course_schedule_ii.cc))                                                                                   |
|3. | Medium     | [Walls and Gates](https://leetcode.com/problems/walls-and-gates/) ([solution](./ds_graph_2D_walls_and_gates.cc))   |
|4. | Medium     | [Word Break](https://leetcode.com/problems/word-break/) ([solution](./ds_graph_word_break.cc))   |

###LRU###
|#  | Difficulty | Problem and Solution                          |
|:--|:-----------|:---------------------------------------------|
|1. | Hard       | [LRU Cache](https://leetcode.com/problems/lru-cache/) ([solution](./ds_lru_cache.cc))        |

###Hash###
|#  | Difficulty | Problem and Solution                          |
|:--|:-----------|:---------------------------------------------|
|1. | Hard       | [Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/) ([solution](./ds_hash_longest_consecutive_seq.cc))  |
|2. | Hard       | [O(1) Insert/Del/Get_Random](https://leetcode.com/problems/insert-delete-getrandom-o1/) ([solution](./ds_hash_ins_del_get_random.cc))  |

###Heap###
|#  | Difficulty | Problem and Solution                         |
|:--|:-----------|:---------------------------------------------|
|1. | Medium     | [Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/) ([solution](./ds_heap_top_k_frequent_elements.cc))      |
|2. | Hard       | [Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/) ([solution](./ds_heap_find_median_in_stream.cc))                                                                                           |

###Linked List###
|#  | Difficulty | Problem and Solution                          |
|:--|:-----------|:----------------------------------------------|
|1. | Easy       |  [Remove Linked-List Elements](https://leetcode.com/problems/remove-linked-list-elements/) ([solution](./ds_linkedlist_delete_val.cc))   |
|2. | Easy       |  [Delete Node in Linked-List](https://leetcode.com/problems/delete-node-in-a-linked-list/) ([solution](./ds_linkedlist_delete_cur_node.cc))                                      |
|3. | Easy       |  [Merge two sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/) ([solution](./ds_linkedlist_merge_two_sorted_lists.cc)) |
|4. | Medium     | [Reverse Linked-List](https://leetcode.com/problems/reverse-linked-list/) <br> [Reverse Linked-List range](https://leetcode.com/problems/reverse-linked-list-ii/) ([solution](./ds_linkedlist_reverse.cc)) |
|5. | Medium     | [Add Two Numbers](https://leetcode.com/problems/add-two-numbers/) ([solution](./ds_linkedlist_add_two_nums.cc))    |
|6. | Medium     | [Rotate List](https://leetcode.com/problems/rotate-list/) ([solution](./ds_linkedlist_rotate_list.cc))             |
|7. | Medium     | [Plus One](https://leetcode.com/problems/plus-one-linked-list/) ([solution](./ds_linkedlist_plus_one.cc))          |
|8. | Hard       | [Copy List with Random Pointer](https://leetcode.com/problems/copy-list-with-random-pointer/) ([solution](./ds_linkedlist_copy_with_random_pointer.cc))                                                                             |


###List###
|#  | Difficulty | Problem and Solution                          |
|:--|:-----------|:---------------------------------------------|
|1. | Easy       | [Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/) ([solution](./ds_list_easy_remove_duplicate_number.cc))                                                                               |
|2. | Medium     | [Find the Celebrity](https://leetcode.com/problems/find-the-celebrity/) ([solution](./ds_list_find_the_celebrity.cc))                                                                                         |
|3. | Medium     | [Missing Number](https://leetcode.com/problems/missing-number/) ([solution](./ds_list_missing_number.cc))          |
|4. | Medium     | [Missing Ranges](https://leetcode.com/problems/missing-ranges/) ([solution](./ds_list_missing_ranges.cc))          |
|5. | Medium     | [Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/) ([solution](./ds_list_product_of_array_except_self.cc))                                                                               |
|6. | Medium     | Range Sum Query [Immutable](https://leetcode.com/problems/range-sum-query-immutable/) [Mutable](https://leetcode.com/problems/range-sum-query-mutable/) ([solution](./ds_list_range_sum_query.cc))                          |
|7. | Medium     | Remove Duplicates from Sorted Array [I](https://leetcode.com/problems/remove-duplicates-from-sorted-array/) [II](https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/) ([solution](./ds_list_remove_duplicates_sorted_i_ii.cc))  |
|8. | Medium     | [Super Ugly Number](https://leetcode.com/problems/super-ugly-number/)  ([soln](./ds_list_super_ugly_numbers.cc))   |
|9. | Medium     | [Sub-array Range addition](https://leetcode.com/problems/range-addition/) ([solution](./ds_list_range_addition.cc))                                  |
|10.| Medium     | [ZigZag iterator](https://leetcode.com/problems/zigzag-iterator/) ([solution](./ds_list_zigzag_iterator.cc))       |
|11.| Hard       | [Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/) ([solution](./ds_list_duplicate_number.cc))      |
|12.| Hard       | [Merge Sorted Array](https://leetcode.com/problems/merge-sorted-array/) ([solution](./ds_list_merge_sorted_arrays.cc)) <br> [Merge K Sorted Array](https://leetcode.com/problems/merge-k-sorted-lists/) ([solution](./ds_list_merge_k_sorted_lists.cc))      |

###Stack###
|#  | Difficulty | Problem and Solution                          |
|:--|:-----------|:---------------------------------------------|
|1. | Easy      | [Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/) <br> [Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/)  ([solution](./ds_stack_using_queue.cc))                   |
|2. | Easy       | [Valid Parantheses](https://leetcode.com/problems/valid-parentheses/) ([solution](./ds_stack_valid_parantheses.cc))|
|3. | Medium     | [Reverse Polish Notation](https://leetcode.com/problems/evaluate-reverse-polish-notation/)  ([solution](./ds_stack_math_reverse_polish_notation.cc))                                                                              |

###String###
|#  | Difficulty | Problem and Solution                          |
|:--|:-----------|:---------------------------------------------|
|1. | Easy       | [Add Binary](https://leetcode.com/problems/add-binary/)  ([solution](./ds_string_easy_add_binary.cc))                                                      |
|2. | Easy       | [Valid Palindrome](https://leetcode.com/problems/valid-palindrome/)  ([solution](./ds_string_easy_valid_palindrome.cc))                                    |
|3. | Easy       | [Isomorphic Strings](https://leetcode.com/problems/isomorphic-strings/)  ([solution](./ds_string_isomorphic.cc))                                           |
|4. | Easy       | [Bijection Check Word Pattern](https://leetcode.com/problems/word-pattern/)  ([solution](./ds_string_word_pattern.cc))                                     |
|5. | Easy       | [Palindrome Permutation](https://leetcode.com/problems/palindrome-permutation/)  ([solution](./ds_string_palindromic_permutation_i_ii.cc))                 |
|6. | Easy       | [atoi](https://leetcode.com/problems/string-to-integer-atoi/)  ([solution](./ds_string_atoi.cc))                                                           |
|7. | Easy       | [ZigZag Converter](https://leetcode.com/problems/zigzag-conversion/)  ([solution](./ds_string_zigzag_conversion.cc))                                       |
|8. | Medium     | [Encode and Decode Strings](https://leetcode.com/problems/encode-and-decode-strings/)  ([solution](./ds_string_encode_decode.cc))                          |
|9. | Medium     | [Integer to Roman](https://leetcode.com/problems/integer-to-roman/)  ([solution](./ds_string_int_to_roman_numerals.cc))                                    |
|10.| Medium     | [Multiply Strings](https://leetcode.com/problems/multiply-strings/)    ([soln](./ds_string_multiply_strings.cc))                                           |
|11.| Medium     | [One Edit Distance](https://leetcode.com/problems/one-edit-distance/)    ([solution](./ds_string_one_edit_distance.cc))                                    |
|12.| Medium     | [Reverse String](https://leetcode.com/problems/reverse-string/) <br> [Reverse vowels of string](https://leetcode.com/problems/reverse-vowels-of-a-string/) <br>  [Reverse words in string](https://leetcode.com/problems/reverse-words-in-a-string/)    ([solution](./ds_string_reverse_words.cc))                                                     |
|13.| Hard       | [Is Strobogrammatic Number](https://leetcode.com/problems/strobogrammatic-number/) <br> [Find Strobogrammatic Numbers of length n](https://leetcode.com/problems/strobogrammatic-number-ii/) <br> [Find Strobogrammatic Numbers within range](https://leetcode.com/problems/strobogrammatic-number-iii/)  ([solution](./ds_string_strobogrammatic_num_i_ii_iii.cc)) |
|14.| Hard       | [Integer to Words](https://leetcode.com/problems/integer-to-english-words/)  ([solution](./ds_string_int_to_words.cc))                                     |
|15.| Hard       | [Text Justification](https://leetcode.com/problems/text-justification/)    ([solution](./ds_string_text_justification.cc))                                 |

###Tree###
|#  | Difficulty | Problem and Solution                          |
|:--|:-----------|:---------------------------------------------|
|1. | Easy       | [Is Same Binary Tree](https://leetcode.com/problems/same-tree/)    ([solution](./ds_tree_is_same_tree_bt.cc))     |
|2. | Easy       | [Is Symmetric Binary Tree](https://leetcode.com/problems/symmetric-tree/)    ([solution](./ds_tree_is_symmetric_bt.cc))                                                                                           |
|3. | Easy       | [Level order BT traversal](https://leetcode.com/problems/binary-tree-level-order-traversal-ii/) ([solution](./ds_tree_traversal_levelorder_bt.cc))                                                                                   |
|4. | Easy       | [Is BT Height Balanced](https://leetcode.com/problems/balanced-binary-tree/) <br> [Min Depth of BT](https://leetcode.com/problems/minimum-depth-of-binary-tree/) <br> [Max Depth of BT](https://leetcode.com/problems/maximum-depth-of-binary-tree/)   ([solution](./ds_tree_min_max_depth_bt.cc))                       |
|5. | Easy       | [Invert Binary Tree](https://leetcode.com/problems/invert-binary-tree/) ([solution](./ds_tree_invert_bt.cc))  |
|6. | Medium     | Path Sum [I](https://leetcode.com/problems/path-sum/) and [II](https://leetcode.com/problems/path-sum-ii/) ([solution](./ds_tree_path_sum_i_ii.cc))                |
|7. | Medium     | [Longest Consecutive Sequence BT](https://leetcode.com/problems/binary-tree-longest-consecutive-sequence/) ([soln](./ds_tree_longest_consecutive_sequence_bt.cc))  |
|8. | Medium     | [Lowest Common Ancestor of Binary Search Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/) <br> [Lowest Common Ancestor of Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/) ([solution](./ds_tree_lca_bt_bst.cc))                  |
|9. | Medium     | [Populate Right pointers in BT](https://leetcode.com/problems/populating-next-right-pointers-in-each-node/) ([solution](./ds_tree_populate_next_pointer.cc))     |
|10.| Medium     | [Binary Tree Preorder traversal](https://leetcode.com/problems/binary-tree-preorder-traversal/)  <br> [Binary Tree Inorder traversal](https://leetcode.com/problems/binary-tree-preorder-traversal/) ([solution](./ds_tree_traversal_pre_in_order_iterative_bt.cc))                                                                       |
|11.| Medium     | [Flatten BT to LinkedList](https://leetcode.com/problems/flatten-binary-tree-to-linked-list/) ([solution](./ds_tree_traversal_preorder_to_list.cc))              |
|12.| Medium     | [Verify Preorder sequence in BST ](https://leetcode.com/problems/verify-preorder-sequence-in-binary-search-tree) ([soln](./ds_tree_verify_preorder_sequence_bst.cc))  |
|13.| Medium     | [Right side view in BT(level-order)](https://leetcode.com/problems/binary-tree-right-side-view/) ([solution](./ds_tree_right_side_view_bt.cc))  |

----------------------------------------------------------------------------------------
Math based
--------------------------------------------
|#  | Difficulty | Problem and Solution                          |
|:--|:-----------|:---------------------------------------------|
|1. | Easy       | [Happy Number](https://leetcode.com/problems/happy-number/) ([soln](./math_happy_number.cc))                      |
|2. | Easy       | [Reverse Integer](https://leetcode.com/problems/reverse-integer/) ([soln](./math_reverse_int_overflow.cc))        |
|3. | Medium     | [3 sum smaller](https://leetcode.com/problems/3sum-smaller/) <br> [3 sum ](https://leetcode.com/problems/3sum/) ([solution](./math_3sum.cc))          |
|4. | Medium     | [Find Sqrt](https://leetcode.com/problems/sqrtx/) ([solution](./math_find_sqrt.cc))                               |
|5. | Medium     | [Integer Break](https://leetcode.com/problems/integer-break/) ([solution](./math_integer_break.cc))               |
|6. | Medium     | [Single Number](https://leetcode.com/problems/single-number/) ([solution](./math_integer_missing_int.cc))         |
|7. | Medium     | [Letter Combinations of Phone number](https://leetcode.com/problems/letter-combinations-of-a-phone-number/) ([solution](./math_letter_combinations_phone.cc))      |
|8. | Medium     | [Validate Perfect Square](https://leetcode.com/problems/valid-perfect-square/) ([solution](./math_validate_perfect_square.cc))        |
|9. | Medium     | [Math Shuffle](https://leetcode.com/problems/shuffle-an-array/) ([solution](./math_shuffle.cc))                   |
|10.| Medium     | [Math Rotate Array](https://leetcode.com/problems/rotate-array/) <br> [Math Rotate Matrix](https://leetcode.com/problems/rotate-image/) <br> ([solution](./math_rotate_array_matrix.cc))                       |
|11.| Medium       | [Next Permutation](https://leetcode.com/problems/next-permutation/) <br> ([solution](./math_permutate.cc)) implements Heap and Dijkstra permutation   |
|12.| Medium       | [Uniform Random Sampling](https://leetcode.com/problems/linked-list-random-node/) ([solution](./math_uniform_rand_sampling.cc))     |
|13. | Hard      | [Patching Array](https://leetcode.com/problems/patching-array/) ([solution](./math_patching_array.cc))            |
|14.| Hard       | [Max 2D points on line](https://leetcode.com/problems/max-points-on-a-line/) ([solution](./math_geometry_max_2Dpoints_line.cc))       |

----------------------------------------------------------------------------------------
