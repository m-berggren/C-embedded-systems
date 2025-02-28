// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __
// Work package 4
// Exercise 4
// Submission code: 250204

// ------ Include section -----------------------------------------------------

#include <stdio.h>  // Used by printf

// ------ Function declarations -----------------------------------------------

// Function that searches for first instance of a number in array.
int search_number(int number, int tab[], int size);

// Function that uses bubble sort to sort the array of numbers, low to high
void sort(int number, int tab[]);

// Function that swaps two integers in the passed array
void swap(int tab[], int pos_1, int pos_2);

// ------ Main ----------------------------------------------------------------
/**
 * Function that a) uses linearch search to find the first encounter of an
 * integer in an array, and b) using bubble sort to sort the array from
 * low to high.
 *
 * Purpose: Using linear search and a simple sorting algorithm to sort an
 * array of integers.
 *
 */
int main(void) {
    // ---- Variable declarations -----

    int num;     // Specifies which number to search for in array
    int result;  // Integer position in array
    int test[] = {1, 2, 34, 5, 67, 3, 23, 12, 13, 10};  // Array of numbers
    int arr_size = sizeof(test) / sizeof(int);  // The length of the array

    // ---- Program logic -------------

    // Sets the number to search for
    num = 3;
    // The position of num in array
    result = search_number(num, test, arr_size);
    // Print out information of the search result
    printf("Index for number %d in array should be 5.\n", num);
    printf("Result -> %d\n\n", result);

    // Number to search for
    num = 4;
    // The position of num in array, in this case should be -1
    result = search_number(num, test, arr_size);
    // Print out information of the search result
    printf("Number %d does not exist in array, so should get -1.\n", num);
    printf("Result -> %d\n\n", result);

    // Setting number to 3 again
    num = 3;
    // Inform that array will be sorted
    printf("Sorting the array...\n\n");
    // Sorting hte array fomr low to high
    sort(arr_size, test);

    // The new position of 3 in the array
    result = search_number(num, test, arr_size);
    // Print out information of the new search result
    printf("Index for number %d in array should now be 2.\n", num);
    printf("Result -> %d\n\n", result);

    // Then print out information
    printf("Print out sorted array:\n");
    // Loop through the array and print out each value one after another
    for (int i = 0; i < arr_size; i++) {
        // Print out the value + whitespace
        printf("%d ", test[i]);
    }
    // End with newline
    printf("\n");

    // Program finises successfully with return 0
    return 0;
}

// ------ Function definitions ------------------------------------------------

/**
 * Function that returns the position of the first encounter of the number in
 * the array. If not found it returns -1.
 *
 * @param number - Integer to search for in the array
 * @param tab - Array of integers to search within
 * @param size - The length of the array
 * @return - Integer that is either the position in the array or -1
 */
int search_number(int number, int tab[], int size) {
    // Loop that goes through the length of the array
    for (int i = 0; i < size; i++) {
        // If position in array holds value that equals number
        if (tab[i] == number) {
            // Return the position in the array
            return i;
        }
    }
    /* For loop has run through without an early return, meaning array does
    not hold the number, so returns -1 */
    return -1;
}

/**
 * Function that sorts the aray with bubble sort. Loops through array with
 * double for loop with average O(n^2) for the amount of swaps. The inner loop
 * moves through the array from left to right, comparing adjacent keys. If a
 * value is higher than its right neighbour they are swapped, until reaching end
 * of array. The second round it starts over but not the last position is not
 * checked against.
 *
 * @param size - Integer that specifies the length of the array
 * @param tab - Array of integers to swap
 */
void sort(int size, int tab[]) {
    // Loop through the array of integers
    for (int i = 0; i < size; i++) {
        /* Second loop, j starts on 1 and array is decreased by  value of i,
        as after every outer round the array has one more value sorted in the
        end of the array, so it is decreased by 1. Since j starts on 1, we make
        sure not to go outside of array and cause segmentation fault. */
        for (int j = 1; j < size - i; j++) {
            // If the value to the right in the array is smaller we swap them
            if (tab[j - 1] > tab[j]) {
                // Swap using j - 1 as j start on 1, to not go out of array
                swap(tab, j - 1, j);
            }
        }
    }
}

/**
 * Function that swap integers at the positions of pos_1 and pos_2 in the given
 * array.
 *
 * @param tab - Pointer to array of integers to swap
 * @param pos_1 - Integer position of first value to swap
 * @param pos_2 - Integer position of second value to swap
 */
void swap(int tab[], int pos_1, int pos_2) {
    int temp;  // Holds value of pos_1

    // Hold value at pos_1 so it is not lost
    temp = tab[pos_1];
    // Set new value at pos_1
    tab[pos_1] = tab[pos_2];
    // And update value at pos_2 using the value that temp holds
    tab[pos_2] = temp;
}