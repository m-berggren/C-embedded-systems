// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __ (2025) 
// Work package 4
// Exercise 1
// Submission code: 250204

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

// ---- Define section --------------------------------------------------------

// ---- Pins --------------------------
#define WHITE_PIN   11      // Defines pin for white LED
#define BLUE_PIN    8       // Defines pin for blue LED
#define YELLOW_PIN  7       // Defines pin for yellow LED
#define ORANGE_PIN  5       // Defines pin for orange LED
#define RED_PIN     3       // Defines pin for red LED
#define TEMP_PIN    A0      // Defines pin for TMP36

// ---- Timer constants ---------------
#define CLOCK_SPEED 16000000 // Clock speed of Uno
#define PRESCALER   1024     // Slow down speed of timer by dividing the freq:
                             // taking Uno clock speed (16MHz) / prescaler
#define INTERVAL    1        // The time interval to update LEDs

// ---- Define variables ---------------------------------------------------

volatile bool update_leds = false;

// Structure to map temperature ranges to output pins
typedef struct {
    float min_temp;         // Lower bound of temperature range (inclusive)
    int pin;                // Pin to activate for this temperature range
} THRESHOLD;

// Temperature range definitions with corresponding output pins
THRESHOLD thresholds[] = {
    {0.0,  WHITE_PIN},      // Range: 0.0C to 10.9C
    {11.0, BLUE_PIN},       // Range: 11.0C to 20.9C
    {21.0, YELLOW_PIN},     // Range: 21.0C to 30.9C
    {31.0, ORANGE_PIN},     // Range: 31.0C to 40.9C
    {41.0, RED_PIN}         // Range: 41.0C and above
};

// ---- Function declarations -------------------------------------------------

// Function that read and converts analog value to celcius
int read_temp_value();

// ---- Setup section ---------------------------------------------------------

/* Information for the setup:
The clock speed for an Arduino Uno is 16MHz (16,000,000 Hz). Timer0 and 
timer2 are 8 bit timers, so they can store max counter value of 255. So timer1 
can be chosen, its 16 bit reaches a max number of 65,535.

For the timer1 with 16 bits it would be 65,536 / 16,000,000 (~ 4ms). To
interrupt every second we can use a prescaler: Hz = clock speed / prescaler

Actual conversion:
CLOCK_SPEED / (PRESCALER * INTERVAL) - 1

Since it's zero-indexed there's a -1 above.

Compare Match Register (CMR)
CMR = 15,624 = 16,000,000 / (1024 * 1) - 1
*/

// Executed once for setup
void setup() {
    // Loop through all thresholds
    for (int i = 0; i < sizeof(thresholds) / sizeof(THRESHOLD); i++) {
        // Define LED to output mode
        pinMode(thresholds[i].pin, OUTPUT);
    }

    // Set temperature sensor to input mode
    pinMode(TEMP_PIN,   INPUT);

    // ---- Setting up the timer interruption logic using timer1

    // Stop all interrupts
    cli();

    // Calculating Compare Match Register (CMR) according to equation above
    int CMR = (CLOCK_SPEED / (PRESCALER * INTERVAL)) - 1;

    // Sets timer1 to interrupt at 1Hz
    TCCR1A = 0; // Timer Counter Control Register 1A, controls operation mode
    TCCR1B = 0; // Timer Counter Control Register 1B, controls operation mode
    TCNT1  = 0; // Timer that's incremented

    // Setting the CMR, it's the value TCNT1 is compared against
    OCR1A = CMR;

    /* Using Clear Timer on Compare Match (CTC) mode will clear the timer after
    TCNT1 matches OCR1A, so we use bitwise OR to set WGM12 to true */
    TCCR1B |= (1 << WGM12);

    // Set the CS12 and CS10 in a prescale of 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);

    /* Enabling OCIE1A on TIMSK1 (Timer Interrupt Mask) means that an interrupt 
    is created whenever timer value TCNT1 matches 0CR1A */
    TIMSK1 |= (1 << OCIE1A);

    // Calling sei() to allow interrupts again
    sei();

}

// ---- Interrupt ---------------------
/**
 * Timer1 Interrupt Service Routine (ISR)
 */
ISR(TIMER1_COMPA_vect) {
  	// Update the value update_leds to true
  	update_leds = true;
}

// ---- Loop section ----------------------------------------------------------
/**
* Triggered every second to:
* 1. Read current temperature from TMP36 sensor
* 2. Convert analog reading to temperature in Celsius 
* 3. Update LED indicators based on temperature thresholds
*/
void loop() {

  // Check if update_leds flag is set to true in the interrupt
  if (update_leds) {
    /* Reads and converts analog value to volt, then temperature in celcius 
    from the TMP36 sensor */
    int temperature = read_temp_value();

    // Loop through each treshold and adjust LED lights accordingly
    for (int i = 0; i < sizeof(thresholds) / sizeof(THRESHOLD); i++) {
        // Check if temp is higher or equal to the min_temp of each threshold
        if (temperature >= thresholds[i].min_temp)
            // If so, light up LED by setting it to HIGH
            digitalWrite(thresholds[i].pin, HIGH);
        else
            // If not, it is lower than min_temp and we set pin to LOW
            digitalWrite(thresholds[i].pin, LOW);
    }
    
    // Set update leds to false
    update_leds = false;
  }
}

// ------ Function definitions ------------------------------------------------

/**
 * Function that reads the analog value, converts to voltage and lastly to
 * celcius.
 * 
 * @return - Integer in celcius  
 */
int read_temp_value() {
    /* Reading the analog value 0-1023. Then convert to voltage by multiplying
    5.0195 / 1024.0 to get the voltage per value since max is 1024.
    Formula used from lecture 4 with Tinkercad. */
    float voltage = analogRead(TEMP_PIN) * 5.0195 / 1024.0;
    // Then convert voltage to celcius, ((voltage - 500mV) times 100)
    return (voltage - 0.5) * 100;
}