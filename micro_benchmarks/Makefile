
INCLUDES = \
	-I $(COMMON_ROOT)/utils	     \
	-I $(COMMON_ROOT)/micro_benchmarks   \

BENCH_MAP_VS_UNORDERED_MAP = \
	$(COMMON_ROOT)/micro_benchmarks/bench_stl_map.o \

DEPS = \
	$(COMMON_C_ROOT)/utils/compiler_api.h \
	$(COMMON_ROOT)/utils/print_utils.h \

OBJS = $(BENCH_MAP_VS_UNORDERED_MAP)                \

#order is important to have dependencies work, declare DEPS before include
include $(COMMON_ROOT)/bld/Makefile.common

# cancel implicit program rule
bench_stl_map: $(BENCH_MAP_VS_UNORDERED_MAP)
	@echo "--------------------------------------------------"
	@echo $@
	$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"
