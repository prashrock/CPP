Least Recently Used (LRU) Cache
===================

----------------------------------------------------------------------------------------
Implementation
--------------------------------------------
- STL Based O(1) [LRU Cache implementation](./lru/lru.h) in under 200 lines. Containers used:
  
  | Container          | Purpose                                                     |
  |:-------------------|:------------------------------------------------------------|
  | STL::List          | maintain LRU keys in chronological (least recently used) order (oldest element first) |
  | STL::Unordered Map | - Used for O(1) LRU Lookup. <br> - Also maintains a reference to list for O(1) direct access during age-refresh |

----------------------------------------------------------------------------------------
