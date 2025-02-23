// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __ (2025)
// Work package 3
// Exercise 6
// Submission code: 175962

// ------ Include section -----------------------------------------------------

#include <stdio.h>                  // Used by fgets
#include <string.h>                 // Used by strchr, strcpy


// ------ Define section ------------------------------------------------------

#define MAX_CHARS 21                // Maximum 20 characters in array + '\0'

// ------ Function declarations -----------------------------------------------

// Function that takes in user input via stdin stream and handling overflow
void read_stdin_input(char *array);
// Function that copies a string from a source array to a destination array
void copy_string(char *old_arr, char *new_arr);

// ------ Main program---------------------------------------------------------

/**
 * This program takes in a string of characters, either a parameter to a
 * text file or a user input during runtime. The program copies the string to
 * additional arrays with aid of library and with manual solution with pointers.
 *
 * Purpose: Showcase using various ways to read the stdin stream, either through
 * file or user input, and copying string between arrays manually with pointers.
 *
 * DIT633
 */
int main(void) {

    // ---- Variable declarations -----

    char char_array[MAX_CHARS];     // Initialize array of max amount of chars
    char strcpy_array[MAX_CHARS];   // Initialize array to copy to w/ strcpy lib
    char man_copy_array[MAX_CHARS]; // Initialize array to manually copy to

    // ---- program logic -------------

    /* Read the input from the stdin stream, could be user input during runtime
    or by using input redirection '<' to read string from a file. It takes in
    MAX_CHARS and truncates anything longer */
    read_stdin_input(char_array);

    // ---- Using library function strcpy()

    // Copies string from char_array to strcpy_array
    strcpy(strcpy_array, char_array);

    // ---- Using own function copy_string()

    // Manual solution to copy information with pointers from old to new array
    copy_string(char_array, man_copy_array);

    // Print out the result of the copied string with copy_string()
    printf("Original string: %s\n", char_array);
    printf("String copy with strcpy: %s\n", strcpy_array);
    printf("Manual string copy: %s", man_copy_array);
}

// ------ Function definitions ------------------------------------------------

/**
 * Function that takes in input from stdin stream. It can be user input during
 * with keyboard during runtime or from a file specified as parameter, as long
 * as input redirection '<' is used. Anything longer than MAX_CHARS will be
 * truncated and the stdin buffer cleared.
 *
 * @param array - Pointer to array of chars to populate
 */
void read_stdin_input(char *array) {
    // Take user input up and store in char_array up until MAX_CHARS limit
    fgets(array, MAX_CHARS, stdin);

    /* If statement is true it means that user input is longer than the max
    allocated memory and we need to clear the buffer */
    if (strchr(array, '\n') == NULL) {
        int c;      // Defines c that checks again newline chars and EOF
        // Get characters from stdin until reaching newline or EOF
        while ((c = getchar()) != '\n' && c != EOF);
    } else {
        // Replace newline with null terminator.
        array[strcspn(array, "\n")] = '\0';
    }
}

/**
 * Function that manually copies characters from a string to another with
 * pointers.
 *
 * @param old_arr - Pointer to the string to copy values from
 * @param new_arr - Pointer to the string to copy to
 */
void copy_string(char *old_arr, char *new_arr) {
    // Loop until array reaches the null terminator of the string
    while (*old_arr != '\0') {
        // Dereference the pointer so we can copy the actual value
        *new_arr = *old_arr;
        // Increment both pointers by one
        new_arr++;
        old_arr++;
    }
    // Need to add a null terminator to the string
    *new_arr = '\0';
}