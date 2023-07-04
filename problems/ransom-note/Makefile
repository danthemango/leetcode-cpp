
DEPS=../../common/*.h ../../tools/*/*.cpp

CC=g++ -g

run: runner.exe readme.md
	cat readme.md | ./runner.exe

runner.exe: runner.cpp
	g++ -g runner.cpp -o runner.exe

runner.cpp: SolutionFunc.json ../../tools/json2runner/json2runner.exe 
	../../tools/json2runner/json2runner.exe -i SolutionFunc.json -o runner.cpp

../../tools/json2runner/json2runner.exe: $(DEPS)
	make -C ../../tools/json2runner/

SolutionFunc.json: Solution.h ../../tools/solution2json/solution2json.exe
	../../tools/solution2json/solution2json.exe -i Solution.h -o SolutionFunc.json

../../tools/solution2json/solution2json.exe: $(DEPS)
	make -C ../../tools/solution2json/

clean:
	rm -rf SolutionFunc.json runner.cpp runner.exe
