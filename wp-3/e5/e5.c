// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __ (2025)
// Work package 3
// Exercise 5
// Submission code: 175962

// ------ Include section -----------------------------------------------------

#include <time.h>               // Used by time
#include <stdlib.h>             // Used by srand, rand
#include <stdio.h>              // Used by printf

// ------ Define section ------------------------------------------------------

#define MAX 10                  // Max array count
#define UPPER_BOUND 99          // Max random number
#define LOWER_BOUND 1           // Min random number

// ------ Main program---------------------------------------------------------

/**
 * This main function creates an array of random integers and print outs
 * information to the console. After printing the first information the program
 * prints out each integer value in the array multiplied by two.
 *
 * Purpose: Showcases usage of pointers and formatting of the prints.
 *
 * DIT633
 */
int main(void) {

    // ---- Variable declarations -----

    unsigned int array[MAX];            // Define array of integers
    int rand_num;                       // Define random in updated in loop
    unsigned int *ptr = array;          // Initializes pointer to array of ints
    int position = 0;                   // Initializes int used in loop

    srand(time(NULL));                  // Set random seed

    // ---- program logic -------------

    // For loop that goes through from 0 to MAX value
    for (int i = 0; i < MAX; i++) {
        // Randomizes a number between LOWER- & UPPER_BOUND
        rand_num = (rand() % UPPER_BOUND) + LOWER_BOUND;
        // Assign random number to index i in array
        array[i] = rand_num;
    }

    // Prints the address of the first position in the array
    printf("The value of the address of the array (pointer) is: %p\n", &array);
    // Print out the first instance in array through index 0
    printf("First integer in the array is (array[0]): %d\n", array[0]);
    // Last integer in the array is MAX - 1 as range starts from 0
    printf("The last integer in the array is: %d\n", array[MAX - 1]);
    // Get the size of the integer at the position of the pointer
    printf("The size of an integer (number of bytes) is: %u\n", (unsigned int)sizeof(*array));
    // sizeof an entire array gives the full size in bytes
    printf("The size of the whole array in bytes is: %ld\n\n", sizeof(array));

    /* Loops until ptr reaches the address of the last element as array + MAX
    points to the last element in the array */
    while (ptr < array + MAX) {
        // Prints out information to console, dereference ptr and multiply by 2
        printf("Array[%d], integer: %2d, integer x 2: %3d\n", position, *ptr, *ptr * 2);
        // Increments integer by one
        position++;
        // Increments pointer by one
        ptr++;
    }
}