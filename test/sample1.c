#include "memory_manager.h"
#include <stdio.h>

void main() {
  display_manager();
  initialize_manager(100);
  display_manager();

  char *p = (char *)my_malloc(2 * sizeof(char));
  display_manager();
  printf("\n");

  char *q = (char *)my_malloc(5 * sizeof(char));
  display_manager();
  printf("\n");

  char *r = (char *)my_malloc(4 * sizeof(char));
  display_manager();
  printf("\n");

  my_free(p);

  display_manager();
  printf("\n");

  my_free(q);

  display_manager();
  printf("\n");

  my_free(r);

  display_manager();
  printf("\n");
}
