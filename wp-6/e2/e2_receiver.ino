// Ibrahim Alzoubi, Marcus Berggren, Carl Vågfelt Nihlmar group: 4 (2025)
// Work package 6
// Excercise 2, 
// Submission code: 133204 (provided by your TA-s)

// Pin definitions
#define TRIGGER_PIN 7   // pin used to send the initial trigger to the ultrasonic sensor
#define ECHO_PIN 6      // pin receiving the incoming pulse
#define LED_PIN1 2      // Standard red LED pin
#define LED_PIN2 3      // Standard red LED pin
#define LED_PIN3 4      // Standard red LED pin
#define LED_PIN4 5      // Standard red LED pin

#define PIEZO_BUZZER_PIN 9 // Piezo buzzer output pin

// distance stamps
#define MAX_LED_DISTANCE 200    // Maximum distance in cm when the led is activated
#define MAX_BUZZER_DISTANCE 250 // max distance at which buzzer is activated - in cm 
#define MIN_DISTANCE 30      // Minimum distance in cm
#define SPEED_OF_SOUND 0.034 // Speed of sound in cm/microsecond


/*############################ FUNCTION DECLARATIONS ###############################*/
// sets up the ultrasonic sensor, reads the puls value and returns it 
long read_ultrasonic_sensor();

// causes all 4 leds to blink when the object is closer than 30cm 
void blink_all_leds();
/*############################ FUNCTION DEFINITIONS ###############################*/
long read_ultrasonic_sensor(){
  // variable declarations
  long duration = 0; // stores the value of the puls duration to be returned
    
  // Initialize ultrasonic sensor pins - setting the trigger pin as output
  pinMode(TRIGGER_PIN, OUTPUT);
  
  // Clear the trigger pin - ensuring there are to triggers from outside noise
  digitalWrite(TRIGGER_PIN, LOW);
  
  delayMicroseconds(5);// wait 5 microsec
  
  digitalWrite(TRIGGER_PIN, HIGH); // Sending high signal to trigger pin - basically telling the sesnor to send a puls out
  
  delayMicroseconds(10);           // Holds high signal for 10 microsec

  // Stops the high signal to the trigger pin - by setting the trigger to low again we are telling the sensor to stop and listen for the incoming puls the one reflected from objects
  digitalWrite(TRIGGER_PIN, LOW);
  
  pinMode(ECHO_PIN, INPUT); // set the echo pin to input to listen for incoming echo 
  
  duration = pulseIn(ECHO_PIN, HIGH, 50000); // read the puls and store it

  return duration; // return the duration of the read puls
	
}


void blink_all_leds(){
  
	// initialize all pins with LOW 
    digitalWrite(LED_PIN1, LOW);
    digitalWrite(LED_PIN2, LOW);
    digitalWrite(LED_PIN3, LOW);
    digitalWrite(LED_PIN4, LOW);
  
    delay(500); // adding a half a sec dely to simulate blinking 
  
  	// setting all pin to HIGH to blink them on 
    digitalWrite(LED_PIN1, HIGH);
    digitalWrite(LED_PIN2, HIGH);
    digitalWrite(LED_PIN3, HIGH);
    digitalWrite(LED_PIN4, HIGH);

}

void setup() {
  // Initialize serial communication
  //Serial.begin(9600);
  Serial.begin(9600);
  
  pinMode(LED_PIN1, OUTPUT); // setup the first led pin as output
  pinMode(LED_PIN2, OUTPUT); // setup the second led pin as output
  pinMode(LED_PIN3, OUTPUT); // setup the third led pin as output
  pinMode(LED_PIN4, OUTPUT); // setup the fourth led pin as output
  
  pinMode(PIEZO_BUZZER_PIN, OUTPUT);// setup the piezo buzzer pin as output

}

void loop() {

  float distance = 0.0; // declaring distance as float to allow for later on floating point calculations. otherwise we get inaccurate distance measures
  String received_distance; // stores the puls duration we get from the sensing arduino as a String value
  
  
  // the sent string has a new line char at the end - here we read until we reach it 
  received_distance = Serial.readStringUntil('\n'); 
  
  
	
  // convert the string distance we got from the other arduino into a float value to be used later
  distance =  received_distance.toFloat();
  

  
  // write LOW to all led pins at the beginning of each loop otherwise they will fail
  // to turn off when the measured distance increases
  digitalWrite(LED_PIN1, LOW);
  digitalWrite(LED_PIN2, LOW);
  digitalWrite(LED_PIN3, LOW);
  digitalWrite(LED_PIN4, LOW);
  
  // turn off the tone at the beginning of each loop, otherwise it will go on without stop
  noTone(PIEZO_BUZZER_PIN);
  // if the distance is less or equal to 250cm a low pitch tone is played 
  if(distance <= MAX_BUZZER_DISTANCE){
  	
   tone(PIEZO_BUZZER_PIN, 500); // sound the alarm with a low frequency tone 
    
  }
  
  // if the distance is less or equal to 200cm turn on the first led and increase tone frequency
  if(distance <= MAX_LED_DISTANCE){
  	
    digitalWrite(LED_PIN1, HIGH); // turn on the first led
    tone(PIEZO_BUZZER_PIN, 1000); // increase tone from 500 to 1000 
    
  }
  
  // if distance is 125 or less, turn on the second led and increase the tone frequency
  if(distance <= 125){
  	
    digitalWrite(LED_PIN2, HIGH); // turn on the second led 
    tone(PIEZO_BUZZER_PIN, 2000); // increase tone from 1000 to 2000 kHz
    
  }
  
  // if distance is 50cm or less, turn on the third led and increase tone frequency
  if(distance <= 50){
  	
    digitalWrite(LED_PIN3, HIGH); // turn on the third led 
    tone(PIEZO_BUZZER_PIN, 3000); // increase tone from 2000 to 3000 kHz
    
  }
  // if distance is 30cm or less, turn on the fourth led and increase tone frequency
  if(distance <= MIN_DISTANCE){
  	
    digitalWrite(LED_PIN4, HIGH); // turn on the fourth led 
    
    tone(PIEZO_BUZZER_PIN, 4000); // increase tone from 3000 to 4000 kHz
    
  }
  
  // if distance is 25cm or less, blink all leds 
  if(distance <= 25){
  	
  	blink_all_leds(); // initiate the blinking 
    
  }

  // Short delay before next reading
  delay(200);
}