#ifndef CUSTOM_ROUTING_H 
#define CUSTOM_ROUTING_H

// CONSTANTS
#define TABLE_SIZE 500

// STRUCTURES
/**
 * Represents a basic mapping between a URL request path 
 * and its corresponding physical file on the disk.
 */
struct route {
    char *r_req_path;
    char *r_file_path;
};
/**
 * A container for the Hash Table buckets.
 * Each node stores the req_path-file_path pair and a pointer to the next 
 * node in case of a hash collision.
 */
struct node {
    char *n_req_path;
    char *n_file_path;
    struct node *next;
};

// Prototypes
int init_routes(struct route routes[]);
char *lookup_route(char *req_path);

#endif