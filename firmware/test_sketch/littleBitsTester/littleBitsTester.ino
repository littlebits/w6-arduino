#include <Wire.h>

/*
littleBitsTester
12 MAY 2014

This program shows basic functionality of the w6-arduino bit.

Copyright 2014 littleBits Electronics

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License at <http://www.gnu.org/licenses/> for more details.
*/

int aVal = 0;
int output = 9;    // output module connected to digital pin 9
char fadeState = 1; // direction of the voltage movement on pin 9
int fadeValue = 0;
int blinkTimer = 0;
char blinkState = 0;

void setup()  {
  
  Serial.begin(9600); // This sets up communication to a serial monitor on your computer!
  
  pinMode(9, OUTPUT);  // make the pin an OUTPUT
  pinMode(5, OUTPUT);  // make the pin an OUTPUT
  pinMode(1, OUTPUT);  // make the pin an OUTPUT
  pinMode(A0, INPUT);  // make the pin an INPUT
  pinMode(A1, INPUT);  // make the pin an INPUT
  pinMode(0,INPUT);    // make the pin an INPUT

  Wire.begin(1);        // start i2c
  Serial.begin(9600);  // 9600bps


} 

void loop()  { 

  Wire.beginTransmission(2); // begin transmission to 0x10                          
                              
  Wire.write("GGG");    
  Wire.write("bbb");                                    
                               
  Wire.endTransmission();      // stop transmission

  aVal = analogRead(A1)/32; //Read the voltage at pin a1...
    
  // fade in from min to max in increments of 5 points:
  
  if (fadeState == 1) // increase voltage until 5
  {
    fadeValue += 5;
    if (fadeValue == 255) fadeState = 0;
  }
  else // decrease voltage until 0
  {
    fadeValue -= 5;
    if (fadeValue == 0) fadeState = 1;
  }
    analogWrite(output, fadeValue);         
    
    delay(35 - aVal); //Make the output ramp faster when aVal is higher.
    
    
    if (digitalRead(0)) //If the digital button is pressed.
    {
      blinkTimer += (35 - aVal); //Then blink on/off once per second
      if (blinkTimer > 500)
      {
          blinkTimer = 0;
          digitalWrite(1,blinkState);
          blinkState = (blinkState+1)%2;
      }   
    }
    else //If not don't blink on/off
    {
      digitalWrite(1,0);
    }

  aVal = analogRead(A0)/4; //Read the voltage at pin a0...
  analogWrite(5, aVal); //Now reproduce the voltage at pin d5
}


