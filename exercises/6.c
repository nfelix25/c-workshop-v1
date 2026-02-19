#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <errno.h>

#include "extensions.h"
#include "errors.h"

#ifdef __linux__
#include <sys/sendfile.h>
#endif

// 👉 First, build and run the program.
//
// To do this, make sure you're in the `exercises` directory, and then run:
//
// gcc -o app6 6.c && ./app6

#define PORT 8080
#define MAX_REQUEST_BYTES 32768


const char* DEFAULT_FILE = "index.html";

char *to_path(char *req) {
    char *start = req;

    while (start[0] != ' ') {
        start++;

        if (start[0] == 0) {
            return NULL;
        }
    }

    start++;

    char *end = start;
    char *last_slash = NULL;
    char *last_dot = NULL;

    while(end[0] != ' ') {
        switch (end[0]) {
            case '/':
                last_slash = end;
                break;
            case '.':
                last_dot = end;
                break;
            case '\0':
                return NULL;
        }

        end++;
    }

    // OPTIONS requests (and requests via proxies) may not start with '/'
    // For now, we don't support these requests. (We could always add support, though!)
    if (last_slash == NULL) {
        return NULL;
    }

    // If there's no file extension, default to index.html as the filename.
    if (last_dot == NULL || last_slash > last_dot) {
        end[0] = '/';

        if (end > last_slash + 1) {
            end++;
        }

        // If there isn't enough room to copy in "index.html" then return NULL.
        // (This only happens if the request has no headers, which should only
        // come up in practice if the request is malformed or something.)
        if (end + strlen(DEFAULT_FILE) > req + strlen(req)) {
            return NULL;
        }

        memcpy(end, DEFAULT_FILE, strlen(DEFAULT_FILE) + 1);
    } else {
        end[0] = '\0';
    }

    // Skip the leading '/'
    return start + 1;
}

size_t write_response_header(char ext[4], char *resp_str) {
    char *content_type;

    content_type = extension_to_content_type(ext);

    printf("Content-Type: %s\n", content_type);

    return sprintf(resp_str, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n", content_type);
}

int handle_req(char *request, int socket_fd) {
    char *path = to_path(request);

    if (path == NULL) {
        return handle_404(socket_fd);
    }

    int fd = open(path, O_RDONLY);

    if (fd == -1) {
        if (errno == ENOENT) {
            return handle_404(socket_fd);
        } else {
            return handle_500(socket_fd);
        }
    }

    struct stat stats;

    // Populate the `stats` struct with the file's metadata
    // If it fails (even though the file was open), respond with a 500 error.
    if (fstat(fd, &stats) == -1) {
        return handle_500(socket_fd);
    }

    // Write the header to the socket ("HTTP/1.1 200 OK" followed by a Content-Type header)
    {
        char ext[4] = {0};

        {
            char *path_ext = strrchr(path, '.'); // Could skip the strrchr() if done in to_path
            size_t ext_len = strlen(path_ext);

            // If the extension is less than 4 bytes (5, counting the '.'), set it to NULL.
            if (path_ext != NULL && ext_len <= 5) {
                strncpy(ext, path_ext + 1, ext_len - 1);
            }
        }

        char resp_str[1024]; // Our responses are short, e.g. "200 OK\n\nContent-Type: text/css"
        size_t resp_length = write_response_header(ext, resp_str);
        ssize_t bytes_to_write = resp_length;
        ssize_t bytes_written = 0;

        while (bytes_to_write) {
            bytes_written = write(socket_fd, resp_str + bytes_written, bytes_to_write);

            if (bytes_written == -1) {
                // If sending the 200 didn't succeed, the odds of 500 succeeding aren't great!
                return handle_500(socket_fd);
            }

            bytes_to_write -= bytes_written;
        }
    }

    {
        // Send the file's contents to the socket as the response body
        ssize_t bytes_to_send = stats.st_size;

        while (bytes_to_send > 0) {
            // 👉 `sendfile` works differently on different operating systems!
            //
            // Try implementing it for both operating systems (even though you can
            // only easily test it on the one you're currently running).
            #ifdef __linux__
                // 👉 Replace these hardcoded integers by calling the Linux sendfile().
                //    Its docs are here:
                //    https://www.man7.org/linux/man-pages/man2/sendfile.2.html#RETURN_VALUE
                ssize_t bytes_sent = sendfile(socket_fd, fd, NULL, bytes_to_send);
                bool send_failed = bytes_sent == -1;
            #elif defined(__APPLE__)
                // 👉 Replace these hardcoded integers by calling the macOS sendfile().
                //    Its docs are here:
                //    https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man2/sendfile.2.html
                off_t bytes_sent = bytes_to_send;
                bool send_failed = sendfile(fd, socket_fd, 0, &bytes_sent, NULL, 0) == -1;
            #else
                #error "Unsupported operating system"
            #endif

            if (send_failed) {
                // We already sent a 200 OK response, so it's too late to send a 500.
                break;
            }

            bytes_to_send -= bytes_sent;
        }
    }

    close(fd);

    return 0;
}

int main() {
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd == -1) {
        perror("Failed to open socket.");
        return -1;
    }

    // Prevent "Address in use" errors when restarting the server
    int opt = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt");
        return -1;
    }

    struct sockaddr_in address; // IPv4 address

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("bind failed");
        return -1;
    }

    if (listen(socket_fd, 4) == -1) {
        perror("listen");
        return -1;
    }

    printf("Listening on port %d\n", PORT);

    char req[MAX_REQUEST_BYTES + 1]; // + 1 for null terminator
    int addrlen = sizeof(address);

    // Loop forever to keep processing new connections
    while (1) {
        // Block until we get a connection on the socket
        int req_socket_fd = accept(socket_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

        if (req_socket_fd >= 0) {
            // Read all the bytes from the socket into the buffer
            ssize_t bytes_read = read(req_socket_fd, req, MAX_REQUEST_BYTES);

            if (bytes_read < MAX_REQUEST_BYTES) {
                req[bytes_read] = '\0'; // Null-terminate

                // Parse the URL and method out of the HTTP request
                handle_req(req, req_socket_fd);
            } else {
                // The request was larger than the maximum size we support!
                handle_413(socket_fd);
            }

            close(req_socket_fd);
        } else {
            perror("accept() failed.");
            // Continue listening for other connections even if accept fails
        }
    }
}
