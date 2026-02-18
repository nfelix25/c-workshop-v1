#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

const char *path = "index.html";
#define BUFFER_SIZE 500

int main() {
  int err_fd = open("ERRRRR", O_RDONLY);
  int fd = open(path, O_RDONLY);

  if (err_fd == -1) {
    printf("Error: %d\nCause: %s\n", err_fd, strerror(errno));
  }

  printf("%d\n", fd);

  char buffer[BUFFER_SIZE];
  // ssize_t is a signed int useful when -1 as an error is possible
  ssize_t bytes_read = read(10, buffer, BUFFER_SIZE);

  if (bytes_read == -1) {
    printf("Error: %zd bytes read.\nCause: %s\n", bytes_read, strerror(errno));
  } else {
    printf("Buffer size: %d\nActual size: %zd\n", BUFFER_SIZE, bytes_read);
  }


  return 0;
}
