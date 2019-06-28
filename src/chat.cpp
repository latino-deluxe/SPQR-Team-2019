#include "chat.h"
#include "goalie.h"
#include "position.h"
#include "space_invaders.h"
#include "vars.h"
#include <Arduino.h>

int count = 0;

bool com(int delay) {
  int d; // funzione di comunicazione
  if (BT.available() > 0) {
    d = BT.read();
  }
  if (d == 42) {
    comrade = true;
    d = 0;
    old_timer = millis();
  }
  if ((millis() - old_timer) > delay) {
    old_timer = millis();
    comrade = false;
  }
  if (comrade) {
    digitalWrite(Y, HIGH);
    digitalWrite(R, LOW);
  } else {
    digitalWrite(R, HIGH);
    digitalWrite(Y, LOW);
  }
  return comrade;
}

elapsedMillis ao2 = 0;

void Ao() {
  if(ao2 >= 200){
    BT.write((byte) zoneIndex);
    ao2 = 0;
  }
  /*if (topolino < 250) {
    topolino++;
  } else {
    topolino = 0;
    BT.write((byte) zoneIndex);
    //BT.write(42);
  }*/

}

void friendo(int delay) {
  int z;
  while(BT.available() > 0){   
    z = (int) (BT.read());
    old_timer = millis();

    comrade = false;
    if(z >= 0 && z <= 8){
      comrade = true;
      friendZone = z;
    } 
    
  }
  if ((millis() - old_timer) > delay) {
    old_timer = millis();
    comrade = false;
  }
  if (comrade) {
    digitalWrite(Y, HIGH);
    digitalWrite(R, LOW);
  } else {
    digitalWrite(R, HIGH);
    digitalWrite(Y, LOW);
  }
}

