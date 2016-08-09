ifndef COMMON_ROOT
COMMON_ROOT = $(shell pwd)/..
endif

#order is important to have dependencies work, declare DEPS before include
include $(COMMON_ROOT)/bld/Makefile.common

INCLUDES = \
	-I $(COMMON_ROOT)/utils	              \
	-I $(COMMON_ROOT)/micro_benchmarks    \

DEPS = \
	$(COMMON_ROOT)/utils/compiler_api.h   \
	$(COMMON_ROOT)/utils/time_api.h       \
	$(COMMON_ROOT)/utils/print_utils.h    \


BENCH_MAP_VS_UNORDERED_MAP = \
	$(COMMON_ROOT)/micro_benchmarks/bench_stl_map.o \

BENCH_GETTIME = \
	$(COMMON_ROOT)/micro_benchmarks/bench_gettime.o \


OBJS = $(BENCH_MAP_VS_UNORDERED_MAP) $(BENCH_GETTIME)       \

# cancel implicit program rule
bench_stl_map: $(BENCH_MAP_VS_UNORDERED_MAP)
	@echo "LD   " $@
	@$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"

bench_gettime: $(BENCH_GETTIME)
	@echo "LD   " $@
	@$(CC) $(OPT) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "--------------------------------------------------"
