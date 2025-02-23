// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __ (2025) 
// Work package 4
// Exercise 2
// Submission code: 

/**
 * This program uses Timer interrupts to periodically read temperature
 * and update LED lights accordingly.
 *
 * Purpose: Learn about timer interrupts and update LED lights according to
 * value readings from a temperature sensor.
 * 
 * Source for setting up timer1 in Arduino Uno: 
 * https://www.instructables.com/Arduino-Timer-Interrupts/
 */

// ---- Include section -------------------------------------------------------
#include <Servo.h>          // Import the servo library 

// ---- Define section --------------------------------------------------------

#define SERVO_PIN A0        //
// ---- Timer constants ---------------
#define CLOCK_SPEED 16000000 // Clock speed of Uno
#define PRESCALER   1024     // Slow down speed of timer by dividing the freq:
                             // taking Uno clock speed (16MHz) / prescaler
#define INTERVAL    1        // The time interval to update LEDs
#define COUNTS_PER_SECOND 61 // Number of timer2 overflows in 1 second


// ---- Typedef & constants ---------------------------------------------------

int counter = 0;                // 
int timer = 60;                //

Servo servo_A0;                 //
volatile bool new_data = false; //


// ---- Function declarations -------------------------------------------------
//
void rotate_servo();

// Writes out seconds remaining of timer
void write_to_output();

// ---- Setup section ---------------------------------------------------------

/* Information for the setup:
The clock speed for an Arduino Uno is 16MHz (16,000,000 Hz). Timer0 and 
timer2 are 8 bit timers, so they can store max counter value of 255. Timer1 is 
ideal but it is in use by Servo.h library.

Timer0, timer1 and timer2 can all utilize the same max precaler value of 1024.
Timer2 sets it with TCCR2B and clock select bits to 1 for all three CS22, CS21
and CS20.

For the timer2 with 8 bits it would be 256 / 16,000,000 (~0.16ms). To
interrupt every second we can use a prescaler, but in order to go under 256 we 
need to divide the calculations even further:
Hz = clock speed / prescaler / counter

The counter needs to be incremented within the ISR until it goes over the
threshold.

Actual conversion:
(CLOCK_SPEED / (PRESCALER * INTERVAL) / COUNTS_PER_SECOND) - 1

Since it's zero-indexed there's a -1 above.

Compare match register (CMR)
CMR = 15,624 = (16,000,000 / (1024 * 1) / 61) - 1
*/

// Executed once for setup
void setup() {

    // Enable printing to the serial output
    Serial.begin(9600);
    

    servo_A0.attach(SERVO_PIN);
    servo_A0.write(0);

    // ---- Setting up the timer interruption logic using timer2

    // Stop all interrupts
    cli();

    // Calculating compare match register (CMR) according to equation above
    int CMR = (CLOCK_SPEED / (PRESCALER * INTERVAL) / COUNTS_PER_SECOND) - 1;

    // Sets timer1 to interrupt at 1Hz
    TCCR2A = 0; // Timer Counter Control Register 2A, controls operation mode
    TCCR2B = 0; // Timer Counter Control Register 2B, controls operation mode
    TCNT2  = 0; // Timer that's incremented

    // Setting the CMR from above
    OCR2A = CMR; // The value that TCNT2 is compared against

    /* Using Clear Timer on Compare Match (CTC) mode will clear the timer after
    TCNT2 matches OCR2A, so we use bitwise OR to set WGM21 to true */
    TCCR2A |= (1 << WGM21);

    // Set the CS22, CC21 and CS20 in a prescale of 1024
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);

    /* Enabling OCIE2A on TIMSK2 means that an interrupt is created whenever 
    timer value TCNT2 matches 0CR2A */
    TIMSK2 |= (1 << OCIE2A); // Timer Interrupt Mask Resiter 1

    // Calling sei() to allow interrupts again
    sei();

}

// ---- Interrupt ---------------------
/**
 * Timer2 Interrupt Service Routine (ISR)
 * Triggered every 0.16s. When counter goes up to COUNTS_PER_SECOND the
 * counter starts over and new_data will flag that method should be run in main
 * loop.
 */
ISR(TIMER2_COMPA_vect) {

    // Checks if counter is equal to or has surpassed defined max count
    if (counter >= COUNTS_PER_SECOND && timer > 0) {
        // When counter reaches COUNTS_PER_SECOND we reset it again
        counter = 0;

        // Flags that there should be an update made
        new_data = true;

        // Decrement timer to use 
        timer--;
        // Print out the information to the output
        Serial.print("Seconds: ");
        Serial.println(timer);
        
    }

    // Increments counter until it reaches max count and then starts over
    counter++;
}

// ---- Loop section ----------------------------------------------------------
// Inifinite loop running
void loop() {

    /* new_data gets flagged from the ISR, when it is true the method inside
    will run and then set it to false again */
    if (new_data) {
        // Run the movement of the servo
        rotate_servo();

        // Change the flag back to false
        new_data = false;
    }
}

// ------ Function definitions ------------------------------------------------

void rotate_servo() {

    // Map the current second (0-59) to a degree value (0-180)
    int degrees = map(timer, 60, 0, 0, 180);
    
    servo_A0.write(degrees);
}
