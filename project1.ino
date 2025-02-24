#include <Servo.h>

#define trigPin A1   // Ultrasonic Sensor Trigger Pin
#define echoPin A0   // Ultrasonic Sensor Echo Pin
#define servoPin 4   // Servo Motor Signal Pin

Servo myServo;  // Create Servo object
long duration;  // Variable to store pulse duration
int distance;   // Variable to store distance in cm

void setup() {
  pinMode(trigPin, OUTPUT); // Set trigPin as OUTPUT
  pinMode(echoPin, INPUT);  // Set echoPin as INPUT
  myServo.attach(servoPin); // Attach Servo to pin 9
  myServo.write(0);         // Keep the dustbin closed initially
  Serial.begin(9600);       // Start serial communication
}

void loop() {
  // Send a pulse to the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the time taken for the pulse to return
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  distance = duration * 0.0344 / 2;

  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If distance is less than 20 cm, open the dustbin lid
  if (distance < 20) {
    myServo.write(180);  // Rotate servo to 180° (Open Lid)
    delay(3000);        // Keep lid open for 3 seconds
    myServo.write(0);   // Close Lid (0°)
  }

  delay(100); // Small delay before the next measurement
}
