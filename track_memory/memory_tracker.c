#include "memory_tracker.h"

static tracker_t *hd_tracker = NULL; 

void *tracker_malloc(size_t size)
{
    void *address_data = malloc(size);
    if (address_data == NULL)
        return NULL;
    
    tracker_t *node = malloc (sizeof(tracker_t));
    if(node == NULL)
    {
        free(address_data);
        return NULL;
    }

    node->address = address_data;
    node->next_addr = hd_tracker;
    hd_tracker = node;
    return node->address;
}
void free_all_allocate()
{
    if (hd_tracker == NULL)
        return;
    
    tracker_t *curr = hd_tracker ;
    tracker_t *next;
    
    while (curr != NULL)
    {
        next = curr->next_addr;
        free(curr->address);
        free(curr);
        curr = next;
    }
    hd_tracker = NULL;
}


int main ()
{
    char *str = tracker_malloc (sizeof(char));
    char *nub = tracker_malloc (sizeof(int));
    char *sls = tracker_malloc (sizeof(-77));

    free_all_allocate();
    while(){}
}