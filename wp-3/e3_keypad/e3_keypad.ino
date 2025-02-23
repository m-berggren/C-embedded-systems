// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __
// (2025) Work package 3
// Exercise 3_keypad
// Submission code: 175962

/**
 * This program implements a 4x4 keypad matrix scanner that detects and reports
 * key presses through serial communication.
 *
 * Purpose: To read and identify which key is pressed on a 4x4 keypad matrix
 *
 */
const int ROWS = 4;  // Number of rows in the keypad matrix
const int COLS = 4;  // Number of columns in the keypad matrix

const char KEYS[ROWS][COLS] = {  // Matrix mapping keys to their positions
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

const int COL_PINS[COLS] = {7, 6, 5, 4};    // Pins connected to keypad columns
const int ROW_PINS[ROWS] = {11, 10, 9, 8};  // Pins connected to keypad rows

/*
 * Function that scans the keypad matrix and returns the pressed key
 * Returns '\0' if no key is pressed
 */
char get_key() {
    /* Nested loops that goes through rows and columns. Checks if setting row
    to LOW will indicate the same to a column */
    for (int row = 0; row < ROWS; row++) {
        // Set one row to LOW
        digitalWrite(ROW_PINS[row], LOW);

        // Loops through each column
        for (int col = 0; col < COLS; col++) {
            /* If the columns is set LOW it means there is a match at this row
            and col position */
            if (digitalRead(COL_PINS[col]) == LOW) {
                // Return the character at the matching row and col position
                digitalWrite(ROW_PINS[row], HIGH);
                // Return the specific key at this position
                return KEYS[row][col];
            }
        }
        // Set the current back to HIGH
        digitalWrite(ROW_PINS[row], HIGH);
    }
    // If nothing is pressed return null temrinator
    return '\0';
}

// Initialize pins and serial communication
void setup() {
    // Used for printing to monitor
    Serial.begin(9600);

    // Configure each row and column pin
    for (int i = 0; i < ROWS; i++) {
        // Set row pins as outputs
        pinMode(ROW_PINS[i], OUTPUT);
        // Initialize row pin to HIGH
        digitalWrite(ROW_PINS[i], HIGH);
        // Set column pins as inputs
        pinMode(COL_PINS[i], INPUT);
        // Initialize column pin to HIGH;
        digitalWrite(COL_PINS[i], HIGH);
    }
}

// Main program loop, runs until stopped
void loop() {
    // Checks for pressed key
    char key = get_key();

    // If a key is pressed, print it and add a small delay
    if (key != '\0') {
        // Print out the key to serial monitor
        Serial.println(key);
        // Delay by 1s to not print extra keys when pressed longer
        delay(1000);
    }
}