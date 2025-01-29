// Include section
#include <ctype.h>      // Used by isdigit
#include <stdlib.h>     // Used by atol
#include <stdio.h>      // Used bu printf

// Define section
#define MAX_SIZE 32     // Size limit of the integer set to 32 bits (0-31)
                        // But for adding '\0' for end of string we use 32

// ------ Function declarations -----------------------------------------------

// Function that checks if all characters are a string
int is_number(const char *input);

// Function utilizes passed number to construct a binary number and
// count occurences of 1s and 0s in that number
void dec_to_binary(int number, char *b_string, int *one_count, int *z_count);

// ------ Main ----------------------------------------------------------------

/**
 * This program takes a decimal number as input from the user. It turns the
 * number into binary and counts how many 0s and 1s are in the binary number.
 *
 * Purpose: Counting the number of 0s and 1s in the binary representation of a
 * decimal number.
 *
 * @author Marcus Berggren
 * @date 2025
 */

int main(int argc, char *argv[]) {
    // Variable declarations
    int input_number;       // Number given as argument by user
    int one_counter = 0;    // The amount of '1's in the binary representation
    int zero_counter = 0;   // The amount of non-leading '0's in binary string
    char binary_string[MAX_SIZE] = {0}; // The string with binary numbers,
                                        // filled with 0s when intialized

    // Program logic

    // Check if there's two arguments, meaning if we receive a number to convert
    if (argc != 2) {
        // Print error information
        printf("Error: No number provided. Please provide a number as a "
        "command line argument.\n");
        // Return
        return 0;
    }

    // Check if argument is a number
    if (is_number(argv[1]) == 0) {
        // Print error information
        printf("Error: Invalid number.");
        // Return
        return 0;
    }

    // After validations done, convert the user input from string to a long int
    input_number = atol(argv[1]);

    // Function that converts the input_number into binary string and
    // counts 1s and 0s within it
    dec_to_binary(input_number, binary_string, &one_counter, &zero_counter);

    // Prints the number argument given by user
    printf("Number: %d\n", input_number);
    // Prints the binary string
    printf("Binary: 0b%s\n", binary_string);
    // Prints the number of 0s in binary number
    printf("Number of 0s: %d\n", zero_counter);
    // Prints the number of 1s in binary number
    printf("Number of 1s: %d\n", one_counter);

    // Return
    return 0;
}

// ------ Function definitions ------------------------------------------------

/**
 * Function goes through each character in the input and returns 0 if a non-
 * digit is found and 1 if they are all digits.
 * @param input - Pointer to the argument number given by the user
 * @return False (0) if a non-digit is found, otherwise true (1)
 */
int is_number(const char *input) {
    // Loop through each character of the input
    for (int i = 0; input[i] != '\0'; i++) {
        // Check if the character at index i is a digit
        if (isdigit(input[i]) == 0) {
            // If not digit return 0
            return 0;
        }
    }
    // Return 1, meaning that all characters are digits
    return 1;
}

/**
 * Function that takes an input number and derives its binary string,
 * counts 1s and 0s within that string.
 * @param number - The number given and utilized to create the binary string
 * @param b_string - Pointer to char array where binary string will be stored
 * @param one_count - Pointer to integer tracking count of 1s in binary number
 * @param z_count - Pointer to integer tracking count of non-leading 0s in
 * binary number
 */
void dec_to_binary(int number, char *b_string, int *one_count, int *z_count) {
    // Variable declarations
    int highest_bit = MAX_SIZE - 1; // Value where the first set bit is found
    int index = 0;                  // Keep track of position in string

    // Loop that right shifts all bits with decreasing value until it finds a
    // first set bit. Then highest_bit is used in subsequent for loop
    while ((number >> highest_bit) == 0) {
        // Decreases highest_bit until first 1 is found
        highest_bit--;
    }

    // Next loop starts at highest_bit's value and decrements until 0
    for (int i = highest_bit; i >= 0; i--) {
        // Checks if current bit position contains a 1
        if ((number >> i) & 1) {
            // Adds '1' character to binary string
            b_string[index] = '1';
            // Increments one_count by 1
            (*one_count)++;
        } else {
            // Adds '0' character to binary string
            b_string[index] = '0';
            // Increments z_count by 1
            (*z_count)++;
        }
        // Increment index to populate new position in next iteration
        index++;
    }
    // Adding NULL terminator to the string
    b_string[index] = '\0';
}





