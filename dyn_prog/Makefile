
INCLUDES = \
	-I $(COMMON_C_ROOT)/utils	 \
	-I $(COMMON_ROOT)/dyn_prog   \

DYN_4_KEYS_MAX_PRINT = \
	$(COMMON_ROOT)/dyn_prog/dyn_4_keys_max_print.o \

DEPS = \
	$(COMMON_C_ROOT)/utils/compiler_api.h \
	$(COMMON_C_ROOT)/utils/scan_utils.h \
	$(COMMON_ROOT)/dyn_prog/dyn_prog_helper.h \


OBJS = $(DYN_4_KEYS_MAX_PRINT)

#order is important to have dependencies work, declare DEPS before include
include $(COMMON_ROOT)/bld/Makefile.common

# cancel implicit program rule
dyn_4_keys_max_print: $(DYN_4_KEYS_MAX_PRINT)
	@echo "--------------------------------------------------"
	@echo $@
	$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"
