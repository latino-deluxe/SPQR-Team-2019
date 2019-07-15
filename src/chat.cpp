#include "chat.h"
#include "bluetooth.h"
#include "goalie.h"
#include "position.h"
#include "vars.h"
#include <Arduino.h>

int count = 0;
elapsedMillis btd;

bool com(int delay) {
  int d; // funzione di comunicazione
  if (BT.available() > 0) {
    d = BT.read();
  }
  if (d == 42) {
    comrade = true;
    d = 0;
    old_timer = millis();
    btd = 0;
  }
  if ((millis() - old_timer) > delay) {
    old_timer = millis();
    comrade = false;
  }
  if (comrade) {
    digitalWrite(R, HIGH);
  } else {
    digitalWrite(R, LOW);
  }

  // if (btd > 5000) {
  //   digitalWrite(G, HIGH);
  //   BT.print("$");
  //   BT.print("$");
  //   BT.print("$");
  // } 
  // if (btd > 5500) BT.println("K, 1");
  // if(btd > 5610) {
  //   BT.print("$");
  //   BT.print("$");
  //   BT.print("$");
  //   // btd = 0;
  // }
  // if(btd > 5400) BT.print("C");
  return comrade;
}

elapsedMillis ao2 = 0;

void Ao() {
  // if(ao2 >= 200){
  //   BT.write((byte) zoneIndex);
  //   ao2 = 0;
  // }
  if (topolino < 250) {
    topolino++;
  } else {
    topolino = 0;
    BT.write(42);
  }

}

void eoooo() {
  int nb;
  if(ao2 >= 200){
    if(ball_distance > 190) nb = 2;
    else nb = 1;
    BT.write(nb);
    ao2 = 0;
  }
}

bool tempGoalie(int delay) {
  int z;
  while(BT.available() > 0) {
    z = int(BT.read());
    old_timer = millis();

    comrade = false;
    if(z > 0) comrade = true;
  }
  if((millis() - old_timer) > delay) {
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
  if(z == 2) {
    return true;
  }
  else return false;
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

