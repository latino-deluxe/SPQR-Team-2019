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

  digitalWrite(SS_PIN,HIGH);
}


unsigned long t1 = 0;
void readSPI() {
  if(millis() - t1 > 10){
  mess = 0;
    SPI.beginTransaction(settings);
  digitalWrite(SS_PIN, LOW);
  mess = SPI.transfer(255);
  digitalWrite(SS_PIN, HIGH);
  SPI.endTransaction();
  t1 = millis();
  if (mess == 255) return;
  ball_sensor = mess & 0b00011111;
  ball_distance = (mess & 0b11100000) >> 5;                                                    //unica differenza con readspi vecchio codice
  }
  }

void ball_read_position()
{
  readSPI(); //getting our data from our spi slave
  ball_seen = true; //in any other case the ball is seen by the robot
  if (ball_distance == 6)
  {
    ball_seen = false; //if the distance is 6 it means that the robot doesnt see the ball
  }

  if (old_s_ball != ball_sensor)
  {
    old_s_ball = ball_sensor;
    time_s_ball = millis();  // per quanto tempo lo stesso sensore vede la palla >usata in keeper e non in goalie<
  }
  return;
}
