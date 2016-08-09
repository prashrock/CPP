ifndef COMMON_ROOT
COMMON_ROOT = $(shell pwd)/..
endif
ifndef COMMON_C_ROOT
COMMON_C_ROOT = $(COMMON_ROOT)/../C
endif

#order is important to have dependencies work, declare DEPS before include
include $(COMMON_ROOT)/bld/Makefile.common

INCLUDES = \
	-I $(COMMON_ROOT)/utils	     \
	-I $(COMMON_ROOT)/bit_ops    \

BITMAP_TEST = \
	$(COMMON_ROOT)/bit_ops/bitmap_test.o \

BITOPS_TEST = \
	$(COMMON_ROOT)/bit_ops/bitops_test.o \

DEPS = \
	$(COMMON_C_ROOT)/utils/compiler_api.h \
	$(COMMON_ROOT)/utils/compiler_api.h   \
	$(COMMON_ROOT)/utils/print_utils.h    \
	$(COMMON_ROOT)/bit_ops/bitmap.h       \
	$(COMMON_ROOT)/bit_ops/bit_ops.h      \

OBJS = $(BITMAP_TEST)  $(BITOPS_TEST)         \

# cancel implicit program rule
bitmap_test: $(BITMAP_TEST)
	@echo "LD   " $@
	@$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -O3 -Os -march=native -o $@ $^
	@echo "--------------------------------------------------"

bitops_test: $(BITOPS_TEST)
	@echo "LD   " $@
	@$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -O3 -Os -march=native -o $@ $^
	@echo "--------------------------------------------------"
