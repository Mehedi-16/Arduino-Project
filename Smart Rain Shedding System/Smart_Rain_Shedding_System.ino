#include <Servo.h>  // Servo library inclusion

const int rainSensorPin = A3;  // Rain sensor connected to A3
const int ledPin = 4;          // LED connected to pin 4
const int buzzerPin = 5;       // Buzzer connected to pin 5
const int servoPin = 6;        // Servo connected to pin 6
int ldrPin = A0;               // LDR connected to analog pin A0
int whiteLed = 2;              // LED for day/night indication
Servo myServo;                 // Create a servo object
bool rainDetected = false;     // To track rain state

void setup() {
  Serial.begin(9600);          // Enable serial monitor
  pinMode(ledPin, OUTPUT);     // Define LED pin
  pinMode(buzzerPin, OUTPUT);  // Define buzzer pin
  pinMode(whiteLed, OUTPUT);   // Define white LED pin
  myServo.attach(servoPin);    // Attach the servo to its pin
  myServo.write(0);            // Set initial position of the servo (0 degrees)
}

void loop() {
  int value = analogRead(rainSensorPin);  // Read value from rain sensor
  Serial.print("Rain Sensor Value : ");
  Serial.println(value);
  
  int ldrValue = analogRead(ldrPin);      // Read value from LDR
  Serial.print("LDR Value : ");
  Serial.println(ldrValue);

  // Day/Night LED control using LDR
  if (ldrValue > 200) {
    digitalWrite(whiteLed, LOW);  // Daytime - turn off LED
  } else {
    digitalWrite(whiteLed, HIGH); // Nighttime - turn on LED
  }

  // Rain detection
  if (value < 400) {                  // Change condition to < 400 for sound on light rain
    if (!rainDetected) {              // If rain was not previously detected
      digitalWrite(ledPin, HIGH);     // Turn on LED
      digitalWrite(buzzerPin, HIGH);  // Turn on buzzer
      myServo.write(180);             // Move servo to 180 degrees to move the cloth
      Serial.println("Rain detected! LED on, Buzzer on, Servo moved to 180 degrees");
      rainDetected = true;            // Set rain detected flag
    }
  } else {
    if (rainDetected) {               // If rain was previously detected
      digitalWrite(ledPin, LOW);      // Turn off LED
      digitalWrite(buzzerPin, LOW);   // Turn off buzzer
      myServo.write(0);               // Move servo back to 0 degrees
      Serial.println("Rain stopped! LED off, Buzzer off, Servo moved to 0 degrees");
      rainDetected = false;           // Reset rain detected flag
    }
  }

  delay(100);  // Small delay for stability
}
