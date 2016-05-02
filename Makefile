#compiler
CC=g++
#compiler options
OPTS=-c -Wall
#source files
SOURCES=$(wildcard *.cpp )
#object files
OBJECTS=$(SOURCES:.cpp=.o)
LIBS=-lncurses
#executable filename
EXECUTABLE=asciidunge
#Special symbols used:
#$^ - is all the dependencies (in this case =$(OBJECTS) )
#$@ - is the result name (in this case =$(EXECUTABLE) )

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(LINK.o) $^ -o $@ $(LIBS)

clean:
#	rm $(EXECUTABLE) $(OBJECTS)
	rm $(OBJECTS)
