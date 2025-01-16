

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Arduino.h>
#include <Wire.h>
#define BNO055_SAMPLERATE_DELAY_MS (10)

#define sda 6
#define scl 7


const int slaveAddress = 0;
// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
int curr , prev = 0;
float initialOrientationY = 0.0;
bool isOrientationYSet = false;

void setupIMU() {

  Wire.begin(sda , scl);

  // while (!Serial) delay(10);  // wait for serial port to open!
  // if (!bno.begin()) {
  //   while (1)
  //     ;
  // }

  bno.setExtCrystalUse(true);
}


float readIMU() {
  curr = millis();
    if (BNO055_SAMPLERATE_DELAY_MS < (curr - prev)) {
      prev = curr;
      sensors_event_t event;
      bno.getEvent(&event);

      // Set the initial orientation.y value the first time the function runs
      return event.orientation.x; 
      
    }

    // Adjust the orientation.x value
}
