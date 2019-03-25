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
#include "music.h"
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
  pAtk = 0;
  pDef = 0;
  portx = 0;

  // BT
  topolino = 0;

  //stincr
  stincr = 0;

  // disable those pins, damaged teensy
  pinMode(A8, INPUT_DISABLE); // pin A8 in corto tra 3.3V e massa
  pinMode(16, INPUT_DISABLE); // pin 16 in corto tra 3.3V e massa

  pinMode(SWITCH_DX, INPUT);

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

  // digitalWrite(30, HIGH);
  // digitalWrite(29, HIGH);
}

void loop() {

  // for ports: 1=Blue 0=Yellow
  pAtk = 0;
  pDef = 1 - pAtk; // the other port for the keeper

  // SWS = digitalRead(SWITCH_SX);
  SWD = digitalRead(SWITCH_DX);
  role = SWD;

  comrade = true;

  if (comrade)
    role = role;
  else
    role = 1 - role;

  // bluetooth and communication stuff
  teamZone();
  whereAreYou();
  // testBluetooth();
  // game routine

  ball_read_position();
  readIMU();
  readUS();
  WhereAmI();
  guessZone();
  calculateZoneIndex();
  goalPosition();
  // Ao();
  // com(2000);

  // if (flag_interrupt) {
  //   int_nuovo();
  // }
  //
  // if (ball_seen == true) {
  //   if (role == HIGH)
  //     goalie();
  //   else
  //     space_invaders_camera();
  // } else {
  //   if (role == HIGH)
  //     goCenter();
  //   else
  //     centerGoalPostCamera();
  // }

  // final drive pid
  // drivePID(globalDir, globalSpeed);
<<<<<<< HEAD
  Serial.println("ciao");
  delay(1000);
=======
  Serial.println(ball_sensor);
>>>>>>> c726b9284d8025cc463ad95281e7c24ea2e308b7
}
