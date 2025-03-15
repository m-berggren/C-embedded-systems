// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __ (2025)
// Work package 5
// Exercise 1
// Submission code: 981234

/**
* This program uses LEDs and a Pushbutton. One LED blinks once every second
* and the other one when the button is pressed down.
* 
* Purpose: Maintaining a time count that changes state of one LED while
* also checking if button is pressed.
*
*/

// ---- Define section --------------------------------------------------------

#define RED_LED 	8				// Digital pin 8 leading to red LED
#define GREEN_LED 10		  // Digital pin 10 leading to green LED
#define BUTTON		2				// Digital pin 2 leading to button
#define INTERVAL 1000     // Duration of the delay

// ---- Constants & variables -------------------------------------------------

int led_state;				    // This can be on two states, 1 (HIGH) and 0 (LOW)

// ---- Setup section ---------------------------------------------------------

// Executed once for setup
void setup() {
  
  // Declares pinmode OUTPUT for LED light that can be turned on or off
  pinMode(RED_LED, OUTPUT);
  // Declares pinmode OUTPUT for LED light that can be turned on or off
  pinMode(GREEN_LED, OUTPUT);
  // Declares pinmode INPUT, for button feedback
  pinMode(BUTTON, INPUT);

  // Initialize the BUTTON pin 2 as interupt that triggers update_led
  attachInterrupt(digitalPinToInterrupt(BUTTON), update_led, CHANGE);
  
  // Sets the state to LOW 
  led_state = LOW;
}

// ---- Loop section ----------------------------------------------------------

// A loop funciton that is executed forever by Uno
void loop() {
  // Sets led to emitting light
  digitalWrite(RED_LED, HIGH);
  // Delay the application 
  delay(INTERVAL);

  // Turns off the LED
  digitalWrite(RED_LED, LOW);
  delay(INTERVAL);
}

// Function that is called from interrupt
void update_led() {
  // Changes the state from LOW to HIGH
  if (led_state == LOW) {
    led_state = HIGH;
    
    // If it is HIGH change to LOW
  } else {
    led_state = LOW;
  }

  // Update the led light based on the led_state
  digitalWrite(GREEN_LED, led_state);
}
