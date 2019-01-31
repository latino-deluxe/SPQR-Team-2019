#include <Arduino.h>
#include "vars.h"
#include "chat.h"

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
