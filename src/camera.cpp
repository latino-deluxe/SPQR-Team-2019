#include "camera.h"
#include "vars.h"

int startpY = 0; // inizio del dato
int startpB = 0;
int endpY = 0; // fine del dato
int endpB = 0;
String valStringY = ""; // stringa dove si vanno a mettere i pacchetti di dati ricevuti
String valStringB = "";
int datavalid = 0; // segnalo se il dato ricevuto è valido
int oldGoal;

void goalPosition() {
  int valY; // variabile a cui attribuisco momentaneamente il valore dell x
            // della porta

  int valB;

  // portx = 999;
  while (CAMERA.available()) {
    // get the new byte:
    char inChar = (char)CAMERA.read();
    // DEBUG_PRINT.write(inChar);
    // if the incoming character is a 'Y', set the start packet flag
    if (inChar == 'Y') {
      startpY = 1;
    }
    // if the incoming character is a 'Y', set the start packet flag
    if (inChar == 'B') {
      startpB = 1;
    }
    // if the incoming character is a '.', set the end packet flag
    if (inChar == 'y') {
      endpY = 1;
    }
    // if the incoming character is a '.', set the end packet flag
    if (inChar == 'b') {
      endpB = 1;
    }

    if ((startpY == 1) && (endpY == 0)) {
      if (isDigit(inChar)) {
        // convert the incoming byte to a char and add it to the string:
        valStringY += inChar;
      }
    }

    if ((startpB == 1) && (endpB == 0)) {
      if (isDigit(inChar)) {
        // convert the incoming byte to a char and add it to the string:
        valStringB += inChar;
      }
    }

    if ((startpY == 1) && (endpY == 1)) {
      valY = valStringY.toInt(); // valid data
      valStringY = "";
      startpY = 0;
      endpY = 0;
      datavalid = 1;
    }
    if ((startpB == 1) && (endpB == 1)) {
      valB = valStringB.toInt(); // valid data
      valStringB = "";
      startpB = 0;
      endpB = 0;
      datavalid = 1;
    }

  } // end of while
  if (valY != 0)
    oldGoal = valY;
  if (valB != 0)
    oldGoal = valB;

  if (valY == 0)
    valY = oldGoal;
  if (valB == 0)
    valB = oldGoal;

  if (datavalid == 1) {
    if(goal_orentation) {      //attacco gialla, difendo blu
      pAtk = valY;
      pDef = valB;
    }
    datavalid = 0;
  }

  if (portx == 0)
    portx = 999;
}
