// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __ (2025)
// Work package 2
// Exercise 4
// Submission code: 471940

// ------ Include section -----------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------ Define section ------------------------------------------------------
#define MAX_ARGS 6                      // Maximum allowed argument count

// ---- Type definitions --------------
typedef struct {
    int engine_on;                      // Bit count 1, wiht range from 0-1
    int gear_pos;                       // Bit count 3, range 0-4
    int key_pos;                        // Bit count 2, range 0-2
    int brake_1;                        // Bit count 1, range 0-1
    int brake_2;                        // Bit count 1, range 0-1
} VEHICLE;

// ------ Function declarations -----------------------------------------------

// Function that validates the input values stored in VEHICLE
int validate_input(VEHICLE *veh);

// Function that packs the vehicle data into a single byte
char pack_the_bits(VEHICLE *veh);

// ------ Main ----------------------------------------------------------------
int main(int argc, char *argv[]) {
    // ---- Validate arguments --------

    // Check that argument count is exactly 6 (file + 5 args)
    if (argc != 6) {
        printf("Error: You must give 5 arguments.\n");
        return 1;
    }

    // Go through each argument and check if they are all just 1 char length
    for (int i = 1; i < MAX_ARGS; i++) {
        if (strlen(argv[i]) > 1) {
            printf("Error: Arguments must have a length of only 1.\n");
            return 1;
        }
    }

    // ---- Variable declarations -----
    VEHICLE pack_values;            // Holds the values that should be packed
    unsigned char packed;           // Variable holding packed bits in 1 byte.

    /* Made sure arguments are the correct amount and length, then store them
    as integers and late rperform the last validation */
    pack_values.engine_on = atoi(argv[1]);
    pack_values.gear_pos  = atoi(argv[2]);
    pack_values.key_pos   = atoi(argv[3]);
    pack_values.brake_1   = atoi(argv[4]);
    pack_values.brake_2   = atoi(argv[5]);

    // Last validation check
    if (!validate_input(&pack_values)) {
        printf("Error: Invalid input values.\n");
        return 1;
    }

    // ---- Program logic -------------
    packed = pack_the_bits(&pack_values);
    printf("0x%02X\n", packed);

    return 0;
}

// ------ Function definitions ------------------------------------------------

/**
 * Validates all the input values stored in the VEHICLE struct
 * Checks if each value is within its specified range:
 * - engine_on: 0-1 (1 bit)
 * - gear_pos:  0-4 (3 bits)
 * - key_pos:   0-2 (2 bits)
 * - brake_1:   0-1 (1 bit)
 * - brake_2:   0-1 (1 bit)
 * 
 * @param veh Pointer to VEHICLE struct containing values to validate
 * @return 1 if all values are valid, 0 if any value is invalid
 */
int validate_input(VEHICLE *veh) {
    // Check if engine_on is less than 0 or more than 1
    if (veh->engine_on < 0 || veh->engine_on > 1) return 0;
    // Check if gear_pos is less than 0 or more than 4
    if (veh->gear_pos  < 0 || veh->gear_pos  > 4) return 0;
    // Check if key_pos is less than 0 or more than 2
    if (veh->key_pos   < 0 || veh->key_pos   > 2) return 0;
    // Check if breake_1 is less than 0 or more than 1
    if (veh->brake_1   < 0 || veh->brake_1   > 1) return 0;
    // Check if breake_2 is less than 0 or more than 1
    if (veh->brake_2   < 0 || veh->brake_2   > 1) return 0;
    // If none got caught then they are all valid, return 1
    return 1;
}

/**
 * Packs the vehicle data into a single byte using bitwise operations
 * Bit layout (MSB to LSB):
 * - Bit 7:    engine_on (1 bit)
 * - Bits 6-4: gear_pos  (3 bits)
 * - Bits 3-2: key_pos   (2 bits)
 * - Bit 1:    brake_1   (1 bit)
 * - Bit 0:    brake_2   (1 bit)
 * 
 * @param veh Pointer to VEHICLE struct containing values to pack
 * @return Packed byte containing all vehicle data
 */
char pack_the_bits(VEHICLE *veh) {
    // Initialize bit string with all bits set to 0
    unsigned char bit_str = 0b0;

    // Pack each value into its designated bit position using left shifts 
    // and OR operations
    bit_str |= (veh->engine_on << 7);             // Bit 7 (MSB)
    bit_str |= (veh->gear_pos  << 4);             // Bits 6-4
    bit_str |= (veh->key_pos   << 2);             // Bits 3-2
    bit_str |= (veh->brake_1   << 1);             // Bit 1
    bit_str |= (veh->brake_2);                    // Bit 0 (LSB)

    // Returns the updated bit string
    return bit_str;
}

// 1 2 2 1 1
// 0000 0010

// 1000 0000
// 0010 0000
// 0000 1000
// 0000 0010
// 0000 0001
// 1010 1011