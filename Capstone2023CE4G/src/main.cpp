#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
// #include <Adafruit_gfx.h>
#include <Adafruit_GPS.h>
#include <SPI.h>
#include <accelerometer.cpp>
#include <globalPosSystem.cpp>
#include <feeds.cpp>
#include <screen.cpp>

#define BUTTON_PIN1 1

#define BUTTON_PIN2 2

int wait_counter = 0;

struct GPS_Data
{
  int value;
  double lattitude;
  double longitude;
  double elevation;
};

void setup()
{

  Serial.begin(9600);

  // SERIAL
  while (!Serial)
    ;
  Serial.print("Connecting to Adafruit IO");
  pinMode(BUTTON_PIN1, INPUT);
  pinMode(BUTTON_PIN2, INPUT);
  accelerometer::accelerometerSetup();
  GPSS::callibrateGPS();
  feeds::callibrateIO();
  screen::init_screen();
  Serial.println("Everything good");
}

void loop()
{
  // Start Inputting things here.
  accelerometer::debugSeizure();
  screen::home();
  if (accelerometer::checkForSeizure())
  {
    screen::clear();
    screen::seizure_alert();
    while (!(wait_counter > 20) && !(digitalRead(BUTTON_PIN1) == HIGH && digitalRead(BUTTON_PIN2) == HIGH))
    {
      if (wait_counter > 18)
      {
        wait_counter = 0;
        GPSS::calculateLocation();
        GPSS::GPS_Data currentData = GPSS::seizureLocation();
        feeds::sendLocation(currentData.value, currentData.lattitude, currentData.longitude, currentData.elevation);
        feeds::seizureAlert();
        screen::clear();
        screen::detected();
        Serial.println("fuk");
        delay(2000);
      }
      if (digitalRead(BUTTON_PIN1) == HIGH && digitalRead(BUTTON_PIN2) == HIGH)
      {
        wait_counter = 0;
        feeds::seizureSafe();
        screen::clear();
        screen::cleared();
      }
      wait_counter++;
      delay(100);
    }
  }
  else
  {
    feeds::seizureSafe();
  }
  delay(100);
}