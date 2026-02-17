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

    return cpy + 1;
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

  return start + 1;
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

// The Mixed Return Problem

// Your `to_path` now sometimes returns a pointer into the original buffer (the in-place path) and sometimes returns a `malloc`'d pointer. The caller has no way to know which one it got. This matters because:

// - `malloc`'d memory **must** be `free`'d, or you leak memory
// - A pointer into the stack buffer **must not** be `free`'d, or you corrupt the heap

// So if the caller does `free(result)`, it works for `req4` but crashes for `req1`. If the caller doesn't call `free`, it works for `req1` but leaks for `req4`. There's no winning.

// This is a real problem in C APIs. Common solutions:

// **1. Always allocate.** Make `to_path` always `malloc` and return a new string. The caller always calls `free`. Simple, consistent contract.

// **2. Never allocate.** Return `NULL` when the buffer is too small (what the solution does). The caller is responsible for providing a big enough buffer. No memory management needed.

// **3. Let the caller provide the output buffer.**
// ```c
// char *to_path(char *req, size_t req_len, char *out, size_t out_len);
// ```
// The caller controls all memory. Very common in C APIs (like `snprintf`).

// ## How to `free`

// For the cases where you do `malloc`, the caller would do:

// ```c
// char *path = to_path(req4);
// printf("Result: \"%s\"\n", path);
// free(path);  // Release the malloc'd memory
// ```

// But again — this only works if you **know** the pointer was `malloc`'d. That's why mixing the two return styles is dangerous.

// ## The solution's philosophy

// The solution chose option 2: if there's not enough room, just return `NULL`. This keeps the contract simple — the return value is always either `NULL` or a pointer into the original buffer, and the caller never needs to call `free`. In C, keeping memory ownership clear and consistent is more important than handling every edge case.
