CC=g++ -g

EXE=printTestcases
DEPS=../../common/*.h ../../tools/*/*.cpp
COMMON_DIR=../../common
OBJ_DIR=$(COMMON_DIR)/obj

$(EXE).exe: $(EXE).cpp $(DEPS)
	${CC} $(EXE).cpp $(OBJ_DIR)/*.o -o $(EXE).exe

clean:
	rm -rf $(EXE).exe obj

run: $(EXE).exe
	./$(EXE).exe

#use an example readme to test the output
test: $(EXE).exe
	./$(EXE).exe -i ../../problems/middle-of-the-linked-list/readme.md
