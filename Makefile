all: compile run

compile:
	g++ -ggdb -std=c++11 -o closest_pair closest_pair.cpp

run: 
	./closest_pair