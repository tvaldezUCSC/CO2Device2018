/*
  CO2LIGHT.h - Library for initializing and reading data from an Adafruit TSL2561 light sensor for our CO2 prototype
  Created by Tyler Valdez, 4 June 2018.
  Last updated 4 June 2018.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_TSL2561_U.h"
#include "CO2LIGHT.h"

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

CO2LIGHT::CO2LIGHT() {
}

int CO2LIGHT::init(int sensgain, int senstime) {

  Serial.begin(9600);
  Serial.print("Initializing Light Sensor..."); Serial.println("");

  /* Initialise the sensor */
  //use tsl.begin() to default to Wire,
  //tsl.begin(&Wire2) directs api to use Wire2, etc.
  if (!tsl.begin())
  {
    /* There was a problem detecting the TSL2561 ... check your connections */
    Serial.println("Failed!");
    return 1;
  } else {
    Serial.println("Done");
  }

  sensor_t sensor;
  tsl.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" lux");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" lux");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" lux");
  Serial.println("------------------------------------");
  /* Setup the sensor gain */
  if (sensgain == 0) {
    tsl.enableAutoRange(true);
    Serial.print  ("Gain:         "); Serial.println("Auto");
  } else if (sensgain == 1) {
    tsl.setGain(TSL2561_GAIN_1X);
    Serial.print  ("Gain:         "); Serial.println("1X");
  } else if (sensgain == 2) {
    tsl.setGain(TSL2561_GAIN_16X);
    Serial.print  ("Gain:         "); Serial.println("16X");
  }
  /* Setup the integration time */
  if (senstime == 0) {
    tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
    Serial.print  ("Timing:       "); Serial.println("13 ms");
  } else if (senstime == 1) {
    tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);
    Serial.print  ("Timing:       "); Serial.println("101 ms");
  } else if (senstime == 2) {
    tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);
    Serial.print  ("Timing:       "); Serial.println("402 ms");
  }
  Serial.println("------------------------------------");


  return 0;
}

int CO2LIGHT::read() {
  sensors_event_t event;
  tsl.getEvent(&event);
  light = event.light;
  Serial.print(event.light); Serial.println(" lux");
  return 0;
}
