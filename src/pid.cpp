#include "goalie.h"
#include "imu.h"
#include "motors.h"
#include "pid.h"
#include "vars.h"
#include <Arduino.h>

// TIMED PID CONTROL TESTING
void drivePID(signed int direzione, float vMot) {
  vx = ((vMot * cosin[direzione]) * x);
  vy = ((-vMot * sins[direzione]) * y);

  speed1 = ((vx * sins[45] ) + (vy * cosin[45] ));
  speed2 = ((vx * sins[135]) + (vy * cosin[135]));
  speed3 = -(speed1);
  speed4 = -(speed2);

  /*speed1 = ((-(sins[((direzione - 45) + 360) % 360])) * vMot);          // mot 1
   speed2 = ((-(sins[((direzione - 135) + 360)% 360])) * vMot);          // mot 2
   speed3 = -(speed1);                                                   // mot 3
   speed4 = -(speed2);*/                                                   // mot 4
 
  pidfactor = updatePid();

  speed1 += pidfactor;
  speed2 += pidfactor;
  speed3 += pidfactor;
  speed4 += pidfactor;
  
  speed1 = constrain(speed1, -255, 255);
  speed2 = constrain(speed2, -255, 255);
  speed3 = constrain(speed3, -255, 255);
  speed4 = constrain(speed4, -255, 255);

  // Send every speed to his motor
  mot(1, int(speed1));
  mot(2, int(speed2));
  mot(3, int(speed3));
  mot(4, int(speed4));
}

void preparePID(int direction, int speed) { preparePID(direction, speed, 0); }

void preparePID(int direction, int speed, int offset) {
  globalDir = direction;
  globalSpeed = speed;
  st = offset;
  if(bounds) st = 0;
}


float updatePid() {
  float errorP, errorD, errorI;
  // assumiamo che la bussola dia un intero positivo, questo lo rende da -179 a +180
  float delta; 

  // calcola l'errore di posizione rispetto allo 0
  delta = imu_current_euler;
  if(delta > 180) delta = delta-360;
  delta = delta-st;

  // calcola correzione proporzionale
  errorP = KP * delta;

  // calcola correzione derivativa
  errorD = KD * (delta - errorePre);
  errorePre = delta;

  // calcola correzione integrativa
  integral = 0.5 * integral + delta;
  errorI = KI * integral;

  // calcota correzione complessiva
  return errorD + errorP + errorI;
}