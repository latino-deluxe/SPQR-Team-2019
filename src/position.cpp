#include "goalie.h"
#include "imu.h"
#include "motors.h"
#include "myspi_old.h"
#include "pid.h"
#include "position.h"
#include "us.h"
#include "vars.h"
#include <Arduino.h>

void WhereAmI() {
  // determines horizontal and vertical position
  // Updates flags:  good_field_x  good_field_y      not used in other routines
  //                 goal_zone                       not used in other routines
  // Updates vars:
  //                 status_x (con valori CENTRO EST  OVEST 255  = non lo so)
  //                 status_y (con valori CENTRO NORD SUD   255  = non lo so)

  int Lx_mis; // total width, estmated from measures
  int Ly_mis; // total length, estimated from measures
  int Ly_min; // Limite inferiore con cui confrontare la misura y
  int Ly_max; // Limite inferiore con cui confrontare la misura y
  int Dy;     // Limite per decidere NORD SUD in funzione della posizione orizzontale

  old_status_x = status_x;
  old_status_y = status_y;
  good_field_x = false; // non é buona x (bad x)
  good_field_y = false; // non é buona y (bad y)
  goal_zone = false;    // im not in front of the opponent's goalpost

  Lx_mis = us_dx + us_sx + robot;     // estimated total width
  Ly_mis = us_fr + us_px + robot;     // estimated total length

  // horizontal checking
  if ((Lx_mis < Lx_max) && (Lx_mis > Lx_min) && (us_dx > 25) && (us_sx > 25)) {
    // if the horizontal measure is acceptable
    good_field_x = true;
    status_x = CENTRO;
    if (us_dx < DxF)        // robot is near the right margin
      status_x = EST;
    if (us_sx < DxF)        // robot is near th left margin
      status_x = OVEST;

    if (status_x == CENTRO) {
      // imposto limiti di controllo lunghezza verticale tra le porte
      Ly_min = LyP_min;
      Ly_max = LyP_max;
      Dy = DyP;
    } else {
      // imposto limiti di controllo lunghezza verticale in fascia
      Ly_min = LyF_min;
      Ly_max = LyF_max;
      Dy = DyF;
    }
  } else {
    // the measure isn't accurate because there is an obstacle
    if ((us_dx >= (DxF + 10)) || (us_sx >= (DxF + 10)) {
      // if i have enough space on the left and on the right, im in the cente
      status_x = CENTRO;
      // imposto limiti di controllo lunghezza verticale tra le porte
      Ly_min = LyP_min;
      Ly_max = LyP_max;
      Dy = DyP;
    } else {
      status_x = 255;
      // i don't know the x coordinate
      // imposto i limiti di controllo verticale in base alla posizione orizzontale precedente
      if (old_status_x == CENTRO) {
        // controlla la posizione precedente per decidere limiti di controllo y
        // imposto limiti di controllo lunghezza verticale tra le porte
        Ly_min = LyP_min;
        Ly_max = LyP_max;
        Dy = DyP;
      } else {
        // imposto limiti di controllo lunghezza verticale in fascia anche per x incognita
        Ly_min = LyF_min;
        Ly_max = LyF_max;
        Dy = DyF;
      }
    }
  }
  // vertical checking
  if ((Ly_mis < Ly_max) && (Ly_mis > Ly_min)) {
    // if the vertical measure is acceptable
    good_field_y = true;
    status_y = CENTRO;
    if (us_fr < Dy) {
      status_y = NORD; // robot is near to the opponent's goalpost
      if (Dy == DyP)
        goal_zone = true; // in front of the goalpost in goal zone
    }
    if (us_px < Dy)
      status_y = SUD; // robot is near its goalpost
  } else {
    // the measure isn't accurate because there is an obstacle
    status_y = 255;                      // i don't know the y coordinate
    if (us_fr >= (Dy + 0))
      status_y = CENTRO;                 // if i have enough space in the front or in the back
    if (us_px >= (Dy + 0))
      status_y = CENTRO;                 // probably it's in the center
  }
  return;
}

void goCenter() {
  if (status_x == EST) {
    if (status_y == SUD) {
      preparePID(330, VEL_RET);
    } else if (status_y == CENTRO) {
      preparePID(270, VEL_RET);
    } else if (status_y == NORD) {
      preparePID(225, VEL_RET);
    } else { //i don't know the y
      preparePID(0,0);
    }
  }
  if (status_x == OVEST) {
    if (status_y == SUD) {
      preparePID(45, VEL_RET);
    } else if (status_y == CENTRO) {
      preparePID(90, VEL_RET);
    } else if (status_y == NORD) {
      preparePID(135, VEL_RET);
    } else { //i don't know the y
      preparePID(0,0);
    }
  }
  if (status_x == CENTRO) {
    if (status_y == SUD) {
      preparePID(0, VEL_RET);
    } else if (status_y == CENTRO) {
      preparePID(0,0);
    } else if (status_y == NORD) {
      preparePID(180, VEL_RET);
    } else { //i don't know the y
      preparePID(0,0);
    }
  }
  if (status_x == 255) {
    if (status_y == SUD) {
      preparePID(0, VEL_RET);

    } else if (status_y == CENTRO) {
      preparePID(0,0);

    } else if (status_y == NORD) {
      preparePID(180, VEL_RET);

    } else { //i don't know the y
      preparePID(0,0);
    }
  }
  return;
}

// called by keeper
void goGoalPost(int posizione) {
  if (posizione == 255) {
    preparePID(0, 0);
  } else {
    switch (posizione) {
    case NORTH_CENTER:
      preparePID(180, VEL_RET);
      break;
    case NORTH_EAST:
      preparePID(210, VEL_RET);
      break;
    case NORTH_WEST:
      preparePID(150, VEL_RET);
      break;
    case SOUTH_CENTER:
      preparePID(0, 0);
      break;
    case SOUTH_EAST:
      preparePID(270, VEL_RET);
      break;
    case SOUTH_WEST:
      preparePID(90, VEL_RET);
      break;
    case CENTER_CENTER:
      preparePID(180, VEL_RET);
      break;
    case CENTER_EAST:
      preparePID(270, VEL_RET);
      break;
    case CENTER_WEST:
      preparePID(90, VEL_RET);
      break;
    }
  }
  return;
}

void update_sensors_all() {
  ball_read_position();
  readIMU();
  readUS();
  return;
}

void testPosition() {
  update_sensors_all();
  WhereAmI();
  DEBUG_PRINT.print("Measured location:\t");
  DEBUG_PRINT.print(status_x);
  DEBUG_PRINT.print(" | ");
  DEBUG_PRINT.println(status_y);
}

int zone[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

void testGuessZone() {
  guessZone();
  Serial.println("-----------------");

  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 3; i++) {
      DEBUG_PRINT.print(zone[i][j]);
      DEBUG_PRINT.print(" | ");
    }
    DEBUG_PRINT.println();
  }
  DEBUG_PRINT.println("-----------------");
  DEBUG_PRINT.print("Guessed location:\t");
  DEBUG_PRINT.print(guessed_x);
  DEBUG_PRINT.print(" | ");
  DEBUG_PRINT.println(guessed_y);
}

void guessZone() {
  updateGuessZone();
  int top = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (zone[i][j] > top) {
        guessed_x = i;
        guessed_y = j;
      }
    }
  }
}

void updateGuessZone() {
  if (status_x == 255 && status_y != 255) {
    for (int i = 0; i < 3; i++) {
      if (zone[i][status_y] < 150)
        zone[i][status_y] += 2;
    }
  } else if (status_x != 255 && status_y == 255) {
    for (int i = 0; i < 3; i++) {
      if (zone[status_x][i] < 150)
        zone[status_x][i] += 2;
    }
  } else {
    if (zone[status_x][status_y] < 150)
      zone[status_x][status_y] += 6;
  }

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (zone[i][j] - 1 >= 0)
        zone[i][j] -= 1;
    }
  }
}

unsigned long ao;  //dunno how to translate it, halp

void gigaTestZone() {
  update_sensors_all();
  WhereAmI();
  guessZone();

  if (millis() - ao >= 100) {
    DEBUG_PRINT.println("------");
    for (int i = 0; i < 4; i++) {
      DEBUG_PRINT.print("US: ");
      DEBUG_PRINT.print(us_values[i]);
      DEBUG_PRINT.print(" | ");
    }
    DEBUG_PRINT.println();
    testPosition();
    testGuessZone();

    DEBUG_PRINT.println("------");
    ao = millis();
  }
}

// gives zoneIndex based on guessed and measured zone
void calculateZoneIndex() {
  int x, y;

  if (status_x == 255) {
    x = guessed_x;
  } else {
    x = status_x;
  }

  if (status_y == 255) {
    y = guessed_y;
  } else {
    y = status_y;
  }

  zoneIndex = y * 3 + x;
}
