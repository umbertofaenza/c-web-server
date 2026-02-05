#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h>
// Custom Headers
#include "./http_handler.h"
#include "./custom_routing.h"
// Variables
struct mime_entry mime_types[] = {
    {"txt",  "text/plain"},
    {"html", "text/html"},
    {"css",  "text/css"},
    {"js",   "application/javascript"},
    {"png",  "image/png"},
    {"jpg",  "image/jpeg"},
    {"jpeg", "image/jpeg"},
    {"webp", "image/webp"},
    {NULL,   NULL} 
};

/**
 * Processes the incoming HTTP request path using a Hash Table lookup.
 * This function queries the routing system to map the client's URL 
 * (e.g., "/about") to its corresponding local file path. It handles
 * the 404 logic if the route is not found and delegates the file 
 * transmission to 'serve_file'.
 */
int handle_request(int sockfd, char *req_path) {
    char *res_code = "200 OK";
    char *file_path = lookup_route(req_path);

    if (file_path == NULL) {
        file_path = "public/404.html";
        res_code = "404 NOT FOUND";
    }

    return serve_file(sockfd, file_path, res_code);
}

/**
 * Reads a local file and sends it to the client over the socket with proper HTTP headers.
 * This function handles the low-level operations: opening the file in binary mode, 
 * calculating the content length, allocating memory, and transmitting the header and body.
 * It includes a safety fallback: if the requested file cannot be opened (e.g., missing 404.html),
 * it sends a hardcoded raw HTML 404 response to ensure the client receives a valid reply.
 */
int serve_file(int sockfd, char *file_path, char *res_code) {
    // Initialize a ptr to the file
    FILE *file = fopen(file_path, "rb");
    // Check for errors in opening the file
    if (file == NULL) {
        char *backup_404 = "HTTP/1.1 404 NOT FOUND\r\nContent-Length: 22\r\n\r\n<h1>404 Not Found</h1>";
        return write(sockfd, backup_404, strlen(backup_404));
    }

    // Find the file size
    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Read file into the file buffer
    char *file_buffer = malloc(file_size);
    fread(file_buffer, sizeof(char), file_size, file);

    // Find MIME type based on file extension
    char *mime = get_mime(file_path);

    // Build header
    char header[512];
    snprintf(
        header, 
        sizeof(header), 
        "HTTP/1.1 %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %d\r\n"
        "\r\n",
        res_code,
        mime,
        file_size
    );

    // Write header
    int sent_bytes = 0;
    int status = write(sockfd, header, strlen(header));
    if (status < 0) {
        free(file_buffer);
        fclose(file);
        return -1;
    }
    sent_bytes += status;
    // Write body
    status = write(sockfd, file_buffer, file_size);
    if (status < 0) {
        free(file_buffer);
        fclose(file);
        return -1;
    }
    sent_bytes += status;

    // Free memory
    free(file_buffer);
    // Close file
    fclose(file);

    return sent_bytes;
}

/**
 * Determines the MIME type of a file based on its extension.
 * If the extension is missing, malformed, or not found in the predefined lookup table, 
 * it defaults to "application/octet-stream" to ensure a safe binary transmission.
 */
char *get_mime(char *file_path) {
    // Get the substring starting from the last dot in the file_path (the file extension)
    char *file_ext = strrchr(file_path, '.');
    // If there is no file extension or the dot is the last character of the string (besides the null terminator)
    // return application/octet-stream
    if (file_ext == NULL || *(file_ext + 1) == '\0') {
        return "application/octet-stream";
    }

    // Get the extension without the dot
    file_ext = file_ext + 1;
    // Iterate through the mime_types associative array and check for the specific extension
    for (int i = 0; mime_types[i].extension != NULL; i++) {
        if (strcasecmp(mime_types[i].extension, file_ext) == 0) return mime_types[i].mime_type;
    }

    // If the file_path extension was included in the mime_types, return application/octet-stream
    return "application/octet-stream";
}
