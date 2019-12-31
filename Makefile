cc = g++
cflag = -c -Wall

#cdep = -lncurses 
cdep = 

headers := matrix.h
sources := matrix.cpp main.cpp
objects := $(sources:.cpp=.o)
target  := markov
path    := /usr/local/bin

all: clean $(target)

$(target): $(objects)
	$(cc) $(objects) -o $(target) $(cdep)
	rm -fr *.o *.gch

$(objects): %.o: %.cpp $(headers)
	$(cc) $(cflag) $(sources) $(headers) $(cdep)

clean:
	rm -rf *.o *.gch $(target)

install:
	install $(target) $(path)

uninstall:
	rm -rf /usr/local/bin/$(target)
