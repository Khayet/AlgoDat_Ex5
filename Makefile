all: compile run

compile:
	g++ -std=c++0x -o closest_pair closest_pair.cpp

run: 
	./closest_pair