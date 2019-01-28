#include "vars.h"
#include "bluetooth.h"

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
