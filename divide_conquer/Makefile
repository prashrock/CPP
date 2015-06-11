
INCLUDES = \
	-I $(COMMON_ROOT)/utils	                       \
	-I $(COMMON_ROOT)/divide_conquer               \

DIV_CONQ_MEDIAN_TWO_SORTED_ARRAYS = \
	$(COMMON_ROOT)/divide_conquer/median_two_sorted_arrays.o \

DEPS = \
	$(COMMON_C_ROOT)/utils/compiler_api.h \
	$(COMMON_ROOT)/utils/print_utils.h \
	$(COMMON_ROOT)/dyn_prog/dyn_prog_helper.h \


OBJS = $(DIV_CONQ_MEDIAN_TWO_SORTED_ARRAYS)

#order is important to have dependencies work, declare DEPS before include
include $(COMMON_ROOT)/bld/Makefile.common

# cancel implicit program rule
median_two_sorted_arrays: $(DIV_CONQ_MEDIAN_TWO_SORTED_ARRAYS)
	@echo "--------------------------------------------------"
	@echo $@
	$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"
