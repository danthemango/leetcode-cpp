TARGET=json2runner
DEPS=../../common/*.h

CC=g++ -g

$(TARGET).exe: $(TARGET).cpp $(DEPS)
	${CC} $(TARGET).cpp -o $(TARGET).exe

clean:
	rm -rf $(TARGET).exe
