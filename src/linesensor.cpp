#include <Arduino.h>
#include "linesensor.h"
#include "motors.h"
byte lettura;


void init_linesensors(){
  pinMode(LN0, INPUT);
  pinMode(LN1, INPUT);
  pinMode(LN2, INPUT);
  pinMode(LN3, INPUT);
  pinMode(LN4, INPUT);
  pinMode(LN5, INPUT);

  attachInterrupt(LN0, int0, FALLING);
  attachInterrupt(LN1, int1, FALLING);
  attachInterrupt(LN2, int2, FALLING);
  attachInterrupt(LN3, int3, FALLING);
  attachInterrupt(LN4, int4, FALLING);
  attachInterrupt(LN5, int5, FALLING);
}


void int0(){
  brake();
  lettura = 0b111110;
  return;
}

void int1(){
  brake();
  lettura = 0b111101;
  return;
}

void int2(){
  brake();
  lettura = 0b111011;
  return;
}

void int3(){
  brake();
  lettura = 0b110111;
  return;
}

void int4(){
  brake();
  lettura = 0b101111;
  return;
}

void int5(){
  brake();
  lettura = 0b011111;
  return;
}