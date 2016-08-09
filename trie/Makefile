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

TRIE_TEST = \
	$(COMMON_ROOT)/trie/trie_test.o                \

DEPS = \
	$(COMMON_C_ROOT)/utils/compiler_api.h          \
	$(COMMON_ROOT)/utils/print_utils.h             \
	$(COMMON_ROOT)/trie/rway_trie.h                \

OBJS = $(TRIE_TEST)

# cancel implicit program rule
trie_test: $(TRIE_TEST)
	@echo "LD   " $@
	@$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"
