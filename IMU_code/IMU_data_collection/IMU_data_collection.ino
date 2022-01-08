// Basic demo for accelerometer readings from Adafruit ICM20948

#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_ICM20948 icm;
uint16_t measurement_delay_us = 65535; // Delay between measurements for testing
// For SPI mode, we need a CS pin
#define ICM_CS 10
// For software-SPI mode we need SCK/MOSI/MISO pins
#define ICM_SCK 13
#define ICM_MISO 12
#define ICM_MOSI 11

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(1000); // will pause Zero, Leonardo, etc until serial console opens

  // Try to initialize!
  if (!icm.begin_I2C()) {
    // if (!icm.begin_SPI(ICM_CS)) {
    // if (!icm.begin_SPI(ICM_CS, ICM_SCK, ICM_MISO, ICM_MOSI)) {

    Serial.println("Failed to find ICM20948 chip");
    while (1) {
      delay(100);
    }
  }

  // icm.setAccelRange(ICM20948_ACCEL_RANGE_16_G);

  // icm.setGyroRange(ICM20948_GYRO_RANGE_2000_DPS);
  
  //  icm.setAccelRateDivisor(4095);
  uint16_t accel_divisor = icm.getAccelRateDivisor();
  float accel_rate = 1125 / (1.0 + accel_divisor);
  
  //  icm.setGyroRateDivisor(255);
  uint8_t gyro_divisor = icm.getGyroRateDivisor();
  float gyro_rate = 1100 / (1.0 + gyro_divisor);
  
  // icm.setMagDataRate(AK09916_MAG_DATARATE_10_HZ);
}


String dataLabel0 = "TEMPERATURE";
String dataLabel1 = "ACCELEROMETER_X";
String dataLabel2 = "ACCELEROMETER_Y";
String dataLabel3 = "ACCELEROMETER_Z";
String dataLabel4 = "GYROSCOPE_X";
String dataLabel5 = "GYROSCOPE_Y";
String dataLabel6 = "GYROSCOPE_Z";
String dataLabel7 = "MAGNETOMETER_X";
String dataLabel8 = "MAGNETOMETER_Y";
String dataLabel9 = "MAGNETOMETER_Z";
bool printHeaders = true;
int dataPoints = 0;

void loop() {

  if (dataPoints < 10) {
    //  /* Get a new normalized sensor event */
    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t mag;
    sensors_event_t temp;
    icm.getEvent(&accel, &gyro, &temp, &mag);
  
    //print out column headers
    while(printHeaders){ //runs once
      Serial.print(dataLabel0);
      Serial.print(",");
      Serial.print(dataLabel1);
      Serial.print(",");
      Serial.print(dataLabel2);
      Serial.print(",");
      Serial.print(dataLabel3);
      Serial.print(",");
      Serial.print(dataLabel4);
      Serial.print(",");
      Serial.print(dataLabel5);
      Serial.print(",");
      Serial.print(dataLabel6);
      Serial.print(",");
      Serial.print(dataLabel7);
      Serial.print(",");
      Serial.print(dataLabel8);
      Serial.print(",");
      Serial.println(dataLabel9);
      printHeaders=false;
      delay(10);
    }
    
    Serial.print(temp.temperature);
    
    Serial.print(",");
    
    Serial.print(accel.acceleration.x);
    Serial.print(","); Serial.print(accel.acceleration.y);
    Serial.print(","); Serial.print(accel.acceleration.z);
    
    Serial.print(",");
    Serial.print(gyro.gyro.x);
    Serial.print(","); Serial.print(gyro.gyro.y);
    Serial.print(","); Serial.print(gyro.gyro.z);
    
    Serial.print(",");
    Serial.print(mag.magnetic.x);
    Serial.print(","); Serial.print(mag.magnetic.y);
    Serial.print(","); Serial.print(mag.magnetic.z);
  
    Serial.println();
    
//    delayMicroseconds(measurement_delay_us);
  
    delay(1000);
    dataPoints =  dataPoints + 1;
  }
}
