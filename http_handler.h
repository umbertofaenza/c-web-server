#ifndef HTTP_HANDLER_H 
#define HTTP_HANDLER_H

// Structures
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
int handle_request(int sockfd, char*req_path);
int serve_file(int sockfd, char *file_path, char *res_code);
char *get_mime(char *file_path);

#endif