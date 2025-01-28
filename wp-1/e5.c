// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __ (2025)
// Work package 1
// Exercise 5

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define section
#define MAX 100         // Defines the maximum number of the values in the table
#define MAXNUMBER 20    // Defines the maximum value of random numbers

// ------ Function declarations ----

// This function generates a set of random numbers
// and fills the table *tab with these numbers
void create_random(int *tab );

// This function takes the *tab of random numbers
// and creates a table with the frequency counts for these numbers
void count_frequency(int *tab, int *freq );

// This function takes the frequency count table
// and draws a histogram of the values in that frequency table
void draw_histogram(int *freq );


// ------ Main --------------------

/**
 * This program generates random numbers, counts their frequency,
 * and displays the results as a histogram
 *
 * Purpose: To demonstrate array manipulation, random number generation,
 * and basic data visualization using a histogram
 *
 * DIT633
 */
int main (void){

    // Variable declarations
    int table[MAX];             // Declare array to store random numbers
    int frequency[MAXNUMBER];   // Declare array to store frequency counts

    // Program logic

    // Generate random numbers and store them in table
    create_random(table);

    // Count frequency of each number in table
    count_frequency(table, frequency);

    // Display histogram of the frequency distribution
    draw_histogram(frequency);
}

// ------ Function definitions ----

/**
 * Creates an array of random numbers between 0 and MAXNUMBER
 * @param tab - Pointer to the array where random numbers will be stored
 */
void create_random(int *tab) {
    // Initialize random number generator with current time as seed
    srand(time(0));

    // Generate MAX random numbers and store them in the array
    for (int i = 0; i < MAX; i++) {
        // Generate random number between 0 and MAXNUMBER
        tab[i] = rand() % (MAXNUMBER + 1);
    }
}

/**
 * Counts the frequency of each number in the input array
 * @param tab - Pointer to array containing random numbers
 * @param freq - Pointer to array where frequencies will be stored
 */
void count_frequency(int *tab, int *freq ) {
    int i;  // Define index used in loops

    // Initialize frequency array to all positions being 0
    for (i = 0; i <= MAXNUMBER; i++) {
        freq[i] = 0;
    }

    // Increment positions in freq array as corresponding index values found in
    // tab array with integers
    for (int i = 0; i <= MAXNUMBER; i++) {
        // Get current number from the input array
        int number = tab[i];
        // Increment the frequency count for this number
        freq[number]++;
    }

}

/**
 * Draws a histogram using 'x' characters to represent frequency counts
 * @param freq - Pointer to array containing frequency counts
 */
void draw_histogram(int *freq ) {
    // Declare loop counter variables
    int i, j;

    // Iterate through all possible numbers (0 to MAXNUMBER)
    for (i = 0; i <= MAXNUMBER; i++) {
        // Get frequency count for current number
        int number = freq[i];

        // Only print numbers that appears at least once
        if (number > 0) {
            // Print the current number with width of 2 chars
            printf("%2d ", i);

            // Print 'x' characters equal to the frequency count
            for (j = 0; j < number; j++) {
                printf("x");
            }
            // Move the next line after printing all 'x' characters
            printf("\n");
        }
    }
}