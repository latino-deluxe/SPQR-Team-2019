#include "imu.h"
#include "interrupt.h"
#include "motors.h"
#include "myspi_old.h"
#include "pid.h"
#include "position.h"
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

void int_nuovo() {
  long t0, dt, at;
  byte sens;
  byte si, sf;

  inchioda(); // al posto di brake, fa 100ms di corsa nella direzione opposta
  t0 = millis();

  tone(BUZZER, 1800);
  do {
    update_sensors_all();
  } while ((millis() - t0) <= 100); // attesa per la frenata di 100ms
  noTone(BUZZER);

  brake();

  sens = 0;
  if (linea[0] == 1)
    sens += 1;
  if (linea[1] == 1)
    sens += 2;
  if (linea[2] == 1)
    sens += 4;
  if (linea[3] == 1)
    sens += 8;
  if (linea[4] == 1)
    sens += 16;
  if (linea[5] == 1)
    sens += 32;

  // DEBUG_PRINT.println(sens);
  // for (int i = 0; i < 4; i++) {
  //   DEBUG_PRINT.print("US: ");
  //   DEBUG_PRINT.print(us_values[i]);
  //   DEBUG_PRINT.print(" | ");
  // }
  // delay(1000);                           //DELAY DI DEBUG: funziona da dio ma
  // scomodo in gioco, meglio fare così:

  /*
   *   Logica: per un secondo, se il sensore palla rimane uguale, ti inchiodi
   *           non sono affatto sicuro che funzioni cos', da controllare in
   * laboratorio
   */

  at = millis();
  do {
    ball_read_position();
    if (inSensorRange(lineBallSensor, byte(1))) {
      readIMU();
      recenter(2.0);
      delay(1);
    } else
      break;
  } while ((millis() - at) <= 1000);

  switch (sens) {
  case 0b000001: // sensori singoli 1

    EXT_LINEA = 210;
    dt = 300;
    break;

  case 0b000010: // sensori singoli 2
    EXT_LINEA = 270;
    dt = 300;
    break;

  case 0b000100: // sensori singoli 3
    EXT_LINEA = 330;
    dt = 300;
    break;

  case 0b001000: // sensori singoli 4
    EXT_LINEA = 30;
    dt = 300;
    break;

  case 0b010000: // sensori singoli 5
    EXT_LINEA = 90;
    dt = 300;
    break;

  case 0b100000: // sensori singoli 6
    EXT_LINEA = 150;
    dt = 300;
    break;

  case 0b000011: // attivati i sensori 1 e 2      // sta uscendo a destra
  case 0b000110: // attivati i sensori 2 e 3
  case 0b000111: // attivati i sensori 1  2 e 3
  case 0b000101:
    dt = 340;
    EXT_LINEA = 270;
    break;

  case 0b110000: // attivati i sensori 5 e 6       // sta uscendo a sinistra
  case 0b011000: //  attivati i sensori 5 e 4
  case 0b111000: //  attivati i sensori 6  5 e 4
  case 0b101000:
    dt = 340;
    EXT_LINEA = 90;
    break;

  case 0b100001: // attivati i sensori 6 1     sta uscendo in avanti
    dt = 360;
    EXT_LINEA = 180;
    break;

  case 0b001100: // attivati i sensori 4 3      sta uscendo indietro
    dt = 340;
    EXT_LINEA = 0;
    break;

  case 0b100010: // attivati 6 2
  case 0b100011: // attivati i sensori 6 2 1   sta in angolo Nord Est
    dt = 340;
    EXT_LINEA = 225;
    break;

  case 0b010001: // attivati 6 5
  case 0b110001: // attivati i sensori 6 5 1   sta in angolo Nord Ovest
    dt = 340;
    EXT_LINEA = 135;
    break;

  case 0b001010: // attivati 4 2
  case 0b001110: // attivati i sensori 4 3 2   sta in angolo Sud Est
    dt = 340;
    EXT_LINEA = 315;
    break;

  case 0b010100: // attivati i sensori 5 3
  case 0b011100: // attivati i sensori 5 4 3     sta in angolo Sud Ovest
    dt = 340;
    EXT_LINEA = 45;
    break;

  case 0b011110: // attivati i sensori 5 4 3 2     sta fuori quasi tutto dietro
    dt = 500;
    EXT_LINEA = 0;
    break;

  case 0b001011: // attivati i sensori 4 2 1
  case 0b001111: // attivati i sensori 4 3 2 1
    dt = 500;
    EXT_LINEA = 315;
    break;

  case 0b110100: // attivati i sensori 6 5 3
  case 0b111100: // attivati i sensori 6 5 4 3
    dt = 500;
    EXT_LINEA = 45;
    break;

  case 0b011001: // attivati i sensori 5 4 1
  case 0b111001: // attivati i sensori 6 5 4 1
    dt = 500;
    EXT_LINEA = 135;
    break;

  case 0b100110: // attivati i sensori 6 3 2
  case 0b100111: // attivati i sensori 6 3 2 1
    dt = 500;
    EXT_LINEA = 225;
    break;

  case 0b110011: // attivati i sensori 6  1  5 e 2 sta fuori quasi tutto avanti
    dt = 500;
    EXT_LINEA = 180;
    break;

  case 0b101111: // attivati i sensori 6  1  2  3  4 sta fuori a destra con solo
                 // 5 in campo
    dt = 600;
    EXT_LINEA = 270;
    break;

  case 0b111101: // attivati i sensori 6  1  3  4  5 sta fuori a sinistra con
                 // solo 2 in campo
    dt = 600;
    EXT_LINEA = 90;
    break;

  case 0b110111: // attivati i sensori 5  6  1  2  3   sta fuori a destra con
                 // solo 4 in campo (angolo NORD EST?)
    dt = 600;
    EXT_LINEA = 220;
    break;

  case 0b111011: // attivati i sensori 4  5  6  1  2   sta fuori a sinistra con
                 // solo 3 in campo (angolo NORD OVEST?)
    dt = 600;
    EXT_LINEA = 120;
    break;

  case 0b111110: // attivati i sensori 6  5  4  3  2  sta fuori indietro con
                 // solo 1 in campo (angolo SUD OVEST?)
    dt = 600;
    EXT_LINEA = 50;
    break;

  case 0b011111: // attivati i sensori 1  2  3  4  5 sta fuori indietro con solo
                 // 6 in campo (angolo SUD EST?)
    dt = 600;
    EXT_LINEA = 310;
    break;

  case 0b000000: // Tutti i sensori sono disattivi interrupt strano (line sensor
                 // =0)?
    // sporco sul campo?
    flag_interrupt = false; // considera conclusa la gestione dell'interrupt
    // Nint = 0;
    // danger = false;
    for (int i = 0; i < 6; i++)
      linea[i] = 0;
    return;
    break;

  case 0b010010: // robot a cavallo della linea con fuori solo o 1,6 oppure 4,3
                 // (attivi 5 e 2)
    if ((ball_sensor > 14) || (ball_sensor < 6))
      EXT_LINEA = 180; // vede la palla in avanti valutare
    if ((ball_sensor > 7) && (ball_sensor < 13))
      EXT_LINEA = 0; // vede la palla dietro valutare
    dt = 400;
    break;

  default: // Si sono attivati 6 sensori o caso non previsto inverto il moto
    dt = 450;
    EXT_LINEA = new_Dir + 180;
    if (EXT_LINEA > 360)
      EXT_LINEA = EXT_LINEA - 360;
    tone(BUZZER, 20000, 500); // avviso che sono uscito
  }

  dt = 320;
  t0 = millis();
  VL_INT = 50;
  do {
    readIMU();
    drivePID(EXT_LINEA, VL_INT);
    if (VL_INT < 255)
      VL_INT++;
    delay(1);
  } while ((millis() - t0) < dt);

  brake();

  for (int i = 0; i < 30; i++) {
    readIMU();
    recenter(1.0);
    delay(10);
  }

  brake();

  for (int i = 0; i < 6; i++)
    linea[i] = 0;
  flag_interrupt = false;
  lineBallSensor = ball_sensor;
}

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
  while (millis() - tline <= 700) { // prima 500
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
    // Va nella direzione opposta a quella a qui stava andando con goalie o
    // space_invaders globalDir + 180 lo sposta di mezza circonferenza
    // goniometria, %360 lo riporta nel primo giro
    ldir = (globalDir + 180) % 360;
    drivePID(ldir, lspeed);
    delay(10);
  }

  flag_interrupt = false;
}
