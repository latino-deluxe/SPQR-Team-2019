#include "libs.h"
#include "goalie.h"
#include "linesensor.h"
//#include "position.h"

//Switch management vars
int SWS = 0;
int SWD = 0;

void setup() {
  Serial.begin(9600);

  pinMode(A8, INPUT_DISABLE); //pin A8 con corto a 3.3V e massa

  pinMode(27, OUTPUT);
  for(int i=29;i<=31;i++) pinMode(i, OUTPUT);
  Wire1.begin();

  SWS = digitalRead(SWITCH_SX);

  initMotorsGPIO();                                         //inizializza GPIO motori
  init_linesensors();                                         //abilita i sensori di linea a chiamare interrupt come PCINT2
  initSPI();                                                 //inizializza comunicazione spi
  initIMU();                                                 //inizializza imu
  initOmnidirectionalSins();                                //inizializza seni
  SWS = digitalRead(SWITCH_SX);                               //lettura switch sinistro
  //valStringY.reserve(30);                                     //riserva 30byte per le stringhe
  //valStringB.reserve(30);
  //initial_p();                                              //inizializza sensore presa palla
  tone(22, 1000, 500);
}


void loop() {



  //update_location_complete();



  //goalie();

}
