#include "interrupt.h"
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
    stopFlag = true;
    return;
  }
  // else {
  //   tline = 0;
  //   // if the current sensor is in a range of sensors from the one that seen the
  //   // ball, just stop
    if (stopFlag) {
      if (inSensorRange(lineBallSensor, (byte) 1)) {
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

  //old version
  
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


  //new version
  //calcolo dell'angolo della linea
  // float angle = atan2(y,x) * 180 / 3.14; 						//atan2 restituisce i gradi in [-180,+180] e seguendo la circonf. goniometrica.
  //
  // int map_angle = 0;
  // map_angle = (int)angle;
  // map_angle = -(angle) + 90;                        //Conversione + cambio di rotazione = nord 0 gradi, senso orario positivo.
  // map_angle = (map_angle +360) % 360; 							//per rientrare nel [0,360]
  //
  // int corrected_angle = map_angle;
  // corrected_angle = corrected_angle - imu_current_euler;	//tolgo la rotazione del robot all'angolo della linea
  // corrected_angle = (corrected_angle +360) % 360; 				//per rientrare nel [0,360]
  //
  // int out_direction = corrected_angle;
  // out_direction = out_direction + 180; 							//trovo opposto all'angolo calcolato
  // out_direction = (out_direction +360)% 360; 				//per rientrare nel [0,360]
  //
  // ldir = out_direction;

  // saves the ball sensors which is seeing the ball
  lineBallSensor = ball_sensor;
  lineBallDistance = ball_distance;
  stopFlag = true;

  preparePID(ldir, lspeed);
}

bool inSensorRange(byte sensor, byte range) {
  // BT.println(lineBallSensor);
  for (int i = 0; i <= range; i++) {
    // BT.print(getSensorIndex(sensor - i));
    // BT.print(" | ");
    // BT.println(getSensorIndex(sensor + i))
    if (ball_sensor == getSensorIndex(sensor - i) || ball_sensor == getSensorIndex(sensor + i)) {
      return true;
    }
  }
  return false;
}

byte getSensorIndex(byte sensor) {
  sensor = sensor % 20;
  return sensor < 0 ? (byte)(20 + sensor) : (byte)(sensor);
}

// handles the interrupt the old way around, using the switch case
void handleInterruptNew() {
  byte line = 0;
  int dir, speed = 150;

  for (int i = 0; i < INT_LUNG; i++) {
    line |= linea[i] << i;
  }

  if (line == 0)
    return;

  switch (line) {

    // VEDI BIBBIA ROSSA

  case 1:
    dir = 190;
    break;
  case 2:
    dir = 270;
    break;
  case 4:
    dir = 340;
    break;
  case 8:
    dir = 30;
    break;
  case 16:
    dir = 90;
    break;
  case 32:
    dir = 170;
    break;

  case 33:
    dir = 180;
    break;

  case 12:
    dir = 0;
    break;

  case 35:
    dir = 225;
    break;
  case 49:
    dir = 135;
    break;
  case 14:
    dir = 315;
    break;
  case 28:
    dir = 60;
    break;

  case 3:
  case 6:
  case 7:
    dir = 270;
    break;

  case 48:
  case 24:
  case 56:
    dir = 90;
    break;

  default:
    speed = 0;
  }

  preparePID(dir, speed);
}
