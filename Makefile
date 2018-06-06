CPP = g++
CPPFLAGS = -Wall -g 

OBJ = main.o MARVEL.o

vecclass: $(OBJ)
	$(CPP) $(CPPFLAGS) $(OBJ) -o main 

Main.o: main.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp -o main.o

MARVEL.o: MARVEL.cpp MARVEL.hpp
	$(CPP) $(CPPFLAGS) -c marvel.cpp -o marvel.o

all: main

clean:
	rm -f *.o
	
