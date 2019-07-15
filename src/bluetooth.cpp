#include "bluetooth.h"
#include "vars.h"

// init bluetooth on Serial1, look in vars.h for define
void initBluetooth() {
  BT.begin(115200);
  connectBT();
}

void connectBT(){
  BT.print("$");  // Print three times individually
  BT.print("$");
  BT.print("$");
  delay(100);
  BT.println("C");
}

bool b = false;

void reconnectBT(){
  //tries to reconnect when he detects he has no comrade
  if(!comrade){
    if(!b){
      BT.print("$");  // Print three times individually
      BT.print("$");
      BT.print("$");
    }else{
      BT.println("C");
    }

    b = !b;
  }else{
    //otherwhise exits command mode
    BT.println("---");
  }
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
