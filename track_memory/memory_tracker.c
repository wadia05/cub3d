#include "memory_tracker.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Include stdlib for malloc/free

// Function to allocate memory and track it
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

    // Zero out the memory to prevent potential use of uninitialized memory
    memset(node, 0, sizeof(tracker_t));

    node->address = address_data;
    node->next_addr = *hd_tracker;
    *hd_tracker = node;

    return address_data;
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

        // Free the tracked address first
        if (curr->address != NULL) {
            free(curr->address);
            curr->address = NULL;
        }

        // Then free the tracking node
        free(curr);
        curr = next;
    }

    *hd_tracker = NULL;
}

// // Main function
// int main()
// {
//     tracker_t *hd_tracker = NULL; // Initialize the tracker

//     // Allocate memory for a single character
//     char *str = tracker_malloc(sizeof(char), &hd_tracker);
//     if (str == NULL) {
//         printf("Failed to allocate memory for str\n");
//         free_all_allocate(&hd_tracker);
//         return 1;
//     }
//     str[0] = 's';

//     // Allocate memory for an array of 2 integers
//     int *nub = tracker_malloc(sizeof(int) * 2, &hd_tracker);
//     if (nub == NULL) {
//         printf("Failed to allocate memory for nub\n");
//         free_all_allocate(&hd_tracker);
//         return 1;
//     }
//     nub[0] = 2;
//     nub[1] = 3;

//     // Free all allocated memory
//     free_all_allocate(&hd_tracker);

//     return 0; // Exit successfully
// }
