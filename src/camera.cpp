#include "camera.h"
#include "vars.h"

 // inizio del dato
int startpY = 0;
int startpB = 0;
// fine del dato
int endpY = 0; 
int endpB = 0;
// stringa dove si vanno a mettere i pacchetti di dati ricevuti
String valStringY = ""; 
String valStringB = "";
// segnalo se il dato ricevuto è valido
int datavalid = 0; 
int oldGoalY,oldGoalB;
bool negateB = false;
bool negateY = false;
// variabile a cui attribuisco momentaneamente il valore dell x della porta
int valY;
int valB;

void goalPosition() {

  portx = 999;
  while (CAMERA.available()) {
    // get the new byte:
    char inChar = (char)CAMERA.read();
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
      }else if(inChar == '-'){
        negateY = true;
      }
    }

    if ((startpB == 1) && (endpB == 0)) {
      if (isDigit(inChar)) {
        // convert the incoming byte to a char and add it to the string:
        valStringB += inChar;
      }else if(inChar == '-'){
        negateB = true;
      }
    }

    if ((startpY == 1) && (endpY == 1)) {
      valY = valStringY.toInt(); // valid data
      if(negateY) valY *= -1;
      valStringY = "";
      startpY = 0;
      endpY = 0;
      negateY = false;
      datavalid ++;
    }
    if ((startpB == 1) && (endpB == 1)) {
      valB = valStringB.toInt(); // valid data
      if(negateB) valB *= -1;
      valStringB = "";
      startpB = 0;
      endpB = 0;
      negateB = false;
      datavalid ++;
    }

  } // end of while

  if (valY != -74)
    oldGoalY = valY;
  if (valB != -74)
    oldGoalB = valB;

  if (valY == -74)
    valY = oldGoalY;
  if (valB == -74)
    valB = oldGoalB;
  
  // entro qui solo se ho ricevuto i pacchetti completi sia del blu che del giallo
  if (datavalid > 1 ) {
    if(goal_orientation == 1){
      //yellow goalpost
      pAtk = valY;
      pDef = valB * -1;
    }else{
      //blue goalpost
      pAtk = valB;
      pDef = valY * -1;
    }

    datavalid = 0;
    cameraReady = 1;  //attivo flag di ricezione pacchetto
  }
}
// un numero grande equivale a stare a destra, piccolo a sinistra


//fix the camera value change caused by the robot twist. Every degree of twist corresponds to a degree of the port change, more or less
int imuOff;
int fixCamIMU(int d){
    if(imu_current_euler > 0 && imu_current_euler < 180) imuOff = imu_current_euler;
    else if (imu_current_euler <= 360 && imu_current_euler >= 180) imuOff = imu_current_euler - 360;
    imuOff = constrain(imuOff*0.8, -30, 30);

    return d + imuOff;
}
