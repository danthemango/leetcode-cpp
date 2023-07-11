CC=g++ -g

COMMON_PATH=../common
TOOL_PATH=../tools

# trigger common objects and tools on if they've been updated
COMMON_OBJS=$(wildcard $(COMMON_PATH)/obj/*.o)
COMMON_SRCS=$(wildcard $(COMMON_PATH)/*.cpp $(COMMON_PATH)/*.h)
TOOLSRCS=$(wildcard $(TOOL_PATH)/*/*.cpp)
HDR_PATH=$(COMMON_PATH)
OBJ_PATH=$(COMMON_PATH)/obj

# in each directory, compile as:
# Solution.h -> SolutionFunc.json -> runner.cpp -> (runner.exe <- readme.md) -> run
# (and ignore directories starting with '_')
SUBDIRS=$(shell find . -maxdepth 1 -type d | sed -r '/^\.$$/d' | sed -r '/^\.\/_/d' )
SOLUTIONS=$(foreach fd, $(SUBDIRS), $(fd)/Solution.h)
RUNNER_EXES=$(foreach fd, $(SUBDIRS), $(fd)/runner.exe)
RUNNER_CPPS=$(foreach fd, $(SUBDIRS), $(fd)/runner.cpp)
SOLUTION_FUNCS=$(foreach fd, $(SUBDIRS), $(fd)/SolutionFunc.json)
ALL_RUN = $(addsuffix .run, $(SUBDIRS))
# also add a makefile to each to make testing a bit easier
MAKEFILES=$(foreach fd, $(SUBDIRS), $(fd)/Makefile)

ALL_CLEAN = $(addsuffix .clean, $(SUBDIRS))

all: $(RUNNER_EXES) $(MAKEFILES)

# all -> subdir.run
run: all $(ALL_RUN)

# subdir.run -> subdir/runner.exe
$(ALL_RUN): %.run : %/runner.exe %/readme.md
	@echo $@
	cd $(basename $@) && ./runner.exe -i readme.md

# subdir/runner.exe -> subdir/runner.cpp
$(RUNNER_EXES) : %.exe : %.cpp $(COMMON_OBJS) $(COMMON_OBJS)
	$(CC) $(COMMON_DIR) $(OBJ_PATH)/*.o $< -o $@

# subdir/runner.cpp -> Solution.h
$(RUNNER_CPPS) : %runner.cpp : %SolutionFunc.json $(TOOL_PATH)/json2runner/json2runner.exe
	$(TOOL_PATH)/json2runner/json2runner.exe -i $< -o $@

$(SOLUTION_FUNCS): %SolutionFunc.json : %Solution.h $(TOOL_PATH)/solution2json/solution2json.exe
	$(TOOL_PATH)/solution2json/solution2json.exe -i $< -o $@

# rebuild json2runner tool if necessary
$(TOOL_PATH)/json2runner/json2runner.exe : %.exe : %.cpp
	make -C $(TOOL_PATH)/json2runner

# rebuild solution2json tool if necessary
$(TOOL_PATH)/solution2json/solution2json.exe : %.exe : %.cpp
	make -C $(TOOL_PATH)/solution2json

makefiles: $(MAKEFILES)

$(MAKEFILES):
	bash createSubMake.sh $(dir $@)

common:
	make -C $(COMMON_PATH)

clean: $(ALL_CLEAN)
	rm -rf $(RUNNER_EXES) $(RUNNER_CPPS) $(SOLUTION_FUNCS) $(MAKEFILES)

.PHONY: tools problems common clean makefiles $(ALL_RUN) $(ALL_CLEAN)
