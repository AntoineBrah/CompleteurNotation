CXX = g++

all: prog

prog: *.o
	$(CXX) *.o -o prog -lncurses

*.o: *.cc *.h
	$(CXX) -c *.cc

