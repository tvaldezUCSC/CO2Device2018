/*
  CO2CHAMBER.h - Library for controlling the fans and valves of the chamber
  Created by Tyler Valdez, 30 May 2018.
  Last updated 30 May 2018.
  Released into the public domain.
*/

#ifndef CO2CHAMBER_h
#define CO2CHAMBER_h

#include "Arduino.h"
#include "Servo.h"

class CO2CHAMBER
{
  public:
    CO2CHAMBER();
    int init();
    int fanpin;
    int servopin;
    int servodirect;
    int setfans(int fanstate);
    int chamberopen();
    int chamberclose();
  private:
};


#endif
