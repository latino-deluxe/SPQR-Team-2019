#include "linesensor.h"
#include "pid.h"
#include "motors.h"
#include "vars.h"
#include <Arduino.h>

// init line sensors and attaches interrput
void initLineSensors() {
  pinMode(S0, INPUT);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
}

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

  if((U0 + U1 + U2 + U3) > 0) outOfBounds();
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
