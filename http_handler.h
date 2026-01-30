#ifndef HTTP_HANDLER_H 
#define HTTP_HANDLER_H

// Prototypes
int handle_request(int sockfd, char*req_path);
int serve_file(int sockfd, char *file_path, char *res_code);

#endif