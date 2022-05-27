SOURCE = ./src

all: main.o backtracking.o
	g++ main.o backtracking.o -o program

test: mainTest.o backtracking.o tests.o
	g++ mainTest.o backtracking.o tests.o -o test

research: all research.py
	python3 research.py

main.o: $(SOURCE)/main.cpp
	g++ -c $(SOURCE)/main.cpp

backtracking.o: $(SOURCE)/backtracking.cpp $(SOURCE)/backtracking.h
	g++ -c $(SOURCE)/backtracking.cpp

mainTest.o: $(SOURCE)/mainTest.cpp
	g++ -c $(SOURCE)/mainTest.cpp

tests.o: $(SOURCE)/tests.cpp
	g++ -c $(SOURCE)/tests.cpp

clean:
	rm -rf *.o