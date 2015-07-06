
INCLUDES = \
	-I $(COMMON_ROOT)/utils	                       \


BIN_TREE_TEST = \
	$(COMMON_ROOT)/tree/binary_tree_test.o         \

DEPS = \
	$(COMMON_C_ROOT)/utils/compiler_api.h          \
	$(COMMON_ROOT)/utils/print_utils.h             \
	$(COMMON_ROOT)/tree/binary_tree.h              \


OBJS = $(BIN_TREE_TEST)

#order is important to have dependencies work, declare DEPS before include
include $(COMMON_ROOT)/bld/Makefile.common

# cancel implicit program rule
binary_tree_test: $(BIN_TREE_TEST)
	@echo "--------------------------------------------------"
	@echo $@
	$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"
