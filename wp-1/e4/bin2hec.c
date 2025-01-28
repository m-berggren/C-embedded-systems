// Work package 1
// Exercise 4.2

// Include section
#include <stdio.h>      // Used by printf
#include <stdlib.h>     // Used by malloc
#include <string.h>     // Used by strlen, strcmp

// Function declaration section
void print_help(void);
int validate_binary(const char *str);
int bin_to_dec(const char *binary);

/**
 * This program converts binary numbers to hexadecimal format.
 * It accepts binary input and outputs the corresponding hexadecimal value.
 *
 * Purpose: Convert binary numbers to hexadecimal format with input validation
 *
 * DIT633
 */

int main(int argc, char *argv[]) {
    // Variable declarations
    int decimal_value;

    // Check if correct number of arguments provided
    if (argc != 2) {
        printf("Error: Invalid number of arguments.\n");
        print_help();
        return 2;
    }

    // Check if help is asked for
    if (strcmp(argv[1], "-h") == 0) {
        print_help();
        return 0;
    }

    // Validate binary input
    if (!validate_binary(argv[1])) {
        printf("Error: Invalid binary input. Must contain only 0s and 1s.\n");
        return 2;
    }

    // Convert binary to decimal
    decimal_value = bin_to_dec(argv[1]);
    if (decimal_value == -1) {
        printf("Error: Binary conversion failed.\n");
        return 2;
    }

    // Output hexadecimal value
    printf("%X\n", decimal_value);

    return 0;
}

/**
 * Validates that the input string contains only 0s and 1s
 * Returns 1 if valid, 0 if invalid
 */
int validate_binary(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return 0;
        }
    }
    return 1;
}

/**
 * Converts binary string to decimal value
 * Returns -1 if conversion fails
 */
int bin_to_dec(const char *binary) {
    int decimal = 0;
    int length = strlen(binary);

    // Check if binary number is too long (max 32 bits)
    if (length > 32) {
        return -1;
    }

    for (int i = 0; binary[i] != '\0'; i++) {
        decimal = decimal * 2 + (binary[i] - '0');
    }

    return decimal;
}

void print_help(void) {
    printf("Usage: ./bin2hex.exe <binary_number>\n");
    printf("Converts a binary number to hexadecimal format.\n");
    printf("The input should be a valid binary number (containing only 0s and 1s).\n");
    printf("Maximum input length is 32 bits.\n");
}