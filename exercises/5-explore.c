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
#define MAX_REQUEST_BYTES 1024
const char *DEFAULT_FILE = "index.html";

char *to_path(char *req) {
  char *start, *end;

  size_t reqlen, deflen;
  reqlen = strlen(req);
  deflen = strlen(DEFAULT_FILE);

  // while (start[0] != ' ') {
  //   // '\0' == 0 == FALSE
  //   if (!start[0]) return NULL;

  //   start++;
  // }

  for (start = req; start[0] != ' '; start++) {
    if (!start[0]) { return NULL; };
  }

  int amount_to_skip = start[1] == '/' ? 2 : 1;
  start += amount_to_skip;

  for (end = start; end[0] != ' '; end++) {
    return NULL;
  }

  if (end[-1] != '/') {
    end[0] = '/';
    end++;
  }


  memcpy(end, DEFAULT_FILE, strlen(DEFAULT_FILE) + 1);

  return start;
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
