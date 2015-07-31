
INCLUDES = \
	-I $(COMMON_ROOT)/utils	     \
	-I $(COMMON_C_ROOT)/utils   \
	-I $(COMMON_ROOT)/string   \

LONGEST_UNIQUE_SUBSTR = \
	$(COMMON_ROOT)/string/longest_unique_substring.o \

SUBSTR_MATCH = \
	$(COMMON_ROOT)/string/substr_match.o \

WORD_FREQ_CNT = \
	$(COMMON_ROOT)/string/word_freq_cnt.o \

DEPS = \
	$(COMMON_C_ROOT)/utils/compiler_api.h \
	$(COMMON_C_ROOT)/utils/time_api.h \
	$(COMMON_ROOT)/utils/print_utils.h \
	$(COMMON_ROOT)/string/substring.h \

OBJS = $(LONGEST_UNIQUE_SUBSTR) $(SUBSTR_MATCH) \

#order is important to have dependencies work, declare DEPS before include
include $(COMMON_ROOT)/bld/Makefile.common

# cancel implicit program rule
longest_unique_substring: $(LONGEST_UNIQUE_SUBSTR)
	@echo "--------------------------------------------------"
	@echo $@
	$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"

substr_match: $(SUBSTR_MATCH)
	@echo "--------------------------------------------------"
	@echo $@
	$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"

word_freq_cnt: $(WORD_FREQ_CNT)
	@echo "--------------------------------------------------"
	@echo $@
	$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -o $@ $^
	@echo "--------------------------------------------------"