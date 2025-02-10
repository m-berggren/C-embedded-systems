// ------ Include section -----------------------------------------------------
#include <string.h>                 // Used of strlen
#include <stdio.h>                  // Used by printf
#include <stdlib.h>                 // Used by malloc, free

// ------ Define section ------------------------------------------------------
#define MAX_LEN 10                  // Max length of the input string

// ------ Function declarations -----------------------------------------------

// Function that calculates factorial of en integer
int calculate_factorial(int count);

// Function that recursively generates all possible permusations of a string
void generate_permutations(char *input, int start, int end,
                           char **permutations, int *count);

// Function that swaps two characters in memory using pointers
void swap(char *a, char *b) ;

// ------ Main ----------------------------------------------------------------
/**
 * Main function that handles string permutation generation. It takes a single
 * CL-argument as an input string and generates all possible character
 * combinations.
 *
 * Purpose: Uses dynamic memory allocation, includes some error handling for
 * invalid inputs and memory allocation failures. Memory allocaiton happends in
 * two steps; first by array of pointers and then a single block for all
 * strings.
 *
 * Source: https://www.geeksforgeeks.org/c-program-to-print-all-permutations-of-a-given-string/
 *
 * @author Marcus Berggren
 * @date 2025
 */
int main(int argc, char *argv[]) {
    // Check if given argument is valid
    if (argc != 2 || strlen(argv[1]) > MAX_LEN) {
        printf("invalid");
        return 0;
    }

    // ---- Variable declarations -----

    char *input = argv[1];              // Assign argument to the input variable
    int input_len = strlen(input);      // Length of the inserted string
    int factorial = calculate_factorial(input_len); // Factorial count of input
    int count = 0;                      // Count of permutations

    // ---- Allocate memory for array of strings ----

    // Array where all different permutations will be stored
    char **permutations = (char **)malloc(factorial * sizeof(char *));

    // Check in case malloc did not go through
    if (permutations == NULL) {
        printf("Memory allocation failed");
        return 0;
    }

    /* Also create space for all strings stored within the array. Makes sure
    to add 1 to input_len to account for '\0' */
    char *all_strings = (char *)malloc(factorial * (input_len + 1) * sizeof(char));
    // Check in case second malloc did not go through
    if (all_strings == NULL) {
        free(permutations);
        printf("Memory alloction failed");
        return 0;
    }

    // Loop over each instance to set pointers to string positions
    for (int i = 0; i < factorial; i++) {
        /* Each instance of permutation stores a pointer to all_strings,
        * that position is incremented by length of the string + 1 */
        permutations[i] = all_strings + (i * (input_len + 1));
    }

    // ---- Program logic -------------

    /* Generates all the permutations in a recursive funtion that takes the
    input, start and end as integers, the pointer to the array of strings,
    and the count of permutations */
    generate_permutations(input, 0, input_len - 1, permutations, &count);

    // Then prints out the permutations
    for (int i = 0; i < count; i++) {
        // Print each string one by one
        printf("%s ", permutations[i]);
    }

    // First free the single block of memory all_strings
    free(all_strings);

    // Lastly freeing the permutations array
    free(permutations);
}

// ------ Function definitions ------------------------------------------------

/**
 * Function that calculates the factorial of an input integer.
 *
 * @param number - The integer to start on.
 * @return int - Returns an integer as the maximum allowed length of the
 * parameter is 10. No need to make it larger.
 */
int calculate_factorial(int number) {
    // Base case, when it's time end recursion and add the returns
    if (number <= 1) return 1;

    // Returns a recursive call on calculate_factorial. Ends when number <= 1
    // and summarizes the results
    return number * calculate_factorial(number - 1);
}

/**
 * Function that recursively generates all possible permutations of a given
 * string. Generates permutations by swappin characters and building
 * combinations through recursive calls.
 *
 * @param input - Pointer to the input string being permuted
 * @param start - Starting index for current permutation
 * @param end - Ending index (length - 1) of input
 * @param permutations - Array to store generated permutations
 * @param count - Pointer to count permutations generated
 */
void generate_permutations(char *input, int start, int end,
                      char **permutations, int *count) {
    // Check if start and end are the same
    if (start == end) {
        // Copy input to pre-allocated space
        strcpy(permutations[*count], input);
        // Increment counter of permutations
        (*count)++;
    } else {
        for (int i = start; i <= end; i++) {
            // Swap characters at start and i to use in next permutation
            swap(input + start, input + i);
            // Call the function to generate permutaitons recursively
            generate_permutations(input, start + 1, end, permutations, count);
            // Swap chars at start and i and then go back to the initial input
            swap(input + start, input + i);
        }
    }
}

/**
 * Function that swaps two characters in memory using pointers
 *
 * @param a - Pointer to the first character
 * @param b - Pointer to the second character
 */
void swap(char *a, char *b) {
    char temp;          // Temporary character to hold value during swap
    temp = *a;          // Store the value pointed to by a
    *a = *b;            // Replace a's value with b's value
    *b = temp;          // Replace b's value with the stored value
}