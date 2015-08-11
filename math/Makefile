
INCLUDES = \
	-I $(COMMON_ROOT)/math	                       \
	-I $(COMMON_ROOT)/utils                        \
	-I $(COMMON_ROOT)/bit_ops                      \

MATH_PRIME_OBJS =                                  \
	$(COMMON_ROOT)/math/math_prime.o               \

MATH_SQRT_OBJS =                                   \
	$(COMMON_ROOT)/math/math_sqrt.o                \

MATH_PERM_COMB_TEST_OBJS =                         \
	$(COMMON_ROOT)/math/math_perm_comb_test.o      \

MATH_TWO_DIE_PROB_OBJS =                           \
	$(COMMON_ROOT)/math/math_two_die_probability.o \

DEPS = \
	$(COMMON_ROOT)/math/math_sqrt.h                \
	$(COMMON_ROOT)/math/math_prime.h               \
	$(COMMON_ROOT)/math/math_perm_comb.h           \
	$(COMMON_ROOT)/utils/rand_generator.h          \
	$(COMMON_ROOT)/utils/print_utils.h             \
	$(COMMON_ROOT)/bit_ops/bitmap.h                \

OBJS = $(MATH_SQRT_OBJS) $(MATH_TWO_DIE_PROB_OBJS) $(MATH_PRIME_OBJS) \
	$(MATH_PERM_COMB_TEST_OBJS)

#order is important to have dependencies work, declare DEPS before include
include $(COMMON_ROOT)/bld/Makefile.common

# cancel implicit program rule
math_sqrt: $(MATH_SQRT_OBJS)
	@echo "--------------------------------------------------"
	@echo $@
	$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -lm -o $@ $^
	@echo "--------------------------------------------------"

math_two_die_probability: $(MATH_TWO_DIE_PROB_OBJS)
	@echo "--------------------------------------------------"
	@echo $@
	$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -lm -o $@ $^
	@echo "--------------------------------------------------"

math_prime: $(MATH_PRIME_OBJS)
	@echo "--------------------------------------------------"
	@echo $@
	$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -lm -o $@ $^
	@echo "--------------------------------------------------"

math_perm_comb_test: $(MATH_PERM_COMB_TEST_OBJS)
	@echo "--------------------------------------------------"
	@echo $@
	$(CC) $(OPT) $(CFLAGS) $(LDFLAGS) -lm -o $@ $^
	@echo "--------------------------------------------------"
