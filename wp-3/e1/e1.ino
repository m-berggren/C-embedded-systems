// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __
// (2025) Work package 3
// Exercise 1
// Submission code: 175962

/**
 * This program uses LEDs and a Pushbutton. One LED blinks once every second
 * and the other one when the button is pressed down.
 *
 * Purpose: Maintaining a time count that changes state of one LED while
 * also checking if button is pressed.
 *
 */

// ---- Define section --------------------------------------------------------

#define RED_LED 4     // Digital pin 4 leading to red LED
#define GREEN_LED 11  // Digital pin 11 leading to green LED
#define BUTTON 8      // Digital pin 8 leading to button

// ---- Constants & variables -------------------------------------------------

unsigned long running_millis = 0;  // Starts at 0 and get updated during loop
const int BLINK_INTERVAL = 1000;   // Constant to declare 1s duration
bool led_state = false;            // Instantiate led_state used w/ GREEN_LED

// ---- Setup section ---------------------------------------------------------

// Executed once for setup
void setup() {
    // Declares pinmode OUTPUT for LED lights that can be turned on or off
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);

    // Declares pinmode INPUT, for button feedback
    pinMode(BUTTON, INPUT);
}

// ---- Loop section ----------------------------------------------------------

// A loop funciton that is executed forever by Uno
void loop() {
    // Sets milliseconds since program started. Unsigned meaning positive values
    // only, long up to 2 ^ 64 -1
    unsigned long current_millis = millis();

    // Check if the difference of MS since start and last updated MS count is
    // longer than the interval (1S)
    if (current_millis - running_millis >= BLINK_INTERVAL) {
        // Changes led_state to the opposite state. Either from false to true or
        // true to false
        led_state = !led_state;

        // Sets the green LED as true or false based on led_state
        // True, false, HIGH, LOW, 1 or 0 are all valid
        digitalWrite(GREEN_LED, led_state);

        // Updating the running_millis to MS count since program started
        running_millis = current_millis;
    }

    // Checks if button is pressed
    if (digitalRead(BUTTON) == HIGH) {
        // Turns on LED
        digitalWrite(RED_LED, HIGH);
        // When no longer pressed
    } else {
        // Turns off LED
        digitalWrite(RED_LED, LOW);
    }
}
