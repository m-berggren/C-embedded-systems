// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __
// Work package 4
// Exercise 3
// Submission code: 250204

#include <Adafruit_NeoPixel.h>

// Pin definitions
#define NEOPIXEL_PIN 6  // NeoPixel ring data pin
#define TRIGGER_PIN 9   // Ultrasonic sensor trigger pin
#define ECHO_PIN 10     // Ultrasonic sensor echo pin
#define RED_LED_PIN 13  // Standard red LED pin

// NeoPixel parameters
#define NUMPIXELS 16          // Number of pixels in the ring
#define MAX_DISTANCE 317      // Maximum distance in cm
#define MIN_DISTANCE 4        // Minimum distance in cm
#define SPEED_OF_SOUND 0.034  // Speed of sound in cm/microsecond

// Initialize NeoPixel ring
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {

    // Initialize serial communication
    Serial.begin(9600);

    // Initialize ultrasonic sensor pins
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // Initialize red LED pin
    pinMode(RED_LED_PIN, OUTPUT);
    digitalWrite(RED_LED_PIN, LOW);
}

void loop() {
    // Measure distance using ultrasonic sensor
    long duration, distance;

    // Clear the trigger pin
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIGGER_PIN, HIGH);  // Sending high signal
    delayMicroseconds(10);            // Holds high signal for 10 microseconds

    // Stops the high signal
    digitalWrite(TRIGGER_PIN, LOW);

    // Read the echo pin, convert to distance
    duration = pulseIn(
        ECHO_PIN,
        HIGH);  // pulse in reads the duration of the pulse in microseconds
    distance = duration * SPEED_OF_SOUND /
               2;  // Calc distance in cm via speed of sound, duration and
                   // divede by 2 due to roundtrip

    // Print distance
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Map the distance to the number of LEDs to light up
    int ledsToLight = map(distance, MIN_DISTANCE, MAX_DISTANCE, 0, NUMPIXELS);

    // Clear all pixels before we light it up for this loop
    pixels.clear();

    // Light up the number of LEDs based on the distance via ledsToLight
    for (int i = 0; i < ledsToLight; i++) {
        // Set the color of the pixel to blue
        pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    }

    // Display the pixels we set via the for loop above
    pixels.show();

    // Lights up the red LED if all LEDs are lit
    if (ledsToLight >= NUMPIXELS || ledsToLight <= 0) {
        digitalWrite(RED_LED_PIN, HIGH);
    } else {
        digitalWrite(RED_LED_PIN, LOW);
    }

    // Short delay before next reading
    delay(100);
}