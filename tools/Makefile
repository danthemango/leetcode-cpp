all: bin/ReadmeParser.exe

testAll: testReadmeParser

testReadmeParser: bin/ReadmeParser.exe
	bin/ReadmeParser.exe ../problems/testproblem/README.md

bin/ReadmeParser.exe: ReadmeParser/ReadmeParser.cpp
	g++ ReadmeParser/ReadmeParser.cpp -o bin/ReadmeParser.exe
