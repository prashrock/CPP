ifndef COMMON_ROOT
COMMON_ROOT = $(shell pwd)/..
endif
ifndef COMMON_C_ROOT
COMMON_C_ROOT = $(COMMON_ROOT)/../C
endif

#order is important to have dependencies work, declare DEPS before include
include $(COMMON_ROOT)/bld/Makefile.common

INCLUDES =                                             \
	-I $(COMMON_ROOT)/divide_conquer               \
	-I $(COMMON_ROOT)/utils	                       \

DIV_CONQ_MEDIAN_TWO_SORTED_ARRAYS =                    \
	$(COMMON_ROOT)/divide_conquer/median_two_sorted_arrays.o \

DEPS =                                                 \
	$(COMMON_ROOT)/utils/print_utils.h             \
	$(COMMON_C_ROOT)/utils/compiler_api.h          \
	$(COMMON_ROOT)/dyn_prog/dyn_prog_helper.h      \

OBJS = $(DIV_CONQ_MEDIAN_TWO_SORTED_ARRAYS)

# cancel implicit program rule
median_two_sorted_arrays: $(DIV_CONQ_MEDIAN_TWO_SORTED_ARRAYS)
	@echo "LD   " $@
	@$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"
