// ------ Include section -----------------------------------------------------
#include <stdio.h>              // Used by fgets
#include <stdlib.h>             // Used by atoi
#include <ctype.h>              // Used by isdigit
#include <string.h>             // Used by strchr, strlen
#include <unistd.h>             // Used by sleep

// ------ Define section ------------------------------------------------------
#define MAX_LENGTH  2           // Max length is one digit + '\0'
                                // Anything above one digit will be truncated

// Enum for using days
enum DAY {
    MONDAY      = 1,
    TUESDAY     = 2,
    WEDNESDAY   = 3,
    THURSDAY    = 4,
    FRIDAY      = 5,
    SATURDAY    = 6,
    SUNDAY      = 7
};

// Enum for using weeks
enum WEEK {
    WEEK_1      = 1,
    WEEK_2      = 2,
    WEEK_3      = 3,
    WEEK_4      = 4,
    WEEK_5      = 5,
};

// New type CALENDAR with enums DAY and WEEK
typedef struct {
    enum DAY current_day;       // Stores the chosen day 1-7
    enum WEEK current_week;     // Stores the chosen week 1-5
} CALENDAR;


// ------ Function declarations -----------------------------------------------

// Function that clears the stdin buffer when needed
void clear_stdin(char *string_ptr);

// Function that checks if string of week or day is valid
int is_string_valid(char *string_ptr);

// Maps digit 1-5 to week string
const char* get_week_string(enum WEEK week);

// Maps digit 1-7 to day string
const char* get_day_string(enum DAY day);

// ------ Main ----------------------------------------------------------------

/**
 * This is a program that writes out and increments week and day every second.
 * It starts on the week and day chosen by the user.
 *
 * Purpose: Demonstrate usage of enums and input validation.
 *
 * @author Marcus Berggren
 * @date 2025
 */
int main() {
    // Variable declarations
    char week_str[MAX_LENGTH];      // Stores input from user. 1 digit + '\0'
    char day_str[MAX_LENGTH];       // Stores input from user. 1 digit + '\0'

    CALENDAR calendar;              // Defines CALENDAR type with week & day

    // ---- Program logic --------------

    // ---- Take inputs ----

    // Ask for a starting week within 1-5
    printf("Provide starting week:\n");

    // Takes input form user, max length of 2, meaning it's one digit + '\0'
    fgets(week_str, MAX_LENGTH, stdin);

    // In case user inserted more than 1 character, the stdin buffer is cleared
    clear_stdin(week_str);


    // Ask for a starting day within 1-7
    printf("Provide starting day:\n");

    // Takes input form user, max length of 2, meaning it's one digit + '\0'
    fgets(day_str, MAX_LENGTH, stdin);

    // In case user inserted more than 1 character, the stdin buffer is cleared
    clear_stdin(day_str);

    // ---- Validate inputs ----

    // Check if week string inserted is valid
    if (!is_string_valid(week_str)) {
        // Prints information if no valid
        printf("invalid week");
        // Return 0 to end application
        return 0;
    }

    // Check if day string is valid
    if (!is_string_valid(day_str)) {
        // Prints information if not valid
        printf("invalid day");
        // Return 0 to end applicaiton
        return 0;
    }

    // After digits are validated, convert and assign chosen week to calendar
    calendar.current_week = atoi(week_str);

    // Same thing, assign chosen day to calendar
    calendar.current_day = atoi(day_str);

    // Check if current_week is within 1 and 5
    if (calendar.current_week < WEEK_1 || calendar.current_week > WEEK_5) {
        // Print needed information when outside of valid week digit
        printf("Invalid week\n");
        // Return 0 to end applicaiton
        return 0;
    }

    // Check if current_day is within 1 and 7
    if (calendar.current_day < MONDAY || calendar.current_day > SUNDAY) {
        // Print needed information when outside of valid day digit
        printf("Invalid day\n");
        // Return 0 to end epplication
        return 0;
    }

    // ---- Loop through weeks and days ----

    // Loop that rinst out weeks and days once per second until WEEK_5 ends
    while (calendar.current_week <= WEEK_5) {
        // Print information of week and day
        printf("%s, %s\n",
            get_week_string(calendar.current_week), // Map enum to week string
            get_day_string(calendar.current_day));  // Map enum to day stirng

        // Wait for 1 second
        sleep(1);

        // Increment day and make sure it stays within 1-7 w/ modulus
        calendar.current_day = (calendar.current_day % 7) + 1;

        // If we have completed a week, increment it
        if (calendar.current_day == MONDAY) {
            // Increment the current week by 1
            calendar.current_week++;
        }
    }
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
 * Function that checks if string is valid.
 * Checks for empty string, lenght not equal to 1 and if it's a digit.
 * @param string_ptr - Pointer to the input string, either week or day
 * @return - If character is a digit returns 1, otherwise 0
 */
int is_string_valid(char *string_ptr) {
    // Check for empty string
    if (string_ptr[0] == '\0' || string_ptr[0] == '\n') {
        // String is empty, return 01
        return 0;
    }

    // Check string length (should be one digit)
    if (strlen(string_ptr) != 1) {
        // String length is less or more than 1, return 0
        return 0;
    }

    // Check if first character is a digit
    if (!isdigit(string_ptr[0])) {
        // First character is not a digit, return 0
        return 0;
    }
    // First char is  a digit, return 1
    return 1;

}


/**
 * Funciton that converts WEEK enum to corresponding string
 * @param week - WEEK enum value
 * @return - String representation of the week
 */
const char* get_week_string(enum WEEK week) {
    switch (week) {
        case WEEK_1: return "Week 1";           // Map from 1 to Week 1
        case WEEK_2: return "Week 2";           // Map from 2 to Week 2
        case WEEK_3: return "Week 3";           // Map from 3 to Week 3
        case WEEK_4: return "Week 4";           // Map from 4 to Week 4
        case WEEK_5: return "Week 5";           // Map from 5 to Week 5
        default: return "None";                 // Give None when no match
    }
}



/**
 * Function that converts DAY enum to corresponding string
 * @param day - DAY enum value
 * @return - String representation of the day
 */
const char* get_day_string(enum DAY day) {
    switch (day) {
        case MONDAY: return "Monday";           // Map from 1 to Monday
        case TUESDAY: return "Tuesday";         // Map from 2 to Tuesday
        case WEDNESDAY: return "Wednesday";     // Map from 3 to Wednesday
        case THURSDAY: return "Thursday";       // Map from 4 to Thursday
        case FRIDAY: return "Friday";           // Map from 5 to Friday
        case SATURDAY: return "Saturday";       // Map from 6 to Saturday
        case SUNDAY: return "Sunday";           // Map from 7 to Sunday
        default: return "None";                 // Give None when no match
    }
}