/*
  CO2LIGHT.h - Library for initializing and reading data from an Adafruit TSL2561 light sensor for our CO2 prototype
  Created by Tyler Valdez, 4 June 2018.
  Last updated 4 June 2018.
  Released into the public domain.
*/

#ifndef CO2LIGHT_h
#define CO2LIGHT_h

#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_TSL2561_U.h"

class CO2LIGHT
{
  public:
    CO2LIGHT();
    int init(int sensgain, int senstime);
    int read();
    int light;
  private:
};

#endif
