ifndef COMMON_ROOT
COMMON_ROOT = $(shell pwd)/..
endif
ifndef COMMON_C_ROOT
COMMON_C_ROOT = $(COMMON_ROOT)/../C
endif

INCLUDES = \
	-I $(COMMON_ROOT)/utils	     \
	-I $(COMMON_C_ROOT)/utils    \
	-I $(COMMON_ROOT)/dyn_prog   \

DYN_4_KEYS_MAX_PRINT = \
	$(COMMON_ROOT)/dyn_prog/dyn_4_keys_max_print.o \

DYN_PARTITION_SET = \
	$(COMMON_ROOT)/dyn_prog/dyn_partition_set.o \

DYN_KNAPSACK_01 = \
	$(COMMON_ROOT)/dyn_prog/dyn_knapsack_01.o \

DYN_SUBSET_SUM = \
	$(COMMON_ROOT)/dyn_prog/dyn_subset_sum.o \

DYN_LCS = \
	$(COMMON_ROOT)/dyn_prog/dyn_longest_common_subsequence.o \

DYN_STR_MIN_EDIT_DISTANCE = \
	$(COMMON_ROOT)/dyn_prog/dyn_str_min_edit_distance.o \

DEPS = \
	$(COMMON_C_ROOT)/utils/compiler_api.h \
	$(COMMON_ROOT)/utils/print_utils.h \

OBJS = $(DYN_4_KEYS_MAX_PRINT) $(DYN_PARTITION_SET) \
       $(DYN_KNAPSACK_01)                           \

DYN_OBJS = dyn_4_keys_max_print dyn_partition_set   \
	   dyn_knapsack_01 dyn_subset_sum           \
	   dyn_longest_common_subsequence           \
	   dyn_str_min_edit_distance		    \

#order is important to have dependencies work, declare DEPS before include
include $(COMMON_ROOT)/bld/Makefile.common

# cancel implicit program rule
dyn_4_keys_max_print: $(DYN_4_KEYS_MAX_PRINT)
	@echo "LD   " $@
	@$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"

dyn_partition_set: $(DYN_PARTITION_SET)
	@echo "LD   " $@
	@$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"

dyn_knapsack_01: $(DYN_KNAPSACK_01)
	@echo "LD   " $@
	@$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"

dyn_subset_sum: $(DYN_SUBSET_SUM)
	@echo "LD   " $@
	@$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"

dyn_longest_common_subsequence: $(DYN_LCS)
	@echo "LD   " $@
	@$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"

dyn_str_min_edit_distance: $(DYN_STR_MIN_EDIT_DISTANCE)
	@echo "LD   " $@
	@$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"


