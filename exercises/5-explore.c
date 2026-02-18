#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define PORT 8080
#define MAX_CONNECTIONS 1
#define MAX_REQUEST_BYTES 32768

const char* DEFAULT_FILE = "index.html";

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

int handle_req(char *request, int socket_fd) {

}

int main() {
  int socket_fd, req_socket_fd;
  int opt = 1;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  char req[MAX_REQUEST_BYTES] = {0};


  // 1. Create socket file descriptor
  // AF_INET for IPv4, SOCK_STREAM for TCP, 0 for default protocol
  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
      perror("socket failed");
  }

  address.sin_family = AF_INET;
  // INADDR_ANY binds to all available network interfaces
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT); // Port number in network byte order

  int bound = bind(socket_fd, (struct sockaddr *)&address, addrlen);

  if (listen(socket_fd, MAX_CONNECTIONS) < 0) {
    perror("listen failed");
  };

  printf("Server listening on port %d...\n", PORT);

  while (1) {
    req_socket_fd = accept(socket_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    printf("Connection accepted from %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

    ssize_t bytes_read = read(req_socket_fd, req, MAX_REQUEST_BYTES);

    char *path = to_path(req);
    int fd = open(path, O_RDONLY);

    write(req_socket_fd, "200 OK\n\n", 8);
    write(req_socket_fd, "Hello, world!", 11);

    close(fd);
    close(req_socket_fd);
  }

  return 0;
}
