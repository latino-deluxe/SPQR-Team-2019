#include "linesensor.h"
#include "pid.h"
#include "motors.h"
#include "myspi_old.h"
#include "vars.h"
#include <Arduino.h>

// init line sensors and attaches interrput
// void initLineSensors() {
//   pinMode(S0, INPUT);
//   pinMode(S1, INPUT);
//   pinMode(S2, INPUT);
//   pinMode(S3, INPUT);
// }

void checkLineSensors() {
  LN0 = analogRead(S0);
  LN1 = analogRead(S1);
  LN2 = analogRead(S2);
  LN3 = analogRead(S3);
  if(LN0 > 500) U0 = true;
  else U0 = false;
  if(LN1 > 500) U1 = true;
  else U1 = false;
  if(LN2 > 500) U2 = true;
  else U2 = false;
  if(LN3 > 500) U3 = true;
  else U3 = false;

  // if((U0 + U1 + U2 + U3) > 0) outOfBounds();           //movimento di rientro con atan2
  // if((U0 + U1 + U2 + U3) > 0) playSafe();                 //annulla movimento asse dove sta uscendo
  // if((U0 == false) && (U1 == false) && (U2 == false) && (U3 == false)) {
  //   x=1;
  //   y=1;
  // }

}


void outOfBounds() {
  //  S0        180
  //  S1        270
  //  S2        0
  //  S3        90

  if(U0) {
    Ux0 = 0;
    Uy0 = -1;
  }
  if(U1) {
    Ux1 = -1;
    Uy1 = 0;
  }
  if(U2) {
    Ux2 = 0;
    Uy2 = 1;
  }
  if(U3) {
    Ux3 = 1;
    Uy3 = 0;
  }

  Ux = ((U0 * Ux0) + (U1 * Ux1) + (U2 * Ux2) + (U3 * Ux3));
  Uy = ((U0 * Uy0) + (U1 * Uy1) + (U2 * Uy2) + (U3 * Uy3));

  U = (-(atan2(Uy, Ux) * 180 / 3.14) + 90) - imu_current_euler;

  preparePID(U, 250);
}



void playSafe() {
  if(U1) {
    if(inSensorRange(5, 5)) {
      x=0;
      y=1;
    }
    else {
      x=1;
      y=1;
    }
  }
  if(U3) {
    if(inSensorRange(14, 5)) {
      x=0;
      y=1;
    }
    else {
      x=1;
      y=1;
    }
  }
  if(U0) {
    if(inSensorRange(0, 5)) {
      x=1;
      y=0;
    }
    else {
      x=1;
      y=1;
    }
  }
  if(U2) {
    if(inSensorRange(10, 5)) {
      x=1;
      y=0;
    }
    else {
      x=1;
      y=1;
    }
  }
}