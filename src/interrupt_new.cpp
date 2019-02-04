#include "vars.h"
#include "interrupt.h"
#include "pid.h"
#include <math.h>
#include <Arduino.h>

//Degrees: 60, 0, 300, 240, 180,120
float lCosins[INT_LUNG] = {0.5, 1, 0.5, -0.5, -1, -0.5};
float lSins[INT_LUNG] = {0.866, 0, -0.866, -0.866, 0, 0.866};
unsigned long tline = 0;

bool stopFlag = false;

int ldir =0; int lspeed = 150;
byte lineBallSensor = 0;

void handleInterruptTrigonometry(){

  if(millis() - tline < 250) {
    preparePID(ldir,lspeed);
    return;
  }else{
    tline = 0;
    if(stopFlag) {
      if(ball_sensor == getSensorIndex(lineBallSensor-2) && ball_sensor <= lineBallSensor+2){
        preparePID(0,0);
        return;
      }
      stopFlag = false;
    }
  }

  byte line = 0;

  for(int i = 0; i < INT_LUNG; i++){
    line |= linea[i] << i;
  }

  if(line == 0) return;

  tline = millis();
  float x = 0, y = 0;

  for(int i = 0; i < INT_LUNG; i++){
      if(linea[i] == 1){
        x += lCosins[i];
        y += lSins[i];
      }
  }

  //l'angolo con cui devo tornare
  float angle = atan2(y,x) * 180 / 3.14;
  int map_angle = 0;
  if(angle < 0) angle += 360;
  map_angle = ((int)(angle - 90)) % 360;

  map_angle = -map_angle;
  ldir = ((int)map_angle + 180) % 360;

  ldir -= imu_current_euler;
  ldir = ldir < 0 ? ldir+=360 : ldir;
  // Serial.print(map_angle);
  // Serial.print(" | ");
  // Serial.println(dir);

  //segna sensore
  lineBallSensor = ball_sensor;
  stopFlag = true;
  preparePID(ldir, lspeed);
}

bool inSensorRange(byte sensor, int range){
  for(int i = 0; i <= range; i++){
    if(ball_sensor == getSensorIndex(sensor-i) || ball_sensor == getSensorIndex(sensor+i)){
      return true;
    }
  }
  return false;
}

byte getSensorIndex(byte sensor){
  if(sensor > 19){
    return sensor-20;
  }else if(sensor < 0){
    return abs(sensor%20);
  }
}

void handleInterruptNew(){

  byte line = 0;
  int dir, speed = 150;

  for(int i = 0; i < INT_LUNG; i++){
    line |= linea[i] << i;
  }

  if(line == 0) return;

  switch(line){

    //VEDI BIBBIA ROSSA

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
