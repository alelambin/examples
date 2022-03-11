SOURCE = ./src

all: main.o node.o bor.o
	g++ main.o node.o bor.o -o lb5

test: mainTest.o node.o bor.o tests.o
	g++ mainTest.o node.o bor.o tests.o -o test

main.o: $(SOURCE)/main.cpp
	g++ -c $(SOURCE)/main.cpp

node.o: $(SOURCE)/node.cpp $(SOURCE)/node.h
	g++ -c $(SOURCE)/node.cpp

bor.o: $(SOURCE)/bor.cpp $(SOURCE)/bor.h
	g++ -c $(SOURCE)/bor.cpp

mainTest.o: $(SOURCE)/mainTest.cpp
	g++ -c $(SOURCE)/mainTest.cpp

tests.o: $(SOURCE)/tests.cpp
	g++ -c $(SOURCE)/tests.cpp

clean:
	rm -rf *.o