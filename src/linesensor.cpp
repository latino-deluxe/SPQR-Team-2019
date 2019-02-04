#include "linesensor.h"
#include "motors.h"
#include "vars.h"
#include <Arduino.h>

void initLineSensors() {
  pinMode(LN0, INPUT);
  pinMode(LN1, INPUT);
  pinMode(LN2, INPUT);
  pinMode(LN3, INPUT);
  pinMode(LN4, INPUT);
  pinMode(LN5, INPUT);

  attachInterrupt(LN0, line0, CHANGE);
  attachInterrupt(LN1, line1, CHANGE);
  attachInterrupt(LN2, line2, CHANGE);
  attachInterrupt(LN3, line3, CHANGE);
  attachInterrupt(LN4, line4, CHANGE);
  attachInterrupt(LN5, line5, CHANGE);
}

     // passInterrupt(lineReading);
 void line0() {
   linea[0] = !digitalRead(LN0);
 }

  void line1() {
    linea[1] = !digitalRead(LN1);
  }

  void line2() {
    linea[2] = !digitalRead(LN2);
  }

  void line3() {
    linea[3] = !digitalRead(LN3);
  }

  void line4() {
    linea[4] = !digitalRead(LN4);
  }

  void line5() {
    linea[5] = !digitalRead(LN5);
  }

// void passInterrupt(byte reading){
//   if(maggica == true) return;
//   brakeI();
//   if(flag_interrupt == true){
//     nint++;
//      if(nint >= INT_LUNG){
//        nint = INT_LUNG-1;
//      }
//   }else{
//     nint=1;
//     flag_interrupt=true;
//   }
//   linea[nint]=reading;
//   return;
// }
