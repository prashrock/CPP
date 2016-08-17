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
	$(COMMON_ROOT)/graph/graph.h                   \

GRAPH_TEST = \
	$(COMMON_ROOT)/graph/graph_test.o              \

OBJS = $(GRAPH_TEST)

# cancel implicit program rule
graph_test: $(GRAPH_TEST)
	@echo "LD   " $@
	@$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"
