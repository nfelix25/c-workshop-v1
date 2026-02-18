#include <stddef.h>
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
  printf("Handling request: %s\n", request);

  // Call to_path() to extract the file path from the request
  char* path = to_path(request);

  // If to_path() returned NULL, send "HTTP/1.1 400 Bad Request\n\n" to socket_fd and return -1
  // Hint: use write(socket_fd, ...) — not printf

  if (!path) {
    write(socket_fd, RESPONSE_400, RESPONSE_400_LEN);
    return -1;
  }

  // Open the file at `path` in read-only mode with open()
  int fd = open(path, O_RDONLY);

  // If open() failed (fd == -1):
  //   - if errno == ENOENT, send "HTTP/1.1 404 Not Found\n\n" to socket_fd
  //   - otherwise send "HTTP/1.1 500 Internal Server Error\n\n" to socket_fd
  //   - return -1 in either case
  if (fd == -1) {
    if (errno == ENOENT) {
      write(socket_fd, RESPONSE_404, RESPONSE_404_LEN);
    } else {
      write(socket_fd, RESPONSE_500, RESPONSE_500_LEN);
    }

    return -1;
  }

  struct stat stats;

  // Use fstat() to get file metadata (we need the file size)
  // If fstat() fails, send "HTTP/1.1 500 Internal Server Error\n\n" to socket_fd
  if (fstat(fd, &stats) == -1) {
    write(socket_fd, RESPONSE_500, RESPONSE_500_LEN);
    return -1;
  }

  // Send the success header to the socket: "HTTP/1.1 200 OK\n\n"
  // write(socket_fd, RESPONSE_200, RESPONSE_200_LEN);
  // Use a write loop to ensure ALL bytes are written (write() can write fewer than requested):
  //   - track bytes_written and bytes_to_write
  //   - loop while bytes_to_write > 0, advancing the pointer on each iteration
  //   - if write() returns -1, send a 500 error and return -1

  // Use a block for scoping vars like bytes_written
  {
    const char* OK = RESPONSE_200;
    size_t bytes_written = 0;
    size_t bytes_to_write = RESPONSE_200_LEN;

    while (bytes_to_write) {
      bytes_written = write(socket_fd, OK + bytes_written, bytes_to_write);

      if (bytes_written == -1) {
        write(socket_fd, RESPONSE_500, RESPONSE_500_LEN);
        return -1;
      }

      bytes_to_write -= bytes_written;
    }
  }

  // Send the file contents to the socket using a read→write loop:
  //   - declare a buffer (e.g. char buffer[4096])
  //   - outer loop: read() from the file into the buffer until read() returns 0 (EOF)
  //   - inner loop: write() all bytes_read to the socket (write may be partial)
  //     - track bytes_written and bytes_remaining
  //     - advance buffer pointer each iteration
  //     - if write() returns -1, send a 500 error and return -1
  //   - after the outer loop, if read() returned -1, send a 500 error and return -1
  {
    char buffer[4096];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
      ssize_t bytes_written = 0;
      ssize_t bytes_remaining = bytes_read;

      while (bytes_remaining > 0) {
        ssize_t result = write(socket_fd, buffer + bytes_written, bytes_remaining);

        if (result == -1) {
          write(socket_fd, RESPONSE_500, RESPONSE_500_LEN);
          return -1;
        }

        bytes_written += result;
        bytes_remaining -= result;
      }
    }

    if (bytes_read == -1) {
      write(socket_fd, RESPONSE_500, RESPONSE_500_LEN);
      return -1;
    }
  }

  // close() the file descriptor
  close(fd);

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

  struct sockaddr* cast_addr = (struct sockaddr *)&address;

  // bind() the socket to the address; return -1 on failure
  if (bind(socket_fd, cast_addr, sizeof(address)) == -1) {
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
    int req_socket_fd = accept(socket_fd, cast_addr, (socklen_t*)&addrlen);
  //   - if accept() succeeded (req_socket_fd >= 0):
    if (req_socket_fd >= 0) {
  //     - read() the request bytes into req
      ssize_t bytes_read = read(req_socket_fd, req, MAX_REQUEST_BYTES);
  //     - if bytes_read < MAX_REQUEST_BYTES:
      if (bytes_read < MAX_REQUEST_BYTES) {
  //       - null-terminate req[bytes_read]
        req[bytes_read] = '\0';
  //       - call handle_req(req, req_socket_fd)
        handle_req(req, req_socket_fd);
  //     - else (request too large):
      } else {
  //       - send "HTTP/1.1 413 Content Too Large\n\n" to req_socket_fd
        write(req_socket_fd, RESPONSE_413, RESPONSE_413_LEN);
      }
  //     - close(req_socket_fd)
      close(req_socket_fd);
  //   - if accept() failed, continue the loop (keep listening)
    } else {
      continue;
    }
  }

  return 0;
}
