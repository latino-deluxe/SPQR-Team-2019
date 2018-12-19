#include "libs.h"
#include "goalie.h"
#include "linesensor.h"
//#include "position.h"

//Switch management vars
int SWS = 0;
int SWD = 0;

void setup() {
        Serial.begin(9600);

        pinMode(A8, INPUT_DISABLE); //pin A8 in corto tra 3.3V e massa
        pinMode(16, INPUT_DISABLE); //pin 16 in corto tra 3.3V e massa

        pinMode(27, OUTPUT);
        for(int i=29; i<=31; i++) pinMode(i, OUTPUT);
        Wire1.begin();

        SWS = digitalRead(SWITCH_SX);

        initMotorsGPIO();                                   //inizializza GPIO motori
        //init_linesensors();                                   //abilita i sensori di linea a chiamare interrupt come PCINT2
        initSPI();                                           //inizializza comunicazione spi
        initIMU();                                           //inizializza imu
        initOmnidirectionalSins();                          //inizializza seni
        SWS = digitalRead(SWITCH_SX);                         //lettura switch sinistro
        //valStringY.reserve(30);                                     //riserva 30byte per le stringhe
        //valStringB.reserve(30);
        //initial_p();                                              //inizializza sensore presa palla
      //  tone(27, 1000, 500);
      digitalWrite(31, HIGH);
}


void loop() {
  //leggo tutto e seguo la palla
  int goaliedirection[20] = { AA0, AA1 , AA2, AA3, AA4, AA5, AA6, AA7, AA8, AA9, AA10, AA11, AA12, AA13, AA14, AA15, AA16, AA17, AA18, AA19 }; //direzioni going around the ball

  readSPI();
  readIMU();
  int atk_direction = goaliedirection[ball_sensor]; //going around the ball
  if(ball_sensor==0) digitalWrite(29, HIGH);
  else digitalWrite(29, LOW);
  drivePID(atk_direction, 255);
}
