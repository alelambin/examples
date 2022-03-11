SOURCE = ./src

all: main.o kmp.o
	g++ main.o kmp.o -o lb4

test: mainTest.o kmp.o tests.o
	g++ mainTest.o kmp.o tests.o -o test

main.o: $(SOURCE)/main.cpp
	g++ -c $(SOURCE)/main.cpp

kmp.o: $(SOURCE)/kmp.cpp $(SOURCE)/kmp.h
	g++ -c $(SOURCE)/kmp.cpp

mainTest.o: $(SOURCE)/mainTest.cpp
	g++ -c $(SOURCE)/mainTest.cpp

tests.o: $(SOURCE)/tests.cpp
	g++ -c $(SOURCE)/tests.cpp

clean:
	rm -rf *.o