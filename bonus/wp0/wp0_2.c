/**
 * @file main.c
 * @brief Prints a greeting and asks the user how their day is.
 *
 * This program takes an argument given by the user and inserts it into
 * "Hello %s, how is your day today?". %s is replaced by the value set by the
 * user. It checks that there is an argument passed, that it does not exceed 50
 * characters or is less than 3 characters.
 *
 * @author Marcus Berggren
 * @date 2025
 */

// Include section
#include <stdio.h>
// Include string.h to utilise strlen method
#include <string.h>

/**
 * Main function that runs the applicaiton.
 *
 * @param argc Number of arguments provided
 * @param argv The actual array of arguments provided
 */
int main(int argc, char *argv[]) {

    // If statement to check if an argument is passed in runtime
    if (argc < 2) {
        // When no argument passes, print to console
        printf("No command line argument provided, please provide a name.");
        // Return 1 (or any non-zero value) to indicate that an error occured
        return 0;
    }

    // Checks if the length of the first argument exceeds length of 50
    if (strlen(argv[1]) > 50 ) {
        // When argument length is too long, print to console
        printf("Name too long, max 50 characters");
        // Return 1 (or any non-zero value) to indicate that an error occured
        return 0;
    }

    // Checks if length of the first argument is less than 3,
    if (strlen(argv[1]) < 3) {
        // When argument length is too short, print to console
        printf("Name too short, min 3 characters");
        // Return 1 (or any non-zero value) to indicate that an error occured
        return 0;
    }

    // When all if statements has passed without early return the argument is
    // inserted into the below string and printed to the console
    printf("Hello %s, how is your day today?", argv[1]);
    // Return 0 to indicate successful execution of the program
    return 0;
}