#include<stdio.h>
#include"a.h"
void main()
{
	 allocate(100);
	 char* p = (char*)mymalloc(2*sizeof(char));
	 display_mem_map();
	 printf("\n");
	 char* q = (char*)mymalloc(5*sizeof(char));
	 display_mem_map();
	 printf("\n");
	 char* r = (char*)mymalloc(4*sizeof(char));
	 display_mem_map();
	 printf("\n");
	 myfree(p);
	 display_mem_map();
	 printf("\n");
	 myfree(q);
	 display_mem_map();
	 printf("\n");
}
