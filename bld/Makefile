COMMON_ROOT = $(shell pwd)/..
COMMON_C_ROOT = $(COMMON_ROOT)/../C
EXES = math_sqrt math_two_die_probability math_prime                \
	math_perm_comb_test                                             \
	dyn_4_keys_max_print dyn_partition_set dyn_knapsack_01          \
	dyn_longest_common_subsequence                                  \
	median_two_sorted_arrays                                        \
	binary_tree_test	                                            \
	trie_test                                                       \
	bench_stl_map    	                                            \
	longest_unique_substring  substr_match word_freq_cnt            \
	nqueens_backtrack                                               \
	bitmap_test                                                     \


.PHONY: all clean etags $(EXES)

all: $(EXES) etags
MAKE := $(MAKE) --no-print-directory

math_sqrt math_two_die_probability math_prime math_perm_comb_test:
	@$(MAKE) -f $(COMMON_ROOT)/math/Makefile \
		COMMON_ROOT="$(COMMON_ROOT)" COMMON_C_ROOT="$(COMMON_C_ROOT)"  $@

median_two_sorted_arrays:
	@$(MAKE) -f $(COMMON_ROOT)/divide_conquer/Makefile \
		COMMON_ROOT="$(COMMON_ROOT)" COMMON_C_ROOT="$(COMMON_C_ROOT)"  $@

dyn_4_keys_max_print dyn_partition_set dyn_knapsack_01 \
	dyn_longest_common_subsequence:
	@$(MAKE) -f $(COMMON_ROOT)/dyn_prog/Makefile \
		COMMON_ROOT="$(COMMON_ROOT)" COMMON_C_ROOT="$(COMMON_C_ROOT)"  $@

binary_tree_test:
	@$(MAKE) -f $(COMMON_ROOT)/tree/Makefile \
		COMMON_ROOT="$(COMMON_ROOT)" COMMON_C_ROOT="$(COMMON_C_ROOT)"  $@

trie_test:
	@$(MAKE) -f $(COMMON_ROOT)/trie/Makefile \
		COMMON_ROOT="$(COMMON_ROOT)" COMMON_C_ROOT="$(COMMON_C_ROOT)"  $@

bench_stl_map:
	@$(MAKE) -f $(COMMON_ROOT)/micro_benchmarks/Makefile \
		COMMON_ROOT="$(COMMON_ROOT)" COMMON_C_ROOT="$(COMMON_C_ROOT)"  $@

longest_unique_substring substr_match word_freq_cnt:
	@$(MAKE) -f $(COMMON_ROOT)/string/Makefile \
		COMMON_ROOT="$(COMMON_ROOT)" COMMON_C_ROOT="$(COMMON_C_ROOT)"  $@

nqueens_backtrack:
	@$(MAKE) -f $(COMMON_ROOT)/backtracking/Makefile \
		COMMON_ROOT="$(COMMON_ROOT)" COMMON_C_ROOT="$(COMMON_C_ROOT)"  $@

bitmap_test:
	@$(MAKE) -f $(COMMON_ROOT)/bit_ops/Makefile \
		COMMON_ROOT="$(COMMON_ROOT)" COMMON_C_ROOT="$(COMMON_C_ROOT)"  $@

clean:
	rm -f $(EXES) TAGS 
	$(MAKE) -C $(COMMON_ROOT)/math/         COMMON_ROOT="$(COMMON_ROOT)" clean
	$(MAKE) -C $(COMMON_ROOT)/dyn_prog/     COMMON_ROOT="$(COMMON_ROOT)" clean
	$(MAKE) -C $(COMMON_ROOT)/tree/         COMMON_ROOT="$(COMMON_ROOT)" clean
	$(MAKE) -C $(COMMON_ROOT)/trie/         COMMON_ROOT="$(COMMON_ROOT)" clean
	$(MAKE) -C $(COMMON_ROOT)/string/       COMMON_ROOT="$(COMMON_ROOT)" clean
	$(MAKE) -C $(COMMON_ROOT)/backtracking/ COMMON_ROOT="$(COMMON_ROOT)" clean
	$(MAKE) -C $(COMMON_ROOT)/bit_ops/      COMMON_ROOT="$(COMMON_ROOT)" clean
	$(MAKE) -C $(COMMON_ROOT)/divide_conquer/   COMMON_ROOT="$(COMMON_ROOT)" clean
	$(MAKE) -C $(COMMON_ROOT)/micro_benchmarks/ COMMON_ROOT="$(COMMON_ROOT)" clean


etags:
	@echo "--------------------------------------------------"
	rm -f TAGS
	$(FIND_HEADERS_CMD) | etags -
	@echo "--------------------------------------------------"

#create etags file
#first line of find is to exclude whatever we do not need to be 
#indexed by etags, add more like:
#'-or -name $(EXCLUDE_DIR1) -or -name $(EXCLUDE_DIR2)'
#last line after find 'ls' is to add explicit include directories, 
#can add more like:
#'ls $(LIB_DIR)/xulrunner-sdk/include/plugin/np*.h;'
define FIND_HEADERS_CMD
( \
	find $(COMMON_ROOT) '(' -type d -name .svn  ')' -prune  \
	-or -type f '(' -name '*.c' -or -name '*.h' -or -name '*.cc' ')' -print; \
	ls /usr/include/*.h; \
)
endef

