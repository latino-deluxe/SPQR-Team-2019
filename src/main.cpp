#include "libs.h"
#include "imu.h"
#include "us.h"
#include "motors.h"
#include "spi.h"
#include "linesensor.h"


//Switch management vars
int SWS = 0;
int SWD = 0;


void setup() {
  Serial.begin(9600);
  pinMode(27, OUTPUT);



  Wire1.begin();
  initIMU();
  initSPI();

  init_linesensors();

  //SWS = digitalRead(SWITCH_SX);
  /*valStringY.rese
  rve(30);                                     //riserva 30byte per le stringhe
  valStringB.reserve(30);*/

  initMotorsGPIO();
  //tone(22, 1000, 500);
  for(int i=29;i<=31;i++) pinMode(i, OUTPUT);

}

void loop() {

  //readSPI();

  //readIMU();
  //readUS();

  /*
  turnMotor(1,0,1,255);
  delay(500);
  turnMotor(1,0,0,0);u
  delay(1000);
  turnMotor(1,1,0,255);
  delay(500);
  turnMotor(1,0,0,0);
  delay(1000);
  */
  delay(500);
}
