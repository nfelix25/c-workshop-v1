#include "errors.h"

static int handle_error (int socket_fd, enum error_code err_code) {
  switch (err_code) {
    case ERR_400: {
      write(socket_fd, RESPONSE_400, RESPONSE_400_LEN);
      break;
    }
    case ERR_404: {
      write(socket_fd, RESPONSE_404, RESPONSE_404_LEN);
      break;
    }
    case ERR_413: {
      write(socket_fd, RESPONSE_413, RESPONSE_413_LEN);
      break;
    }
    case ERR_500: {
      write(socket_fd, RESPONSE_500, RESPONSE_500_LEN);
      break;
    }
    default:
      break;
  }

  return -1;
}

int handle_400 (int socket_fd) {
  return handle_error(socket_fd, ERR_400);
}

int handle_404 (int socket_fd) {
  return handle_error(socket_fd, ERR_404);
}

int handle_413 (int socket_fd) {
  return handle_error(socket_fd, ERR_413);
}

int handle_500 (int socket_fd) {
  return handle_error(socket_fd, ERR_500);
}
