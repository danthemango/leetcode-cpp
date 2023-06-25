
# compiles each .cpp file in the current directory
# and runs each executable 

CC := g++
CFLAGS := -g
TARGET := test

DEPS := $(wildcard ../../*.h)
# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cpp)
# $(patsubst %.cpp,%.exe,$(SRCS)): substitute all ".cpp" file name strings to ".exe" file name strings
EXES := $(patsubst %.cpp,%.exe,$(SRCS))
RUNEXES := $(patsubst %,run%,$(EXES))

all: $(EXES)

%.exe: %.cpp $(DEPS)
	$(CC) $(CFLAGS) $< -o $@

run: argParse.exe
	./argParse.exe -i argParse.cpp -o tmp

clean:
	rm -rf $(TARGET) *.exe tmp

.PHONY: all clean run
