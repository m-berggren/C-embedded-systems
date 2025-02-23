// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __ (2025)
// Work package 2
// Exercise 2
// Submission code: 471940

// ------ Include section -----------------------------------------------------
#include <stdio.h>                      // Used by
#include <stdlib.h>                     // Used by srand
#include <time.h>                       // Used by time

// ------ Define section ------------------------------------------------------

// Constants
#define MAX 5                           // Max 5 nodes in list
#define RND_MAX 100                     // Allow random number 0-100

// ---- Typedefs ----

// Define a new type REGTYPE as a node
typedef struct q {
    int number;                         // Random number stored within
    struct q *next;                     // Pointer to next node
    struct q *prev;                     // Pointer to previous node
} REGTYPE;

// ------ Function declarations -----------------------------------------------
// Function creates a linked list of random integers 0-100
REGTYPE *random_list (void);

// Function that adds a node to the first position
REGTYPE *add_first(REGTYPE *temp, int data);

// ------ Main program---------------------------------------------------------
/**
 * This program created a linked list of randomized integers from 0 to RND_MAX,
 * in this case 100. Memory is allocated dynamically as each node is created and
 * each has pointers to both previous and next node, meaning it's a doubly
 * linked list.
 *
 * Purpose: Utilize linked lists, pointers and dynamic memory allocaiton with
 * malloc and lastly freeing memory.
 *
 * DIT633
 */
int main(void) {
    // ---- Variable declarations -----
    srand(time(0));                     // Set random seed
    int nr = 0;                         // Initialize counter that's printed out

    REGTYPE *act_post,                  // Define first current node
            *head = NULL;               // Define first node as head
    head = random_list();               // Creates a linked list of random ints
                                        // that head points to
    int random_num = rand() % RND_MAX;  // Create a random in used in add_first
    head = add_first(head, random_num); // Point head to a new first address
    act_post = head;                    // Assign current node as the first one

    // ---- program logic -------------

    // Loop through linked list and print each current node until next is NULL
    while (act_post != NULL) {
        // Print node information to console
        printf("\n Post nr %d : %d", nr++, act_post->number);
        // Traverse the linked list. The next node becomes the current
        act_post = act_post->next;
    }

    // ---- Free allocated memory -----
    // Frees memory until there are no more pointers to memory address
    while ((act_post = head) != NULL) {
        // Updates head to the next object
        head = act_post->next;
        // Frees this address of its memory
        free(act_post);
    }
    // Successful run, returns 0
    return 0;
}

// ------ Function definitions ------------------------------------------------
/**
 * Function that creates a linked list with a MAX amount of nodes of randomized
 * integers 0 - RND_MAX.
 * @return - Pointer to the first instance of the list
 */
REGTYPE *random_list (void) {
    int i = 0;                              // Counter
    REGTYPE *top, *old, *item;              // Pointers for manipulating list

    // Create first node
    top = malloc(sizeof(REGTYPE));          // Set needed memory for first node

    // Immediately check if malloc succeded
    if (top == NULL) return NULL;

    // Initialize first node
    top->number = rand() % RND_MAX;         // Randomize number 0-100
    top->next = NULL;                       // First node has no next node
    top->prev = NULL;                       // No prev node for the first one

    old = top;                              // Storing top as old node

    // Create a list of MAX count + 1 instances (nodes) with randomized numbers
    for (i = 0; i < MAX; i++) {
        item = malloc(sizeof(REGTYPE));     // Create new current node

        // If malloc fails return the latest working node
        if (item == NULL) return top;

        // Initialize current node
        item->number = rand() % RND_MAX;    // Randomize number 0-100
        item->next = NULL;                  // There is no next item yet
        item->prev = old;                   // Point to previous node

        // Then link prev node with this one. Every next link will be declared
        // one iteration later
        old->next = item;

        // Update old with current, for next iteration
        old = item;
    }

    // Return pointer to the first item in the list
    return(top);
}

/**
 * Function that adds a node to the first position in the linked list
 * @param temp - Takes the pointer to linked list and adds new item to it
 * @param data - A random integer 0-100
 * @return - Pointer to the newly inserted item in the ist
 */
REGTYPE *add_first(REGTYPE *temp, int data) {
    REGTYPE *item = malloc(sizeof(REGTYPE)); // Create memory for new node

    // Return NULL if malloc failed
    if (item == NULL) return NULL;

    item->number = data;                    // Data is a random number 0-100
    item->next = temp;                      // Previous temp node
    item->prev = NULL;                      // No node before this one

    // Update the temp node to point backwards to the new node
    if (temp != NULL) {
        // Point from old node backwards to the new node
        temp->prev = item;
    }

    // Return the newly added item; it is the new entry point of the linked list
    return item;
}
