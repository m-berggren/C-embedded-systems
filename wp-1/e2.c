// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __ (2025)
// Work package 1
// Exercise 2
// Submission code: 397024

// Include section
#include <stdio.h>
#include <stdlib.h> // Used by atoi method
#include <string.h> // Used by strlen method

// Define section
#define MAX_BUFFER 20       // Maximum input buffer size
#define ALPHABET_LEN 26     // Number of letters in alphabet
#define NUM_LEN 10          // Number of digits (0-9)
#define UPPER_START 65      // ASCII value for A
#define UPPER_END 90        // ASCII value for Z
#define LOWER_START 97      // ASCII value for a
#define LOWER_END 122       // ASCII value for z
#define NUM_START 48        // ASCII value for 0
#define NUM_END 57          // ASCII value for 9

// ------ Function declarations ------

// Checks if a character is a letter (uppercase or lowercase)
_Bool is_a_letter(char c);

// Checks if a character is a number (0-9)
_Bool is_a_number(char c);

// Determines the base ASCII value (LOWER_START or UPPER_START) for a letter
int base_start(char c);

// Performs the shift calculation with handling for negative numbers
int normalize_shift(char input, int base, int shift, int len);

// ------ Function definitions ------


// Main program section

/**
 * This program shifts letters and numbers based on what user provides as value.
 * The input are read character by character until encountering a newline or
 * EOF. It preserves case sensitivity and shifts numbers independently of
 * letters.
 *
 * Purpose: Encrypt text using ciphering with a customizable shift value.
 * DIT633
 */

int main(int argc, char *argv[]) {

    // Variable declarations
    int shift = atoi(argv[1]);  // Convert input shift value to integer
    char input[MAX_BUFFER];     // Declare input buffer
    char c;                     // Declare c used to store getchar()
    int n = 0;                  // Initialize n, used in while loop

    // Program logic

    // Check if correct number of arguments provided
    if (argc != 2) {
        // Print useage information to console
        printf("Use like this: %s <shift_value>", argv[0]);
        // Signals that the program has ended successfully
        return 0;
    }

     // Read input character by character until newline, EOF, or buffer limit
    while ((c = getchar()) != '\n' && c != EOF && n < MAX_BUFFER - 1) {
        // Populate the input array with character in stdin
        input[n] = c;
        // Increment n for next iteration
        n++;
    }

    // Add \0 (NULL terminator) after array is populated,to mark its end
    input[n] = '\0';

    // Process each character in the input string
    for (int i = 0; i < strlen(input); i++) {
        // Checks if character is a letter (upper or lower case)
        if (is_a_letter(input[i])) {
            // Gets the start value, either a or A
            int base = base_start(input[i]);
            // Exchanges the input value at i with the new shifted value
            input[i] = normalize_shift(input[i], base, shift, ALPHABET_LEN);
        }

        // Checks if character is a number
        if (is_a_number(input[i])) {
            // Base ASCII value of 0
            int base = NUM_START;
            // Exchanges the input value at i with the new shifted value
            input[i] = normalize_shift(input[i], base, shift, NUM_LEN);
        }
    }

    // Final print with shifted characters
    printf("%s", input);
    // Signals that the program has ended successfully
    return 0;
}

/**
 * Function checks if a character is a letter (uppercase or lowercase)
 * @param c - Specific character from input
 * @return - Boolean value 0 or 1, for true and false
 */
_Bool is_a_letter(char c){
    // Checks if character is an upper- or lower case letter based on ASCII
    if ((c >= LOWER_START && c <= LOWER_END) || (c >= UPPER_START && c <= UPPER_END)) {
        // It is a letter, returns true
        return 1;
    }
    // It is no letter, returns false
    return 0;
}

/**
 * Fnuction checks if a character is a number (0-9)
 * @param c - Specific character from input
 * @return - Boolean value 0 or 1, for true and false
 */
_Bool is_a_number(char c) {
    // Checks if character is a digit between 0-9
    if (c >= NUM_START && c <= NUM_END) {
        // It is a digit, returns true
        return 1;
    }
    // It is not a digit, returns false
    return 0;
}

/**
 * Function determines the base ASCII value (LOWER_START or UPPER_START) for a
 * letter.
 * @param c - Specific character from input
 * @return - Integer with ASCII value for lower- or upper case start
 */
int base_start(char c) {
    // Returns integer for base ASCII value
    return (c >= LOWER_START && c <= LOWER_END) ? LOWER_START: UPPER_START;
}

/**
 * Funciton performs the shift calculation with handling for negative numbers
 * @param input - Character's ASCII value
 * @param base - Base ASCII value used: a, A or 0 start
 * @param shift - Shift value passed as argument at runtime
 * @param len - Length of alphabet or digit count, used with modulus operator
 * @return - ASCII value with the new shifted character
 */
int normalize_shift(char input, int base, int shift, int len) {
    // Calculates the value to shift. First, the int value of the input, then
    // subtract with base value (the rest is minimum 0), then add the shift
    // count and modulo with the length of the alphabet or number count
    int temp_shift = (input - base + shift) % len;
    // To ensure negative numbers can be handled, add the length of the
    // alphabet or number count, and do the modulo again
    int shift_count = (temp_shift + len) % len;
    // Return the shift count along with starting ASCII value of a, A or 0
    return base + shift_count;
}
