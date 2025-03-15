// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __ (2025) 
// Work package 5
// Exercise 2
// Submission code: 981234

/**
 * This program reads the temperature every second and update LED lights
 * accordingly.
 *
 * Purpose: Update LED lights according to value readings from a 
 * temperature sensor that uses a library.
 */

// ---- Include section -------------------------------------------------------
#include <DHT.h> // Use DHT library

// ---- Define section --------------------------------------------------------

// ---- Pins --------------------------
#define WHITE_PIN   11      // Defines pin for white LED
#define BLUE_PIN    8       // Defines pin for blue LED
#define YELLOW_PIN  7       // Defines pin for yellow LED
#define ORANGE_PIN  5       // Defines pin for orange LED
#define RED_PIN     3       // Defines pin for red LED
#define TEMP_PIN    2       // Defines pin for TMP36

#define INTERVAL    1000    // The time interval to update LEDs

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

DHT dht(TEMP_PIN, DHT11);

// ---- Setup section ---------------------------------------------------------

// Executed once for setup
void setup() {
    Serial.begin(9600);
    dht.begin();
    // Loop through all thresholds
    for (int i = 0; i < sizeof(thresholds) / sizeof(THRESHOLD); i++) {
        // Define LED to output mode
        pinMode(thresholds[i].pin, OUTPUT);
    }
}

// ---- Loop section ----------------------------------------------------------
/**
* Triggered every second to:
* 1. Read current temperature from DHT11 sensor
* 2. With library convert reading to temperature in Celsius 
* 3. Update LED indicators based on temperature thresholds
*/
void loop() {

  // Reads temperature in celcius from the DHT11 sensor
  int temperature = dht.readTemperature();

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

  // Print out information to the console
  Serial.print("Temp reading: ");
  Serial.println(temperature);
  Serial.println("");

  // Delay the applicaiton by the set interval in ms
  delay(INTERVAL);
}