/*
  CO2COZIR.h - Library for initializing and reading data from a COZIR sensor for our CO2 prototype.
  Created by Tyler Valdez, 17 May 2018.
  Last updated 30 May 2018.
  Released into the public domain.
*/
#ifndef CO2COZIR_h
#define CO2COZIR_h

#include "Arduino.h"
#include "SoftwareSerial.h"

class CO2COZIR
{
  public:
    CO2COZIR();
    int init(double multiplier, int filter, int filtersize);
    int read();
    int co2;
    int humid;
    int temp;
  private:
    double _mult;
    uint8_t _buff[50];
    uint8_t _ind = 0;
    uint8_t _idx = 0;
};

#endif
