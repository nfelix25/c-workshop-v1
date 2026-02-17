#include <stdio.h>
#include <unistd.h>

// 👉 First, build and run the program.
//
// To do this, make sure you're in the `exercises` directory, and then run:
//
// gcc -o app1 1.c && ./app1

int main() {
    // 👉 Try changing this string to "Hello, World!\n" - and also
    //    changing the length to 14.
    // 👉 Try making the length less than 14. What happens when you run the program?
    // 👉 Try making the length much longer than 14, like 200. What happens? 😱
    char msg[] = "Greetings, Planet?";

    size_t msg_length = sizeof(msg);

    int length = 0;
    char *ptr = msg;

    while (*ptr != '\0') {
      length++;
      ptr++;
    }

    *ptr = '\n';
    length++;

    write(1, msg, msg_length);
    write(1, msg, length);

    // 👉 Try uncommenting the next 2 lines, as well as the #include <stdio.h> at the top.
    //    (You'll want to change the length of write() above back to 14 first!)
    // 👉 Try adding a second number, named num2. Set it to something other than 42.
    int num = 42;
    int num2 = 67;
    printf("The number is: %d\t%d\n", num, num2);

    // 👉 Try having printf print *both* numbers.
    //    Hint: you'll need to make 2 changes to printf's arguments to do this!

    // 👉 Try returning something other than 0. (To see it, you'll need to run `echo $?`
    //    immediately after the program finishes running.)
    return 0;
}
