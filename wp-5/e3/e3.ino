// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __ (2025)
// Work package 5
// Exercise 3
// Submission code: 981234

/**
* This program reads temperature and light values from sensors and controls
* three LED lights based on different thresholds of these readings. It signals
* with green (OK), red (too hot), blue (too cold).
*
* Purpose: To create a monitoring system that provides visual feedback through
* LEDs based on temperature and light conditions.
*
*/

// ---- Include section -------------------------------------------------------
#include <DHT.h>            // Use DHT library

// ---- Define section --------------------------------------------------------

#define RED_LED		 	3			  // Red LED to digital port (DP) 3
#define GREEN_LED	 	7			  // Green LED to DP 7
#define BLUE_LED	 	8			  // Blue LED to DP 8
#define LIGHT_PIN		A0			// Light sensor to analog port A0
#define TEMP_PIN 		A1			// Temp sensor to analog port A1

#define WAIT_INTERVAL 2000  // Wait time 1 second 

// ---- Function definitions ------------------------------------------------------

/*
* Function that changes the state of three LED lights based on parameters.
* @param red - Integer of 0 to 1
* @param green - Integer of 0 to 1
* @param blue - Integer of 0 to 1
*/
void update_leds(int red, int green, int blue) {
  digitalWrite(RED_LED, red);
  digitalWrite(GREEN_LED, green);
  digitalWrite(BLUE_LED, blue);
}

// ---- Variable declarations ---------------------------------------------------

DHT temp_sensor(TEMP_PIN, DHT11); // Initialize the temp sensor
int temp_value	 = 0;	            // Initializing temp
int light_value	 = 0;	            // Initializing light


// ---- Setup section -----------------------------------------------------------
//
void setup() {
  // Enable printing to serial monitor
  Serial.begin(9600);

  // Enable the temperature sensor
  temp_sensor.begin();
  
  // Set red LED to output mode
  pinMode(RED_LED, OUTPUT);
  // Set green LED to output mode
  pinMode(GREEN_LED, OUTPUT);
  // set blue LED to output mode
  pinMode(BLUE_LED, OUTPUT);
  // Set light sensor to input mode
  pinMode(LIGHT_PIN, INPUT);
}

// ---- Loop section -----------------------------------------------------------
//
void loop() {

  // ---- Light Sensor Conversion ----
  /* Simple percentage conversion for light (0-100%). The analog reading
  (0-1023) can be divided by 10.23 to get percentage. Like so: light_value =
  analogRead(LIGHT) / 10.23, but we can also use map function like below. */
  light_value = map(analogRead(LIGHT_PIN),0, 1023, 0, 100);
  
  // Temperature reading using the dht library
  temp_value = temp_sensor.readTemperature();

  // Print out information to the console
  Serial.print("Light reading: ");
  Serial.println(light_value);
  Serial.print("Temp reading:  ")
  Serial.println(temp_value);
  Serial.println("");
  
  // When there is no light (completely dark)
  if (light_value == 0) {
    // Check temperature in dark conditions
    if (temp_value < -12) {
      // Very cold and dark - show green
      update_leds(LOW, HIGH, LOW);
    } else {
      // Not very cold but dark - show red
      update_leds(HIGH, LOW, LOW);
    }
    // Low light conditions (0-20)
  } else if (light_value <= 20) {
    // Check temperature in low light
    if (temp_value < -12) {
      // Very cold and low light - show blue
      update_leds(LOW, LOW, HIGH);
    } else if (temp_value > 0) {
      // Above freezing and low light - show red
      update_leds(HIGH, LOW, LOW);
    } else {
      // Between -12 and 0 with low light - show green
      update_leds(LOW, HIGH, LOW);
    }
    
    // Medium light conditions (21-60)
  } else if (light_value <= 60) {
    // Check temperature in medium light
    if (temp_value < 0) {
      // Below freezing in medium light - show blue
      update_leds(LOW, LOW, HIGH);
    } else if (temp_value > 20) {
      // Warm in medium light - show red
      update_leds(HIGH, LOW, LOW);
    } else {
      // Moderate temperature in medium light - show green
      update_leds(LOW, HIGH, LOW);
    }
    
    // Bright light conditions (>60)
  } else {
    // Check temperature in bright conditions
    if (temp_value >= 21) {
      // Hot and bright - show green
      update_leds(LOW, HIGH, LOW);
    } else {
      // Not hot but bright - show blue
      update_leds(LOW, LOW, HIGH);
    }
  }
  
  // Wait for 1 second before next reading
  delay(WAIT_INTERVAL);
  
}