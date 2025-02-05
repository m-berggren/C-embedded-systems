// ------ Include section -----------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// ------ Define section ------------------------------------------------------
#define MAX_SIZE 4                          // Max size of row and columns
#define MAX_MATRIX_INPUT 256                // Takes maximum 255 chars + '\0'
                                            // Plenty of space as 4 * 4 dims w/
                                            // allowed input of 2 chars + spaces
                                            // would need less than 50 chars
#define MAX_INT 99                          // Max integer allowed as a number

// ------ Function declarations -----------------------------------------------

// Function that clears the stdin buffer if string length exceeds MAX_STRING
void clear_stdin(char *string_ptr);
int get_matrix_size(int *height, int *length);
void populate_matrix(char matrix[]);
int is_valid_matrix(char *char_matrix, int *matrix, int rows, int cols);
void add_matrices(int *matrix_1, int *matrix_2, int *result, int rows, int cols);
void display_matrix(int *matrix, int rows, int cols);

// ------ Main ----------------------------------------------------------------
/**
 * Main function that handles matrix addition. Takes user input for matrix
 * dimensions and values. Then validates the inputs, adds the matrices
 * and displays the result.
 *
 * Purpose: Uses dynamic memory allocation for matrix storage and includes some
 * error handling for invalid inputs and memory allocation failures.
 *
 * @author Marcus Berggren
 * @date 2025
 */
int main(void) {
    // ---- Variable declarations -----

    /**
     * Due to validation of arrays taking place efter all inputs are inserted,
     * they are stored in placeholder arrays first before being validated.
     */
    char matrix_input_1[MAX_MATRIX_INPUT];  // Temporary container for 1st input
    char matrix_input_2[MAX_MATRIX_INPUT];  // Temporary container for 2nd input
    int *matrix_1;                          // Eventual array of valid integers
    int *matrix_2;                          // Eventual 2nd array of valid ints
    int *result;                            // Hold sum of matrix_1 and matrix_2
    int rows;                               // User inserted amount of rows
    int cols;                               // User inserted amount of columns

    // ---- Program logic -------------

    // Lets user insert row and columns, then validates the input
    if (!get_matrix_size(&rows, &cols)) {
        // Print invalid information to console and return 0 to end program
        printf("invalid");
        return 0;
    }

    // Populate matrices in placeholder arrays before validating them, to let
    // tests pass
    populate_matrix(matrix_input_1);
    populate_matrix(matrix_input_2);

    // Assign dynamic memory with malloc based on the row and column values
    // for matrix_1, matrix_2 and result
    matrix_1 = malloc(rows * cols * sizeof(char));
    matrix_2 = malloc(rows * cols * sizeof(char));
    result = malloc(rows * cols * sizeof(int));

    // Check if memory was successfully assigned
    if(matrix_1 == NULL || matrix_2 == NULL || result == NULL) {
        // If any of the memory allocations failed we free all memory
        free(matrix_1);
        free(matrix_2);
        free(result);
        // Print error info to console and return 0 to end program
        printf("Error allocating memory\n");
        return 0;
    }

    // Validate temporary matrix 1 and populate new matrix with numbers
    if(!is_valid_matrix(matrix_input_1, matrix_1, rows, cols)) {
        // The array is not valid and memory is freed to avoid memory leak
        free(matrix_1);
        free(matrix_2);
        free(result);
        // Prints information to console and return 0 to end program
        printf("invalid");
        return 0;
    }

    // Validate temporary matrix 2 and populate new matrix with numbers
    if(!is_valid_matrix(matrix_input_2, matrix_2, rows, cols)) {
        // The array is not valid and memory is freed to avoid memory leak
        free(matrix_1);
        free(matrix_2);
        free(result);
        // Prints information to console and return 0 to end program
        printf("invalid");
        return 0;
    }

    // Add the two matrices together into a new one
    add_matrices(matrix_1, matrix_2, result, rows, cols);

    // Display the new matrix
    display_matrix(result, rows, cols);

    // Important to free memory for the three arrays after successful run
    free(matrix_1);
    free(matrix_2);
    free(result);

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
 * Function that will take in input of the size of the matrix. It needs at least
 * two arguments, but if more arguments are passed the additional ones will be
 * ignored. It also checks if input values are within MAX_SIZE.
 * @param height - The amount of rows, needs to be less or equal to MAX_SIZE
 * @param length - The amount of rows, needs to be less or equal to MAX_SIZE
 * @return - Integer 1 or 0 to indicate boolean values True and False
 */
int get_matrix_size(int *height, int *length) {
    char matrix_size[MAX_SIZE]; // Temporary array to get rows and cols from

    // Give user some information
    printf("Insert row and column count 1-4 below in format '<row> <col>'\n");

    // Takes input from user up until MAX_SIZE, last input is '\0'
    fgets(matrix_size, MAX_SIZE, stdin);
    // In case user inserts more than max characters, the stdin buffer is cleared
    clear_stdin(matrix_size);

    // We can read the string that fgets registered and store the values.
    // This way fgets can prevent buffer overflow and sscanf can parse the input
    if (sscanf(matrix_size, "%d %d", height, length) != 2) {
        // In case sscanf it not equal to 2 (arguments), return 0
        return 0;
    }

    // Check so input is not more than MAX_SIZE for cols and rows
    if (*height > MAX_SIZE || *length > MAX_SIZE) {
        // If height (rows) or length (cols) are higher than MAX_SIZE return 0
        return 0;
    }
    // Returns 1, signalling that validation is successful
    return 1;
}

/**
 * Function that lets user insert a set of numbers that will populate an array
 * and eventually be visualized in a matrix.
 * @param matrix - Pointer to the predefined array
 */
void populate_matrix(char *matrix) {

    printf("Please insert a set of numbers:\n");
    // Lets user insert numbers up until MAX_MATRIX_INPUT
    fgets(matrix, MAX_MATRIX_INPUT, stdin);
    // In case of inserting more allowed memory, the input buffer will be cleared
    clear_stdin(matrix);
}

/**
 * Function does two things; it validates that the inputs are valid numbers and
 * populates the array of integers.
 * @param char_matrix - The placeholder-array that stores all characters
 * @param matrix - The matrix with validates numbers
 * @param rows - Count of rows in the matrix
 * @param cols - Count of columns in the matrix
 * @return 1 or 0, signaling True and False
 */
int is_valid_matrix(char *char_matrix, int *matrix, int rows, int cols) {
    const char *ptr = char_matrix;  // Assigning a pointer to the array of chars
    char number[20]; // Temp array for storage. 20 chosen for some extra space
    int count = 0;  // Amount of iterations - need to align w/ row * cols count

    // While loop that runs until null terminator found in the char_matrix
    while (*ptr != '\0') {
        // Check if character is a space
        if (isspace(*ptr)) {
            // If so, then increment pointer and move to next iteration
            ptr++;
            continue;
        }

        // Check if character is a digit. If not we return 0 and end function
        if (!isdigit(*ptr) && *ptr != '-') return 0;

        // Set i t\o 0 each time while loop iterates, used to get several chars
        int i = 0;

        // Check if '-' sign, if so then increment values and add it to number
        if(*ptr == '-') {
            // Set number to current pointer value and after we increment both
            number[i++] = *ptr++;
        }

        // Check for null terminator and if space again, since ptr may be
        // incremented in case dash, '-', found earlier
        while (*ptr != '\0' && !isspace(*ptr)) {
            // Insert the value at ptr to the index of number, then increment
            number[i++] = *ptr++;
        }

        // In the end of the string we set /0 to declare its end
        number[i] = '\0';

        // Converts string to integer
        int value = atoi(number);

        // Check so input number is not larger than MAX_INT
        if (value > MAX_INT) {
            // Input is higher than allowed, returns 0
            return 0;
        }

        // Number is validated and is added to the array of integers
        matrix[count++] = value;
    }
    // If iteration count is equal to rows * cols, this statement is true (1),
    // otherwise it is false (0)
    return count == rows * cols;
}

/**
 * Function sums two matrices into a new one.
 * @param matrix_1 - One of the matrices with integers
 * @param matrix_2 - Another of the matrices with integers
 * @param result - The combined result of matrix_1 and Matrix_2
 */
void add_matrices(int *matrix_1, int *matrix_2, int *result, int rows, int cols) {
    // For loop that goes through all values in array
    // (their length is validated earlier)
    for (int i = 0; i < rows * cols; i++) {
        // Inserts the sum of the addition to result array
        result[i] = matrix_1[i] + matrix_2[i];
    }
}

/**
 * Function that displays the passed matrix into rows and columns.
 * @param matrix - The passed array with integers to loop over
 * @param rows - The row count inserted by user
 * @param cols - The column count inserted by user
 */
void display_matrix(int *matrix, int rows, int cols) {
    // Create a pointer that starts at the beginning of the array
    int *ptr = matrix;

    // Print the first line to console
    printf("The sum is:\n");

    // Outer loop for each row of the matrix
    for(int i = 0; i < rows; i++) {
        // Inner loop for each column within current row
        for(int j = 0; j < cols; j++) {
            // We can simply increment the pointer and the structure of the for
            // loops with \n will handle the structure, as *ptr++ will ge the
            // value at current position. After incrementing ptr it is pointing
            // to the next integer
            printf("%d ", *ptr++);
        }
        // After each row is printed, add a new line to start next row
        printf("\n");
    }
}