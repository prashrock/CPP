
INCLUDES = \
	-I $(COMMON_ROOT)/utils	     \
	-I $(COMMON_ROOT)/dyn_prog   \

DYN_4_KEYS_MAX_PRINT = \
	$(COMMON_ROOT)/dyn_prog/dyn_4_keys_max_print.o \

DYN_PARTITION_SET = \
	$(COMMON_ROOT)/dyn_prog/dyn_partition_set.o \

DYN_KNAPSACK_01 = \
	$(COMMON_ROOT)/dyn_prog/dyn_knapsack_01.o \

DYN_LCS = \
	$(COMMON_ROOT)/dyn_prog/dyn_longest_common_subsequence.o \

DEPS = \
	$(COMMON_C_ROOT)/utils/compiler_api.h \
	$(COMMON_ROOT)/utils/print_utils.h \
	$(COMMON_ROOT)/dyn_prog/dyn_prog_helper.h \


OBJS = $(DYN_4_KEYS_MAX_PRINT) $(DYN_PARTITION_SET) \
	$(DYN_KNAPSACK_01)                              \

#order is important to have dependencies work, declare DEPS before include
include $(COMMON_ROOT)/bld/Makefile.common

# cancel implicit program rule
dyn_4_keys_max_print: $(DYN_4_KEYS_MAX_PRINT)
	@echo "--------------------------------------------------"
	@echo $@
	$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"

dyn_partition_set: $(DYN_PARTITION_SET)
	@echo "--------------------------------------------------"
	@echo $@
	$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"

dyn_knapsack_01: $(DYN_KNAPSACK_01)
	@echo "--------------------------------------------------"
	@echo $@
	$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"

dyn_longest_common_subsequence: $(DYN_LCS)
	@echo "--------------------------------------------------"
	@echo $@
	$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"
