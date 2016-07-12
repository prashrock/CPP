#order is important to have dependencies work, declare DEPS before include
#include $(COMMON_ROOT)/bld/Makefile.common

#Make one obj for each .cc file found in the current directory
all: $(patsubst %.cc, %, $(wildcard *.cc))

#Make rule for each individual .cc. Since each cc is embedded
#With its own compilation rule, extract 1st line, remove comment
#and directly execute the make target
%: %.cc Makefile
	@echo "Building " $@
	@$(shell head -n 1 $@.cc | cut -c 3-)

clean:
	@echo "Cleaning all leetcode programs"
	@rm -f $(patsubst %.cc, %, $(wildcard *.cc))

.PHONY: all clean
