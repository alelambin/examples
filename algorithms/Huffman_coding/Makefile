all: main.o node.o tree.o
	g++ -std=c++17 main.o node.o tree.o -o program

main.o: source/main.cpp source/tree.h
	g++ -std=c++17 -c source/main.cpp

node.o: source/node.cpp source/node.h
	g++ -std=c++17 -c source/node.cpp

tree.o: source/tree.cpp source/tree.h source/node.h
	g++ -std=c++17 -c source/tree.cpp

clean:
	rm -rf *.o
