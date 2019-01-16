// Here to correctly init vars.h, do not remove
#define MAIN

#include "Wire.h"
#include <Arduino.h>

#include "goalie.h"
#include "imu.h"
#include "linesensor.h"
#include "motors.h"
#include "myspi_old.h"
#include "pid.h"
#include "position.h"
#include "us.h"
#include "vars.h"

// IR shield pin
#define BUZZER 27
#define SWITCH_SX 24
#define SWITCH_DX 25

// Note
#define LA3 220.00
#define C4 261.63
#define F3 174.61
#define E6 1318.51
#define F6 1396.91
#define GB6 1479.98

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
  old_guessedlocation = CENTRO_CENTRO;
  goal_zone = false;
  good_field_x = true;
  good_field_y = true;
  status_x = CENTRO;
  status_y = CENTRO;
  currentlocation = CENTRO_CENTRO;
  guessedlocation = CENTRO_CENTRO;
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
  init_linesensors(); // abilita i sensori di linea a chiamare interrupt come
                      // PCINT2
  initSPI();          // inizializza comunicazione spi
  initUS();
  initIMU();          // inizializza imu
  initOmnidirectionalSins(); // inizializza seni
  // valStringY.reserve(30);                                     //riserva
  // 30byte per le stringhe valStringB.reserve(30);  //  tone(27, 1000, 500);
  digitalWrite(31, HIGH);
}

void loop() {
  //readUSTEST();
  update_sensors_all();
  WhereAmI();
  if(ball_seen==true) goalie();
  else centroporta();
  //readUSTEST();
  //
  // Serial.print(us_values[0]);
  // Serial.print(" | ");
  // Serial.print(us_dx);
  // Serial.print(" | ");
  // Serial.print(us_px);
  // Serial.print(" | ");
  // Serial.print(us_sx);
  // Serial.println(" | ");
  // Serial.println(status_x);
  // Serial.print("  ");
  // Serial.println(status_y);
}
