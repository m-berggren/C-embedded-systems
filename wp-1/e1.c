// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __ (2025)
// Work package 1
// Exercise 1
// Submission code: 397024

//Include section
#include <stdio.h> 	// Used for printf, getchar, fgets methods
#include <string.h> // Used for strcmp method

// Define section
#define MAX_LENGTH 31 	// Max number of chars in array is 30 + \0 (NULL terminator)
#define NUM_SENTENCES 5 // Define number of sentences to read in

// Main program section

/**
 * This program takes 5 sentences of max 30 characters and stores them
 * in a two-dimensional array. The user can access them through input of 1-5,
 * any other integer will exit the application. It will alert the user if the
 * chosen sentence is not unique.
 *
 * Purpose: Program prints out sentences you have stored, depending on a chosen
 * integer in the interval 1 to 5.
 * DIT633
 */

int main(int argc, char *argv[]) {

    // Variable declarations
    char sentences[NUM_SENTENCES][MAX_LENGTH]; // 2D-array with rows x columns
    int num_input; // Integer read from input, valid numbers are 1-5

	// Program logic

	// Print initial information to console
	printf("Enter 5 unique sentences (max 30 characters each).\n");

	// For loop to store the sentences in in the array
    for (int i = 0; i < NUM_SENTENCES; i++) {

		// Print to console every time the while loop runs
		printf("Please enter sentence %i:\n", i + 1);

		// Inserts input into index i of sentences, but needs one extra length
		// as fgets sets \0 (NULL terminator) in the last position of the array
		fgets(sentences[i], MAX_LENGTH, stdin);

		// If sentence does not contain \n it is longer than the array and
		// we clear the stdin buffer
		if (strchr(sentences[i], '\n') == NULL) {
			// Get characters from stdin until it reaches \n
			while (getchar() != '\n');
		}
    }

	// While loop for user to pass in integers between 1 and 5
	while (1) {

		// Print information to log on every run
		printf("Enter a number between 1 and 5 (or any other number to exit):\n");

		// If scanf does not succeed in reading a number, means it is no integer
		if (scanf("%d", &num_input) != 1) {
			// Get characters from stdin until it reaches \n
			while (getchar() != '\n');

			// Print information to console
			printf("Invalid input, please enter a number between 1 and 5.\n");
			// Continue with loop
			continue;
		}

		// Check if the user input matches 1-5
    	if (num_input >= 1 && num_input <= 5) {
			// Loop to go through each sentence in sentences array
			for (int i = 0; i < NUM_SENTENCES; i++) {
				// If sentence is equal to the chosen sentence at num_input
				if (strcmp(sentences[i], sentences[num_input - 1]) == 0) {
					// If the read num_input is equal to index we skip iteration
					if (i == num_input - 1) {
						// Continues to next iteration
						continue;
					}
					// Print information about duplicate values
					printf("Duplicate found.");
					// Signals that the program has ended successfully
					return 0;
				}
			}

			// Prints the chosen sentence to console
			printf("%s\n", sentences[num_input - 1]);
			// Breaks the loop and progam will end
			break;

		// If input is any integer but 1-5
		} else {
			// Print out information to the console
			printf("Please restrict to a valid digit...\n");
			// Continue the loop
			continue;
		}
    }

	// Signals that the program has ended successfully
    return 0;
}