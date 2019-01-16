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

  attachInterrupt(LN0, int0, FALLING);
  attachInterrupt(LN1, int1, FALLING);
  attachInterrupt(LN2, int2, FALLING);
  attachInterrupt(LN3, int3, FALLING);
  attachInterrupt(LN4, int4, FALLING);
  attachInterrupt(LN5, int5, FALLING);
}

void int0() {
   interruptHandle(0b111110, LA3);
}

void int1() {
  interruptHandle(0b111101, C4);
}

void int2() {
  interruptHandle(0b11011, F3);
}

void int3() {
  interruptHandle(0b110111, E6);
}

void int4() {
  interruptHandle(0b101111, F6);
}

void int5() {
  interruptHandle(0b011111, GB6);
  //return;
}

void interruptHandle(byte b, float note){
  brake();
  noTone(BUZZER);
  tone(BUZZER, note);
  lineReading = b;
  delay(50);
}
