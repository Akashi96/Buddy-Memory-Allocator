/*input
 
*/
///-------------------------------------------------------------------------------------
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
#include "my_allocator.h"


using namespace std;

int main()
{	
	 init_allocator(5,1024);
	// release_allocator();
	 void *addr = my_malloc(64);
	 cout <<"address" << addr<<endl;
	show_freeList();
	cout <<"Free list after free()\n";
	my_free(addr,64);
	show_freeList();
	return 0;
}