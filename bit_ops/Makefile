
INCLUDES = \
	-I $(COMMON_ROOT)/utils	     \
	-I $(COMMON_ROOT)/bit_ops    \

BITMAP_TEST = \
	$(COMMON_ROOT)/bit_ops/bitmap_test.o \

DEPS = \
	$(COMMON_C_ROOT)/utils/compiler_api.h \
	$(COMMON_ROOT)/utils/print_utils.h    \
	$(COMMON_ROOT)/bit_ops/bitmap.h       \

OBJS = $(BITMAP_TEST)                \

#order is important to have dependencies work, declare DEPS before include
include $(COMMON_ROOT)/bld/Makefile.common

# cancel implicit program rule
bitmap_test: $(BITMAP_TEST)
	@echo "--------------------------------------------------"
	@echo $@
	$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"
