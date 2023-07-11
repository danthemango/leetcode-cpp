CC=g++ -g
CPPS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,obj/%.o,$(CPPS))

all: obj $(OBJS)

obj:
	mkdir -p obj

$(OBJS): obj/%.o : %.cpp %.h
	echo $^
	$(CC) -c $< -o $@

clean:
	rm -f obj/*.o

.PHONY: all clean