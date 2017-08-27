///--------------------------------------------------------------------------------------
/*
	AUTHOR:		Akash Agarwal
				1405231007-Computer Science Department
				IET LUCKNOW
	LIFE MOTTO:	while(!(suceed=try()))
*/
///--------------------------------------------------------------------------------------

//#INCLUDES 

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "my_allocator.h"

using namespace std;

//GLOBAL VARIABLES
bool isinitialized = 0;
void *memory_start;
void *last_valid_address;
int _basic_block_size;
int _length;
int req_mem;
mem_ptr *freeLists[32];  //Because INT_MAX = 2^31 
								    //therefore there should be ceil(log2(INT_MAX)) = 32 freelists.


//METHODS' DEFINITION
unsigned int upper_powerof_two(unsigned int x)
{
	x--;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x++;
	return x;
}
void* remove_addr(int index)
{
	void *addr = freeLists[index]->ptr.back();
	freeLists[index]->ptr.pop_back();
	if(!freeLists[index]->ptr.size())
		{
			delete freeLists[index];
			freeLists[index] = NULL;
		}
	return addr;
}
void addtoList(int index,void *addr)
{
	if(!freeLists[index])
		freeLists[index] = new mem_ptr;
	freeLists[index]->ptr.push_back(addr);
}

void* return_addr(int index,void* addr)
{
	if(pow(2,index) == req_mem)
		return addr;

	addtoList(index-1,addr);
	cout << "addr" << (void*)addr << endl;
	cout << pow(2,index)/2 << endl;
	cout << (void*)((char*)addr + (int)pow(2,index)/2) << endl; 
	return_addr(index-1,((char*)addr + (int)pow(2,index)/2));
}

unsigned int init_allocator(unsigned int _basic_block_size, unsigned int _length)
{
	_length = upper_powerof_two(_length);
	_basic_block_size = upper_powerof_two(_basic_block_size);
	cout << _length << endl
		 << _basic_block_size;
	if(_basic_block_size <= sizeof(mem_ptr))// sizeof(mem_ptr) = 16
		_basic_block_size = 32;
	::_basic_block_size = _basic_block_size;
	if(_length < _basic_block_size)
		_length = _basic_block_size;
	::_length = _length;
	cout << endl << ::_length
		 << endl << ::_basic_block_size;
	memory_start = sbrk(0);
	cout << endl << memory_start;
	sbrk(_length);
	last_valid_address = sbrk(0);
	cout << endl << last_valid_address;
	isinitialized = 1;
	int index = log2(_length);
	freeLists[index] = new mem_ptr;
	freeLists[index]->ptr.push_back(memory_start);
	// cout << freeLists[index]->ptr[0];
	return 0;
}
int release_allocator()
{
	sbrk(-_length);
	last_valid_address = sbrk(0);
	for (int i = 0; i < 32; ++i)
	{	
		delete freeLists[i];
		freeLists[i] = NULL;
	}
	// cout << endl << last_valid_address;
	return 0;
}
void* my_malloc(unsigned int _length)
{	
	_length = upper_powerof_two(_length);
	req_mem = _length;
	cout <<endl<< _length << endl;
	
	if(!isinitialized)
	{
		cout << "INIT\n";
		init_allocator(32,_length);
	}
	cout << "here\n";
	int index = log2(_length);

	// if(freeLists[index])
	// 	return remove_addr(index);

	while(!freeLists[index])
	{	
		if(index > 32)
			return NULL;
		index++;
	}
	return return_addr(index,remove_addr(index));
}
int my_free(void* addr,int size)
{
	int index = log2(size);
	void *buddy;
	int find_buddy = ((((char*)memory_start - (char*)addr))/size);
	if(find_buddy % 2 != 0 )
		buddy = (char*)addr - size;
	else
		buddy = (char*)addr + size;
	if(buddy < memory_start || buddy > last_valid_address)
		buddy = NULL;
	if(!buddy)
		return 0;
	if(freeLists[index])
	{
		for(int it = 0;it < freeLists[index]->ptr.size();it++)
		{
			if(freeLists[index]->ptr[it] == buddy)
			{
				freeLists[index]->ptr.erase(freeLists[index]->ptr.begin() + it);
				if(find_buddy % 2 != 0)
					addr = buddy;
				break;
			}
			else
			{
				freeLists[index]->ptr.push_back(addr);
				return 0;
			}
		}
		my_free(addr,size*2);
	}
	freeLists[index] = new mem_ptr;
	freeLists[index]->ptr.push_back(addr);
return 0;
}
void show_freeList()
{
	for (int i = 5; i < 32; ++i)
	{
		if(freeLists[i] != NULL)
		{
			for(std::vector<void*>::iterator it = freeLists[i]->ptr.begin() ; it != freeLists[i]->ptr.end() ; it++)
				cout << "i= " << i << "address= " << *it<< "\n";
		}
	}
}