#include "libs.h"

byte lettura;

void init_linesensors();
void int0();
void int1();
void int2();
void int3();
void int4();
void int5();


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
  // brake();
  lettura = 0b111110;
  digitalWrite(27, HIGH);
  delay(200);
  digitalWrite(27, LOW);
}

void int1(){
  // brake();
  lettura = 0b111101;
  digitalWrite(27, HIGH);
  delay(200);
  digitalWrite(27, LOW);
}

void int2(){
  // brake();
  lettura = 0b111011;
  digitalWrite(27, HIGH);
  delay(200);
  digitalWrite(27, LOW);
}

void int3(){
  // brake();
  lettura = 0b110111;
  digitalWrite(27, HIGH);
  delay(200);
  digitalWrite(27, LOW);
}

void int4(){
  // brak4e();
  lettura = 0b101111;
  digitalWrite(27, HIGH);
  delay(200);
  digitalWrite(27, LOW);
}

void int5(){
  // brake();
  lettura = 0b011111;
  digitalWrite(27, HIGH);
  delay(200);
  digitalWrite(27, LOW);
}
