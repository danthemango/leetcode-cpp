# ListNode test Makefile

CC=g++ -g

CPPS=$(wildcard *.cpp)
EXES=$(patsubst %.cpp,%.exe,$(CPPS))
RUNS=$(patsubst %,%.run,$(EXES))
COMMON_DIR=../..
OBJ_DIR=../../obj
COMMON_CPPS=$(wildcard $(COMMON_DIR)/*.cpp)
COMMON_HS=$(wildcard $(COMMON_DIR)/*.h)
COMMON_OBJS=$(patsubst %.cpp,obj/%.o,$(COMMON_CPPS))

run: $(RUNS)

all: $(EXES) common

common: $(COMMON_DIR)/*.cpp $(COMMON_DIR)/*.h
	make -C $(COMMON_DIR)

$(COMMON_OBJS): obj/%.o : %.cpp
	@echo $@
	make -C $(COMMON_DIR)

$(RUNS): %.run : %
	@echo $@
	./$<

$(EXES): %.exe : %.cpp $(COMMON_CPPS) $(COMMON_HS) common
	$(CC) $< -I$(COMMON_DIR) $(OBJ_DIR)/*.o -o $@	

$(COMMON_CPPS) $(COMMON_HS):
	make -C $(COMMON_PATH)

clean:
	rm -rf *.exe

.PHONY: all clean run common
