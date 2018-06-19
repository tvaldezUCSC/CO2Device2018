/*
  CO2CHAMBER.h - Library for controlling the fans and valves of the chamber
  Created by Tyler Valdez, 30 May 2018.
  Last updated 30 May 2018.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Servo.h"
#include "CO2CHAMBER.h"

Servo myservo;

CO2CHAMBER::CO2CHAMBER() {
}

int CO2CHAMBER::init() {
  pinMode(fanpin, OUTPUT);
  pinMode(servopin, OUTPUT);
  pinMode(servodirect, OUTPUT);
  return 0;
  Serial.begin(9600);
}

int CO2CHAMBER::setfans(int fanstate) {
  if (fanstate == 1) {
    digitalWrite(fanpin, HIGH);
  } else if (fanstate == 0) {
    digitalWrite(fanpin, LOW);
  }

  return 0;
}

int CO2CHAMBER::chamberopen() {
  Serial.println("Chamber Opening");
  digitalWrite(servopin, HIGH);
  myservo.attach(servodirect);
  myservo.write(-2000);
  delay(5000);
  myservo.detach();
  digitalWrite(servopin, LOW);
  return 0;
}

int CO2CHAMBER::chamberclose() {
  Serial.println("Chamber Closing");
  digitalWrite(servopin, HIGH);
  myservo.attach(servodirect);
  myservo.write(2000);
  delay(5000);
  myservo.detach();
  digitalWrite(servopin, LOW);
  return 0;
}

