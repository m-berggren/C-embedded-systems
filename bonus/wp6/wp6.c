// ------ Include section -----------------------------------------------------
#include <stdio.h>   // Used by fgets
#include <string.h>  // Used by strlen, strcpy

// ------ Define section ------------------------------------------------------
#define MAX_CHARS 250  // Max characters in each string
#define STR_COUNT 5    // Max amount of strings in array

// ------ Function declarations -----------------------------------------------
// Finds and removes the shortest string in the array
void remove_shortest_string(char strings[][250]);

// ------ Main ----------------------------------------------------------------
/**
 * Program that reads 5 strings from user input and removes the shortest one.
 * Prints the array before and after removal.
 *
 * Purpose: To demonstrate arrray manipulation and string handling by
 * removing the shortest string from an array of strings given by the user.
 *
 * @author Marcus Berggren
 * @date 2025
 */
int main(void) {
    // ---- Variable declaration -----
    char input_strings[STR_COUNT][MAX_CHARS];  // A 2D-array storing strings

    // ---- Program logic -------------
    // Loop through the array of strings
    for (int i = 0; i < STR_COUNT; i++) {
        // Read string from user input
        fgets(input_strings[i], MAX_CHARS, stdin);

        // Store the end character
        int last_char_index = strlen(input_strings[i]) - 1;
        // Check if end_char is a newline, if so change it to null terminator
        if (input_strings[i][last_char_index] == '\n') {
            // Replace newline with null terminator
            input_strings[i][last_char_index] = '\0';
        }
    }

    // Remove the shortest string from array
    remove_shortest_string(input_strings);

    // Print the modified array
    printf("Array after removal:\n");
    // Loop through array excluding the last position
    for (int i = 0; i < STR_COUNT - 1; i++) {
        // Print each remaining string
        printf("%s\n", input_strings[i]);
    }
}

// ------ Function definitions ------------------------------------------------
/**
 * Finds the shortest string in the array and removes it by shifting subsequent
 * elements. Prints which string was removed.
 *
 * @param strings The 2D-array of strings to process
 */
void remove_shortest_string(char strings[][250]) {
    int shortest_index = 0;  // Position of shortest string found

    // Find position of shortest string
    for (int i = 0; i < STR_COUNT; i++) {
        // Compare length with current shortest
        if (strlen(strings[i]) < strlen(strings[shortest_index])) {
            // Update position if shorter string found
            shortest_index = i;
        }
    }

    // Print the string that will be removed
    printf("Shortest string removed: %s\n", strings[shortest_index]);

    // Shift remaining elements to fill the gap
    for (int i = shortest_index; i < STR_COUNT - 1; i++) {
        // Copy next string to current position
        strcpy(strings[i], strings[i + 1]);
    }
}