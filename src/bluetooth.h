#include "libs.h"

// comrade variables
int ruolo = 0, a, count;
long timer, old_timer;
unsigned long tt = 0;                    // time between transmissions
bool comrade = false;                    // counts comrade as true if it gets something in datoArrivato
int datoArrivato;                        // for data reception
byte tent = 0;                           // tries counter

void initBluetooth() {                   // bluetooth initialization
  bluetooth.begin(115200);
  tt=millis();
}

bool communication(int intervallo) {     // communication function

  if (bluetooth.available() > 0) {
    a = bluetooth.read();
  }
  if (a == 42) {
    comrade = true;
    a = 0;
    old_timer = millis();
  }
  if ((millis() - old_timer ) > intervallo) {
    old_timer = millis();
    comrade = false;
  }
  return comrade;
}
