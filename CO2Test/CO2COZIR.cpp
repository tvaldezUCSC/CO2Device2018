/*
  CO2COZIR.h - Library for initializing and reading data from a COZIR sensor for our CO2 prototype.
  Created by Tyler Valdez, 17 May 2018.
  Last updated 17 May 2018.
  Released into the public domain.
*/
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "CO2COZIR.h"

#define mySerial Serial1

CO2COZIR::CO2COZIR() {
}

int CO2COZIR::init(double multiplier, int filter, int filtersize) {

  _ind = 0;
  _idx = 0;
  _mult = multiplier;

  Serial.begin(9600);
  Serial.println("Initializing COZIR sensor...");
  mySerial.begin(9600); // Start serial communications with sensor
  if (filter == 1) {
    mySerial.println("M 4164"); // send Mode for filtered co2, humid, and temp output
  } else if (filter == 0) {
    mySerial.println("M 4162"); // send Mode for unfiltered co2, humid, and temp
  }
  // "Z xxxxx z xxxxx" (CO2 filtered and unfiltered)

  mySerial.println("K 1");  // set streaming mode (0 for command mode, 2 for polling mode)

  mySerial.print("A ");       // Set filter size
  mySerial.print(filtersize);
  mySerial.print("\r\n");

  mySerial.println("Q\r\n");

  if (mySerial.available()) {
    Serial.println("Done");
    return 0;
  } else {
    Serial.println("Failed!");
    return 1;
  }
}

int CO2COZIR::read() {
  // Fill buff with sensor ascii data
  _ind = 0;
  while (_buff[_ind - 1] != 0x0A) { // Read sensor and fill buff up to 0XA = CR
    if (mySerial.available()) {
      _buff[_ind] = mySerial.read();
      _ind++;
    }
  }
  // buff() now filled with sensor ascii data
  // ind contains the number of characters loaded into buff up to 0xA =  CR
  _ind = _ind - 2;            // decrement buff to exactly match last numerical character

  co2 = _buff[23] - 0x30;
  co2 += (_buff[22] - 0x30) * 10; //subtract 48 to get decimal value
  co2 += (_buff[21] - 0x30) * 100;
  co2 += (_buff[20] - 0x30) * 1000;
  co2 += (_buff[19] - 0x30) * 10000;
  co2 = co2 * _mult;
  temp = _buff[15] - 0x30;
  temp += (_buff[14] - 0x30) * 10;
  temp += (_buff[13] - 0x30) * 100;
  temp += (_buff[12] - 0x30) * 1000;
  temp += (_buff[11] - 0x30) * 10000;
  temp = (temp - 1000) / 10;
  humid = _buff[7] - 0x30;
  humid += (_buff[6] - 0x30) * 10;
  humid += (_buff[5] - 0x30) * 100;
  humid += (_buff[4] - 0x30) * 1000;
  humid += (_buff[3] - 0x30) * 10000;
  humid = humid / 10;
  Serial.print("\n CO2 = ");
  Serial.print(co2);
  Serial.print("\n Temp = ");
  Serial.print(temp);
  Serial.print("\n Humidity = ");
  Serial.print(humid);
  Serial.print("\n");

  return 0;
}

