CC=g++ -g

COMMON_PATH=../common
TOOL_PATH=../tools

# recompile problems if there were changes in tool or common files
COMMONSRCS=$(wildcard $(COMMON_PATH)/*.h)
TOOLSRCS=$(wildcard $(TOOL_PATH)/*/*.cpp)

# in each directory, compile as:
# Solution.h -> SolutionFunc.json -> runner.cpp -> (runner.exe <- readme.md) -> run
SUBDIRS=$(shell find . -maxdepth 1 -type d | sed -r '/^\.$$/d' )
SOLUTIONS=$(foreach fd, $(SUBDIRS), $(fd)/Solution.h)
RUNNER_EXES=$(foreach fd, $(SUBDIRS), $(fd)/runner.exe)
RUNNER_CPPS=$(foreach fd, $(SUBDIRS), $(fd)/runner.cpp)
SOLUTION_FUNCS=$(foreach fd, $(SUBDIRS), $(fd)/SolutionFunc.json)
ALL_RUN = $(addsuffix .run, $(SUBDIRS))

ALL_CLEAN = $(addsuffix .clean, $(SUBDIRS))

all: $(COMMONSRCS) $(RUNNER_EXES)

# all -> subdir.run
run: all $(ALL_RUN)

# subdir.run -> subdir/runner.exe
$(ALL_RUN): %.run : %/runner.exe %/readme.md
	cd $(basename $@) && ./runner.exe -i readme.md

# subdir/runner.exe -> subdir/runner.cpp
$(RUNNER_EXES) : %.exe : %.cpp $(COMMONSRCS)
	$(CC) $< -o $@

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

# rebuild common files if necessary
$(COMMONSRCS):
	make -C $(COMMON_PATH)

clean: $(ALL_CLEAN)
	rm -rf $(RUNNER_EXES) $(RUNNER_CPPS) $(SOLUTION_FUNCS)

.PHONY: tools problems common clean $(ALL_RUN) $(ALL_CLEAN)
