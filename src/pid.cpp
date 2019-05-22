#include "goalie.h"
#include "imu.h"
#include "motors.h"
#include "pid.h"
#include "vars.h"
#include <Arduino.h>

// TIMED PID CONTROL TESTING
void drivePID(signed int direzione, float vMot) {
  // mette in variabili globali direzione e velocitá precedenti e attuali
  new_Dir = direzione;
  
  // vx = vMot * sins[direzione];
  // vy = vMot * cosin[direzione];

  // speed1 = (-vx * cosin[45]) + (vy * cosin[45]);
  // speed2 = (vx * cosin[45]) + (vy * cosin[45]);
  // speed3 = (-speed1);
  // speed4 = (-speed2);

  vx = vMot * cosin[direzione + 12];
  vy = -vMot * sins[direzione + 12];

  speed1 = ((vx * sins[45] ) + (vy * cosin[45] ));
  speed2 = ((vx * sins[135]) + (vy * cosin[135]));
  speed3 = ((vx * sins[225]) + (vy * cosin[225]));
  speed4 = ((vx * sins[315]) + (vy * cosin[315]));

  pidfactor = updatePid();

  speed1 += pidfactor;
  speed2 += pidfactor;
  speed3 += pidfactor;
  speed4 += pidfactor;

  // CheckSpeed(); // normalizza la velocita' a 255 max al motore piu' veloce e
  // gli altri in proporzione

  speed1 = constrain(speed1, -255, 255);
  speed2 = constrain(speed2, -255, 255);
  speed3 = constrain(speed3, -255, 255);
  speed4 = constrain(speed4, -255, 255);

  // Send every speed to his motor
  mot(1, int(speed1));
  mot(2, int(speed2));
  mot(3, int(speed3));
  mot(4, int(speed4));

  old_Dir = direzione;

  Serial.print(speed1);
  Serial.print("|");
  Serial.print(speed2);
  Serial.print("|");
  Serial.print(speed3);
  Serial.print("|");
  Serial.println(speed4);
}

void preparePID(int direction, int speed) { preparePID(direction, speed, 0); }

void preparePID(int direction, int speed, int offset) {
  globalDir = direction;
  globalSpeed = speed;
  st = offset;
}

float updatePid() {
  float errorP, errorD, errorI;
  float delta; // assumiamo che la bussola dia un intero positivo, questo lo
               // rende da -179 a +180

  // calcola l'errore di posizione rispetto allo 0
  if (imu_current_euler < 180)
    // delta = float(imu_current_euler);
    delta = float(imu_current_euler + st);
  else
    delta = float((imu_current_euler - 360) - st);
  // delta = (imu_current_euler - 360);

  // calcola correzione proporzionale
  errorP = KP * delta;

  // calcola correzione derivativa
  errorD = KD * (delta - errorePre);
  errorePre = delta;

  // DEBUG_PRINT.println(errorD);

  // calcola correzione integrativa
  integral =
      0.5 * integral + delta; // corretta per non far divergere il contributo
  errorI = KI * integral;

  // calcota correzione complessiva
  return errorD + errorP + errorI;
}

void CheckSpeed() {
  float Max, Min;
  if ((speed1 <= 255.0 && speed1 >= -255.0) &&
      (speed2 <= 255.0 && speed2 >= -255.0) &&
      (speed3 <= 255.0 && speed3 >= -255.0) &&
      (speed4 <= 255.0 && speed4 >= -255.0))
    return;

    Max = speed1;
  if (speed2 > Max)
    Max = speed2;
  if (speed3 > Max)
    Max = speed3;
  if (speed4 > Max)
    Max = speed4;

    Min = speed1;
  if (speed2 < Min)
    Min = speed2;
  if (speed3 < Min)
    Min = speed3;
  if (speed4 < Min)
    Min = speed4;

  if (Max > 255.0) {
    Max = 255.0 / Max;
    speed1 = speed1 * Max;
    speed2 = speed2 * Max;
    speed3 = speed3 * Max;
    speed4 = speed4 * Max;
    // speedx = 255.0 * speedx / Max;
  }
  if (Min < -255.0) {
    Min = -255.0 / Min;
    speed1 = speed1 * Min;
    speed2 = speed2 * Min;
    speed3 = speed3 * Min;
    speed4 = speed4 * Min;
    // speedx = -255.0 * speedx / Min;
  }
}

// recenter the robot while being steady; spd e' sempre 1
// da chiamare in test per vedere se raddrizza
void recenter(float spd) {
  pidfactor = updatePid();
  speed1 = spd * pidfactor;
  speed2 = spd * pidfactor;
  speed3 = spd * pidfactor;
  speed4 = spd * pidfactor;

  CheckSpeed();

  // Send every speed to his motor
  mot(1, int(speed1));
  mot(2, int(speed2));
  mot(3, int(speed3));
  mot(4, int(speed4));

  return;
}
