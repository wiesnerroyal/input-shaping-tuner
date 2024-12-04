#include <AccelStepper.h>

#define STP_PIN 4    // Step pin for controlling the motor
#define DIR_PIN 3    // Direction pin to set the motor's rotation direction
#define ENA_PIN 2    // Optional enable pin to activate the motor

AccelStepper stepper(AccelStepper::DRIVER, STP_PIN, DIR_PIN);  // Create an AccelStepper object

String inString = "";  // String to hold the input frequency

void setup() {
  Serial.begin(115200);          // Start serial communication at 9600 baud rate
  while (!Serial) {
    ;  // Wait for serial port to connect (needed for native USB port only)
  }

  pinMode(ENA_PIN, OUTPUT);    // Set ENA_PIN as an output (optional)
  digitalWrite(ENA_PIN, LOW);  // Enable the motor (LOW activates the motor)

  // Set the stepper motor max speed (you can adjust this value)
  stepper.setMaxSpeed(10000);    // Max speed in steps per second
  stepper.setAcceleration(500);  // Acceleration value (steps per second squared)
  
  Serial.println("\nEnter a frequency (Hz) for motor control");
}

void loop() {
  // Read serial input:
  while (Serial.available() > 0) {
    int inChar = Serial.read();  // Read a byte from the serial input

    if (isDigit(inChar) || inChar == '.' || inChar == '-') {  // Check if it's a digit or decimal
      // Convert the incoming byte to a character and add it to the string:
      inString += (char)inChar;
    }

    // If we receive a newline, process the frequency value:
    if (inChar == '\n') {
      // Try to parse the frequency as a float
      float frequency = inString.toFloat();

      if (frequency > 0) {
        stepper.setSpeed(frequency);
      } else {
        stepper.setSpeed(0);
      }

      Serial.print("Frequency set to: ");
      Serial.println(frequency);

      // Clear the string for new input:
      inString = "";
    }
  }

  // Update the stepper to move it at the set speed
  stepper.runSpeed();  // Run the motor at the set speed continuously
}
