// ------ Include section -----------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// ------ Define section ------------------------------------------------------
#define BINARY_FILE "binary_file"       // Constant binary filename
#define MAX_NAME 20                     // First- & family name 19 chars + '\0'
#define MAX_SSN  13                     // Max SSN 12 chars + '\0'

// ---- Typedefs ----
typedef struct {
    char firstname[MAX_NAME];           // First name
    char famname[MAX_NAME];             // Last name
    char pers_number[13];               // YYYYMMDDXXXX
} PERSON;

// ------ Function declarations -----------------------------------------------

// Function that prints menu options to the console
void print_main_console();

// Function that handles user menu choice input (1-5)
int get_choice_input();

// Function that handles input of person details (first name, family name, SSN)
PERSON input_record(void);

// Function that creates a new binary file and writes initial record
void write_new_file(PERSON *inrecord);

// Function that prints all records from the binary file
void printfile(void);

// Function that searches for a person by first or family name
void search_by_firstname(char *name);

// Function that appends a new person record to the binary file
void append_file(PERSON *inrecord);

// Function that clears stdin buffer when input exceeds buffer size
void clear_stdin(char *string_ptr);

// ------ Main ----------------------------------------------------------------
/**
 * Main function that runs a menu-driven program for managing person records
 * in a binary file. Allows creating, adding, searching, and displaying records.
 *
 * Purpose: Provides a user interface for managing a simple person database
 * with operations for creating, adding, searching, and viewing records.
 *
 * @Author Marcus Berggren
 * @Date 2025
 */
int main(void) {
    // ---- Variable declarations ----
    PERSON ppost = (PERSON){                // Initialize person
        .firstname = "John",                // First name
        .famname = "Doe",                   // Last name
        .pers_number = "000000000000"       // SSN
    };

    // ---- Program logic -------------

    // While loop that runs until user input digit 5
    while (1) {
        // Print choices to the console
        print_main_console();

        // Let user input choices 1-5
        int choice = get_choice_input();

        // Switch case of choices 1-5 and default
        switch(choice) {
            case 1:
                // 1. Create a new and delete the old file
                write_new_file(&ppost);
                break;
            case 2:
                // 2. Add a new person to the file
                // Update ppost with information to append binary file
                ppost = input_record();
                // Append ppost to binary file
                append_file(&ppost);
                // End the switch case
                break;
            case 3:
                // 3. Search for a person in the file
                char name[20];           // Define an array to store name
                printf("Insert first name or last name to search for:\n");
                // Let user insert name to search for
                fgets(name, 20, stdin);
                // Check if newline is in the input
                if (strchr(name, '\n')) {
                    // Remore '\n' if there is any
                    name[strcspn(name, "\n")] = '\0';
                } else {
                    // Function clears the stdin buffer if input length > MAX_NAME
                    clear_stdin(name);
                }
                // Searches for a first- or last name match in the binary file
                search_by_firstname(name);
                // Ends switch case
                break;
            case 4:
                // 4. Print out all in file
                printfile();
                // Ends switch case
                break;
            case 5:
                // 5. Exits the program
                exit(1);
            default:
                // When digit not within 1-5 prints below
                printf("Invalid input, please try again.\n");
        }
    }
    return 0;
}

// ------ Function definitions ------------------------------------------------

/**
 * Function that prints out information of menu choices to the console.
 */
void print_main_console() {
    printf("\n1 Create a new and delete the old file.\n");
    printf("2 Add a new person to the file.\n");
    printf("3 Search for a person in the file.\n");
    printf("4 Print out all in the file.\n");
    printf("5 Exit the program.\n");
}

/**
 * Function that handles user input for menu choices
 *
 * @return int - Returns the user's choice as an integer
 */
int get_choice_input() {
    char digit[2];              // Initialize memory for 1 digit + '\0'

    // Lets user insert a characters, allows space for one didigt + NULL temrinator
    fgets(digit, 2, stdin);
    // Clear the buffer in case user inserted more characters
    clear_stdin(digit);

    // Converts character into a digit
    return atoi(digit);
}


/**
 * Function that handles user input for person records. Reads and validates
 * first name, family name, and personal number. Handles buffer overflow and
 * newline characters for each input.
 *
 * @return PERSON - Returns a PERSON structure containing the input data
 */
PERSON input_record(void) {

    PERSON person;              // Define struct PERSON to insert into file

    // --- Read in first name ----
    // Print information to console
    printf("Please input your first name (max 19 chars):\n");
    // Reads user input and truncates anything above MAX_NAME
    fgets(person.firstname, MAX_NAME, stdin);

    // Check if newline is in the input
    if (strchr(person.firstname, '\n')) {
        // Remore '\n' if there is any
        person.firstname[strcspn(person.firstname, "\n")] = '\0';
    } else {
         // Function clears the stdin buffer if input length > MAX_NAME
        clear_stdin(person.firstname);
    }

    // --- Read in family name ----
    // Print information to console
    printf("Please input your family name (max 19 chars):\n");
    // Reads user input and truncates anything above MAX_NAME
    fgets(person.famname, MAX_NAME, stdin);

    // Check if newline is in the input
    if (strchr(person.famname, '\n')) {
        // Remore '\n' if there is any
        person.famname[strcspn(person.famname, "\n")] = '\0';
    } else {
         // Function clears the stdin buffer if input length > MAX_NAME
        clear_stdin(person.famname);
    }

    // --- Read in SSN ----
    // Print information to console
    printf("Please input your personal number (YYYYMMDDXXXX):\n");
    // Reads user input and truncates anything above MAX_SSN
    fgets(person.pers_number, MAX_SSN, stdin);

    // Check if newline is in the input
    if (strchr(person.pers_number, '\n')) {
        // Remore '\n' if there is any
        person.pers_number[strcspn(person.pers_number, "\n")] = '\0';
    } else {
         // Function clears the stdin buffer if input length > MAX_SSN
        clear_stdin(person.pers_number);
    }

    // Retaurn the created struct PERSON
    return person;
}

/**
 * Function that creates a new binary file and writes initial record.
 * Overwrites existing file if it exists
 *
 * @param inrecord - Pointer to PERSON structure containing initial record
 */
void write_new_file(PERSON *inrecord) {
    // ---- Define variables & prepare file ----
    FILE *output_file; // Define pointer to file

    // Opens file in write mode as we want to overwrite and create a new file.
    // Also checks so opening file is successful
    if ((output_file = fopen(BINARY_FILE, "wb+")) == NULL) {
        // Print information to console if not successful
        printf("Error: Cannot open %s. It does not exist.", BINARY_FILE);
        // End application with exit
        exit(1);
    }

    // ---- Write dummy data & close file ----
    // Writes out premade data (the whole struct) to the binary file
    fwrite(inrecord, sizeof(PERSON), 1, output_file);

    // Best practise to close opened file
    fclose(output_file);
}

/**
 * Function that reads and displays all records from the binary file.
 * Shows formatted output of each person's details.
 * Displays message if file is empty
 */
void printfile(void) {
   FILE *file;                  // Define pointer for file operations
   PERSON temp;                 // Temporary structure to store read records
   int match = 0;               // Flag to track if any records were found

   // Try to open file in binary read mode, exit if failed
   if ((file = fopen(BINARY_FILE, "rb")) == NULL) {
       // Display error message if file can't be opened
       printf("Error: Cannot open %s. It does not exist.", BINARY_FILE);
       // Exit program with error status
       exit(1);
   }

   // Read records one by one until end of file
   while (fread(&temp, sizeof(PERSON), 1, file)) {
       // Print first name, famil name & SSN with formatting
       printf("\n     First name: %s\n", temp.firstname);
       printf("    Family name: %s\n", temp.famname);
       printf("Personal number: %s\n", temp.pers_number);
       // Set flag indicating record were found
       match = 1;
   }

   // Print message if no records were found
   if (!match) printf("No information in file.");

}

/**
 * Function that searches for a person by first or family name.
 * Displays all matching records or indicates if no match found.
 *
 * @param name - Pointer to string containing name to search for
 */
void search_by_firstname(char *name) {
    FILE *file = fopen(BINARY_FILE, "rb");  // Open and store file info
    PERSON temp;                            // Temporary structure for storage
    int match = 0;                          // Flag to track if any record found

    // Check if file is not found
    if (file == NULL) {
        // Print information to console if opening file failed
        printf("Error: Cannot open %s. File does not exist", BINARY_FILE);
        // End application with exit
        exit(1);
    }

    // Loop to go through every input in the file, it reads one struct then next
    while(fread(&temp, sizeof(PERSON), 1, file)) {
        // Check if user input matches first- or last name
        if (strcmp(temp.firstname, name) == 0 || strcmp(temp.famname, name) == 0) {
            // If it does print out informaton to console
            printf("     First name: %s\n", temp.firstname);
            printf("    Family name: %s\n", temp.famname);
            printf("Personal number: %s\n", temp.pers_number);

            // Set the flag to 1 as match was found
            match = 1;
        }
    }
    // If no match print information to console log
    if (match == 0) printf("No match found.\n");

    // Remember to close file when done
    fclose(file);
}

/**
 * Function that appends a person to the existing binary file
 * @param inrecord - Pointer to person type
 */
void append_file(PERSON *inrecord) {
    // ---- Define variables & prepare file ----
    FILE *output_file;                          // Define pointer to file
    output_file = fopen(BINARY_FILE, "ab");    // Initialize and open file
    // Check if opening file is successful
    if (output_file == NULL) {
        // Print information to console if opening file failed
        printf("Error: Cannot open %s. It does not exist.", BINARY_FILE);
        // End application with exit
        exit(1);
    }

    // ---- Write & close file ----
    // Appends the whole struct to the binary file
    fwrite(inrecord, sizeof(PERSON), 1, output_file);

    // Best practise to close opened file
    fclose(output_file);
}

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