ifndef COMMON_ROOT
COMMON_ROOT = $(shell pwd)/..
endif
ifndef COMMON_C_ROOT
COMMON_C_ROOT = $(COMMON_ROOT)/../C
endif

#order is important to have dependencies work, declare DEPS before include
include $(COMMON_ROOT)/bld/Makefile.common

INCLUDES = \
	-I $(COMMON_ROOT)/utils	                       \

LRU_TEST = \
	$(COMMON_ROOT)/lru/lru_test.o                  \

DEPS = \
	$(COMMON_C_ROOT)/utils/compiler_api.h          \
	$(COMMON_ROOT)/utils/print_utils.h             \
	$(COMMON_ROOT)/lru/lru.h                       \

OBJS = $(LRU_TEST)

# cancel implicit program rule
lru_test: $(LRU_TEST)
	@echo "LD   " $@
	@$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"
