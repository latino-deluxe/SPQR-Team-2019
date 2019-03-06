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
  // decide la posizione in orizzontale e verticale
  // Aggiorna i flag :  good_field_x  good_field_y      non utilizzata da altre
  // routines
  //                    goal_zone                       non utilizzata da altre
  //                    routines
  // Aggiorna le variabili:
  //                    status_x (con valori CENTRO EST  OVEST 255  = non lo so)
  //                    status_y (con valori CENTRO NORD SUD   255  = non lo so)

  int Lx_mis; // larghezza totale stimata dalle misure
  int Ly_mis; // lunghezza totale stimata dalle misure
  int Ly_min; // Limite inferiore con cui confrontare la misura y
  int Ly_max; // Limite inferiore con cui confrontare la misura y
  int Dy;     // Limite per decidere NORD SUD in funzione della posizione
              // orizzontale

  old_status_x = status_x;
  old_status_y = status_y;
  good_field_x = false; // non é buona x
  good_field_y = false; // non é buona y
  goal_zone = false;    // non sono davanti alla porta avversaria

  if (role == HIGH)
    DxF = DxF_Atk;
  else
    DxF = DxF_Def;

  Lx_mis = us_dx + us_sx + robot; // larghezza totale stimata
  Ly_mis = us_fr + us_px + robot; // lunghezza totale stimata

  // controllo orizzontale
  if ((Lx_mis < Lx_max) && (Lx_mis > Lx_min) && (us_dx > 25) && (us_sx > 25)) {
    // se la misura orizzontale é accettabile
    good_field_x = true;
    status_x = CENTRO;
    if (us_dx < DxF) // robot é vicino al bordo destro
      status_x = EST;
    if (us_sx < DxF) // robot é vicino al bordo sinistro
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
    // la misura non é pulita per la presenza di un ostacolo
    if ((us_dx >= (DxF + 10)) || (us_sx >= (DxF + 10))) {
      // se ho abbastanza spazio a destra o a sinistra
      // devo stare per forza al cento
      status_x = CENTRO;
      // imposto limiti di controllo lunghezza verticale tra le porte
      Ly_min = LyP_min;
      Ly_max = LyP_max;
      Dy = DyP;
    } else {
      status_x = 255;
      // non so la coordinata x
      // imposto i limiti di controllo verticale in base alla posizione
      // orizzontale precedente
      if (old_status_x == CENTRO) {
        // controlla la posizione precedente per decidere limiti di controllo y
        // imposto limiti di controllo lunghezza verticale tra le porte
        Ly_min = LyP_min;
        Ly_max = LyP_max;
        Dy = DyP;
      } else {
        // imposto limiti di controllo lunghezza verticale in fascia anche per x
        // incognita
        Ly_min = LyF_min;
        Ly_max = LyF_max;
        Dy = DyF;
      }
    }
  }
  // controllo verticale
  if ((Ly_mis < Ly_max) && (Ly_mis > Ly_min)) {
    // se la misura verticale é accettabile
    good_field_y = true;
    status_y = CENTRO;
    if (us_fr < Dy) {
      status_y = NORD; // robot é vicino alla porta avversaria
      if (Dy == DyP)
        goal_zone = true; //  davanti alla porta in zona goal
    }
    if (us_px < Dy)
      status_y = SUD; // robot é vicino alla propria porta
  } else {
    // la misura non é pulita per la presenza di un ostacolo
    status_y = 255; // non so la coordinata y
    if (us_fr >= (Dy + 0))
      status_y = CENTRO; // ma se ho abbastanza spazio dietro o avanti
    if (us_px >= (Dy + 0))
      status_y = CENTRO; //  e'probabile che stia al centro
  }
  return;
}

void goCenter() {

  // if (status_x == EST) {
  //   if (status_y == SUD) {
  //     preparePID(330, VEL_RET);
  //   } else if (status_y == CENTRO) {
  //     preparePID(270, VEL_RET);
  //   } else if (status_y == NORD) {
  //     preparePID(225, VEL_RET);
  //   } else { // non conosco la y
  //     preparePID(0, 0);
  //   }
  // }
  // if (status_x == OVEST) {
  //   if (status_y == SUD) {
  //     preparePID(45, VEL_RET);
  //   } else if (status_y == CENTRO) {
  //     preparePID(90, VEL_RET);
  //   } else if (status_y == NORD) {
  //     preparePID(135, VEL_RET);
  //   } else { // non conosco la y
  //     preparePID(0, 0);
  //   }
  // }
  // if (status_x == CENTRO) {
  //   if (status_y == SUD) {
  //     preparePID(0, VEL_RET);
  //   } else if (status_y == CENTRO) {
  //     preparePID(0, 0);
  //   } else if (status_y == NORD) {
  //     preparePID(180, VEL_RET);
  //   } else { // non conosco la y
  //     preparePID(0, 0);
  //   }
  // }
  // if (status_x == 255) {
  //   if (status_y == SUD) {
  //     preparePID(0, VEL_RET);
  //
  //   } else if (status_y == CENTRO) {
  //     preparePID(0, 0);
  //
  //   } else if (status_y == NORD) {
  //     preparePID(180, VEL_RET);
  //
  //   } else { // non conosco la y
  //     preparePID(0, 0);
  //   }
  // }

  if (zoneIndex == 8)
    preparePID(330, 180);
  if (zoneIndex == 7)
    preparePID(0, 180);
  if (zoneIndex == 6)
    preparePID(45, 180);
  if (zoneIndex == 5)
    preparePID(270, 180);
  if (zoneIndex == 4)
    preparePID(0, 0);
  if (zoneIndex == 3)
    preparePID(90, 180);
  if (zoneIndex == 2)
    preparePID(255, 180);
  if (zoneIndex == 1)
    preparePID(180, 180);
  if (zoneIndex == 0)
    preparePID(135, 180);

  return;
}

// called by keeper
void goGoalPost(int posizione) {
  if (posizione == 255) {
    preparePID(0, 0);
  } else {
    switch (posizione) {
    case NORD_CENTRO:
      preparePID(180, VEL_RET);
      break;
    case NORD_EST:
      preparePID(210, VEL_RET);
      break;
    case NORD_OVEST:
      preparePID(150, VEL_RET);
      break;
    case SUD_CENTRO:
      preparePID(0, 0);
      break;
    case SUD_EST:
      preparePID(270, VEL_RET);
      break;
    case SUD_OVEST:
      preparePID(90, VEL_RET);
      break;
    case CENTRO_CENTRO:
      preparePID(180, VEL_RET);
      break;
    case CENTRO_EST:
      preparePID(270, VEL_RET);
      break;
    case CENTRO_OVEST:
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

  ball_read_position();
  readIMU();
  readUS();

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

unsigned long ao;

void gigaTestZone() {
  ball_read_position();
  readIMU();
  readUS();
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
