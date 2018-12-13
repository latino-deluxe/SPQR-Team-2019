#include "libs.h"

byte mess;

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
  Serial.println(mess);
  delay(500);
}
