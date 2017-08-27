#Makefile for Memory_allocator implementation 
a: all
run: all
	./all
all: main.o my_allocator.o
	 g++ main.o my_allocator.o -o all
main.o: main.cpp
		g++ -c main.cpp
my_allocator.o: my_allocator.cpp
				g++ -c my_allocator.cpp
clean: 
		rm -rf *o all		
				