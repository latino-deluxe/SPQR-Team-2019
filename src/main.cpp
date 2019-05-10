// Here to correctly init vars.h, do not remove
#define MAIN

#include "Wire.h"
#include <Arduino.h>
#include <TeensyThreads.h>

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
#include "test.h"
#include "threads.h"100
#include "us.h"
#include "vars.h"

// Switch management vars
int SWS = 0;
int SWD = 0;

void setup() {
  startSetup();
  
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
  goal_zone = false;
  good_field_x = true;
  good_field_y = true;
  status_x = CENTRO;
  status_y = CENTRO;
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

  // BT
  topolino = 0;
  fpos = 0;

  // stincr
  stincr = 0;

  //Misc
  ball = false;

  //thread id's
  THRD1 = 0;
  THRD2 = 0;
  THRD3 = 0;
  THRD4 = 0;
  THRD5 = 0;
  THRD6 = 0;

  // Motors PWM frequency
  // analogWriteFrequency(4 , 1000);
  // analogWriteFrequency(7 , 1000);
  // analogWriteFrequency(10, 1000);

  // disable those pins, damaged teensy
  pinMode(A8, INPUT_DISABLE); // pin A8 in corto tra 3.3V e massa
  pinMode(16, INPUT_DISABLE); // pin 16 in corto tra 3.3V e massa

  pinMode(SWITCH_DX, INPUT);

  // Setups a bunch of pins
  pinMode(27, OUTPUT);
  for (int i = 29; i <= 31; i++)
    pinMode(i, OUTPUT);

  // Misc inits
  initIMU();
  initMotorsGPIO();
  initLineSensors();
  initSPI();
  initUS();
  initOmnidirectionalSins();
  initBluetooth();
  initSoftwareSerial();

  // Enable Serial 
  Serial.begin(9600);
  CAMERA.begin(19200);

  //Init threads
  THRD1 = threads.addThread(update_everything_pos);
  THRD2 = threads.addThread(update_atk);
  THRD3 = threads.addThread(friendo);
  // THRD4 = threads.addThread(imperial_thread);
  // THRD5 = threads.addThread(gameroutine);      NON VA
  THRD6 = threads.addThread(storcimentoFigo);

  //suspend imperial thread at the start
  threads.suspend(THRD4);         

  //per gioco da solo
  // threads.suspend(THRD3);     

  stopSetup();
}

void loop() {
  //readIMU here because it doesnt work in the thready thingy
    readIMU(); 

    // and this 'cause yeah
    SWD = digitalRead(SWITCH_DX);
    role = SWD;

    // for ports: 1=Blue 0=Yellow
    pAtk = 0;
    pDef = 1 - pAtk; // the other port for the keeper

    if ((flagtest == true) || (Serial.available() > 0)) testMenu(); // test

    // game routine
    if (flag_interrupt) int_nuovo();

    if (ball_seen == true) {
      if (role == HIGH) {
        if (comrade)
          goalie();
        else
          keeper();
      } else {
        if (stop_menamoli)
          centerGoalPost();
        else {
          if (ball_distance <= 2 && inSensorRange(0, 2) && !comrade) {
            goalie();
          } else {
            keeper();
          }
        }
      }
    } else {
      stincr = 0;
      if (role == HIGH) {
        if (comrade)
          goCenter();
        else
          centerGoalPost();
      } else {
        centerGoalPost();
      }
    }

    // commentare se il robot sta fermo dopo essere uscito anche se la posizione
    // della palla cambia di tanto
    // if (ball_seen && ball_sensor == lineBallSensor &&
    //     ball_distance == lineBallDistance && // potrebbe dar fastidio a portiere
    //     (globalDir > (((globalDir - 10) + 360) % 360)) &&
    //     (globalDir < (((globalDir + 10) + 360) % 360))) {
    //   preparePID(0, 0);
    // }

    // // letteralmente se ho palla faccio la marcia imperiale
    // if(ball_distance <= 2 && (ball_sensor == 18 || ball_sensor == 19 || ball_sensor == 0 || ball_sensor == 1) || ball_sensor == 2) ball = true;
    // else ball = false;

    // if(ball) threads.restart(THRD4);
    // else threads.suspend(THRD4);

    // final drive pid
    if (globalSpeed != 0) {
      if (role) {
        globalSpeed = 200;
      } else {
        globalSpeed = 200;
      }
    }

    drivePID(globalDir, globalSpeed);
}
