//	FIRST FIT method
//	Done by :
//	Ramakrishnan K
//	PES1201701906
//	4th SEM
//	PESU

#include <stdio.h>
#include <stdlib.h>

#include "a.h"

#pragma pack(2)
#define BLOCK_SIZE sizeof(block_)

char *p = NULL;
static int SIZE = 0;

typedef union block_
{
	struct
	{
		char status_;	// is free('0') or allocated('1')
		int size_;		// size of block (bytes)
		int next_;		// index of next block (-1 is NULL)
	}metadata_;
	char ALIGN[10];	// Align size of structure to 10 bytes. ALIGN is not used.
}block_;

void allocate(int n)
{
	/*// Check if p is aldready allocated and free if so.
	// May cause SEGMENTATION fault if previous mymalloc calls are dereferenced without passing to myfree.
	if(p != NULL)
	{	
		free(p);
		p = NULL;
	}
	*/
	block_ *temp;
	p = (char*)malloc(sizeof(char)*n);
	if(p!=NULL)
	{
		// p is allocated. New block is initialised.
		temp = (block_*)p;
		temp->metadata_.status_ = '0';
		temp->metadata_.size_ = n - BLOCK_SIZE;
		temp->metadata_.next_ = -1;
		// SIZE is global and stores size of array allocated.
		SIZE = n;
	}
	else
	{
		// p is not allocated. Handled using SIZE variable.
		SIZE = 0;
	}
}

void* mymalloc(int size)
{
	
	if(SIZE == 0)
	{
		return NULL;
	}
	
	void *retAddr = NULL;
	int n;
	int i = 0;
	int j = 0;
	block_ *present;
	block_ *next;
	
	present = (block_*)(&p[0]);
	n = SIZE;
	while( i < n )
	{
		present = (block_ *)(&p[i]);
		i = i + BLOCK_SIZE;
		if( present->metadata_.status_ == '1' )
		{
			i = i + present->metadata_.size_;
		}
		else if(present->metadata_.size_ < size )
		{
			i = i + present->metadata_.size_;
		}
		// Check if appropriate block is found, keep going to next block until then.
		else
		{
			// FIRST FIT ALGORITHM
			retAddr = (void*)(&p[i]);
			j = i;
			// Find next block.
			i = i + size;
			block_ *temp = (block_*)(&p[i]);
			i = i + BLOCK_SIZE;
			if(present->metadata_.next_ == -1)
			{
				// Last block. No next block
				temp->metadata_.status_ = '0';
				temp->metadata_.size_ = n - i;
				temp->metadata_.next_ = -1;
				present->metadata_.next_ = i - BLOCK_SIZE;
			}
			else
			{
				// In between block
				present->metadata_.next_ = i - BLOCK_SIZE;
			}
			// Update First block
			present->metadata_.status_ = '1';
			present->metadata_.size_ = size;
			return retAddr;
		}
	}
	// return NULL if not found.
	return NULL;
}

void myfree(void *b)
{
	if(SIZE == 0 || b == NULL)
	{
		return ;
	}
	int n;
	int i=0;
	block_ *present;
	block_ *previous;
	
	present = (block_*)(&p[0]);
	n = SIZE;
	while(i<n)
	{
		previous = present;
		present = (block_*)(&p[i]);
		i = i + BLOCK_SIZE;
		if(present->metadata_.status_ == '0')
		{
			i = i + present->metadata_.size_;
		}
		else if(b == (void*)(&p[i]))
		{
			// Address is present in p
			block_ *next;
			i = i + present->metadata_.size_;
			next = (block_*)(&p[i]);
			i = i + BLOCK_SIZE;
			if(next->metadata_.status_ == '0')
			{
				// Next block is free
				present->metadata_.size_ += BLOCK_SIZE + next->metadata_.size_;
				present->metadata_.next_ = next->metadata_.next_;
			}
			if(previous != present)
			{
				// Previous block is not first, and is free
				if(previous->metadata_.status_ == '0')
				{
					previous->metadata_.size_ += BLOCK_SIZE + present->metadata_.size_;
					previous->metadata_.next_ = present->metadata_.next_;
				}
			}
			// Mark as free
			present->metadata_.status_ = '0';
			return ;
		}
	}
	// Address not in p
	printf("INVALID ADDRESS\n");
}

void print_book()
{
	// Size for both allocated and free bookkeeping is size of block_
	printf("%lu\n%lu\n\n", sizeof(block_), sizeof(block_));
}

void display_mem_map()
{
	if(SIZE == 0)
	{
		return ;
	}
	block_ *present;
	int n;
	int i=0;
	int start;
	int size;
	int status;
	
	present = (block_*)(&p[0]);
	n = SIZE;
	while(i<n && i != -1)
	{
		// Untill i becomes NULL or >n
		present = (block_*)(&p[i]);
		
		if(present->metadata_.size_ != 0)
			{
			start = i;
			size = BLOCK_SIZE;
			printf("%d\t%d\tbook\n", start, size);
			i = i + size;
			
			start = i;
			size = present->metadata_.size_;
			printf("%d\t%d\t", start, size);
			if(present->metadata_.status_ == '0')
			{
				printf("free\n");
			}
			else
			{
				printf("allocated\n");
			}
		}
		i = present->metadata_.next_;
	}
	printf("\n");
}

#if 0
int main()
{
	allocate(100);
	print_book();
	char *p1, *p2, *p3, *p4, *p5;
	display_mem_map();
	
	p1 = mymalloc(30);
	display_mem_map();
	
	p2 = mymalloc(40);
	display_mem_map();
	
	p3 = mymalloc(40);
	display_mem_map();
	
	myfree(p3);
	display_mem_map();
	
	p4 = mymalloc(20);
	display_mem_map();
	
	myfree(p5);
	display_mem_map();
	
	myfree(p4);
	display_mem_map();
	
	myfree(p2);
	display_mem_map();
	
	myfree(p1);
	display_mem_map();
	
	free(p);
	return 0;
}
#endif
