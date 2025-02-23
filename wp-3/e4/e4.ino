// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __
// (2025) Work package 3
// Exercise 4
// Submission code: 175962

#include <Keypad.h>  // Include the Keypad library to handle matrix keypad input

// Define keypad dimensions
const byte ROWS = 4;    // Number of rows in the keypad
const byte COLS = 4;    // Number of columns in the keypad

// Define the keypad layout matrix
const char KEYS[ROWS][COLS] = { // Create a 2D array repr. the keys on the keypad
  {'1', '2', '3', 'A'},    // First row of keys
  {'4', '5', '6', 'B'},    // Second row of keys
  {'7', '8', '9', 'C'},    // Third row of keys
  {'*', '0', '#', 'D'}     // Fourth row of keys
};

// Define the Arduino pins connected to the keypad
byte COL_PINS[COLS] = {7, 6, 5, 4};   // Arduino pins connected to keypad columns
byte ROW_PINS[ROWS] = {11, 10, 9, 8}; // Arduino pins connected to keypad rows

// Create keypad instance with pin mappings
Keypad keypad = Keypad(makeKeymap(KEYS), ROW_PINS, COL_PINS, ROWS, COLS);

void setup()
{
  Serial.begin(9600);    // Initialize serial communication at 9600 baud rate
}

void loop()
{
  char key = keypad.getKey(); // Check if a key is pressed and store the value
  
  if (key) {                  // If a key was pressed (key is not null)
   Serial.print(key);         // Print the key value to serial monitor
   Serial.print('\n');        // Print a newline character for better readability
  }
}