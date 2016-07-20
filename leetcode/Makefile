#Make one obj for each .cc file found in the current directory
all: $(patsubst %.cc, %, $(wildcard *.cc))

#Each individual program (.cc) has its own make rule embedded in the
#first line as a comment. Just extract this line, remove the comment
#and directly execute the make target
%: %.cc Makefile
	@echo "Building " $@
	@$(shell head -n 1 $@.cc | cut -c 3-)

clean:
	@echo "Cleaning all leetcode programs"
	@rm -f $(patsubst %.cc, %, $(wildcard *.cc))

.PHONY: all clean
