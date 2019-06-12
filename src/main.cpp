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

void setup() {
  startSetup();
  // imperial_march();
  
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
  // attack
  atk_direction = 0;
  atk_speed = 0;
  atk_offset = 0;
  // defense
  flag_interrupt = false;
  // end of variable set up
  Nint = 0;

  // CAMERA
  pAtk = 0;
  pDef = 0;
  portx = 0;
  goal_orentation = 0;
  cameraReady = 0;

  // BT
  topolino = 0;
  fpos = 0;

  // stincr
  stincr = 0;

  //axis
  y = 1;
  x = 1;

  //bounds
  EXTIME = 100;      //prima era 75

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

  // pinMode(SWITCH_DX, INPUT);

  // Enable Serial for test
  Serial.begin(9600);
  // Enable Serial4 for the slave
  NANO_BALL.begin(57600);

  // Setups a bunch of pins
  // pinMode(27, OUTPUT);
  // for (int i = 29; i <= 31; i++)
  //   pinMode(i, OUTPUT);

  // Misc inits
  initIMU();
  initMotorsGPIO();
  // initLineSensors();
  initUS();
  initSinCos();
  // initBluetooth();
  CAMERA.begin(19200);

  
  timertest = 0;

  if(digitalRead(SWITCH_DX) == HIGH && digitalRead(SWITCH_SX) == HIGH){
    // NANO_BALL.end();
    // //pinMode(31, INPUT_DISABLE);
    // //pinMode(32, INPUT_DISABLE);
    // tone(BUZZER, C6);
    // delay(500);
    // noTone(BUZZER);
    super_mario();
  } else stopSetup();
}

void loop() {   
  role = digitalRead(SWITCH_DX);                //se HIGH sono attaccante
  goal_orentation = digitalRead(SWITCH_SX);     //se HIGH attacco gialla, difendo blu

  if(Serial.available() > 0) testMenu();

  readIMU();
  readBallNano();
  goalPosition();

  if(cameraReady == 1) {
    storcimentoPortaIncr();
    // calcPhyZoneCam = true;
    cameraReady = 0;
  }
  
  if(ball_seen){
    if(role) goalie();
    else space_invaders();
  } 
  else preparePID(0, 0);
  
  checkLineSensors();                           //Last thing in loop, for priority

  drivePID(globalDir, globalSpeed);
}
