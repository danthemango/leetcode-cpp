CC=g++ -g

main.exe: main.cpp
	${CC} main.cpp -o main.exe

clean:
	rm -rf main.exe obj

run: main.exe
	./main.exe

rerun: main.exe
	make clean
	make run