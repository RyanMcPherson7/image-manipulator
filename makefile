all: compile link

compile: 
	g++ -I src/include -c main.cpp Functionality.cpp image.cpp

link: 
	g++ bin/main.o bin/Functionality.o bin/image.o -o bin/main