#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Custom Headers
#include "./custom_routing.h"

// Variables
static struct node *routes_table[TABLE_SIZE];

/* Implements the "djb2" Hash Function by Dan Bernstein. */
static unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

/**
 * Initializes the global hash table using an array of route configurations.
 * Iterates through the routes, hashes the keys, and performs "insertion at head"
 * to handle collisions within the table buckets.
 */
int init_routes(struct route routes[]) {
    for (int i = 0; routes[i].r_req_path != NULL; i++) {
        unsigned long hashed_v = hash(routes[i].r_req_path);
        int index = hashed_v % TABLE_SIZE;

        struct node *n = malloc(sizeof(struct node));
        if (n == NULL) {
            perror("Error allocating memory for route node.\n");
            return -1;
        }
        n->n_req_path = routes[i].r_req_path;
        n->n_file_path = routes[i].r_file_path;
        n->next = routes_table[index];

        routes_table[index] = n;
    }

    return 0;
}

/**
 * Searches the hash table for a specific request path.
 * Returns the corresponding file path if found, or NULL if the route 
 * is not defined.
 */
char *lookup_route(char *req_path) {
    unsigned long hashed_v = hash(req_path);
    int index = hashed_v % TABLE_SIZE;

    struct node *cursor = routes_table[index];
    while (cursor != NULL) {
        if (strcmp(cursor->n_req_path, req_path) == 0) return cursor->n_file_path;

        cursor = cursor->next;
    }
    
    return NULL;
}