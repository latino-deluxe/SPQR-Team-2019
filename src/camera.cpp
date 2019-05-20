#include "camera.h"
#include "vars.h"

int startpY = 0; // inizio del dato
int startpB = 0;
int endpY = 0; // fine del dato
int endpB = 0;
String valStringY = ""; // stringa dove si vanno a mettere i pacchetti di dati ricevuti
String valStringB = "";
int datavalid = 0; // segnalo se il dato ricevuto è valido
int oldGoalY,oldGoalB;

void goalPosition() {
  int valY; // variabile a cui attribuisco momentaneamente il valore dell x
            // della porta

  int valB;

  portx = 999;
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
      datavalid ++;
    }
    if ((startpB == 1) && (endpB == 1)) {
      valB = valStringB.toInt(); // valid data
      valStringB = "";
      startpB = 0;
      endpB = 0;
      datavalid ++;
    }

  } // end of while

  if (valY != 0)
    oldGoalY = valY;
  if (valB != 0)
    oldGoalB = valB;

  if (valY == 0)
    valY = oldGoalY;
  if (valB == 0)
    valB = oldGoalB;

  if (datavalid > 1) {  ///entro qui solo se ho ricevuto i pacchetti completi sia del blu che del giallo
    if (role == HIGH) {
      if (pAtk == 1) { // leggi porta blu
        portx = valB;
      } else { // leggi porta gialla
        portx = valY;
      }
    } else {
      if (pDef == 1) { // leggi porta blu
        portx = valB;
      } else { // leggi porta gialla
        portx = valY;
      }

    }
    datavalid = 0;
    CameraReady = 1;  //attivo flag di ricezione pacchetto
  }
  // update_location_complete();
  // if (portx == 0)
  //   portx = 999;
}
// un numero grande equivale a stare a destra, piccolo a sinistra

//fix the camera value change caused by the robot twist
int imuOff, fst;
int fixCamIMU(){
    //fix for camera distortion when the robot twists
    if(imu_current_euler > 30 && imu_current_euler < 180) imuOff = 30;
    else if(imu_current_euler < 330 && imu_current_euler >= 180) imuOff = -30;
    else if (imu_current_euler <= 360 && imu_current_euler >= 330) imuOff = imu_current_euler - 360;
    else imuOff = imu_current_euler;

    fst = map(imuOff, -30, 30, -90, 90);
    return portx - fst;
}
