#include <NewPing.h>
#define TRIGGER_PIN_1   6  // Ultrasonic sensor trigger pin for Tank 1
#define ECHO_PIN_1      7  // Ultrasonic sensor echo pin for Tank 1
#define MAX_DISTANCE_1  200 // Maximum distance we want to measure for Tank 1 (in centimeters)
#define RELAY_PIN_1     3   // Relay module control pin for Pump 1

#define TRIGGER_PIN_2   8   // Ultrasonic sensor trigger pin for Tank 2
#define ECHO_PIN_2      9   // Ultrasonic sensor echo pin for Tank 2
#define MAX_DISTANCE_2  200 // Maximum distance we want to measure for Tank 2 (in centimeters)
#define RELAY_PIN_2     2  // Relay module control pin for Pump 2

#define TRIGGER_PIN_GND 12   // Ultrasonic sensor trigger pin for the Ground Tank
#define ECHO_PIN_GND    13   // Ultrasonic sensor echo pin for the Ground Tank
#define MAX_DISTANCE_GND 200 // Maximum distance we want to measure for the Ground Tank (in centimeters)
#define PUMP1_RELAY_PIN 3   // Relay module control pin for Pump 1
#define PUMP2_RELAY_PIN 2   // Relay module control pin for Pump 2

NewPing tank1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE_1); // Create a NewPing object for Tank 1
NewPing tank2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE_2); // Create a NewPing object for Tank 2
NewPing groundTank(TRIGGER_PIN_GND, ECHO_PIN_GND, MAX_DISTANCE_GND); // Create a NewPing object for the Ground Tank

void setup() {
  Serial.begin(9600); // Initialize serial communication

  pinMode(RELAY_PIN_1, OUTPUT); // Set the relay pin for Pump 1 as an output
  digitalWrite(RELAY_PIN_1, LOW); // Initialize Pump 1's relay as OFF

  pinMode(RELAY_PIN_2, OUTPUT); // Set the relay pin for Pump 2 as an output
  digitalWrite(RELAY_PIN_2, LOW); // Initialize Pump 2's relay as OFF

  pinMode(PUMP1_RELAY_PIN, OUTPUT); // Set the relay pin for Pump 1 as an output
  digitalWrite(PUMP1_RELAY_PIN, LOW); // Initialize Pump 1's relay as OFF

  pinMode(PUMP2_RELAY_PIN, OUTPUT); // Set the relay pin for Pump 2 as an output
  digitalWrite(PUMP2_RELAY_PIN, LOW); // Initialize Pump 2's relay as OFF
}

void loop() {
  delay(500); // Wait for a moment

  unsigned int distance1 = tank1.ping_cm(); // Send a ping and get the distance in centimeters for Tank 1
  unsigned int distance2 = tank2.ping_cm(); // Send a ping and get the distance in centimeters for Tank 2
  unsigned int groundDistance = groundTank.ping_cm(); // Send a ping and get the distance in centimeters for the Ground Tank

  if (distance1 == 0 || distance2 == 0 && groundDistance == 0) {
    Serial.println("Error: No object detected");
    digitalWrite(RELAY_PIN_1, HIGH);
    digitalWrite(RELAY_PIN_2, HIGH);
  } else {
    Serial.print("Tank 1 - Distance: ");
    Serial.print(distance1);
    Serial.println(" cm");

    Serial.print("Tank 2 - Distance: ");
    Serial.print(distance2);
    Serial.println(" cm");

    Serial.print("Ground Tank - Distance: ");
    Serial.print(groundDistance);
    Serial.println(" cm");
// Logic to control the pumps based on the Ground Tank level

    // Logic to control Pump 1 based on water level in Tank 1
    if (  groundDistance > 5 || distance1 <=3) {
      Serial.println("Water level in the Ground Tank is high!");
      Serial.println("Water level in Tank 1 is high!");
      digitalWrite(RELAY_PIN_1, HIGH); // Turn on Pump 1
    } else {
      Serial.println("Water level in Tank 1 is normal.");
      digitalWrite(RELAY_PIN_1, LOW); // Turn off Pump 1
    }

    // Logic to control Pump 2 based on water level in Tank 2
    if (groundDistance > 5 || distance2 <=3) {
      Serial.println("Water level in the Ground Tank is high!");
      Serial.println("Water level in Tank 2 is high!");
      digitalWrite(RELAY_PIN_2, HIGH); // Turn on Pump 2
    } else {
      Serial.println("Water level in Tank 2 is normal.");
      digitalWrite(RELAY_PIN_2, LOW); // Turn off Pump 2
    }

    
  }
}
