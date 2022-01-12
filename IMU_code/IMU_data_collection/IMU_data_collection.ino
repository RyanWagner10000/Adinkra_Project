// Date and time functions using a PCF8523 RTC connected via I2C and Wire lib

#include "RTClib.h"
#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_ICM20948 icm;
RTC_PCF8523 rtc;

const int buttonPin = 12;
const int exitButtonPin = 14;
const long interval = 1000; //ms
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int buttonState = 0;
int exitState = 0;
int buttonPressed = 0;

void setup(void) {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(exitButtonPin, INPUT);
  
  Serial.begin(57600);
  while (!Serial)
    delay(100); // will pause Zero, Leonardo, etc until serial console opens

  // Try to initialize!
  if (!icm.begin_I2C()) {
    Serial.println("Failed to find ICM20948 chip");
    while (1) delay(100);
  }
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(100);
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
//----------------------------------------------------------------------------------------------------------------------------
  if (! rtc.initialized() || rtc.lostPower()) {
    // RTC is NOT initialized, let's set the time!

    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(year, month, day, hour, min, sec));
  }

  // Let's do this to ensure the RTC is running.
  rtc.start();

  // The PCF8523 can be calibrated for:
  //        - Aging adjustment
  //        - Temperature compensation
  //        - Accuracy tuning
  // The offset mode to use, once every two hours or once every minute.
  // The offset Offset value from -64 to +63. See the Application Note for calculation of offset values.
  // https://www.nxp.com/docs/en/application-note/AN11247.pdf
  // The deviation in parts per million can be calculated over a period of observation. Both the drift (which can be negative)
  // and the observation period must be in seconds. For accuracy the variation should be observed over about 1 week.
  // Note: any previous calibration should cancelled prior to any new observation period.
  // Example - RTC gaining 43 seconds in 1 week
  float drift = 43; // seconds plus or minus over oservation period - set to 0 to cancel previous calibration.
  float period_sec = (7 * 86400);  // total obsevation period in seconds (86400 = seconds in 1 day:  7 days = (7 * 86400) seconds )
  float deviation_ppm = (drift / period_sec * 1000000); //  deviation in parts per million (μs)
  float drift_unit = 4.34; // use with offset mode PCF8523_TwoHours
  // float drift_unit = 4.069; //For corrections every min the drift_unit is 4.069 ppm (use with offset mode PCF8523_OneMinute)
  int offset = round(deviation_ppm / drift_unit);
  // rtc.calibrate(PCF8523_TwoHours, offset); // Un-comment to perform calibration once drift (seconds) and observation period (seconds) are correct
  // rtc.calibrate(PCF8523_TwoHours, 0); // Un-comment to cancel previous calibration

  // Serial.print("Offset is "); Serial.println(offset); // Print to control offset
//----------------------------------------------------------------------------------------------------------------------------
}
String timeLabel0 = "Year";
String timeLabel1 = "Month";
String timeLabel2 = "Day";
String timeLabel3 = "Day of Week";
String timeLabel4 = "Hour";
String timeLabel5 = "Minute";
String timeLabel6 = "Second";
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

unsigned long currentMillis;
unsigned long nextMillis;
int dataStop = 0;

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  exitState = digitalRead(exitButtonPin);

  if (buttonState == HIGH) {
    buttonPressed = 1;
    buttonState = LOW;
    dataStop = 0;
    delay(250);
  } else if (exitState == HIGH) {
//    Serial.end();
    delay(250);
    while(1){};
  }
  
  while(buttonPressed == 1) {// button pressed
    currentMillis = millis();
    nextMillis = currentMillis + interval;
    while(currentMillis < nextMillis) {
      buttonState = digitalRead(buttonPin);
      exitState = digitalRead(exitButtonPin);

      if (buttonState == HIGH) {
        buttonPressed = 0;
        buttonState = LOW;
        dataStop = 1;
        delay(250);
        break;
      } else if (exitState == HIGH) {
//        Serial.end();
        delay(250);
        while(1){};
      }
      currentMillis = millis();
    }
    if (dataStop != 1) {
      //  /* Get a new normalized sensor event */
      sensors_event_t accel;
      sensors_event_t gyro;
      sensors_event_t mag;
      sensors_event_t temp;
      icm.getEvent(&accel, &gyro, &temp, &mag);
    
      //print out column headers
      while(printHeaders){ //runs once
        Serial.print(timeLabel0);
        Serial.print(",");
        Serial.print(timeLabel1);
        Serial.print(",");
        Serial.print(timeLabel2);
        Serial.print(",");
        Serial.print(timeLabel3);
        Serial.print(",");
        Serial.print(timeLabel4);
        Serial.print(",");
        Serial.print(timeLabel5);
        Serial.print(",");
        Serial.print(timeLabel6);
        Serial.print(",");
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
        delay(1);
      }
  
//      currentMillis = millis();
//      Serial.print(currentMillis);
      DateTime now = rtc.now();
  
      Serial.print(now.year(), DEC);
      Serial.print(","); Serial.print(now.month(), DEC);
      Serial.print(","); Serial.print(now.day(), DEC);
      Serial.print(","); Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
      Serial.print(","); Serial.print(now.hour(), DEC);
      Serial.print(","); Serial.print(now.minute(), DEC);
      Serial.print(","); Serial.print(now.second(), DEC);
      
      
      Serial.print(","); Serial.print(temp.temperature);
      
      Serial.print(","); Serial.print(accel.acceleration.x);
      Serial.print(","); Serial.print(accel.acceleration.y);
      Serial.print(","); Serial.print(accel.acceleration.z);
      
      Serial.print(","); Serial.print(gyro.gyro.x);
      Serial.print(","); Serial.print(gyro.gyro.y);
      Serial.print(","); Serial.print(gyro.gyro.z);
      
      Serial.print(","); Serial.print(mag.magnetic.x);
      Serial.print(","); Serial.print(mag.magnetic.y);
      Serial.print(","); Serial.print(mag.magnetic.z);
    
      Serial.println();
    }
  }
}
