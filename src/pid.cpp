// #include "goalie.h"
// #include "imu.h"
// #include "motors.h"
// #include "pid.h"
// #include "vars.h"
// #include <Arduino.h>

// // TIMED PID CONTROL TESTING
// void drivePID(signed int direzione, float vMot) {
//   // mette in variabili globali direzione e velocitá precedenti e attuali
//   new_Dir = direzione;
//   // old_vMot = new_vMot;
//   // new_vMot = vMot;

//   int dir2 = (direzione - imu_current_euler + 360) % 360;

//   speed1 = ((-(sins[((dir2 - 60) + 360) % 360])) * vMot); // mot 1
//   speed2 = ((sins[(dir2 + 360) % 360]) * vMot);           // mot 2
//   speed3 = ((-(sins[(dir2 + 60) % 360])) * vMot);         // mot 3

//   // int dead = 35;
//   pidfactor = orientationPid(st);
//   speed1 -= pidfactor;
//   speed2 -= pidfactor;
//   speed3 -= pidfactor;
//   // if (pidfactor > 0) {
//   //   speed1 = map(pidfactor, 0, 225, -dead, -vMot);
//   //   speed2 = map(pidfactor, 0, 225, -dead, -vMot);
//   //   speed3 = map(pidfactor, 0, 225, -dead, -vMot);
//   // } else {
//   //   speed1 = map(pidfactor, 0, -225, dead, vMot);
//   //   speed2 = map(pidfactor, 0, -225, dead, vMot);
//   //   speed3 = map(pidfactor, 0, -225, dead, vMot);
//   // }

//   // Serial.println(pidfactor);
//   // CheckSpeed(); // normalizza la velocita' a 255 max al motore piu' veloce e
//   // gli altri in proporzione

//   // rinomarlizzo al massimo del maggiore
//   // un giorno metteremo una spiegazione più semplice
//   int speedMax = max(speed1, max(speed2, speed3));
//   if (speedMax > 255) {
//     speed1 = (speed1 / speedMax) * 255;
//     speed2 = (speed2 / speedMax) * 255;
//     speed3 = (speed3 / speedMax) * 255;
//   }

//   // Send every speed to his motor
//   mot(2, int(speed2));
//   mot(1, int(speed1));
//   mot(3, int(speed3));

//   // Serial.print(speed1);
//   // Serial.print("   ");
//   // Serial.print(speed2);
//   // Serial.print("   ");
//   // Serial.print(speed3);
//   // Serial.println("   ");
//   old_Dir = direzione;
// }

// void preparePID(int direction, int speed) { preparePID(direction, speed, 0); }

// void preparePID(int direction, int speed, int offset) {
//   globalDir = direction;
//   globalSpeed = speed;
//   st = offset;
// }

// float errorP, errorD, errorI, er;
// unsigned long timePid = 0;

// float orientationPid(int dir) {
//   if (micros() < timePid + 4000)
//     return errorD + errorP + errorI;
//   timePid = micros();

//   // calcola l'errore di posizione rispetto allo 0 con logica -10<-|0|-> 10
//   er = (dir - imu_current_euler + 360) % 360;
//   // Serial.print(er);
//   // Serial.print("  ");
//   if (er > 180)
//     // delta = float(imu_current_euler);
//     er -= 360;
//   Serial.print(er);
//   Serial.print("  ");
//   // calcola correzione proporzionale
//   errorP = KP * er;

//   // calcola correzione derivativa
//   errorD = KD * (er - errorePre);
//   errorePre = er;

//   // calcola correzione integrativa
//   if (abs(integral + er) < IMAX) {
//     integral += er; // corretta per non far divergere il contributo
//     errorI = KI * integral;
//   }
//   Serial.println((errorD + errorP + errorI));
//   // calcota correzione complessiva
//   return (errorD + errorP + errorI);
// }

// float updatePid() {
//   float errorP, errorD, errorI;
//   float delta; // assumiamo che la bussola dia un intero positivo, questo lo
//                // rende da -179 a +180

//   // calcola l'errore di posizione rispetto allo 0
//   if (imu_current_euler < 180)
//     // delta = float(imu_current_euler);
//     delta = float(imu_current_euler + st);
//   else
//     delta = float((imu_current_euler - 360) - st);
//   // delta = (imu_current_euler - 360);

//   // calcola correzione proporzionale
//   errorP = KP * delta;

//   // calcola correzione derivativa
//   errorD = KD * (delta - errorePre);
//   errorePre = delta;

//   // DEBUG_PRINT.println(errorD);

//   // calcola correzione integrativa
//   integral =
//       0.5 * integral + delta; // corretta per non far divergere il contributo
//   errorI = KI * integral;

//   // calcota correzione complessiva
//   return errorD + errorP + errorI;
// }

// void CheckSpeed() {
//   float Max, Min;
//   if ((speed1 <= 255.0 && speed1 >= -255.0) &&
//       (speed2 <= 255.0 && speed2 >= -255.0) &&
//       (speed3 <= 255.0 && speed3 >= -255.0))
//     return;

//   Max = speed1;
//   if (speed2 > Max)
//     Max = speed2;
//   if (speed3 > Max)
//     Max = speed3;
//   Min = speed1;
//   if (speed2 < Min)
//     Min = speed2;
//   if (speed3 < Min)
//     Min = speed3;

//   if (Max > 255.0) {
//     Max = 255.0 / Max;
//     speed1 = speed1 * Max;
//     speed2 = speed2 * Max;
//     speed3 = speed3 * Max;
//     // speedx = 255.0 * speedx / Max;
//   }
//   if (Min < -255.0) {
//     Min = -255.0 / Min;
//     speed1 = speed1 * Min;
//     speed2 = speed2 * Min;
//     // speed3 = speed3 * Min;
//     // speedx = -255.0 * speedx / Min;
//   }
// }

// // recenter the robot while being steady; spd e' sempre 1
// // da chiamare in test per vedere se raddrizza
// void recenter(float spd) {
//   pidfactor = updatePid();
//   speed1 = spd * pidfactor;
//   speed2 = spd * pidfactor;
//   speed3 = spd * pidfactor;

//   CheckSpeed();

//   // Send every speed to his motor
//   mot(2, int(speed2));
//   mot(1, int(speed1));
//   mot(3, int(speed3));

//   return;
// }