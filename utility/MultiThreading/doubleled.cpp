#include <Arduino.h>
#include "TeensyThreads.h"

#define LED 13                         //pin dei led (ma va?)
#define LED2 14

volatile int b1 = 0;                  //numero dei blink, volatile perché la modifichiamo fuori loop
volatile int b2 = 0;                  //altrimenti la wiki lo definisce come "buggy code"

int id1, id2;                         //numero ID dei thread
int co, cc;                           //inizializzo contatori

void blinkthread() {                  //funzione primo thread
  while(1) {                          //loop ;)
    if (b1) {                         //controllo
      for (int i=0; i<b1; i++) {      //for per blinkare
        digitalWrite(LED, HIGH);
        threads.delay(150);           //DELAY CHE NON ROMPE IL CAZZO
        digitalWrite(LED, LOW);
        threads.delay(150);
      }
      b1 = 0;                         //resetti per uscire
    }
    threads.yield();                  //devo ancora capire a che serve
  }
}

void blinkthread2() {                 //uguale
  while(1) {
    if (b2) {
      for (int i=0; i<b2; i++) {
        digitalWrite(LED2, HIGH);
        threads.delay(500);           //con un delay diverso ;)
        digitalWrite(LED2, LOW);
        threads.delay(500);
      }
      b2 = 0;
    }
    threads.yield();
  }
}

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  id1 = threads.addThread(blinkthread);       //assegno un id al thread per fare funzioni
  id2 = threads.addThread(blinkthread2);      //nel loop, es. sospensione, restart, kill, ecc
}



void loop() {
  co++;
  cc++;
  b1 = co;
  b2 = cc;
//sospendo per un secondo il thread del secondo led
  threads.suspend(id2);
  delay(500);
  threads.restart(id2);
  delay(500);
}
