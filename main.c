// LIBRARIES
#include <stdio.h>
#include <sys/socket.h> // For core functions such as 'socket', 'bind', 'listen'
#include <netinet/in.h> // For the 'sockaddr_in' structure and constants such as 'INADDR_ANY'
#include <string.h> // To reset the struct memory
#include <unistd.h> // For the 'close' function
#include <stdlib.h> // For memory management
// EXTERNAL FILES
#include "./functions.c"

int main(void) {
    // SOCKET
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed.\n");
        return 1;
    }
    printf("Socket created succesfully.\n");

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET; // IPv4
    address.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
    address.sin_port = htons(8080); // Set the port (htons gives the number to the OS in 'BigEndian style')

    // BIND
    int bind_status = bind(sockfd, (struct sockaddr *)&address, sizeof(address));
    if (bind_status < 0) {
        perror("Binding failed.\n");
        return 2;
    }
    printf("Binding successful.\n");

    // LISTEN
    int listen_status = listen(sockfd, 10);
    if (listen_status < 0) {
        perror("Listening process failed.\n");
        return 3;
    }
    printf("Listening successful.\n");

    // ACCEPT
    struct sockaddr_in client_address;
    socklen_t addr_len = sizeof(client_address);
    while(1) {
        printf("\n---- Waiting for a new connection... ----\n");
        
        // Create a new socket for the specific connection
        int new_socket = accept(sockfd, (struct sockaddr *)&client_address, &addr_len);
        if (new_socket < 0) {
            perror("Error while trying to accept.\n");
            continue;
        }

        // Connection established message
        printf("\nConnection with client established.\n");
        printf("-----------------------------------\n");

        // READ
        // Create a buffer and store the request text in it
        char buffer[1024];
        int bytes_read = read(new_socket, buffer, sizeof(buffer) - 1);
        if (bytes_read < 0) {
            perror("Error while reading.\n");
            close(new_socket);
            continue;
        }
        buffer[bytes_read] = '\0';
        printf("%s\n", buffer);

        // 'Strip' the request text to get the specific request path
        char req_path[256];
        sscanf(buffer, "GET %255s", req_path);

        // WRITE
        if (serve_file(new_socket, req_path) < 0) {
            perror("Error while responding.\n");
            close(new_socket);
            continue;
        }

        // Close the connection specific socket
        close(new_socket);
    }

    return 0;
}
