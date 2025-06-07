#include <Wire.h>

#define MPU_ADDR 0x68  // MPU6050 I2C address

void setup() {
  Serial.begin(115200);
  Serial.println("Starting I2C communication with MPU6050...");
  
  Wire.begin(21, 22);  // SDA = 21, SCL = 22 for ESP32
  Serial.println("Wire.begin done ✅");

  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Serial.print("Sending to register 0x6B (Power Management)... ");
  Wire.write(0x6B);
  Wire.write(0);  // Wake up command
  uint8_t status = Wire.endTransmission();
  Serial.print("I2C Transmission status: "); Serial.println(status == 0 ? "Success ✅" : "Failed ❌");

  delay(100);
}

void loop() {
  Serial.println("Requesting sensor data...");
  
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // Start reading from register 0x3B
  Wire.endTransmission(false); // Restart for read
  
  Wire.requestFrom(MPU_ADDR, 14); // Read 14 bytes
  Serial.print("Bytes received: "); Serial.println(Wire.available());

  if (Wire.available() == 14) {
    uint8_t data[14];
    for (int i = 0; i < 14; i++) {
      data[i] = Wire.read();
      Serial.print("Byte["); Serial.print(i); Serial.print("] = ");
      Serial.println(data[i]);
    }

    // Now convert raw data to meaningful values
    int16_t ax = (data[0] << 8) | data[1];
    int16_t ay = (data[2] << 8) | data[3];
    int16_t az = (data[4] << 8) | data[5];
    // Skip temp = (data[6] << 8) | data[7];
    int16_t gx = (data[8] << 8) | data[9];
    int16_t gy = (data[10] << 8) | data[11];
    int16_t gz = (data[12] << 8) | data[13];

    Serial.println("✅ Sensor Values:");
    Serial.print("Accel X: "); Serial.println(ax);
    Serial.print("Accel Y: "); Serial.println(ay);
    Serial.print("Accel Z: "); Serial.println(az);
    Serial.print("Gyro X: "); Serial.println(gx);
    Serial.print("Gyro Y: "); Serial.println(gy);
    Serial.print("Gyro Z: "); Serial.println(gz);
  } else {
    Serial.println("❌ Error: Did not receive expected 14 bytes.");
  }

  Serial.println("------");
  delay(1000);  // Wait a second before next read
}
