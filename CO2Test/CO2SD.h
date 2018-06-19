/*
  CO2SD.h - Library for initializing and read/writing data to an SD card for our CO2 prototype.
  Created by Tyler Valdez, 7 May 2018.
  Last updated 30 May 2018.
  Released into the public domain.
*/
#ifndef CO2SD_h
#define CO2SD_h

#include "Arduino.h"
#include "SD.h"
#include "SPI.h"

class CO2SD
{
  public:
    CO2SD();
    int init();
    int write_data(int time, int co2, int temp, int humid, int light);
  private:
    int _i;
    char _filename[11] = "data00.csv";
    File _datafile;
};

#endif
