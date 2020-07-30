FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
all: arrow.o
	g++ -c main.cpp
	g++ main.o arrow.o -o sfml-app $(FLAGS)
arrow: arrow.cpp arrow.h
	g++ -c arrow.cpp -lsfml-graphics
clean:
	rm *.o
