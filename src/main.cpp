// Here to correctly init vars.h, do not remove
#define MAIN

#include "Wire.h"
#include <Arduino.h>

#include "bluetooth.h"
#include "camera.h"
#include "chat.h"
#include "goalie.h"
#include "imu.h"
#include "linesensor.h"
#include "motors.h"
#include "music.h"
#include "nano_ball.h"
#include "pid.h"
#include "position.h"
#include "space_invaders.h"
#include "test.h"
#include "us.h"
#include "vars.h"

// Switch management vars
int SWS = 0;
int SWD = 0;
elapsedMillis timertest;
int aiut = 0;

void setup() {
  startSetup();

  // Now assign value to variables, first thing to do
  // IMU
  imu_current_euler = 0;
  // MySPI
  ball_distance = 0;
  ball_seen = false;
  // PID
  errorePre = 0.0;
  integral = 0.0;
  st = 0;
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
  // attack
  atk_direction = 0;
  atk_speed = 0;

  // CAMERA
  pAtk = 0;
  pDef = 0;
  portx = 0;
  goal_orientation = 0;
  cameraReady = 0;

  // BT
  topolino = 0;
  fpos = 0;

  // stincr
  stincr = 0;

  //axis
  y = 1;
  x = 1;

  // ;)
  analogWriteFrequency(2 , 15000);
  analogWriteFrequency(5 , 15000);
  analogWriteFrequency(6, 15000);
  analogWriteFrequency(23, 15000);

  // disable those pins, damaged teensy
  pinMode(A8, INPUT_DISABLE); // pin A8 in corto tra 3.3V e massa
  pinMode(16, INPUT_DISABLE); // pin 16 in corto tra 3.3V e massa

  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(Y, OUTPUT);

  pinMode(SWITCH_DX, INPUT);
  pinMode(SWITCH_SX, INPUT);

  // Enable Serial for test
  Serial.begin(9600);
  //Enable Serial3 for debug
  BT.begin(9600);
  // Enable Serial4 for the slave
  NANO_BALL.begin(57600);
  // Enable Serial2 for the camera
  CAMERA.begin(19200);

  // Misc inits
  initIMU();
  initMotorsGPIO();
  initUS();
  initSinCos();
  // initBluetooth();



  timertest = 0;

  // if(digitalRead(SWITCH_DX) == HIGH && digitalRead(SWITCH_SX) == HIGH){
  //   // NANO_BALL.end();
  //   // //pinMode(31, INPUT_DISABLE);
  //   // //pinMode(32, INPUT_DISABLE);
  //   // tone(BUZZER, C6);
  //   // delay(500);
  //   // noTone(BUZZER);
  //   // super_mario();
  // } else
  delay(500);
  stopSetup();
}

float cstorc = 0;

void loop() {
  role = digitalRead(SWITCH_DX);                //se HIGH sono attaccante
  goal_orientation = digitalRead(SWITCH_SX);     //se HIGH attacco gialla, difendo blu

  if(Serial.available() > 0) testMenu();

  readIMU();
  readUS();
  readBallNano();
  goalPosition();
  if(cameraReady == 1) {
    // storcimentoPortaIncr();
    calcPhyZoneCam = true;
    cameraReady = 0;

      if (pAtk > 20) cstorc+=0.1;
      if (pAtk < -20) cstorc-=0.1;
  //    Serial.println(pAtk);
      }
  calculateLogicZone();

  if(ball_seen){
    if(role) goalie();
    else space_invaders();
  } else {
    if(role) goCenter();
    else centerGoalPost();
  }

  checkLineSensors();                           //Last thing in loop, for priority
  // Serial.print(pAtk);
  // Serial.print (" ");
  // Serial.println(imu_current_euler);
  // delay(100);
  // BT.print(pAtk);
  // BT.print("      ");
  // delay(250);

  preparePID(0, 0, cstorc);
  drivePID(globalDir, globalSpeed);
}
