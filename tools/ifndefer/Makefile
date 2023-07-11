CC=g++ -g

COMMON_DIR=../../common
OBJ_DIR=../../common/obj

main.exe: main.cpp
	${CC} -I$(COMMON_DIR) $(OBJ_DIR)/*.o main.cpp -o main.exe

clean:
	rm -rf main.exe

run: main.exe
	./main.exe ../../common/common.h

