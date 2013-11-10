all: ass1
ass1: bin/Main.o
	g++ -o bin/Main bin/Main.o
	
bin/Main.o: src/Main.cpp
	g++ -g -Wall -Weffc++ -c -Linclude -o bin/Main.o src/Main.cpp
	
clean:
	rm -f bin/*