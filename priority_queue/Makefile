ifndef COMMON_ROOT
COMMON_ROOT = $(shell pwd)/..
endif

#order is important to have dependencies work, declare DEPS before include
include $(COMMON_ROOT)/bld/Makefile.common

INCLUDES = \
	-I $(COMMON_ROOT)/utils	                       \

DEPS = \
	$(COMMON_ROOT)/utils/compiler_api.h            \
	$(COMMON_ROOT)/utils/print_utils.h             \
	$(COMMON_ROOT)/tree/binary_tree.h              \

BIN_TREE_TEST = \
	$(COMMON_ROOT)/tree/binary_tree_test.o         \

OBJS = $(BIN_TREE_TEST)

# cancel implicit program rule
binary_tree_test: $(BIN_TREE_TEST)
	@echo "LD   " $@
	@$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"
