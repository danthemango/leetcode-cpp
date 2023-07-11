
CC=g++ -g
COMMON_DIR=../../common
OBJ_DIR=../../common/obj

EXE=solution2json
DEPS=../../common/*.h ../../tools/*/*.cpp

$(EXE).exe: $(EXE).cpp $(DEPS)
	$(CC) -I$(COMMON_DIR) $(OBJ_DIR)/*.o $< -o $@

clean:
	rm -rf $(EXE).exe obj

run: $(EXE).exe
	./$(EXE).exe
