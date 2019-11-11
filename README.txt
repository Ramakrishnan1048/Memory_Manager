	MEMORY MANAGER


1. Allocation Policy :	FIRST FIT
2. Bookkeeping details :
	1. Bookkeeping stores (for both ALLOCATED and FREE):
		char status -> 0 if free, and 1 if allocated.
		int size -> size of the allocated block.
		int next -> -1 if there is no next block, otherwise index to the next block.
	2. Union with charecter array of 10 bytes, for uniformity and better understanding.
	3. The above attributes are encapsulated into a structure called metadata_ and within the union called block_
3. A test main() function is commented in the implementation. It is neccesary to free 'extern char *p' in the client function to prevent memory leak.
4. Uses sequential search through all blocks to find free blocks -> O(n)
5. Transition form one block to another is through index element i in most functions. (next) index is used for displaying memory map.
6. Uses static int SIZE to store allocated size.
7. LOGIC:
	mymalloc(int n)
	while(block i exists in p)
		if(block i is not free)
			i <- next block
		else if(block size is lower than required)
			i <- next block
		else
			// suitable block is found
			find return address.
			update next block details if next exists
			update current block details
			return address
	return NULL
	
	myfree(void *p)
	while(block i exists in p)
		if (block i is free)
			i <- next block
		else if(p = address of block i)
			check if next block is free
				merge with current
			check if previous block is free
				merge with current
			update current block details
		i <- next block
	

8. For compiling : gcc src.c test_client.c
9. Run: ./a.out