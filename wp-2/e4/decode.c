// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __
// Work package 2
// Exercise 4
// Submission code: 471940

// ------ Include section -----------------------------------------------------
#include <stdio.h>   // Used by printf
#include <stdlib.h>  // Used by strtol
#include <string.h>  // Used bu strlen

// ------ Define section ------------------------------------------------------

// Setting up VEHICHLE typedef
typedef struct {
    int engine_on;  // Bit count 1, with range from 0-1
    int gear_pos;   // Bit count 3, range 0-4
    int key_pos;    // Bit count 2, range 0-2
    int brake_1;    // Bit count 1, range 0-1
    int brake_2;    // Bit count 1, range 0-1
} VEHICLE;

// ------ Function declarations -----------------------------------------------
// Function that extracts individual values from a packed byte and stores them
// in a VEHICLE struct
void unpack_bits(unsigned char byte, VEHICLE* veh);

// ------ Main ----------------------------------------------------------------
/**
 * This program takes a hexadecimal byte as input and decodes it into individual
 * vehicle control values according to a specific bit layout. The program
 * validates the input argument and displays the decoded values in a formatted
 * table.
 *
 * Purpose: Decode a packed byte containing vehicle control data and display
 * the component values (engine status, gear position, key position, and brake
 * states).
 *
 */
int main(int argc, char* argv[]) {

    // ---- Validate argument ---------
    // Ensure that there is an argument given
    if (argc != 2) {
        printf("Error: Please give one argument.\n");
        return 1;
    }

    // Ensures that argument is 2 chars long
    if (strlen(argv[1]) != 2) {
        printf("Error: Please give an argument with the length of 2 chars.\n");
        return 1;
    }

    // ---- Variable declarations -----
    // Convert the hexadecimal string argument to an unsigned char
    unsigned char hex_val = (unsigned char)strtol(argv[1], NULL, 16);
    // Create a VEHICLE struct to store the unpacked values
    VEHICLE vehicle;

    // ---- Program logic -------------
    // Unpack the byte into individual components
    unpack_bits(hex_val, &vehicle);

    // Print the table header
    printf("Name            Value\n");
    printf("-----------------------------\n");
    // Print each unpacked value in formatted rows
    printf("engine_on       %d\n", vehicle.engine_on);
    printf("gear_pos        %d\n", vehicle.gear_pos);
    printf("key_pos         %d\n", vehicle.key_pos);
    printf("brake1          %d\n", vehicle.brake_1);
    printf("brake2          %d\n", vehicle.brake_2);

    // Return success status code
    return 0;
}

// ------ Function definitions ------------------------------------------------
/**
 * Unpacks a byte into individual values and stores them in a VEHICLE struct.
 * The byte is interpreted according to the following bit layout (MSB to LSB):
 * - Bit 7:    engine_on (1 bit)
 * - Bits 6-4: gear_pos  (3 bits)
 * - Bits 3-2: key_pos   (2 bits)
 * - Bit 1:    brake_1   (1 bit)
 * - Bit 0:    brake_2   (1 bit)
 *
 * @param byte The packed byte to decode
 * @param veh Pointer to a VEHICLE struct where the unpacked values will be
 * stored
 */
void unpack_bits(unsigned char byte, VEHICLE* veh) {
    // Extract engine status from bit 7 (MSB)
    veh->engine_on = (byte >> 7) & 0x01;
    // Extract gear position from bits 6-4
    veh->gear_pos = (byte >> 4) & 0x07;
    // Extract key position from bits 3-2
    veh->key_pos = (byte >> 2) & 0x02;
    // Extract brake1 status from bit 1
    veh->brake_1 = (byte >> 1) & 0x01;
    // Extract brake2 status from bit 0 (LSB)
    veh->brake_2 = byte & 0x01;
}