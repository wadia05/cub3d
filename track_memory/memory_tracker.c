#include "memory_tracker.h"


void *tracker_malloc(size_t size, tracker_t **hd_tracker) 
{
    void *address_data = malloc(size);
    if (address_data == NULL)
        return NULL;
    
    tracker_t *node = malloc(sizeof(tracker_t));
    if (node == NULL) {
        free(address_data);
        return NULL;
    }

    node->address = address_data;
    node->next_addr = *hd_tracker;
    *hd_tracker = node;
    return node->address;
}

// Function to free all allocated memory
void free_all_allocate(tracker_t **hd_tracker) 
{
    if (*hd_tracker == NULL)
        return;
    
    tracker_t *curr = *hd_tracker;
    tracker_t *next;
    
    while (curr != NULL) {
        next = curr->next_addr;
        
        // Check if the address is already free before freeing it
        if (curr->address != NULL) {
            free(curr->address);
            curr->address = NULL;
        }
        
        free(curr);
        curr = next;
    }
    
    *hd_tracker = NULL;
}


// int main ()
// {
//     char *str = tracker_malloc (sizeof(char));
//     str[0]='s';
//     // char *sls = tracker_malloc (sizeof(-77));

//     free_all_allocate();
//     // char *ll = malloc(sizeof(int)*2);
//     int *nub = tracker_malloc (sizeof(int)*2);
//     nub[0] = 2;
//     while(1){};
// }