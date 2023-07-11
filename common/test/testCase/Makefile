CC=g++ -g -Wall

CPPS=$(wildcard *.cpp)
EXES=$(patsubst %.cpp,%.exe,$(CPPS))
RUNS=$(patsubst %.cpp,%.run,$(CPPS))
COMMON_DIR=../..
OBJS=$(COMMON_DIR)/obj/*.o

run: $(RUNS)

$(RUNS): %.run : %.exe
	echo $@
	./$<

$(EXES): %.exe : %.cpp
	$(CC) $(OBJS) $^ -o $@

common:
	make -C $(COMMON_DIR)

clean:
	rm -f *.exe

.PHONY: clean common
