/*
   State Machine for CO2 Project
   Created by Tyler Valdez 17 May 2018
   Last updated 4 June 2018

*/

#include "SD.h"
#include "SPI.h"
#include "SoftwareSerial.h"
#include "Servo.h"

#include "CO2COZIR.h"
#include "CO2CHAMBER.h"
#include "CO2LIGHT.h"
#include "CO2SD.h"


#include "Wire.h"
#include "Adafruit_Sensor.h"      // requires non-default Arduino library "Adafruit Unified Sensor" 
#include "Adafruit_TSL2561_U.h"   // requires non-default Arduino library "Adafruit TSL2561"

#define SETUP 0             // placeholder integers to define what the states are
#define WAITING_FOR_USER 1
#define TAKING_DATA 2
#define CYCLING_AIR 3
#define ERRORSTATE 5
#define BEGINCYCLING 6
#define ENDCYCLING 7
#define BEGINDATA 8

#define LIGHTGAIN 0        // Gain for the light sensor. 0 is auto (default), 1 is 1X, 2 is 16X
#define LIGHTTIME 0        // Timing for the light sensor. 0 is 13ms (default), 1 is 101ms, 2 is 402ms

#define MULTIPLIER 1  // 1 for 2% =20000 PPM, 10 for 20% = 200,000 PPM
#define FILTER 1      // 1: digitally filter CO2 readings (recommended), 0: unfiltered
#define FILTERSIZE 32 // set size of digital filter (recommended 32)

#define INTERVAL 500 // time interval between readings, in milliseconds (minimum 500)
#define RUNTIME 300   // single-test runtime, in seconds
#define OPENTIME 1500  // time spent cycling air

CO2SD co2sd;
CO2COZIR co2cozir;
CO2CHAMBER co2chamber;
CO2LIGHT co2light;

int STATE = SETUP;   // state defaults to setup

int LED = 13;        // this is our LED pin

unsigned long starttime;  // these are for the timer logic
unsigned long nowtime;
unsigned long timer1;
unsigned long timer2;

int err = 0;                  // this pops if we get an error

void setup() {
  Serial.begin(9600);
  co2chamber.fanpin = 3;        // This pin turns the fans on
  co2chamber.servopin = 4;      // This pin enables power to the motors
  co2chamber.servodirect = 12;  // This pin gives the motors a direction

  pinMode(LED, OUTPUT);          // output pin for our LED

  err += co2cozir.init(MULTIPLIER, FILTER, FILTERSIZE);     // initialize COZIR (filter size, etc)
  err = 0;
  if (err) {
    STATE = ERRORSTATE;                // errors go to errorstate
  }
}

void loop() {
  switch (STATE) {
    case SETUP:
      err += co2sd.init();               // initialize SD card (new file, etc)
      err += co2light.init(LIGHTGAIN, LIGHTTIME);
      STATE = BEGINCYCLING;
      break;
      if (err) {
        STATE = ERRORSTATE;                // errors go to errorstate
      } else {
        STATE = WAITING_FOR_USER;          // if successful, wait for the user
      }
      break;
    case WAITING_FOR_USER:
      Serial.println("State:WaitingforUser");
      if (err) {
        STATE = ERRORSTATE;                // errors go to errorstate
      } else {
        starttime = millis();                         // get current time
        STATE = BEGINCYCLING;                          // move to next state
      }
      break;
    case BEGINDATA:
      nowtime = millis();
      Serial.println("State:BeginData");
      timer1 = nowtime + ( RUNTIME * 1000 );      // this tells us when to stop getting data
      timer2 = nowtime + ( INTERVAL );            // this tells us when to take another point
      STATE = TAKING_DATA;
      break;
    case TAKING_DATA:
      nowtime = millis();                // get time
      if ( nowtime >= timer2) {          // take a data point if it's time to
        co2cozir.read();
        co2light.read();
        co2sd.write_data(nowtime - starttime, co2cozir.co2, co2cozir.humid, co2cozir.temp, co2light.light);
        timer2 = nowtime + INTERVAL;              // new interval for a new data point
      }
      if (err) {
        STATE = ERRORSTATE;              // errors go to errorstate
      }
      if (nowtime >= timer1) {
        STATE = BEGINCYCLING;             // once timer1 pops, move to next state
      }
      break;
    case BEGINCYCLING:
      Serial.println("BeginCycling");
      co2chamber.chamberopen();
      co2chamber.setfans(1);
      nowtime = millis();
      timer1 = nowtime + ( OPENTIME * 1000 );
      STATE = CYCLING_AIR;
      break;
    case CYCLING_AIR:
      nowtime = millis();
      if (nowtime >= timer1) {
        STATE = ENDCYCLING;
      }
      break;
    case ENDCYCLING:
      Serial.println("EndCycling");
      co2chamber.chamberclose();
      co2chamber.setfans(0);
      STATE = BEGINDATA;
      break;
    case ERRORSTATE:
      Serial.println("State:ErrorState");
      while (1) {
        digitalWrite(LED, HIGH);        // blink the LED in errorstate
        delay(1000);
        digitalWrite(LED, LOW);
        delay(1000);
      }
      break;
    default:
      STATE = SETUP;
      break;
  }
}
