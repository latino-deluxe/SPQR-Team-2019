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
    Serial.println(d);
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
  // if (comrade) {
  //   digitalWrite(Y, HIGH);
  //   digitalWrite(R, LOW);
  // } else {
  //   digitalWrite(R, HIGH);
  //   digitalWrite(Y, LOW);
  // }
  return comrade;
}

bool commy(int delay) {
  if(millis() - count > 250){
    int d; // funzione di comunicazione
    if (BT.available() > 0) {
      d = BT.read();
      if(d != 0) fpos = d;
    }
    if ((fpos >= 1) && (fpos <= 9)) {
      comrade = true;
      fpos = fpos - 1;
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
    count = millis();
    return comrade;
  }
}

void Ao() {
  if (topolino < 100) {
    topolino++;
  } else {
    topolino = 0;
    BT.write(42);
  }
}

void WOW() {
  if (topolino < 100) {
    topolino++;
  } else {
    topolino = 0;
    BT.write(zoneIndex + 1);
  }
}
