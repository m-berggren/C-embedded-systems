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

// ---- Include section -------------------------------------------------------
#include <DHT11.h> // Use DHT library

// ---- Define section --------------------------------------------------------

// ---- Pins --------------------------
#define WHITE_PIN   11      // Defines pin for white LED
#define BLUE_PIN    8       // Defines pin for blue LED
#define YELLOW_PIN  7       // Defines pin for yellow LED
#define ORANGE_PIN  5       // Defines pin for orange LED
#define RED_PIN     3       // Defines pin for red LED
#define TEMP_PIN    A0      // Defines pin for TMP36

#define INTERVAL    1        // The time interval to update LEDs

// ---- Define variables ---------------------------------------------------

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

DHT11 temp_sensor(TEMP_PIN);

// ---- Function declarations -------------------------------------------------

// Function that read and converts analog value to celcius
int read_temp_value();

// ---- Setup section ---------------------------------------------------------

// Executed once for setup
void setup() {
    Serial.begin(9600);
    // Loop through all thresholds
    for (int i = 0; i < sizeof(thresholds) / sizeof(THRESHOLD); i++) {
        // Define LED to output mode
        pinMode(thresholds[i].pin, OUTPUT);
    }
}

// ---- Loop section ----------------------------------------------------------
/**
* Triggered every second to:
* 1. Read current temperature from TMP36 sensor
* 2. Convert analog reading to temperature in Celsius 
* 3. Update LED indicators based on temperature thresholds
*/
void loop() {

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

  Serial.println(temperature);

  delay(INTERVAL);
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