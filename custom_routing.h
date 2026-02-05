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
/**
 * A mapping structure that associates a file extension with its 
 * corresponding MIME type.
 * This structure is used by the server's MIME-type detection system 
 * to ensure that the 'Content-Type' header in the HTTP response 
 * accurately reflects the nature of the file being served (e.g., ".css" -> "text/css").
 */
struct mime_entry {
    char *extension;
    char *mime_type;
};

// Prototypes
int init_routes(struct route routes[]);
char *lookup_route(char *req_path);
char *get_mime(char *file_path);

#endif