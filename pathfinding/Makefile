SOURCE = ./src

all: main.o node.o graph.o
	g++ main.o node.o graph.o -o program

test: mainTest.o tests.o node.o graph.o
	g++ mainTest.o tests.o node.o graph.o -o test

main.o: $(SOURCE)/main.cpp
	g++ -c $(SOURCE)/main.cpp

node.o: $(SOURCE)/node.cpp $(SOURCE)/node.h
	g++ -c $(SOURCE)/node.cpp

graph.o: $(SOURCE)/graph.cpp $(SOURCE)/graph.h
	g++ -c $(SOURCE)/graph.cpp

mainTest.o: $(SOURCE)/mainTest.cpp
	g++ -c $(SOURCE)/mainTest.cpp

tests.o: $(SOURCE)/tests.cpp
	g++ -c $(SOURCE)/tests.cpp

clean:
	rm -rf *.o