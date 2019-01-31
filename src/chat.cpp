#include <Arduino.h>
#include "vars.h"
#include "chat.h"
#include "goalie.h"
#include "position.h"
#include "space_invaders.h"

int count = 0;

bool comunicazione (int intervallo) {                             //funzione di comunicazione
  if (BT.available() > 0) {
    comrade = true;
    old_timer = millis();
  }
  if ((millis() - old_timer ) > intervallo) {
    old_timer = millis();
    comrade = false;
  }
  return comrade ;
}

void teamZone() {
  calculateZoneIndex();
  iAmHere = zoneIndex;
  if (count < 30 ) {
    count++;
  }
  else {
    count = 0;
    BT.write(iAmHere);
  }
}

void whereAreYou() {
  calculateZoneIndex();
  if (BT.available() > 0) {
    friendZone = BT.read();
  }
  if (zoneIndex == friendZone) {
    if (ruolo == HIGH) goalie();
    else centroporta();
  }
}
