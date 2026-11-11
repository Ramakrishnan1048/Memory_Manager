#include <assert.h>

#include "memory_manager.h"

int main() {
  display_manager();
  // prints nothing

  initialize_manager(1000);
  assert(chunk_header_size() == 10);
  display_manager();
  //  0   9   10  chunk_header
  //  10  999 990 free_chunk

  void *first = my_malloc(100);

  display_manager();
  //  0   9   10  chunk_header
  //  10  109 100 allocated_chunk
  //  110 119 10  chunk_header
  //  120 999 880 free_chunk

  my_free(first);

  display_manager();
  //  0   9   10  chunk_header
  //  10  999 990 free_chunk

  first = my_malloc(100);

  display_manager();
  //  0   9   10  chunk_header
  //  10  109 100 allocated_chunk
  //  110 119 10  chunk_header
  //  120 999 880 free_chunk

  my_free(first);

  display_manager();
  //  0   9   10  chunk_header
  //  10  999 990 free_chunk
}
