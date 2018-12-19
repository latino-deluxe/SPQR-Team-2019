#include "libs.h"

byte mess;
//VARIABILI RELATIVE ALLA LETTURA DELLA PALLA---------------
byte spi_temp_byte = 0;    // dato grezzo letto da SPI
byte ball_sensor = 0;      // sensore che vede la palla
byte ball_distance = 0;    // distanza della palla con valore da 0 a 6
bool ball_seen = false;    // palla in vista si/no era byte
byte old_s_ball;           // sensore che vedeva la palla in precedenza, paragonato con ball_sensor
unsigned long time_s_ball; // millisecondipassati dal cambiamento di sensore che vede la palla (KEEPER)

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
  ball_sensor = mess & 0b00011111;
  ball_distance = (mess & 0b11100000) >> 5;

  Serial.print(ball_sensor);
  delay(200);
  Serial.print(" | ");
  delay(200);
  Serial.println(ball_distance);
  delay(200);
}
