#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h> 

// Prototypes
int handle_404(int sockfd);
int serve_file(int sockfd, char *req_path);

/**
 * Serves requested files to the client.
 * Maps specific URL paths to local files in the 'public/' directory,
 * calculates the file size for the HTTP 'Content-Length' header,
 * and sends the complete HTTP response (header + body) to the socket.
 * If the file is not found, it redirects the flow to the 404 handler.
 */
int serve_file(int sockfd, char *req_path) {
    // Initialize a ptr to the file
    FILE *file = NULL;

    // Open file based on requested path
    if (strcmp(req_path, "/") == 0) {
        file = fopen("public/index.html", "rb");
    } else if (strcmp(req_path, "/about") == 0) {
        file = fopen("public/about.html", "rb");
    } else {
        return handle_404(sockfd);
    }

    // Check for errors in opening the file
    if (file == NULL) {
        perror("Error opening file.\n");
        return -1;
    }
    // Find the file size
    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Read file into the file buffer
    char *file_buffer = malloc(file_size);
    fread(file_buffer, sizeof(char), file_size, file);

    // Build header
    char header[512];
    snprintf(
        header, 
        sizeof(header), 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %d\r\n"
        "\r\n",
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
 * Sends a 404 Not Found response to the client.
 * This function attempts to open and serve a custom 'public/404.html' file. 
 * If the custom error file is missing, it provides a hardcoded HTML fallback 
 * to ensure the client always receives a valid HTTP response. 
 */
int handle_404(int sockfd) {
    // Open 404.html file
    FILE *file = fopen("public/404.html", "rb");
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

    // Build header
    char header[512];
    snprintf(
        header, 
        sizeof(header), 
        "HTTP/1.1 404 NOT FOUND\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %d\r\n"
        "\r\n",
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
