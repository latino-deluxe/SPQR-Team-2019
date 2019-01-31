// Here to correctly init vars.h, do not remove
#define MAIN

#include "Wire.h"
#include <Arduino.h>

#include "goalie.h"
#include "imu.h"
#include "linesensor.h"
#include "motors.h"
#include "myspi_old.h"
#include "myspi.h"
#include "pid.h"
#include "position.h"
#include "us.h"
#include "interrupt.h"
#include "vars.h"
#include "bluetooth.h"

// Switch management vars
int SWS = 0;
int SWD = 0;

void setup() {
  // Now assign value to variables, first thing to do
  // IMU
  imu_current_euler = 0;
  imu_temp_euler = 0;
  // MySPI
  ball_sensor = 0;
  ball_distance = 0;
  ball_seen = false;
  tspi = 0;
  // PID
  errorePre = 0.0;
  integral = 0.0;
  reaching_ball = false;
  st = 0;
  old_Dir = 0;
  new_Dir = 0;
  new_vMot = 0;
  // US
  reading = 0;
  us_t0 = 0;
  us_t1 = 0;
  us_flag = false;
  // Position
  old_status_x = CENTRO;
  old_status_y = CENTRO;
  // old_guessedlocation = CENTRO_CENTRO;
  goal_zone = false;
  good_field_x = true;
  good_field_y = true;
  status_x = CENTRO;
  status_y = CENTRO;
  // currentlocation = CENTRO_CENTRO;
  // guessedlocation = CENTRO_CENTRO;
  //Linesensors and interrupt
  flag_interrupt = false;
  nint = 0;
  attesa = 0;
  linea[0] = 63;                                              //prima degli interrupt sensori linea ok
  zoneIndex = 0;
  //bluetooth misc
  a = 0;
  compagno = false;
  old_timer = 0;


  maggica = false;


  // end of variable set up

  // disable those pins, damaged teensy
  pinMode(A8, INPUT_DISABLE); // pin A8 in corto tra 3.3V e massa
  pinMode(16, INPUT_DISABLE); // pin 16 in corto tra 3.3V e massa

  // Enable Serial for test
  Serial.begin(9600);

  // Setups a bunch of pins
  pinMode(27, OUTPUT);
  for (int i = 29; i <= 31; i++)
    pinMode(i, OUTPUT);

  SWS = digitalRead(SWITCH_SX);
  SWD = digitalRead(SWITCH_DX);

  // Misc inits
  initMotorsGPIO();   // inizializza GPIO motori
  initLineSensors(); // abilita i sensori di linea a chiamare interrupt come
                      // PCINT2
  initSPI();          // inizializza comunicazione spi
  initUS();
  initIMU();          // inizializza imu
  initOmnidirectionalSins(); // inizializza seni
  initBluetooth();
  // valStringY.reserve(30);                                     //riserva
  // 30byte per le stringhe valStringB.reserve(30);  //  tone(27, 1000, 500);
  digitalWrite(31, HIGH);
}

unsigned long t1 = 0;

void loop() {
  calculateZoneIndex();
  if(millis() - t1 >= 200){
    BT.println(zoneIndex);
  }
  if(flag_interrupt){
    handleInterrupt();
  }
  update_sensors_all();
  WhereAmI();
  guessZone();
  // gigaTestZone();
  if(ball_seen==true) goalie();
  else ritornacentro();
}
