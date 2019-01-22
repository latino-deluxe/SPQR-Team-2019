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

  attachInterrupt(LN0, line0, FALLING);
  attachInterrupt(LN1, line1, FALLING);
  attachInterrupt(LN2, line2, FALLING);
  attachInterrupt(LN3, line3, FALLING);
  attachInterrupt(LN4, line4, FALLING);
  attachInterrupt(LN5, line5, FALLING);
}

void line0() {
   lineReading = 0b111110;
   brakeI();
   if(flag_interrupt == true){
     nint++;
      if(nint >= INT_LUNG){
        nint = INT_LUNG-1;
      }
   }else{
     nint=1;
     flag_interrupt=true;
   }
   linea[nint]=lineReading;
   return;
}

void line1() {
  lineReading = 0b111101;
  brakeI();
  if(flag_interrupt == true){
    nint++;
     if(nint >= INT_LUNG){
       nint = INT_LUNG-1;
     }
  }else{
    nint=1;
    flag_interrupt=true;
  }
  linea[nint]=lineReading;
  return;
}

void line2() {
  lineReading = 0b111011;
  brakeI();
  if(flag_interrupt == true){
    nint++;
     if(nint >= INT_LUNG){
       nint = INT_LUNG-1;
     }
  }else{
    nint=1;
    flag_interrupt=true;
  }
  linea[nint]=lineReading;
  return;
}

void line3() {
  lineReading = 0b110111;
  brakeI();
  if(flag_interrupt == true){
    nint++;
     if(nint >= INT_LUNG){
       nint = INT_LUNG-1;
     }
  }else{
    nint=1;
    flag_interrupt=true;
  }
  linea[nint]=lineReading;
  return;
}

void line4() {
  lineReading = 0b101111;
  brakeI();
  if(flag_interrupt == true){
    nint++;
     if(nint >= INT_LUNG){
       nint = INT_LUNG-1;
     }
  }else{
    nint=1;
    flag_interrupt=true;
  }
  linea[nint]=lineReading;
  return;
}

void line5() {
  lineReading = 0b011111;
  brakeI();
  if(flag_interrupt == true){
    nint++;
     if(nint >= INT_LUNG){
       nint = INT_LUNG-1;
     }
  }else{
    nint=1;
    flag_interrupt=true;
  }
  linea[nint]=lineReading;
  return;
}
