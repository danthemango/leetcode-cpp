
# run 'make -C subdir' for each subdirectory with a .cpp file that has been changed 
# each tool has a .cpp file, and a corresponding .exe target of the same name
SUBDIRS=$(shell find . -maxdepth 1 -type d | sed -r '/^\.$$/d' )
SRCS=$(wildcard *.cpp $(foreach fd, $(SUBDIRS), $(fd)/*.cpp))
EXE=$(patsubst %.cpp,%.exe,$(SRC))
COMMON_PATH=../common
COMMONSRCS=$(wildcard $(COMMON_PATH)/*.h)

SRC = $(wildcard */*.cpp)

all: $(EXE)

# rebuild common files if necessary
$(COMMONSRCS):
	make -C $(COMMON_PATH)

$(EXE): %.exe : %.cpp $(COMMONSRCS)
	$(MAKE) -C $(dir $@)

# run 'make -C subdir clean' for each subdir
### clean ###

ALL_MOD_CLEAN = $(addsuffix .clean, $(SUBDIRS))

$(ALL_MOD_CLEAN): 
	echo "cleaning $(basename $@)"
	if [ -e $(basename $@)/Makefile ] ; then \
	        $(MAKE) -C $(basename $@) clean ;\
	fi 

clean: $(ALL_MOD_CLEAN)
    echo "cleaning complete: " $(SUBDIRS)

PHONY: $(ALL_MOD_CLEAN) $(SUBDIRS) default all clean
