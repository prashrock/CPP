ifndef COMMON_ROOT
COMMON_ROOT = $(shell pwd)/..
endif

#order is important to have dependencies work, declare DEPS before include
include $(COMMON_ROOT)/bld/Makefile.common

INCLUDES = \
	-I $(COMMON_ROOT)/utils	              \
	-I $(COMMON_ROOT)/math                \

SORT_TEST = \
	$(COMMON_ROOT)/sort/sort_test.o       \

DEPS = \
	$(COMMON_ROOT)/utils/compiler_api.h   \
	$(COMMON_ROOT)/utils/print_utils.h    \
	$(COMMON_ROOT)/utils/rand_generator.h \
	$(COMMON_ROOT)/utils/time_api.h       \
	$(COMMON_ROOT)/math/math_shuffle.h    \


OBJS = $(SORT_TEST)                           \

# cancel implicit program rule
sort_test: $(SORT_TEST)
	@echo "LD   " $@
	@$(CC) $(OPT) $(CFLAGS)  -O3 -Os -march=native -o $@ $^ $(LDFLAGS)
	@echo "--------------------------------------------------"
