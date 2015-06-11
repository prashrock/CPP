
INCLUDES = \
	-I $(COMMON_ROOT)/math	 \
	-I $(COMMON_C_ROOT)/utils/ \

MATH_SQRT_OBJS = \
	$(COMMON_ROOT)/math/math_sqrt.o \

MATH_TWO_DIE_PROB_OBJS = \
	$(COMMON_ROOT)/math/math_two_die_probability.o \

DEPS = \
	$(COMMON_ROOT)/math/math_sqrt.h \
	$(COMMON_C_ROOT)/utils/rand_utils.h \

OBJS = $(MATH_SQRT_OBJS) $(MATH_TWO_DIE_PROB_OBJS)

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