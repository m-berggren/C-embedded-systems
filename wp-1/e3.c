/**
 * number_guessing_game.c
 *
 * A simple number guessing game where the user tries to guess a random number
 * between 1 and 100. The program provides feedback if the guess is too high
 * or too low, and limits the number of attempts to prevent infinite guessing.
 *
 * Course: DIT633 (2025)
 * Work package: 1
 * Exercise: 3
 */

#include <stdio.h>      // Used for input/output operations
#include <stdlib.h>     // Used for random number generation
#include <time.h>       // Used for seeding random number generator

/* Constants */
#define MAX_ATTEMPTS 10     // Maximum number of allowed guesses
#define MIN_NUMBER 1        // Minimum value for the random number
#define MAX_NUMBER 100      // Maximum value for the random number

/* Function Declarations */
void print_welcome_message(void);
int get_user_guess(void);
void print_guess_feedback(int guess, int target);
void print_game_over(int target, int attempts, int won);

/**
 * Main function - Entry point of the game
 *
 * @param argc Number of command line arguments (unused)
 * @param argv Array of command line arguments (unused)
 * @return 0 for successful execution
 */
int main(int argc, char *argv[]) {
    // Initialize random number generator
    srand(time(NULL));

    // Generate random number between MIN_NUMBER and MAX_NUMBER
    int target_number = (rand() % MAX_NUMBER) + MIN_NUMBER;
    int attempts = 0;
    int guess;
    int game_won = 0;

    print_welcome_message();

    // Main game loop
    while (attempts < MAX_ATTEMPTS) {
        guess = get_user_guess();

        // Check if user wants to quit
        if (guess < MIN_NUMBER || guess > MAX_NUMBER) {
            printf("\nGame terminated by user.\n");
            break;
        }

        attempts++;

        // Process the guess
        if (guess == target_number) {
            game_won = 1;
            break;
        }

        print_guess_feedback(guess, target_number);
        printf("Attempts remaining: %d\n\n", MAX_ATTEMPTS - attempts);
    }

    print_game_over(target_number, attempts, game_won);

    return 0;
}

/**
 * Prints the welcome message and game instructions
 */
void print_welcome_message(void) {
    printf("Welcome to the Number Guessing Game!\n");
    printf("I'm thinking of a number between %d and %d.\n", MIN_NUMBER, MAX_NUMBER);
    printf("You have %d attempts to guess it.\n", MAX_ATTEMPTS);
    printf("Enter a number outside %d-%d to quit.\n\n", MIN_NUMBER, MAX_NUMBER);
}

/**
 * Gets a guess from the user
 *
 * @return The user's guess as an integer
 */
int get_user_guess(void) {
    int guess;
    printf("Enter your guess: ");
    scanf("%d", &guess);
    return guess;
}

/**
 * Provides feedback on the user's guess
 *
 * @param guess The user's guess
 * @param target The target number to guess
 */
void print_guess_feedback(int guess, int target) {
    if (guess > target) {
        printf("Your guess is too high!\n");
    } else if (guess < target) {
        printf("Your guess is too low!\n");
    }
}

/**
 * Prints the game over message with final results
 *
 * @param target The target number
 * @param attempts Number of attempts made
 * @param won Whether the player won (1) or lost (0)
 */
void print_game_over(int target, int attempts, int won) {
    if (won) {
        printf("\nCongratulations! You guessed the number %d correctly!\n", target);
        printf("It took you %d attempt(s).\n", attempts);
    } else if (attempts >= MAX_ATTEMPTS) {
        printf("\nGame Over! You've used all %d attempts.\n", MAX_ATTEMPTS);
        printf("The number was: %d\n", target);
    }
}