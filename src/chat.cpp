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

void Ao() {
  if (topolino < 100) {
    topolino++;
  } else {
    topolino = 0;
    BT.write(char(zoneIndex));
  }
}

void friendo(int delay) {
  int z;
  if(Serial3.available()){   
    z = (BT.read());
    old_timer = millis();
    if(z >= 0 && z <= 8) comrade = true;
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
  if(comrade) friendZone = z;
}

