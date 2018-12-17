#include "libs.h"

byte mess;
int ball_sensor;
int ball_distance;

SPISettings settings(100000, MSBFIRST, SPI_MODE0);

void initSPI() {
  pinMode(SS_PIN, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
}

void readSPI() {
  mess = 0;
  SPI.beginTransaction(settings);
  digitalWrite(SS_PIN, LOW);
  mess = SPI.transfer(255);
  digitalWrite(SS_PIN, HIGH);
  SPI.endTransaction();
  if (mess == 255) return;

  ball_sensor = mess & 31;
  ball_distance = (mess & 224) >> 5;

  Serial.println(mess);
  delay(500);
}
