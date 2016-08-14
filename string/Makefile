ifndef COMMON_ROOT
COMMON_ROOT = $(shell pwd)/..
endif

#order is important to have dependencies work, declare DEPS before include
include $(COMMON_ROOT)/bld/Makefile.common

INCLUDES =                                  \
	-I $(COMMON_ROOT)/utils	            \
	-I $(COMMON_ROOT)/string            \

DEPS = \
	$(COMMON_ROOT)/utils/compiler_api.h \
	$(COMMON_ROOT)/utils/time_api.h     \
	$(COMMON_ROOT)/utils/print_utils.h  \
	$(COMMON_ROOT)/utils/hash_fns.h     \
	$(COMMON_ROOT)/string/substring.h   \

LONGEST_UNIQUE_SUBSTR = \
	$(COMMON_ROOT)/string/longest_unique_substring.o \

SUBSTR_MATCH = \
	$(COMMON_ROOT)/string/substr_match.o \

WORD_FREQ_CNT = \
	$(COMMON_ROOT)/string/word_freq_cnt.o \


OBJS = $(LONGEST_UNIQUE_SUBSTR) $(SUBSTR_MATCH) \

# cancel implicit program rule
longest_unique_substring: $(LONGEST_UNIQUE_SUBSTR)
	@echo "LD   " $@
	@$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"

substr_match: $(SUBSTR_MATCH)
	@echo "LD   " $@
	@$(CC) $(OPT) $(CFLAGS) -O3 -Os -march=native -o $@ $^ $(LDFLAGS)
	@echo "--------------------------------------------------"

word_freq_cnt: $(WORD_FREQ_CNT)
	@echo "LD   " $@
	@$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"
