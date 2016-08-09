Bit operations
===================

----------------------------------------------------------------------------------------
Bitmap
--------------------------------------------
- Simple resizable [Bitmap implementation](./bitmap.h) in under 200 lines using STL Vector as underlying container.
- Supports bitmap resize and get_next_set_bit operation which are not available in STL Bitset.
- Comparable in performance to STL Bitset, simple microbenchmark with 1 Million get/set/clear operations (code-included) shows:

  | Measure                           |  STL Bitset | [Bitmap](./bit_ops/bitmap.h)      |
  |:----------------------------------|:------------|:------------|
  | Total time taken (1 million loop) |  71 ms      | 60 ms       | 
  | Avg #Cycles per loop              |  189 cycles | 162 cycles  |
  - Note: micro-benchmarks were measured on an Ubuntu 16.04 VM running on Intel(R) Xeon(R) CPU X5650 @ 2.67GHz with GCC 5.4.0 with C++11 and OPT flags(-O3 -Os, -march=native)
  
----------------------------------------------------------------------------------------
Bit Operations
--------------------------------------------
- Below is a list of [algorithms/bit-technique implementations](./bit_ops.h).
  - isPow2, isEven, isOdd
  - bitSet, bitReset, bitToggle
  - bitPopCnt, bitParity, avg
  - bitSwap, bitReverse
  - grayCode, inverseGrayCode
  - bit_propagate_ones_to_right, bit_get_msb, bit_get_lsb
  - bit_num_leading_zeros, bit_num_trailing_zeros, bit_snoob, bit_log2 (floor, ceil), bit_is_pow2, bit_in_place_permutate
  
----------------------------------------------------------------------------------------