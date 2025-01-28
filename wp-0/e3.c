// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __ (2025)
// Work package 0
// Exercise 3
// Submission code: 202074 (provided by your TA-s)

// Include section
#include <stdio.h>
// string.h included to utilize the strcmp method
#include <string.h>

/**
 * This program takes an argument given by the user and concatenates it
 * with "Hello World - I'm %s!". %s is replaced by the value set by the user.
 * @param argc Number of arguments provided
 * @param argv The actual array of arguments provided
 */

// Main function in the program
int main(int argc, char *argv[]) {

    // argv[1] is the first CLI argument, index 0 is the program's name
    char* given_arg;
    // strcmp(str1, str2) is a method used for comparing two strings
    // Returns 0 on equal and a non-zero value otherwise
    int is_h_typed;

    // Check if there are more than one argument, else if less than one and
    // else when there is precisely one given
    if (argc > 2) {
        // Print error message when too many arguments
        printf("Error - You provided more than one argument. "
        "Type -h for help.\n ");
    // If argument count is less than two, print error
    } else if (argc < 2) {
        // Print error message when too few arguments
        printf("Error - You need to provide one argument. Type -h for help\n");
    // argc is exactly two
    } else {
        // Set variable to the first argument given
        given_arg = argv[1];

        // Compares the two strings, if argument equals "-h" then first if
        // statement is called, otherwise the greeting is showed
        is_h_typed = strcmp("-h", given_arg);
        if(is_h_typed == 0) {
            // Print help mesage with information
            printf("This is a help message.\n");
            printf("You may run the program and include <your_name>");
        } else {
            // Print a string to the console
            printf("Hello World! - I'm %s!\n", given_arg);
        }
    }
    // Return 0 to indicate successful execution of the program
    return 0;
}