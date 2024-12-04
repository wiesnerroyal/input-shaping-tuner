#include <Wire.h>

#define MPU6050_ADDRESS       0x68 // I2C address of MPU6050
#define MPU6050_PWR_MGMT_1    0x6B // Register for power management
#define MPU6050_ACCEL_XOUT_H  0x3B // Register for acceleration data (X-axis high byte)
#define LED_PIN               13   // Pin for the status LED

unsigned long previousMillis = 0;       // Previous time for LED control
const unsigned long ledInterval = 30;   // LED blink interval in milliseconds
bool ledState = false;                  // Current state of the LED

void setup() {
  Serial.begin(2000000);          // Start serial communication
  Wire.begin();                   // Start I2C communication

  // Set I2C clock to 1 MHz (Fast Mode Plus)
  Wire.setClock(1000000);

  pinMode(LED_PIN, OUTPUT);      // Set the LED pin as output

  // Wake up MPU6050 from sleep mode
  writeRegister(MPU6050_PWR_MGMT_1, 0x00);
  Serial.println("MPU6050 initialized with LED status indicator");
}

void loop() {
  
  int16_t accel[3];

  // Read acceleration data
  readAcceleration(accel);

  // Display acceleration data
  Serial.print(accel[0]);
  Serial.print(",");
  Serial.print(accel[1]);
  Serial.print(",");
  Serial.println(accel[2]);

  // Update LED state without blocking
  updateLED();

}

void writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

void readAcceleration(int16_t *accel) {
  Wire.beginTransmission(MPU6050_ADDRESS);
  Wire.write(MPU6050_ACCEL_XOUT_H);
  Wire.endTransmission(false); // Repeated start
  Wire.requestFrom((uint8_t)MPU6050_ADDRESS, (uint8_t)6, (bool)true); // Read 6 bytes for acceleration

  // Parse acceleration data for X, Y, Z
  accel[0] = (Wire.read() << 8) | Wire.read();
  accel[1] = (Wire.read() << 8) | Wire.read();
  accel[2] = (Wire.read() << 8) | Wire.read();
}

void updateLED() {
  unsigned long currentMillis = millis();

  // Toggle LED state at the specified interval
  if (currentMillis - previousMillis >= ledInterval) {
    previousMillis = currentMillis;
    ledState = !ledState; // Flip LED state
    digitalWrite(LED_PIN, ledState); // Update LED
  }
}
