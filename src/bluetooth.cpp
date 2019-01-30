#include "vars.h"
#include "bluetooth.h"

//Bluetooth on Serial1

void initBluetooth() {                                           //inizializza bluetooth
  BT.begin(115200);
  //tt=millis();
}

bool comunicazione (int intervallo) {                             //funzione di comunicazione

  if (BT.available() > 0) {
    a = BT.read();
  }
  if (a == 42) {
    compagno = true;
    a = 0;
    old_timer = millis();
  }
  if ((millis() - old_timer ) > intervallo) {
    old_timer = millis();
    compagno = false;
  }
  return compagno ;
}

void testBluetooth(){
  //prints the serial read to bluetooth and bluetooth to serial monitor
  if(BT.available()){
    Serial.println((char)BT.read());
  }
  if(Serial.available()){
    BT.write((char)Serial.read());
  }
}
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
