// Here to correctly init vars.h, do not remove
#define MAIN

#include "Wire.h"
#include <Arduino.h>

#include "bluetooth.h"
#include "camera.h"
#include "chat.h"
#include "goalie.h"
#include "imu.h"
#include "interrupt.h"
#include "linesensor.h"
#include "motors.h"
#include "mysoftware_serial.h"
#include "myspi_old.h"
#include "pid.h"
#include "position.h"
#include "space_invaders.h"
#include "us.h"
#include "vars.h"

// Switch management vars
int SWS = 0;
int SWD = 0;

void setup() {
  // analogWriteFrequency(4,  1000);
  // analogWriteFrequency(7,  1000);
  // analogWriteFrequency(10, 1000);
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
  // Linesensors and interrupt
  flag_interrupt = false;
  nint = 0;
  attesa = 0;
  zoneIndex = 0;
  lineReading = 0;

  // bluetooth misc
  a = 0;
  old_timer = 0;
  role = 0;
  friendZone = 0;
  iAmHere = 0;
  comrade = false;

  // global vars for angles
  globalDir = 0;
  globalSpeed = 0;
  st = 0;
  // attacco
  atk_direction = 0;
  atk_speed = 0;
  atk_offset = 0;
  // end of variable set up
  Nint = 0;

  // CAMERA
  p = 0;
  XP_SX = false;
  XP_DX = false;
  portx = 0;

  // disable those pins, damaged teensy
  pinMode(A8, INPUT_DISABLE); // pin A8 in corto tra 3.3V e massa
  pinMode(16, INPUT_DISABLE); // pin 16 in corto tra 3.3V e massa

  // Enable Serial for test
  Serial.begin(9600);

  // Setups a bunch of pins
  pinMode(27, OUTPUT);
  for (int i = 29; i <= 31; i++)
    pinMode(i, OUTPUT);

  // Misc inits
  initMotorsGPIO();
  initLineSensors();
  initSPI();
  initUS();
  initIMU();
  initOmnidirectionalSins();
  initBluetooth();
  initSoftwareSerial();
  CAMERA.begin(19200);
  // valStringY.reserve(30);                                     //riserva
  // 30byte per le stringhe valStringB.reserve(30);  //  tone(27, 1000, 500);
  digitalWrite(31, HIGH);
}

void loop() {
  SWS = digitalRead(SWITCH_SX);
  SWD = digitalRead(SWITCH_DX);

  // update_sensors_all();
  // WhereAmI();
  // space_invaders();

  // if(millis() - t1 >= 200){
  //   BT.println(imu_current_euler);
  // }

  // // game routine

  ball_read_position();
  readIMU();
  readUS();
  WhereAmI();
  guessZone();
  calculateZoneIndex();
  goalPosition();
  // teamZone();            //DA USARE CON COMPAGNO
  // comunicazione(2000);

  // currently setting the role and the goal by code
  role = HIGH;
  p = 1; // dove 1=Blu 0=Gialla
  if (flag_interrupt) {
    int_nuovo();
  }
  if (ball_seen == true) {
    if (role == HIGH)
      goalie();
    else
      space_invaders_3();
  } else {
    if (role == HIGH)
      goCenter();
    else
      centerGoalPost();
  }

  // if((comrade == true) && (role == HIGH) && (zoneIndex > 6)) goCenter(); //DA
  // USARE CON COMPAGNO

  // final drive pid
  drivePID(globalDir, globalSpeed);
}
