
INCLUDES = \
	-I $(COMMON_ROOT)/utils	     \
	-I $(COMMON_C_ROOT)/utils   \
	-I $(COMMON_ROOT)/string   \

NQUEENS_BACKTRACK = \
	$(COMMON_ROOT)/backtracking/nqueens_backtrack.o \

DEPS = \
	$(COMMON_C_ROOT)/utils/compiler_api.h \
	$(COMMON_C_ROOT)/utils/time_api.h \
	$(COMMON_ROOT)/utils/print_utils.h \

OBJS = $(NQUEENS_BACKTRACK) \

#order is important to have dependencies work, declare DEPS before include
include $(COMMON_ROOT)/bld/Makefile.common

# cancel implicit program rule
nqueens_backtrack: $(NQUEENS_BACKTRACK)
	@echo "--------------------------------------------------"
	@echo $@
	$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"
