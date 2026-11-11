#include <stdio.h>

#include "memory_manager.h"

const int CAPACITY = 100;

int main() {
  printf("Size of allocated chunk header: %lu\n", chunk_header_size());
  printf("Size of free chunk header: %lu\n\n", chunk_header_size());

  printf("Initialize memory manager with %lu bytes\n", CAPACITY);
  initialize_manager(CAPACITY);

  printf("Current state of manager:\n");
  display_manager();

  char *p1;
  int p1_size = 30;

  char *p2;
  int p2_size = 40;

  char *p3;
  int p3_size = 40;

  char *p4;
  int p4_size = 20;

  char *p5;
  int p5_size = 90;

  printf("Allocate %lu bytes\n", p1_size);
  p1 = my_malloc(p1_size);
  display_manager();

  printf("Allocate %lu bytes\n", p2_size);
  p2 = my_malloc(p2_size);
  display_manager();

  printf("Allocate %lu bytes\n", p3_size);
  p3 = my_malloc(p3_size);
  display_manager();

  printf("Free p3 of %lu bytes\n", p3_size);
  my_free(p3);
  display_manager();

  printf("Allocate %lu bytes\n", p4_size);
  p4 = my_malloc(p4_size);
  display_manager();

  printf("Allocate %lu bytes\n", p5_size);
  p5 = my_malloc(p5_size);
  display_manager();

  printf("Free p5 of %lu bytes\n", p5_size);
  my_free(p5);

  printf("Free p4 of %lu bytes\n", p4_size);
  my_free(p4);
  display_manager();

  printf("Free p2 of %lu bytes\n", p2_size);
  my_free(p2);
  display_manager();

  printf("Free p1 of %lu bytes\n", p1_size);
  my_free(p1);
  display_manager();
  return 0;
}
