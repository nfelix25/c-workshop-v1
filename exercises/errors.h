#ifndef ERRORS_H
#define ERRORS_H

#include <unistd.h>
#include <string.h>

#define RESPONSE_400 "HTTP/1.1 400 Bad Request\n\n"
#define RESPONSE_404 "HTTP/1.1 404 Not Found\n\n"
#define RESPONSE_413 "HTTP/1.1 413 Content Too Large\n\n"
#define RESPONSE_500 "HTTP/1.1 500 Internal Server Error\n\n"
#define RESPONSE_200 "HTTP/1.1 200 OK\n\n"

#define RESPONSE_400_LEN strlen(RESPONSE_400)
#define RESPONSE_404_LEN strlen(RESPONSE_404)
#define RESPONSE_413_LEN strlen(RESPONSE_413)
#define RESPONSE_500_LEN strlen(RESPONSE_500)
#define RESPONSE_200_LEN strlen(RESPONSE_200)

enum error_code {
    ERR_400 = 400,
    ERR_404 = 404,
    ERR_413 = 413,
    ERR_500 = 500
};

int handle_400(int socket_fd);
int handle_404(int socket_fd);
int handle_413(int socket_fd);
int handle_500(int socket_fd);

#endif
