#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// 👉 First, build and run the program.
//
// To do this, make sure you're in the `exercises` directory, and then run:
//
// gcc -o app3 3.c && ./app3

const char* DEFAULT_FILE = "index.html";

char *find_next_break(char *str) {
  char *curr = str;

  while (curr[0] != ' ' && curr[0] != '\0') {
    curr++;
  }

  return curr;
}

char *my_first_attempted_to_path(char *req) {
    char *first_break = find_next_break(req);
    char *next_break = find_next_break(first_break + 1);

    if (next_break[0] == '\0') return NULL;

    if (first_break[1] == '/') {
      first_break++;
    }

    if (next_break[-1] == '/') {
      next_break--;
    }

    size_t base_length = next_break - first_break;
    size_t length = base_length + strlen(DEFAULT_FILE) + 2;

    char *cpy = malloc(length);
    char* sep = "/";
    memcpy(cpy, first_break, base_length);
    memcpy(cpy + base_length, sep, 1);
    memcpy(cpy + base_length + 1, DEFAULT_FILE, strlen(DEFAULT_FILE));
    cpy[length - 1] = '\0';

    return cpy;
}

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

  // Skip over the space
  start++;

  for (end = start; end[0] != ' '; end++) {
    if (!end[0] || end + deflen > req + reqlen) {
      if (!end[0]) return NULL;
      return my_first_attempted_to_path(req);
    };
  }

  if (end[-1] == '/') {
    end--;
  } else {
    end[0] = '/';
  }


  memcpy(end + 1, DEFAULT_FILE, strlen(DEFAULT_FILE) + 1);

  return start;
}

int main() {
    // 👉 These three don't currently trim off the leading '/' - modify to_path to fix them!
    char req1[] = "GET /blog HTTP/1.1\nHost: example.com";
    printf("Should be \"blog/index.html\": \"%s\"\n", to_path(req1));

    char req2[] = "GET /blog/ HTTP/1.1\nHost: example.com";
    printf("Should be \"blog/index.html\": \"%s\"\n", to_path(req2));

    char req3[] = "GET / HTTP/1.1\nHost: example.com";
    printf("Should be \"index.html\": \"%s\"\n", to_path(req3));

    // 👉 Before fixing this next one, try moving it up to the beginning of main().
    //    What happens?

    // 👉 Finally, fix it by handling the case where `req` is too short to
    //    have "index.html" memcpy'd into it.
    //    Hint: `strlen()` returns an integer whose type is not `int` but rather `size_t`
    char req4[] = "GET /blog ";
    printf("Should be \"(null)\": \"%s\"\n", to_path(req4));

    return 0;
}
