#include "chat.h"
#include "goalie.h"
#include "position.h"
#include "space_invaders.h"
#include "vars.h"
#include <Arduino.h>

int count = 0;

// comunicate with the comrade
bool comunicazione(int intervallo) {
  if (BT.available() > 0) {                           //se c'è qualcosa nella seriale metto a true il compagno
    comrade = true;                                   //da cambiare per sicurezza in modo che riconosca se è veramente il dato della zoneIndex
    old_timer = millis();
  }
  if ((millis() - old_timer) > intervallo) {          //controlla se la comunicazione va in timeout
    old_timer = millis();
    comrade = false;                                  //in caso imposta compagno a false
  }
  return comrade;                                     //returna la booleana
}

// sends via bt the value of the zoneIndex
void teamZone() {                                     //DA METTERE IN OGNI LOOP
  // calculateZoneIndex();
  iAmHere = zoneIndex;
  if (count < 30) {                                   //ogni 30 cicli invia il dato della zona al compagno
    count++;
  } else {
    count = 0;
    BT.write(iAmHere);
  }
}

//WHERE ARE YOU NOOOOWW
void whereAreYou() {
  calculateZoneIndex();                               //forse va tolto ogni volta il richiamo a zoneIndex??
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
  //Se robot si trova da solo deve switchare il ruolo a PortiereViolento, funzione portiere completa con aggiunto di funzione di attacco menamoli (da scrivere)
}
