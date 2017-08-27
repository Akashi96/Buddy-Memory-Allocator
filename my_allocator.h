#ifndef MY_ALLOCATOR_H_INCLUDED
#define MY_ALLOCATOR_H_INCLUDED

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

struct mem_ptr
{
	std::vector<void*> ptr;	
};

//METHOD DECLARATIONS
unsigned int upper_powerof_two(unsigned int x);
unsigned int init_allocator(unsigned int _basic_block_size, unsigned int _length);
int release_allocator();
void* my_malloc(unsigned int _length);
void show_freeList();
int my_free(void* addr ,int size);

#endif // MY_ALLOCATOR_H_INCLUDED
