#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

/**
 * Initialize the memory manager with provided capacity.
 * @param[in]   capacity    Total number of bytes available to memory manager
 * @return 0 on success, -1 otherwise
 */
int initialize_manager(int capacity);

/**
 * Request memory manager to provide a buffer of \p request_size bytes.
 * @param[in]   request_size    Number of bytes to be allocated
 * @return Pointer to allocated memory region on success, NULL otherwise
 */
void *my_malloc(int request_size);

/**
 * Return the \p buffer back to the memory manager
 * @param[in]   buffer  Pointer to buffer region provided by \p my_malloc
 */
void my_free(void *buffer);

/**
 * Get the size of each chunk's header. The header size is being maintained same
 * for allocated and free chunks.
 * @return Size of chunk header
 */
int chunk_header_size();

/**
 * Display the internal state of the memory manager.
 * The display format is [start_address, end_address, size_of_chunk, state]
 * where state is one of {"chunk_header", "allocated_chunk", "free_chunk"}
 *
 * For example:
 * \code{.c}
 * int main() {
 *  display_manager();
 *  // prints nothing
 *
 *  initialize_manager(1000);
 *  assert(chunk_header_size() == 10);
 *
 *  display_manager();
 *  //  0   9   10  header
 *  //  10  999 990 free
 *
 *  void *first = my_malloc(100);
 *  display_manager();
 *  //  0   9   10  header
 *  //  10  109 100 allocated
 *  //  110 119 10  header
 *  //  120 999 880 free
 *
 *  my_free(first);
 *  display_manager();
 *  //  0   9   10  header
 *  //  10  109 100 free
 *  //  110 119 10  header
 *  //  120 999 880 free
 * }
 * \endcode
 */
void display_manager();

#endif
