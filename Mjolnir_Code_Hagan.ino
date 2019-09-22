/* 
 FPS_Enroll.ino - Library example for controlling the GT-511C3 Finger Print Scanner (FPS)
 Created by Josh Hawley, July 23rd 2013
 Licensed for non-commercial use, must include this license message
 basically, Feel free to hack away at it, but just give me credit for my work =)
 TLDR; Wil Wheaton's Law
 Also created with inspiration from Allen Pan's Mjolnir Sketch 
 */

#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"

//FPS_GT511C3 fps(9, 11);
FPS_GT511C3 fps(10,11);

//Hardware setup - FPS connected to:
//digital pin 10(arduino rx, fps tx)
//digital pin 11(arduino tx - 560ohm resistor fps tx - 1000ohm resistor - ground)
//this brings the 5v tx line down to about 3.2v so we dont fry our fps

//Capacitive sensor attached to pin 4, relay to pin 7
const int touchPin = 4;
const int relayPin = 7;

//has the hammer been touched
int sense;

//timer to keep track of how long ago the hammer was touched
long timer = 0;

//time that the relay goes off when a fingerprint match is detected
int relayPause = 10000;

void setup() {
  //enable to serial monitor and start the fingerprint scanner
  Serial.begin(9600);
  delay(100);
  //fps.UseSerialDebug = true;
  
  //if the fingerprint scanner is not plugged in, it will stall here.
  fps.Open();
  fps.SetLED(true); 
  pinMode(touchPin, INPUT);
  pinMode(relayPin, OUTPUT);
  sense = 0;
}

void loop() {
  //check if the hammer is touched
  fps.SetLED(true);
  sense = digitalRead(touchPin);
  //Serial.println("why u no print?");

  //if the hammer notices a finger print, keep the relay off long enough to lift from the ground)
  if (millis() - timer < relayPause){
    digitalWrite(relayPin, LOW);
  }


  //turn the fingerprint LED back on once the time has passed
  if (millis() - timer > relayPause){
    fps.SetLED(true);
  }

  //if the hammer is sensed
  if (sense){
    //and there is a pressed finger 
    /*if (fps.IsPressFinger()){
      fps.CaptureFinger(false);
      int id = fps.Identify1_N();
      //and the finger is recognized, set the timer
        if (id < 20){
          digitalWrite(relayPin, LOW);
          fps.SetLED(false);
          timer = millis();
        }
        //if the finger isn't recognized, set relay high
        else{*/
           digitalWrite(relayPin, HIGH);
           //Serial.println("relayed!");
        //}
      }
     //if touched but no fingerprint, set relay high
    else{
        digitalWrite(relayPin, LOW);
        //Serial.println("relay off!");
    }

  delay(200);
}
