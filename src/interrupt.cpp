#include "imu.h"
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
unsigned long tstop = 0;

bool stopFlag = false;

// byte lineBallSensor = 0;
int ldir = 0, lspeed = 180;

// brand new way to handle the interrupt: trigonometry!
void handleInterruptTrigonometry() {

  if (stopFlag) {
    if (inSensorRange(lineBallSensor, (byte)1)/* && millis() - tstop < 1500 && ball_distance <= lineBallDistance*/) {
      drivePID(0, 0);
      return;
    }
    stopFlag = false;
    flag_interrupt = false;
  }

  byte line = 0;
  // constructs a complete byte using the array that stores the interrupt data
  for (int i = 0; i < INT_LUNG; i++) {
    line |= linea[i] << i;
  }

  if (line == 0)
    return;

  // interpolates the data with sine and cosine and using atan2 construct an
  // angle of exit

  float x = 0, y = 0;

  for (int i = 0; i < INT_LUNG; i++) {
    if (linea[i] == 1) {
      x += lCosins[i];
      y += lSins[i];
    }
  }

  // new version
  // calcolo dell'angolo della linea
  float angle = atan2(y, x) * 180 / 3.14;
  int map_angle = 0;
  map_angle = -(angle) + 90;
  int corrected_angle = map_angle;
  corrected_angle = corrected_angle - imu_current_euler;

  int out_direction = corrected_angle;
  out_direction = out_direction + 180;
  ldir = out_direction;

  tline = millis();
  while (millis() - tline <= 500) {
    readIMU();
    drivePID(ldir, lspeed);
    delay(10);
  }

  // saves the ball sensors which is seeing the ball
  stopFlag = true;
  lineBallSensor = ball_sensor;
  lineBallDistance = ball_distance;
}

/*Per Ematino che oggi è l'unico che può
  Controlla se così funziona:
  Semplicemente quando vede interrupt va nella direzione opposta a dove stava
  andando. Il punto è che nel frattempo potrebbe beccare altri interrupt,
  dovresti provare a vedere una specie di blocco da impostargli finché non
  risolve questo. Ho aggiunto il brakeI() nelle funzioni chiamate dagli
  interrupt
  
  -Emaletta
*/
void handleInterruptEasy() {
  tline = millis();
  while (millis() - tline <= 500) {
    readIMU();
    // Va nella
    ldir = (globalDir + 180) % 360;
    drivePID(ldir, lspeed);
    delay(10);
  }

  flag_interrupt = false;
}
