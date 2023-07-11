TARGET=json2runner
OBJS=../../common/obj/*.o

CC=g++ -g

$(TARGET).exe: $(TARGET).cpp $(DEPS)
	${CC} $(OBJS) $(TARGET).cpp -o $(TARGET).exe

clean:
	rm -rf $(TARGET).exe
