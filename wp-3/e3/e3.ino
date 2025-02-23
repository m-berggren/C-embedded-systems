// (C) __Marcus Berggren, Carl Vågfelt Nihlmar, Ibrahim Alzoubi, group: 4 __
// (2025) Work package 3
// Exercise 3
// Submission code: 175962

// Pin definitions
const int TEMP_SENSOR = A0;  // Temperature sensor on analog pin A0

// Configurable reading period (in milliseconds)
int readingPeriod = 500;  // Default 0,5 second, can be modified

// Function to convert analog reading to temperature in Celsius
float readTemperature() {
    int reading = analogRead(
        TEMP_SENSOR);  // Reads the analog input into an int between 0 and 1023
    float voltage =
        reading * 5.0 / 1024.0;  // Converts the reading to voltage (0-5V)

    return (voltage - 0.5) *
           100;  // conversion formula for voltage to celsius temperature
}

void setup() {
    // Initialize serial communication
    Serial.begin(9600);

    // Set analog pins as inputs
    pinMode(TEMP_SENSOR, INPUT);
}

void loop() {
    // reads sensors
    float temperature = readTemperature();  // reads temperature

    // Prints readings to serial monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" Celsius");

    // Wait before next reading
    delay(readingPeriod);  // Delay for 1 second
}
