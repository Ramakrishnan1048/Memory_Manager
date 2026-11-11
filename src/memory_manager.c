//	FIRST FIT method
//	Done by :
//	Ramakrishnan K
//	PES1201701906
//	4th SEM
//	PESU

#include <stdio.h>
#include <stdlib.h>

#include "memory_manager.h"

#pragma pack(2)
#define BLOCK_SIZE sizeof(block_)

char *p = NULL;
static int SIZE = 0;

typedef union block_ {
  struct {
    char status_; // is free('0') or allocated('1')
    int size_;    // size of block (bytes)
    int next_;    // index of next block (-1 is NULL)
  } metadata_;
  char ALIGN[10]; // Align size of structure to 10 bytes. ALIGN is not used.
} block_;

int initialize_manager(int capacity) {
  /*// Check if p is aldready allocated and free if so.
  // May cause SEGMENTATION fault if previous mymalloc calls are dereferenced
  without passing to myfree. if(p != NULL)
  {
          free(p);
          p = NULL;
  }
  */
  block_ *temp;
  p = (char *)malloc(sizeof(char) * capacity);
  if (p != NULL) {
    // p is allocated. New block is initialised.
    temp = (block_ *)p;
    temp->metadata_.status_ = '0';
    temp->metadata_.size_ = capacity - BLOCK_SIZE;
    temp->metadata_.next_ = -1;
    // SIZE is global and stores size of array allocated.
    SIZE = capacity;
  } else {
    // p is not allocated. Handled using SIZE variable.
    SIZE = 0;
    return -1;
  }
  return 0;
}

void *my_malloc(int request_size) {

  if (SIZE == 0) {
    return NULL;
  }

  void *retAddr = NULL;
  int n;
  int i = 0;
  int j = 0;
  block_ *present;
  block_ *next;

  present = (block_ *)(&p[0]);
  n = SIZE;
  while (i < n) {
    present = (block_ *)(&p[i]);
    i = i + BLOCK_SIZE;
    if (present->metadata_.status_ == '1') {
      i = i + present->metadata_.size_;
    } else if (present->metadata_.size_ < request_size) {
      i = i + present->metadata_.size_;
    }
    // Check if appropriate block is found, keep going to next block until then.
    else {
      // FIRST FIT ALGORITHM
      retAddr = (void *)(&p[i]);
      j = i;
      // Find next block.
      i = i + request_size;
      block_ *temp = (block_ *)(&p[i]);
      i = i + BLOCK_SIZE;
      if (present->metadata_.next_ == -1) {
        // Last block. No next block
        temp->metadata_.status_ = '0';
        temp->metadata_.size_ = n - i;
        temp->metadata_.next_ = -1;
        present->metadata_.next_ = i - BLOCK_SIZE;
      } else {
        // In between block
        present->metadata_.next_ = i - BLOCK_SIZE;
      }
      // Update First block
      present->metadata_.status_ = '1';
      present->metadata_.size_ = request_size;
      return retAddr;
    }
  }
  // return NULL if not found.
  return NULL;
}

void my_free(void *buffer) {
  if (SIZE == 0 || buffer == NULL) {
    return;
  }
  int n;
  int i = 0;
  block_ *present;
  block_ *previous;

  present = (block_ *)(&p[0]);
  n = SIZE;
  while (i < n) {
    previous = present;
    present = (block_ *)(&p[i]);
    i = i + BLOCK_SIZE;
    if (present->metadata_.status_ == '0') {
      i = i + present->metadata_.size_;
    } else if (buffer == (void *)(&p[i])) {
      // Address is present in p
      block_ *next;
      i = i + present->metadata_.size_;
      next = (block_ *)(&p[i]);
      i = i + BLOCK_SIZE;
      if (next->metadata_.status_ == '0') {
        // Next block is free
        present->metadata_.size_ += BLOCK_SIZE + next->metadata_.size_;
        present->metadata_.next_ = next->metadata_.next_;
      }
      if (previous != present) {
        // Previous block is not first, and is free
        if (previous->metadata_.status_ == '0') {
          previous->metadata_.size_ += BLOCK_SIZE + present->metadata_.size_;
          previous->metadata_.next_ = present->metadata_.next_;
        }
      }
      // Mark as free
      present->metadata_.status_ = '0';
      return;
    }
  }
  // Address not in p
  printf("INVALID ADDRESS\n");
}

int chunk_header_size() {
  // Size for both allocated and free bookkeeping is size of block_
  return sizeof(block_);
}

void display_manager() {
  if (SIZE == 0) {
    return;
  }
  block_ *present;
  int n;
  int i = 0;
  int start;
  int end;

  int size;
  int status;

  present = (block_ *)(&p[0]);
  n = SIZE;
  while (i < n && i != -1) {
    // Untill i becomes NULL or >n
    present = (block_ *)(&p[i]);

    if (present->metadata_.size_ != 0) {
      start = i;
      size = BLOCK_SIZE;
      end = start + size - 1;
      printf("%d\t%d\t%d\tchunk_header\n", start, end, size);

      i = i + size;

      start = i;
      size = present->metadata_.size_;
      end = start + size - 1;

      printf("%d\t%d\t%d\t", start, end, size);
      if (present->metadata_.status_ == '0') {
        printf("free_chunk\n");
      } else {
        printf("allocated_chunk\n");
      }
    }
    i = present->metadata_.next_;
  }
  printf("\n");
}
