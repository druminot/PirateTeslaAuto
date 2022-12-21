// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);

 if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }



  Serial.println("");
  delay(100);
}

void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  LoRa.beginPacket();
  /* Print out the values */
 LoRa.print("Acceleration X: ");
//LoRa.print(a.acceleration.x);
  LoRa.print(", Y: ");
// LoRa.print(a.acceleration.y);
 LoRa.print(", Z: ");
 //LoRa.print(a.acceleration.z);
  LoRa.endPacket();

  Serial.println(" ");
  delay(5000);
}
