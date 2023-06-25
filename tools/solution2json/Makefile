CC=g++ -g

EXE=solution2json
DEPS=../../common/*.h ../../tools/*/*.cpp

$(EXE).exe: $(EXE).cpp $(DEPS)
	${CC} $(EXE).cpp -o $(EXE).exe

clean:
	rm -rf $(EXE).exe obj

run: $(EXE).exe
	./$(EXE).exe