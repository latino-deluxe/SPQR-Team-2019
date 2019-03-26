#include "bluetooth.h"
#include "vars.h"

// init bluetooth on Serial1, look in vars.h for define
void initBluetooth() {
  BT.begin(9600);
  /*BT.print("$"); // Print three times individually
  BT.print("$");
  BT.print("$"); // Enter command mode
  delay(550);    // Short delay, wait for the Mate to send back CMD
  // sets up a bunch of things for bluetooth to work correctly
  BT.println("SM,6");
  BT.println("SA,0");
  BT.println("C");*/ // Temporarily Change the baudrate to 9600, no parity
}

// prints the serial read to bluetooth and bluetooth to serial monitor
void testBluetooth() {
  if (BT.available()) {
    Serial.println((char)BT.read());
  }
  if (Serial.available()) {
    BT.write((char)Serial.read());
  }
}

// Code to fix when we'll have two robots
/*
void btZone () {
  update_sensors_all();
  WhereAmI();
  guessZone();

  if(millis() - ao >= 100){
    Serial.println("------");
    for(int i = 0; i < 4; i++){
      Serial.print("US: ");
      Serial.print(us_values[i]);
      Serial.print(" | ");
    }
    Serial.println();
    testPosition();
    testGuessZone();

    Serial.println("------");
    ao = millis();
  }
}*/
