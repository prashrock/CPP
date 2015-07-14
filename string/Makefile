
INCLUDES = \
	-I $(COMMON_ROOT)/utils	     \
	-I $(COMMON_ROOT)/string   \

LONGEST_UNIQUE_SUBSTR = \
	$(COMMON_ROOT)/string/longest_unique_substring.o \

DEPS = \
	$(COMMON_C_ROOT)/utils/compiler_api.h \
	$(COMMON_ROOT)/utils/print_utils.h \

OBJS = $(LONGEST_UNIQUE_SUBSTR)                \

#order is important to have dependencies work, declare DEPS before include
include $(COMMON_ROOT)/bld/Makefile.common

# cancel implicit program rule
longest_unique_substring: $(LONGEST_UNIQUE_SUBSTR)
	@echo "--------------------------------------------------"
	@echo $@
	$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"
