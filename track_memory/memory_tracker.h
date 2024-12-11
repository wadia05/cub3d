#ifndef MEMORY_TRACKER
#define MEMORY_TRACKER

#include <stdlib.h>

typedef struct tracker_s
{
    void *address;
    struct tracker_s *next_addr;
} tracker_t;

void *tracker_malloc(size_t size, tracker_t **hd_tracker) ;
void free_all_allocate(tracker_t **hd_tracker);

#endif