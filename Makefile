#Makefile

CXX = g++
CXXFLAGS = -Wall -g

prog2: splayTree.o main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

splayTree.o: splayTree.cpp splayTree.h
	$(CXX) $(CXXFLAGS) -c splayTree.cpp

main.o: main.cpp splayTree.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	/bin/rm -f prog2 *.o
