/*
  CO2SD.h - Library for initializing and read/writing data to an SD card for our CO2 prototype.
  Created by Tyler Valdez, 7 May 2018.
  Last updated 4 June 2018.
  Released into the public domain.
*/
#include "Arduino.h"
#include "SD.h"
#include "SPI.h"
#include "CO2SD.h"

CO2SD::CO2SD() {
}

int CO2SD::init()
{

  Serial.begin(9600);
  while (!Serial) {
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("Initialization failed!");
    return 1;
  }

  Serial.println("Initialization done.");

  Serial.println("Creating log file...");
  for (_i = 1; SD.exists(_filename); _i++) {
    if (_i == 100) {
      Serial.print("100 data files in SD card. Please empty before collecting further data.");
      return 1;
    }
    _filename[4] = _i / 10 + '0';
    _filename[5] = _i % 10 + '0';
  }

  _datafile = SD.open(_filename, FILE_WRITE);

  _datafile.println("Time(s),CO2(PPM),Temperature(C),Humidity(%),Light Intensity(lux)");

  _datafile.close();

  Serial.println("Data file created:");
  Serial.println(_filename);
  return 0;
}

int CO2SD::write_data(int time, int co2, int temp, int humid, int light) {
  Serial.println("Logging data point...");

  if (! SD.exists(_filename)) {
    Serial.print("Error: data file ");
    Serial.print(_filename);
    Serial.println(" not found");
    return 1;
  }

  _datafile = SD.open(_filename, FILE_WRITE);

  _datafile.seek(_datafile.size());

  _datafile.print("\r");
  _datafile.print("\n");
  _datafile.print(time);
  _datafile.print(",");
  _datafile.print(co2);
  _datafile.print(",");
  _datafile.print(temp);
  _datafile.print(",");
  _datafile.print(humid);
  _datafile.print(",");
  _datafile.print(light);

  _datafile.close();

  Serial.println("Done");

  return 0;
}

