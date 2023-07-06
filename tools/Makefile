
# run 'make -C subdir' for each subdirectory with a .cpp file that has been changed 
# each tool has a .cpp file, and a corresponding .exe target of the same name
SUBDIRS=$(shell find . -maxdepth 1 -type d | sed -r '/^\.$$/d' )
SRCS=$(wildcard *.cpp $(foreach fd, $(SUBDIRS), $(fd)/*.cpp))
EXE=$(patsubst %.cpp,%.exe,$(SRC))

SRC = $(wildcard */*.cpp)

all: $(EXE)

$(EXE): %.exe : %.cpp
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
