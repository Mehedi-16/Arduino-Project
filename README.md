# Smart Rain Shedding System

## Project Overview
The Smart Rain Shedding System automatically detects rainfall and deploys a cover to protect items from getting wet. This system utilizes various sensors, including a rain sensor and a light-dependent resistor (LDR), to monitor weather conditions and can provide visual and audio alerts.

## Features
- **Automatic Rain Detection**: Automatically closes the cover when rain is detected.
- **Day/Night Indication**: An LED indicator lights up at night.
- **Audio Alerts**: A buzzer sounds when rain is detected.
- **Manual Override**: Option to manually control the servo motor for opening or closing the cover.

## Components Required
- Arduino (e.g., Arduino Uno)
- Rain Sensor
- Servo Motor
- Light Dependent Resistor (LDR)
- LED (for night indication)
- Buzzer
- Resistors (for LDR)
- Jumper Wires
- Breadboard (optional)
- Power Supply (battery or adapter)

## Circuit Diagram
![Rain-Detection-using-Raindrop-Sensor-Module-Arduino-1](https://github.com/user-attachments/assets/348672a1-5ca8-4ac0-9386-387d4bcdcf7d)


## Code
```cpp
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
```

Installation
Clone the repository:
```bash
git clone https://github.com/Mehedi-16/SmartRainSheddingSystem.git
```
Open the .ino file in the Arduino IDE.

Upload the code to your Arduino board.

Set up the hardware according to the circuit diagram.

##Usage
Ensure all components are connected properly.

Power the system and observe the operation.

The system will automatically detect rain and deploy the cover.

##License
This project is licensed under the MIT License - see the LICENSE file for details.

##Acknowledgements
Arduino for the platform.
Instructables for inspiration and guidance.

