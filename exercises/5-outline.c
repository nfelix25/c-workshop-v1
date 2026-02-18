#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <errno.h>

const int PORT = 8080;
const int MAX_REQUEST_BYTES = 32768;
const int MAX_CONNECTIONS = 2;
const char* DEFAULT_FILE = "index.html";

const char* RESPONSE_400 = "HTTP/1.1 400 Bad Request\n\n";
const char* RESPONSE_404 = "HTTP/1.1 404 Not Found\n\n";
const char* RESPONSE_500 = "HTTP/1.1 500 Internal Server Error\n\n";
const char* RESPONSE_200 = "HTTP/1.1 200 OK\n\n";

#define RESPONSE_400_LEN = sizeof(RESPONSE_400) - 1;
#define RESPONSE_404_LEN = sizeof(RESPONSE_404) - 1;
#define RESPONSE_500_LEN = sizeof(RESPONSE_500) - 1;
#define RESPONSE_200_LEN = sizeof(RESPONSE_200) - 1;

char *to_path(char *req) {
    char *start, *end;

    // Advance `start` to the first space
    for (start = req; start[0] != ' '; start++) {
        if (!start[0]) {
            return NULL;
        }
    }

    start++; // Skip over the space

    // Advance `end` to the second space
    for (end = start; end[0] != ' '; end++) {
        if (!end[0]) {
            return NULL;
        }
    }

    // Ensure there's a '/' right before where we're about to copy in "index.html"
    if (end[-1] != '/') {
        end[0] = '/';
        end++;
    }

    // If there isn't enough room to copy in "index.html" then return NULL.
    // (This only happens if the request has no headers, which should only
    // come up in practice if the request is malformed or something.)
    if (end + strlen(DEFAULT_FILE) > req + strlen(req)) {
        return NULL;
    }

    // Copy in "index.html", overwriting whatever was there in the request string.
    memcpy(end, DEFAULT_FILE, strlen(DEFAULT_FILE) + 1);

    return start + 1; // Skip the leading '/' (e.g. in "/blog/index.html")
}

// handle_req: parse the request, open the file, and write an HTTP response to socket_fd
// Returns 0 on success, -1 on error.
int handle_req(char *request, int socket_fd) {

    // Call to_path() to extract the file path from the request
    char* path = to_path(request);

    // If to_path() returned NULL, send "HTTP/1.1 400 Bad Request\n\n" to socket_fd and return -1
    // Hint: use write(socket_fd, ...) — not printf

    if (!path) {
      write(socket_fd, "HTTP/1.1 400 Bad Request\n\n", 23);
    }

    // Open the file at `path` in read-only mode with open()

    // If open() failed (fd == -1):
    //   - if errno == ENOENT, send "HTTP/1.1 404 Not Found\n\n" to socket_fd
    //   - otherwise send "HTTP/1.1 500 Internal Server Error\n\n" to socket_fd
    //   - return -1 in either case

    // Use fstat() to get file metadata (we need the file size)
    // If fstat() fails, send "HTTP/1.1 500 Internal Server Error\n\n" to socket_fd

    // Send the success header to the socket: "HTTP/1.1 200 OK\n\n"
    // Use a write loop to ensure ALL bytes are written (write() can write fewer than requested):
    //   - track bytes_written and bytes_to_write
    //   - loop while bytes_to_write > 0, advancing the pointer on each iteration
    //   - if write() returns -1, send a 500 error and return -1

    // Send the file contents to the socket using a read→write loop:
    //   - declare a buffer (e.g. char buffer[4096])
    //   - outer loop: read() from the file into the buffer until read() returns 0 (EOF)
    //   - inner loop: write() all bytes_read to the socket (write may be partial)
    //     - track bytes_written and bytes_remaining
    //     - advance buffer pointer each iteration
    //     - if write() returns -1, send a 500 error and return -1
    //   - after the outer loop, if read() returned -1, send a 500 error and return -1

    // close() the file descriptor

    return 0;
}

int main() {
    // Create a TCP socket with socket(AF_INET, SOCK_STREAM, 0)
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Return -1 if it fails
    if (socket_fd == -1) {
      printf("Opening socket failed.\n");
      return -1;
    }

    // Set SO_REUSEADDR with setsockopt() to avoid "Address already in use" on restart
    int opt = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
      printf("Setting socket options failed.\n");
      return -1;
    }

    struct sockaddr_in address;

    // Fill in a sockaddr_in struct:
    //   - sin_family = AF_INET
    //   - sin_addr.s_addr = INADDR_ANY  (listen on all interfaces)
    //   - sin_port = htons(PORT)        (convert to network byte order)
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // bind() the socket to the address; return -1 on failure
    if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
      printf("Bind failed.\n");
      return -1;
    }

    // listen() for incoming connections (backlog of 2); return -1 on failure
    if (listen(socket_fd, MAX_CONNECTIONS) == -1) {
      printf("Listen failed.\n");
      return -1;
    }

    // Print "Listening on port <PORT>"
    printf("Listening on port: %d\n", PORT);

    // Declare: request buffer (char req[MAX_REQUEST_BYTES + 1]), addrlen
    char req[MAX_REQUEST_BYTES + 1];
    int addrlen = sizeof(address);

    // Loop forever:
    while (1) {
    //   - accept() a connection; this blocks until a client connects
    //   - if accept() succeeded (req_socket_fd >= 0):
    //     - read() the request bytes into req
    //     - if bytes_read < MAX_REQUEST_BYTES:
    //       - null-terminate req[bytes_read]
    //       - call handle_req(req, req_socket_fd)
    //     - else (request too large):
    //       - send "HTTP/1.1 413 Content Too Large\n\n" to req_socket_fd
    //     - close(req_socket_fd)
    //   - if accept() failed, continue the loop (keep listening)
    }

    return 0;
}
