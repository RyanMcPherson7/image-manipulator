all: compile link

compile: 
	g++ -I src/include -c main.cpp Functionality.cpp image.cpp

link: 
	g++ main.o Functionality.o image.o -o main