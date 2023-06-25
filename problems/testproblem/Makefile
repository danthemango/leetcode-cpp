CC=g++ -g

run: main.exe
	./main.exe

debug: main.exe
	gdb main.exe

# main.exe: main.cpp
main.exe:  
	${CC} main.cpp -o main.exe

clean:
	rm -rf main.exe
