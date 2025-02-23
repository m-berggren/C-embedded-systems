// ------ Include section -----------------------------------------------------
#include <stdio.h>              // Used by printf
#include <string.h>             // Used by strlen
#include <ctype.h>              // Used by isdigit
#include <stdlib.h>             // Used by atoi

// ------ Define section ------------------------------------------------------

#define ARG_COUNT 6             // Maximum allowed arguments (including file)

// ---- Type definitions --------------
typedef struct {                // Defining an ELEVATOR type
    int engine_on;              // 1 bit, MSB
    int floor_pos;              // 3 bits
    int door_pos;               // 2 bits
    int brake_1;                // 1 bit
    int brake_2;                // 1 bit, LSB
} ELEVATOR;

// ------ Function declarations -----------------------------------------------

// Function that validates the input values stored in ELEVATOR
int validate_input(ELEVATOR *elev);

// Function that packs the elevator data into a single byte
char pack_the_bits(ELEVATOR *elev);

// ------ Main ----------------------------------------------------------------
/**
 * This program packs bits into a byte. It takes 5 arguments and will print out 
 * its value as a hexadecimal.
 *
 * @author Marcus Berggren
 * @date 2025
 */
int main(int argc, char *argv[]) {

    // ---- Validate arguments --------

    // Check so that file + 5 arguments are passed
    if (argc != ARG_COUNT) {
        // If argument count not equal to ARG_COUNT print info and return
        printf("invalid");
        return 0;
    }

    // Go through each argument and check lenght and if a digit. Starts on 1
    // as we do not want to check the file param
    for (int i = 1; i < ARG_COUNT; i++) {
        // Checks if length of each argument not equal to 1
        if (strlen(argv[i]) != 1) {
            // If not then print info and return
            printf("invalid");
            return 0;
        }

        // Also check if argument is a digit. Since argv[i] is a string and 
        // isdigit checks one character, we check the first (and only) char
        if (!isdigit(argv[i][0])) {
            // If not a digit print info and return
            printf("invalid");
            return 0;
        }
    }

    // ---- Variable declarations -----

    ELEVATOR elevator;              // Type that holds the values to be packed
    unsigned char packed;           // Variable holding packed bits in 1 byte

    /* Arguments are the correct amount and length from above. This stores them
    as integers and later below performs the last validation */
    elevator.engine_on = atoi(argv[1]);
    elevator.floor_pos = atoi(argv[2]);
    elevator.door_pos  = atoi(argv[3]);
    elevator.brake_1   = atoi(argv[4]);
    elevator.brake_2   = atoi(argv[5]);

    // Last validation check that passes the address of the elevator
    if (!validate_input(&elevator)) {
        // If not valid then print info and return
        printf("invalid");
        return 0;
    }

    // ---- Program logic -------------

    // Returns a packed bit string using left shift and OR operations
    packed = pack_the_bits(&elevator);

    // Formats and prints out the hexadecimal value
    printf("0x%02X", packed);

    // End of program
    return 0;
}

// ------ Function definitions ------------------------------------------------

/**
 * Validates all the input values stored in the ELEVATOR struct
 * Checks if each value is within its specified range:
 * - engine_on:  0-1 (1 bit)
 * - floor_pos:  0-7 (3 bits)
 * - door_pos:   0-3 (2 bits)
 * - brake_1:    0-1 (1 bit)
 * - brake_2:    0-1 (1 bit)
 * 
 * @param elev Pointer to ELEVATOR struct containing values to validate
 * @return 1 if all values are valid, 0 if any value is invalid
 */
int validate_input(ELEVATOR *elev) {
    // Check if engine_on is less than 0 or more than 1
    if (elev->engine_on < 0 || elev->engine_on > 1) return 0;
    // Check if floor_pos is less than 0 or more than 7
    if (elev->floor_pos < 0 || elev->floor_pos > 7) return 0;
    // Check if door_pos is less than 0 or more than 3
    if (elev->door_pos  < 0 || elev->door_pos  > 3) return 0;
    // Check if brake_1 is less than 0 or mor ethan 1
    if (elev->brake_1   < 0 || elev->brake_1   > 1) return 0;
    // Check if brake_2 is less than 0 or more than 1
    if (elev->brake_2   < 0 || elev->brake_2   > 1) return 0;

    // If none of the above were true then they are valid & return 1
    return 1;
}

/**
 * Packs the elevator data into a single byte using bitwise operations
 * Bit layout (MSB to LSB):
 * - Bit 7:    engine_on (1 bit)
 * - Bits 6-4: floor_pos (3 bits)
 * - Bits 3-2: door_pos  (2 bits)
 * - Bit 1:    brake_1   (1 bit)
 * - Bit 0:    brake_2   (1 bit)
 * 
 * @param elev Pointer to ELEVATOR struct containing values to pack
 * @return Packed byte containing all elevator data
 */
char pack_the_bits(ELEVATOR *elev) {
    // Initialize bit string with all bits set to 0
    unsigned char bit_str = 0b0;

    // Pack each value into its designated bit position using left shifts 
    // and OR operations
    bit_str |= (elev->engine_on << 7);      // Bit 7 (MSB)
    bit_str |= (elev->floor_pos << 4);      // Bits 6-4
    bit_str |= (elev->door_pos  << 2);      // Bits 3-2
    bit_str |= (elev->brake_1   << 1);      // Bit 1
    bit_str |= (elev->brake_2);             // Bit 0 (LSB)

    // Returns the updated bitstring
    return bit_str;
}
