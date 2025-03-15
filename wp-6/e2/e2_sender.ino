// Ibrahim Alzoubi, Marcus Berggren, Carl Vågfelt Nihlmar group: 4 (2025)
// Work package 6
// Exercise 2
// Submission code: 133204 (provided by your TA-s)

// Pin definitions
#define TRIGGER_PIN 7   // pin used to send the initial trigger to the ultrasonic sensor
#define ECHO_PIN 6      // pin used to listent o the incoming puls

// distance stamp
#define SPEED_OF_SOUND 0.034 // Speed of sound in cm/microsecond
/*############################ FUNCTION DECLARATIONS ###############################*/
// sets up the ultrasonic sensor, reads the puls value and returns it 
long read_ultrasonic_sensor();

/*############################ FUNCTION DEFINITIONS ###############################*/
long read_ultrasonic_sensor(){
  // variable declarations
  long duration = 0; // stores the value of the puls duration to be returned
    
  // Initialize ultrasonic sensor pins
  pinMode(TRIGGER_PIN, OUTPUT);
  
  // Clear the signal pin
  digitalWrite(TRIGGER_PIN, LOW);
  
  delayMicroseconds(5);// wait 5 microsec
  
  digitalWrite(TRIGGER_PIN, HIGH); // Sending high signal
  
  delayMicroseconds(10);           // Holds high signal for 10 microsec

  // Stops the high signal 
  digitalWrite(TRIGGER_PIN, LOW);
  
  pinMode(ECHO_PIN, INPUT); // set the signal pin to input again to listen for incoming echo
  
  duration = pulseIn(ECHO_PIN, HIGH, 50000); // read the puls and store it
  
  return duration; // return the duration of the read puls
	
}



void setup()
{
  // Initialize serial communication
  Serial.begin(9600);
}

void loop()
{
  // declaring distance as float to allow for later on floating point calculations. otherwise we get inaccurate distance measures
  float distance; 
  
  // stores the puls duration from the sensor Singal pin
  long duration; 
  
  duration = read_ultrasonic_sensor(); // read the puls 
  
  distance = (duration * SPEED_OF_SOUND) / 2.0; // Calc distance in cm via speed of sound, duration and divede by 2 due to roundtrip

  // convert the distance to a C string and write to the Serial port
  Serial.print(distance);
  Serial.write("\n"); // sending a new line char - used for parsing in the receiving arduino


  delay(200); // short delay to avoid values being merged together when read on the other side
	
}










