#include "errors.h"

static void handle_error (int socket_fd, enum error_code err_code) {
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
      return;
  }
}

void handle_400 (int socket_fd) {
  handle_error(socket_fd, ERR_400);
}

void handle_404 (int socket_fd) {
  handle_error(socket_fd, ERR_404);
}

void handle_413 (int socket_fd) {
  handle_error(socket_fd, ERR_413);
}

void handle_500 (int socket_fd) {
  handle_error(socket_fd, ERR_500);
}
