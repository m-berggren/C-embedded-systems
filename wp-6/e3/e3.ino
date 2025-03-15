// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __
// Work package 6
// Exercise 3
// Submission code: 133204

// Include section
#include <Adafruit_NeoPixel.h>  // Neopixel library
#include <Keypad.h>             // Keypad library

// Define section
#define PIN 2               // Input pin Neopixel is attached to
#define NUM_LEDS 24         // Number of neopixels in ring
#define ARRAY_COUNT 8       // Allowed input count in a sequence
#define KEY_COUNT 7         // Amount of arrays of different keys there are
#define DELAY_COUNT 3000    // Delay count in ms
#define BLINK_INTERVAL 200  // Interval in ms in which LEDs blink
#define LED_TAIL 4          // Lenght of the LED tail

Adafruit_NeoPixel stargate =  // Defines the neopixel ring used
    Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

const byte ROWS = 4;  // Amount of rows on the keypad
const byte COLS = 4;  // Amount of columns on the keypad

const char KEYS[ROWS][COLS] = {{'1', '2', '3', 'A'},  // Key choices on keypad
                               {'4', '5', '6', 'B'},
                               {'7', '8', '9', 'C'},
                               {'*', '0', '#', 'D'}};

byte COL_PINS[COLS] = {8, 7, 6, 5};  // Which pin goes to what column in keypad
byte ROW_PINS[ROWS] = {12, 11, 10, 9};  // Which pin goes to what row in keypad

int array_of_indexes[ARRAY_COUNT] = {  // Which LEDs to light up in the ring
    3, 6, 9, 12, 15, 18, 21, 24};

Keypad keypad = Keypad(makeKeymap(KEYS), ROW_PINS, COL_PINS, ROWS, COLS);
int counter = 0;

char input_sequence[ARRAY_COUNT] = {};  // Input choices by user in a sequence

const char VALID_KEYS[KEY_COUNT][ARRAY_COUNT] = {  // Valid arrays of keys
    {'1', '3', '6', '5', '4', '3', '2', '9'},
    {'A', '4', 'D', '2', '1', '4', '3', '9'},
    {'C', '2', '1', 'A', '3', '2', 'B', '9'},
    {'9', '8', '7', '6', '5', '4', '3', '9'},
    {'1', '2', '3', '4', '5', '6', '9', '9'},
    {'B', '4', '2', 'A', '3', 'C', '3', '9'},
    {'D', 'A', 'B', 'C', 'A', 'C', 'B', '9'}};

const uint32_t BLINK_COLOR = stargate.Color(255, 100, 0);  // The main color

// Sets a scale used to define the LED-lights, used to create- the "moving" look
const uint32_t LED_COLORS[4] = {
    BLINK_COLOR,                  // The first LED
    stargate.Color(200, 100, 0),  // Second LED with different color
    stargate.Color(150, 100, 0),  // Third LED with slightly different color
    stargate.Color(100, 100, 0)   // Fourth LED with most difference in color
};

// ---- Function declarations

// Function that blinks two LEDs based on input order
void blink_LEDs(int index, int times, int interval);
// Function that creates a dial going through a circle
void run_circle_light(int index);
// Function that creates the dial for every input character in the keypab
void dial_sequence();
// Function that validates if the input from keypad is correct or not
int validate_input_sequence();
// Function that sets all LEDs to a certain color
void set_all_LEDs(int red, int green, int blue);

// ---- Setup for the arduino program
void setup() {
    // Setting up to print to serial monitor
    Serial.begin(9600);
    // Initialize the NeoPixel library.
    stargate.begin();
    // Set brightness (toning it down)
    stargate.setBrightness(75);
    // Display changes to stargate
    stargate.show();
}

// ---- Main loop that goes on until interrupted
void loop() {

    // Loops user has inserted 8 characters with keypab
    while (counter < ARRAY_COUNT) {

        // Get the key press from keypad
        char key = keypad.getKey();

        // If there is a key registered
        if (key) {
            // Print out the chosen key to the console
            Serial.print(key);
            Serial.print('\n');

            // Store input in the sequence
            input_sequence[counter] = key;

            // This ensures light goes in sequence 3, 6, 9, 12, 15, 18, 21, 24
            int led_index = array_of_indexes[counter];
            /* Blinks these LED lights depending on led_index:
            2-3, 5-6, 8-9, 11-12, 14-15, 17-18, 20-21, 23-0 */
            blink_LEDs(led_index, 3, BLINK_INTERVAL);

            // Increment the counter so loop eventually ends
            counter++;
        }
    }

    // Display the dial sequence for each input character
    dial_sequence();

    // Validate sequence input
    int validated = validate_input_sequence();

    // Display green or red LED lights based on valid or invalid sequence
    if (validated) {
        // Set all LEDs green for a valid input
        set_all_LEDs(50, 200, 0);
    } else {
        // Set all LEDs red for invalid input
        set_all_LEDs(230, 20, 0);
    }

    // Let the lights above show until delay has passed
    delay(DELAY_COUNT);
    // Turn off all LEDs
    set_all_LEDs(0, 0, 0);

    // Set counter back to 0 to allow further input
    counter = 0;
}

// ---- Function definitions

/**
 * Function that takes the index and lights up LEDs at index posiiton and the
 * position before it.
 * @param index is the position in the neopixel ring
 * @param times how many times to repeat the blinking
 * @param interval the delay in ms between every blink
 */
void blink_LEDs(int index, int times, int interval) {
    // Updates LED lights x times, with a set delay
    for (int i = 0; i < times; i++) {

        // Set first LED pixel
        stargate.setPixelColor(index % NUM_LEDS, BLINK_COLOR);
        // Set second LED pixel
        stargate.setPixelColor((index - 1) % NUM_LEDS, BLINK_COLOR);
        // Show updated LEDs
        stargate.show();

        // Delay application by x ms
        delay(interval);

        // Turn off first LED pixel
        stargate.setPixelColor(index % NUM_LEDS, stargate.Color(0, 0, 0));
        // Turn off second LED pixel
        stargate.setPixelColor((index - 1) % NUM_LEDS, stargate.Color(0, 0, 0));
        // Show updated LEDs
        stargate.show();

        // Delay application by x ms
        delay(interval);
    }
}

/**
 * Function that creates the dial that goes through the entire neopixel ring
 * @param index that's the starting index of the dial
 */
void run_circle_light(int index) {

    // Turn off all LEDs first
    set_all_LEDs(0, 0, 0);

    // Loop over every LED position
    for (int i = index; i < NUM_LEDS + index; i++) {
        // Reset all LEDs before setting new ones
        set_all_LEDs(0, 0, 0);

        // Set colors for the tail (4 LEDs with changing colors)
        for (int j = 0; j < LED_TAIL; j++) {
            // Calculate position, using modulo to wrap around the ring
            int position = (i - j) % NUM_LEDS;
            // Handle negative numbers in modulo operation
            if (position < 0) position += NUM_LEDS;
            // Set color from the array of LED_COLORS
            stargate.setPixelColor(position, LED_COLORS[j]);
        }

        // Show the updated LEDs
        stargate.show();
        // Delay at 0.25s, ensuring a quick dial
        delay(25);
    }

    // Turn off all LEDs before blinking
    set_all_LEDs(0, 0, 0);
    // Blink LEDs at the index
    blink_LEDs(index, 2, BLINK_INTERVAL);
}

/**
 * Function that runs the dial for every input in the input_array.
 */
void dial_sequence() {
    // Run the dial sequence for every instance in the input_array
    for (int i = 0; i < ARRAY_COUNT; i++) {
        // Creates the LEDs moving around the circle
        run_circle_light(array_of_indexes[i]);
    }
}

/**
 * Function that loops through the array of valid keys that consists of arrays
 * of characters 0-9 and A-D.
 * @return Integer value 0 or 1, depending on if input sequence has a match in
 * the array of valid keys.
 */
int validate_input_sequence() {
    // Set match as 0
    int match = 0;

    // Loop through the array of valid key sequences
    for (int i = 0; i < KEY_COUNT; i++) {
        // No need to check more arrays if there is a matching array
        if (match) break;
        // Defining j here as it is used in if statement outside of loop
        int j;
        // Loops through array of characters
        for (j = 0; j < ARRAY_COUNT; j++) {
            // Break loop if char at index j is not equal to the key in array
            if (input_sequence[j] != VALID_KEYS[i][j]) {
                break;
            }
        }
        // When j equals 8 it means that an array has been traversed
        if (j == 8) {
            // There is a matching array so sets match to 1
            match = 1;
        }
    }
    // Return match 0 or 1
    return match;
}

/**
 * Function that sets all LEDs to a defined LED value.
 * @param red
 * @param green
 * @param blue
 */
void set_all_LEDs(int red, int green, int blue) {
    // Loop through all 24 LED lights in Neopixel ring
    for (int i = 0; i < NUM_LEDS; i++) {
        // Set LED at index to specific RGB value
        stargate.setPixelColor(i, stargate.Color(red, green, blue));
    }
    // Display changes to stargate
    stargate.show();
}