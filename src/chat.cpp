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

// sends via bt the value of the zoneIndex
void teamZone() { // DA METTERE IN OGNI LOOP
  // calculateZoneIndex();
  iAmHere = zoneIndex;
  if (count < 30) { // ogni 30 cicli invia il dato della zona al compagno
    count++;
  } else {
    count = 0;
    BT.write(iAmHere);
  }
}

// WHERE ARE YOU NOOOOWW
void whereAreYou() {
  // calculateZoneIndex();                               //forse va tolto ogni
  // volta il richiamo a zoneIndex?? //già, andava proprio tolto :P
  if (BT.available() > 0) {
    friendZone = BT.read();
  }
  // if (zoneIndex == friendZone) {                   //non mi convince
  //   if (role == HIGH)
  //     goalie();
  //   else
  //     centerGoalPost();
  // }

  /*-----NUOVA LOGICA DA SCRIVERE-----*/
  // Se robot si trova da solo deve switchare il ruolo a PortiereViolento,
  // funzione portiere completa con aggiunto di funzione di attacco menamoli (da
  // scrivere)
}
