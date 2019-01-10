#include <Arduino.h>
#include "Wire.h"
#include "motors.h"
#include "imu.h"
#include "linesensor.h"
#include "myspi.h"
#include "motors.h"
#include "us.h"
#include "goalie.h"
#include "position.h"
#include "pid.h"

//IR shield pin
#define BUZZER 27
#define SWITCH_SX 24
#define SWITCH_DX 25


//Note
#define LA3 220.00
#define C4  261.63
#define F3  174.61
#define E6  1318.51
#define F6  1396.91
#define GB6 1479.98

//Switch management vars
int SWS = 0;
int SWD = 0;

extern int ball_distance;

void setup() {
        Serial.begin(9600);

        pinMode(A8, INPUT_DISABLE); //pin A8 in corto tra 3.3V e massa
        pinMode(16, INPUT_DISABLE); //pin 16 in corto tra 3.3V e massa

        pinMode(27, OUTPUT);
        for(int i=29; i<=31; i++) pinMode(i, OUTPUT);
        Wire1.begin();

        SWS = digitalRead(SWITCH_SX);

        initMotorsGPIO();                                     //inizializza GPIO motori
        init_linesensors();                                   //abilita i sensori di linea a chiamare interrupt come PCINT2
        initSPI();                                            //inizializza comunicazione spi
        initIMU();                                            //inizializza imu
        initOmnidirectionalSins();                            //inizializza seni
        SWS = digitalRead(SWITCH_SX);                         //lettura switch sinistro
        //valStringY.reserve(30);                                     //riserva 30byte per le stringhe
        //valStringB.reserve(30);  //  tone(27, 1000, 500);
        digitalWrite(31, HIGH);
}


void loop() {
  ball_read_position();
  readIMU();
  if(ball_distance < 6){
  goalie();
}
  else recenter(2);
}
