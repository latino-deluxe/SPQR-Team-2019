#include "interrupt.h"
#include "myspi_old.h"
#include "pid.h"
#include "vars.h"
#include <Arduino.h>
#include <math.h>

// Degrees: 60, 0, 300, 240, 180,120
float lCosins[INT_LUNG] = {0.5, 1, 0.5, -0.5, -1, -0.5};
float lSins[INT_LUNG] = {0.866, 0, -0.866, -0.866, 0, 0.866};
unsigned long tline = 0;

bool stopFlag = false;

int ldir = 0;
int lspeed = 180;
// byte lineBallSensor = 0;

// brand new way to handle the interrupt: trigonometry!
void handleInterruptTrigonometry() {

  if (millis() - tline < 250) {
    // continues the old movement, due to high motors inertia
    preparePID(ldir, lspeed);
    lineBallSensor = ball_sensor;
    lineBallDistance = ball_distance;
    stopFlag = true;
    return;
  }
  // else {
  //   tline = 0;
  //   // if the current sensor is in a range of sensors from the one that seen
  //   the
  //   // ball, just stop
  tline = 0;
  if (stopFlag) {
    if (inSensorRange(lineBallSensor, (byte)1)) {
      preparePID(0, 0);
      return;
    }
    stopFlag = false;
  }
  // }

  byte line = 0;
  // constructs a complete byte using the array that stores the interrupt data
  for (int i = 0; i < INT_LUNG; i++) {
    line |= linea[i] << i;
  }

  if (line == 0)
    return;

  // interpolates the data with sine and cosine and using atan2 construct an
  // angle of exit
  tline = millis();

  float x = 0, y = 0;

  for (int i = 0; i < INT_LUNG; i++) {
    if (linea[i] == 1) {
      x += lCosins[i];
      y += lSins[i];
    }
  }

  // old version

  // exit angle
  float angle = atan2(y, x) * 180 / 3.14;

  // shifts the angle by 90 degrees, so the 0 in the front of the robot
  int map_angle = 0;
  if (angle < 0)
    angle += 360;
  map_angle = ((int)(angle - 90)) % 360;

  map_angle = -map_angle;

  // now calculates the go-back angle (the opposite of the exit angle)
  ldir = ((int)map_angle + 180) % 360;

  // shifts a bit the go-back angle by the imu reading (robot rotation over
  // itself) and calculates the final go-back angle
  ldir -= imu_current_euler;
  ldir = ldir < 0 ? ldir += 360 : ldir;

  // Serial.print(map_angle);
  // Serial.print(" | ");
  // Serial.println(dir);

  // new version
  // calcolo dell'angolo della linea
  // float angle = atan2(y,x) * 180 / 3.14;
  // //atan2 restituisce i gradi in [-180,+180] e seguendo la circonf.
  // goniometrica.
  //
  // int map_angle = 0;
  // map_angle = (int)angle;
  // map_angle = -(angle) + 90;                        //Conversione + cambio di
  // rotazione = nord 0 gradi, senso orario positivo. map_angle = (map_angle
  // +360) % 360; 							//per rientrare
  // nel [0,360]
  //
  // int corrected_angle = map_angle;
  // corrected_angle = corrected_angle - imu_current_euler;	//tolgo la
  // rotazione del robot all'angolo della linea corrected_angle =
  // (corrected_angle +360) % 360; 				//per rientrare
  // nel [0,360]
  //
  // int out_direction = corrected_angle;
  // out_direction = out_direction + 180; 							//trovo
  // opposto all'angolo calcolato out_direction = (out_direction +360)% 360;
  // //per rientrare nel [0,360]
  //
  // ldir = out_direction;

  // saves the ball sensors which is seeing the ball
  lineBallSensor = ball_sensor;
  lineBallDistance = ball_distance;
  stopFlag = true;

  preparePID(ldir, lspeed);
}
