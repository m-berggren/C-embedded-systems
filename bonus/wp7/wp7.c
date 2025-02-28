// ------ Include section -----------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

// ------ Define section ------------------------------------------------------

typedef struct FibonacciNode {   // Define a node struct for the linked list
    int value;                   // Value to store Fibonacci number
    struct FibonacciNode *next;  // Pointer to next node in the list
    struct FibonacciNode *prev;  // Pointer to previous node in the list
} FibonacciNode;

// ------ Function declarations -----------------------------------------------
// Function that creates a linked list of fibonacci numbers and return the head
FibonacciNode *create_fibonacci_list(int count);

// Function that frees all allocated memory for the list
void free_fibonacci_list(FibonacciNode *head);

// ------ Main ----------------------------------------------------------------
/**
 * Program that calculates and displays the nth Fibonacci number using a linked
 * list.
 *
 * Purpose: To demonstrate linked list implementation for Fibonacci sequence.
 *
 * @author Marcus Berggren
 * @date 2025
 */
int main(int argc, char *argv[]) {
    // Check if correct number of arguments is provided
    if (argc != 2) {
        // Print usage message if incorrect argument count and end program
        printf("Need to input one argument.");
        return 0;
    }

    // Convert command-line argument to integer
    int sequence_length = atoi(argv[1]);

    // Handle special case for values <= 0
    if (sequence_length <= 0) {
        // Print result for 0 or negative index and end program
        printf("0\n");
        return 0;
    }

    // Create and populate the linked list with Fibonacci numbers
    FibonacciNode *head = create_fibonacci_list(sequence_length);

    // ---- Free memory ---------------
    // Clean up allocated memory
    if (head != NULL) {
        // Release all memory allocated for the linked list
        free_fibonacci_list(head);
    }

    // Indicate sucessful run of the program
    return 0;
}

// ------ Function definitions ------------------------------------------------
/**
 * Creates a doubly-linked list containing the Fibonacci sequence up to the nth
 * number and prints the last (nth) Fibonacci number
 *
 * @param count Number of Fibonacci numbers to generate
 * @return Pointer to the head of the linked list, or NULL if memory allocation
 * fails
 */
FibonacciNode *create_fibonacci_list(int count) {

    FibonacciNode *first_node,  // This is the header node
        *second_node,           // Second node in the linked list
        *previous_node,         // The previous node in the list
        *new_node;              // Newly created node

    // ---- Create head node ----------
    // Allocate memory for the first node (F(0) = 0)
    first_node = malloc(sizeof(FibonacciNode));
    // Check if memory allocation was successful
    if (first_node == NULL) return NULL;

    // Initialize the first node with value 0
    first_node->value = 0;
    // First node has no next node yet
    first_node->next = NULL;
    // First node has no previous node
    first_node->prev = NULL;

    // ---- Create second node --------
    // Allocate memory for the second node (F(1) = 1)
    second_node = malloc(sizeof(FibonacciNode));
    // If memory allocation fails, return what we have so far
    if (second_node == NULL) return first_node;

    // Initialize the second node with value 1
    second_node->value = 1;
    // Second node has no next node yet
    second_node->next = NULL;
    // Link second node to previous node
    second_node->prev = first_node;
    // Link first node to second node
    first_node->next = second_node;

    // Set the current last node for the loop below
    previous_node = second_node;

    // Generate remaining Fibonacci numbers
    for (int i = 2; i < count; i++) {
        // Allocate memory for the next Fibonacci number
        new_node = malloc(sizeof(FibonacciNode));
        // If memory allocation fails, return what we have so far
        if (new_node == NULL) return first_node;

        // Calculate next Fibonacci number as sum of previous two
        new_node->value = previous_node->value + previous_node->prev->value;
        // New node has no next node yet
        new_node->next = NULL;
        // Link current node to previous node
        new_node->prev = previous_node;
        // Link previous node to current node
        previous_node->next = new_node;

        // Update the last node reference for next iteration
        previous_node = new_node;
    }

    // Print the last Fibonacci number as per user input
    printf("%d\n", previous_node->value);

    // Return pointer to the head of the linked list
    return first_node;
}

/**
 * Frees all memory allocated for the linked list
 *
 * @param head Pointer to the first node of the linked list
 */
void free_fibonacci_list(FibonacciNode *head) {
    FibonacciNode *current_node = head;  // Start at the head of the list
    FibonacciNode *next_node;  // Temporary pointer to hold the next node

    // Iterate through the entire list
    while (current_node != NULL) {
        // Save the next node before freeing current
        next_node = current_node->next;
        // Free the current node
        free(current_node);
        // Move to the next node
        current_node = next_node;
    }
}