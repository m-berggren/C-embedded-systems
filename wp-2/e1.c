// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __ (2025)
// Work package 2
// Exercise 1
// Submission code: 471940

// Include section
#include <stdio.h>      // Used by fgets
#include <string.h>     // Used by strchar
#include <ctype.h>      // Used by isdigit
#include <stdlib.h>     // Used by atol

// Define section

#define MAX_STRING 31   // Number of chars in string + '\0' (NULL terminator)
#define MAX_LEN_NUM 3   // Max number meaning two digits and '\0'

// Enum with directions abbreviated for North, East, South, West
enum DIRECTION {N, O, S, W};

// Struct for robot, with X- & y-positon and direction the robot faces
typedef struct {
    int xpos;           // X-coordinate of the robot
    int ypos;           // Y-coordinate of the robot
    enum DIRECTION dir; // Direction the robot faces: N, O, S or W
} ROBOT;

// ------ Function declarations -----------------------------------------------

// Function that clears the stdin buffer if string length exceeds MAX_STRING
void clear_stdin(char *string_ptr);

// Function that checks if the input string of coordinates are all digits
int is_valid_coordinate(char *coord_str);

// Function that moves the robot further in its facing direction
void move(ROBOT *robot_ptr);

// Function that turns the robot 90 degrees clockwise
void turn(ROBOT *robot_ptr);

// ------ Main ----------------------------------------------------------------
/**
 * This program lets the user control a robot by first giving it a starting
 * position and then inserting various move or turn commands that takes the
 * robot forward in its facing direction.
 *
 * Purpose: Demonstrate usage of enums, pointers and control flows.
 *
 * DIT633
 */
int main() {

    // ---- Variable declarations -----
    char movement_command[MAX_STRING];  // String of robot commands
                                        // ('m' for move, 't' for turn)
    char start_x_str[MAX_LEN_NUM];      // X-coordinate as string (range: 0-99)
    char start_y_str[MAX_LEN_NUM];      // Y-coordinate as string (range: 0-99)
    ROBOT robot = {                     // Initializes robot w/ x-, y-pos & dir
        .xpos = 0,                      // X-coordinates
        .ypos = 0,                      // Y-coordinates
        .dir = N                        // Set start direction North
    };

    // ---- Program logic -------------

    // Print initial greeting sentence once program starts
    printf("Welcome! You have gotten your hands on a Robot.\n");
    printf("We need you to specify the start location, as well as a string \n");
    printf("of commands that will move it around in different directions.\n");

    // Main while loop that allows program to re-run after a complete set of
    // instructions have been issued. Runs until user quits by hitting 'q'
    while (1) {

        // In case program runs again, need to reset the robot's direction
        robot.dir = N;

        // While loop to get validated x-coordinates. Will run until user
        // interrupts with 'q' or inserts characters 0-99
        while (1) {
            // Print information about storing x-coordinate data
            printf("\nPlease insert a number 0-99 for the start X-coordinate.\n");
            printf("Anything above 99 will be truncated to two decimals.\n");
            printf("You can exit the program by inserting 'q':\n");

            // Reads user input and truncate anything above 2 characters
            fgets(start_x_str, MAX_LEN_NUM, stdin);

            // Function clears the stdin buffer if input length > MAX_LEN_NUM
            clear_stdin(start_x_str);

            // Check if the user input for x-coordinate is valid
            if (is_valid_coordinate(start_x_str)) {
                // Convert X-coordinate to an integer
                robot.xpos = atoi(start_x_str);
                // Break while loop and move to the next
                break;

            // Check if user wishes to quit
            } else if (start_x_str[0] == 'q') {
                // Quit running application, return 0
                return 0;

            // Input string is not valid
            } else {
                // Print information that string is not valid
                printf("Invalid input.\n");
                // Run the loop again, giving the user another chance
                continue;
            }
            }

            // While loop to get validated y-coordinates. Will run until user
            // interrupts with 'q' or inserts characters 0-99
        while (1) {
            // Print information about storing y-coordinate data
            printf("\nPlease insert a number 0-99 for the start Y-coordinate:\n");
            printf("Anything above 99 will be truncated to two decimals.\n");
            printf("You can exit the program by inserting 'q':\n");

            // Reads user input and truncate anything above 2 characters
            fgets(start_y_str, MAX_LEN_NUM, stdin);

            // Function clears the stdin buffer if input length > MAX_LEN_NUM
            clear_stdin(start_y_str);

            // Check if the user input is valid
            if (is_valid_coordinate(start_y_str)) {
                // Convert Y-coordinate to an integer
                robot.ypos = atoi(start_y_str);
                // Run the loop again, giving the user another chance
                break;

            // Check if user wishes to quit
            } else if (start_y_str[0] == 'q') {
                // Quit running application, return 0
                return 0;

            // Input string is not valid
            } else {
                // Prints information that string is not valid
                printf("Invalid input.\n");
                // Runs the while loop again, giving the user an option to redo
                continue;
            }
        }

        // Prints information about the movement of the robot
        printf("\nPlease input a sequence of characters as per below.\n");
        printf("'m' will move the Robot one step in current direction.\n");
        printf("'t' will turn the Robot 90 degrees clockwise.\n");
        printf("You may end the program prematurely by hitting 'q'.\n");

        // Reads user input and truncates anything over MAX_STRING length
        fgets(movement_command, MAX_STRING, stdin);

        // Function clears the stdin buffer if input length > MAX_STRING
        clear_stdin(movement_command);

        // Check if user wishes to quit
        if (movement_command[0] == 'q') {
            // Quit running application, return 0
            return 0;
        }

        // Loop through each instance of the input string until we find the
        // NULL terminator
        for (int i = 0; movement_command[i] != '\0'; i++) {
            // Check if character at index i is 't'
            if (movement_command[i] == 't') {
                // If so turn the robot 90 degrees clockwise
                turn(&robot);

            // Check if character at index i is 'm'
            } else if (movement_command[i] == 'm') {
                // If so move the robot in the direction it is facing
                move(&robot);
            }
        }

        // Print the result of all turns and movements
        printf("\nRobot's position:\n");
        printf("X-coordinate: %d\n", robot.xpos);
        printf("Y-coordinate: %d\n", robot.ypos);

    }

    // Return 0 to indicate successful run of the program
    return 0;
}

// ------ Function definitions ------------------------------------------------

/**
 * Function that clears the standard input buffer in case user inserted more
 * than the maximum string count.
 * @param string_ptr - Pointer to the input string by user
 */
void clear_stdin(char *string_ptr) {
    // If sentence does not contain \n it is longer than the array and
    // we clear the stdin buffer
    if (strchr(string_ptr, '\n') == NULL) {
        int c;  // Define c that checks ASCII values
        // Get characters from stdin until it reaches \n or EOF
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

/**
 * Function that validates that a string of characters all consists of digits.
 * @param string - String of characters
 * @return - If it's only digits in the string return 1, otherwise 0
 */
int is_valid_coordinate(char *coord_str) {
    // Loop through input string until end of it (\0)
    for (int i = 0; coord_str[i] != '\0'; i++) {
        // First catch newline character and skip that check
        if (coord_str[i] == '\n') {
            // Skip to the next iteration
            continue;
        }

        // Check if index i of string i a digit
        if (!isdigit(coord_str[i])) {
            // Non-digit found, return 0
            return 0;
        }
    }
    // String is all digits, return 1
    return 1;
}

/**
 * Function that moves the robot in the direction it is facing.
 * - increments ypos if facing north
 * - increments xpos if facing east
 * - decrements ypos if facing south
 * - decrements xpos if facing west
 * @param robot_ptr - Pointer to robot, adjusts xpos and ypos based on dir
 */
void move(ROBOT *robot_ptr) {
    // Switch case that increment or decrement robot's value on x- & y-axis
    switch (robot_ptr -> dir) {
        case N: robot_ptr -> ypos++; break; // Faces north, increment y
        case O: robot_ptr -> xpos++; break; // Faces east, increment x
        case S: robot_ptr -> ypos--; break; // Faces south, decrement y
        case W: robot_ptr -> xpos--; break; // Faces west, decrement x
    }
}

/**
 * Function that turns the robot 90 degrees in clockwise pattern.
 * @param robot_ptr - Pointer to robot
 */
void turn(ROBOT *robot_ptr) {
    // Switch case that moves the robot's direction 90 degrees clockwise
    switch (robot_ptr -> dir) {
        case N: robot_ptr -> dir = O; break; // Turns from north to east
        case O: robot_ptr -> dir = S; break; // Turns from east to south
        case S: robot_ptr -> dir = W; break; // Turns from south to west
        case W: robot_ptr -> dir = N; break; // Turns from west to north
    }
}