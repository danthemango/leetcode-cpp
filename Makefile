
all: problems 

tools:
	make -C tools all

common:
	make -C common all

problems: common tools
	make -C problems all

run: problems
	make -C problems run

clean:
	make -C tools clean
	make -C common clean
	make -C problems clean

.PHONY: all tools problems common clean
