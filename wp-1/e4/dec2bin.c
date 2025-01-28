/**
 * dec2bin.c
 *
 * A program that converts decimal numbers to their binary representation.
 * The program accepts a decimal number as a command line argument and outputs
 * its binary equivalent, automatically adjusting to 8, 16, 32, or 64 bits
 * based on the input size.
 *
 * Course: DIT633
 *
 * Usage: ./dec2bin.exe <decimal_number>
 * Example: ./dec2bin.exe 42
 */

#include <limits.h>     // Used for LONG_MAX
#include <stdio.h>      // Used for input/output operations
#include <stdlib.h>     // Used for memory allocation
#include <string.h>     // Used for string operations

/* Function Declarations */
void print_help(void);
int validate_input(const char* input);
int determine_bit_count(long int number);
char* create_binary_string(long int number, int bit_count);

/**
 * Main function - Entry point of the program
 *
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings
 * @return 0 for successful execution, 2 for errors
 */
int main(int argc, char *argv[]) {
    // Check for correct number of arguments
    if (argc != 2) {
        printf("Error: Invalid number of arguments.\n");
        print_help();
        return 2;
    }

    // Check if help is requested
    if (strcmp(argv[1], "-h") == 0) {
        print_help();
        return 0;
    }

    // Validate input
    if (!validate_input(argv[1])) {
        return 2;
    }

    // Convert input string to long integer
    long int input = atol(argv[1]);

    // Determine required number of bits
    int bit_count = determine_bit_count(input);

    // Create binary string representation
    char* binary = create_binary_string(input, bit_count);
    if (binary == NULL) {
        return 2;
    }

    // Print result and clean up
    printf("%s\n", binary);
    free(binary);

    return 0;
}

/**
 * Prints help information about program usage
 */
void print_help(void) {
    printf("How to use: ./dec2bin.exe <decimal_number>\n");
    printf("The number should be between 0 and %ld.\n", LONG_MAX);
}

/**
 * Validates the input string to ensure it contains only digits
 * and is within the acceptable range
 *
 * @param input The input string to validate
 * @return 1 if input is valid, 0 otherwise
 */
int validate_input(const char* input) {
    // Check each character is a digit
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] < '0' || input[i] > '9') {
            printf("Error: Invalid input, must contain only digits.\n");
            return 0;
        }
    }

    // Check input length (LONG_MAX is 19 digits)
    if (strlen(input) > 19) {
        printf("Error: Number too large. Must be between 0 and %ld.\n", LONG_MAX);
        return 0;
    }

    return 1;
}

/**
 * Determines the number of bits needed to represent the input number
 *
 * @param number The input number
 * @return The number of bits needed (8, 16, 32, or 64)
 */
int determine_bit_count(long int number) {
    if (number < (1L << 8)) {
        return 8;
    } else if (number < (1L << 16)) {
        return 16;
    } else if (number < (1L << 32)) {
        return 32;
    } else {
        return 64;
    }
}

/**
 * Creates a string representation of the binary number
 *
 * @param number The decimal number to convert
 * @param bit_count The number of bits to use in the representation
 * @return A dynamically allocated string containing the binary representation,
 *         or NULL if memory allocation fails
 */
char* create_binary_string(long int number, int bit_count) {
    // Allocate memory for binary string (plus null terminator)
    char* binary = malloc(bit_count + 1);
    if (binary == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // Initialize the string
    memset(binary, '0', bit_count);
    binary[bit_count] = '\0';

    // Convert number to binary
    for (int i = bit_count - 1; i >= 0; i--) {
        int bit_position = bit_count - 1 - i;
        long mask = 1L << bit_position;
        binary[i] = (number & mask) ? '1' : '0';
    }

    return binary;
}