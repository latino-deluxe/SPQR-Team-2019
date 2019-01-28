#include "goalie.h"
#include "imu.h"
#include "motors.h"
#include "pid.h"
#include "position.h"
#include "us.h"
#include "myspi_old.h"
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

  Lx_mis = us_dx + us_sx + robot; // larghezza totale stimata
  Ly_mis = us_fr + us_px + robot; // lunghezza totale stimata

  // controllo orizzontale
  if ((Lx_mis < Lx_max) && (Lx_mis > Lx_min) && (us_dx > 25) &&
      (us_sx > 25)) // se la misura orizzontale é accettabile
  {
    good_field_x = true;
    status_x = CENTRO;
    if (us_dx < DxF)
      status_x = EST; // robot é vicino al bordo destro
    if (us_sx < DxF)
      status_x = OVEST; // robot é vicino al bordo sinistro

    if (status_x == CENTRO) {
      Ly_min = LyP_min; // imposto limiti di controllo lunghezza verticale tra
                        // le porte
      Ly_max = LyP_max;
      Dy = DyP;
    } else {
      Ly_min =
          LyF_min; // imposto limiti di controllo lunghezza verticale in fascia
      Ly_max = LyF_max;
      Dy = DyF;
    }
  } else {
    // la misura non é pulita per la presenza di un ostacolo
    if ((us_dx >= (DxF + 10)) ||
        (us_sx >= (DxF + 10))) // se ho abbastanza spazio a destra o a sinistra
    {
      status_x = CENTRO; // devo stare per forza al cento
      Ly_min = LyP_min;  // imposto limiti di controllo lunghezza verticale tra
                         // le porte
      Ly_max = LyP_max;
      Dy = DyP;
    } else {
      status_x = 255; // non so la coordinata x
      // imposto i limiti di controllo verticale in base alla posizione
      // orizzontale precedente
      if (old_status_x == CENTRO) // controlla la posizione precedente per
                                  // decidere limiti di controllo y
      {
        Ly_min = LyP_min; // imposto limiti di controllo lunghezza verticale tra
                          // le porte
        Ly_max = LyP_max;
        Dy = DyP;
      } else {
        Ly_min = LyF_min; // imposto limiti di controllo lunghezza verticale in
                          // fascia anche per x incognita
        Ly_max = LyF_max;
        Dy = DyF;
      }
    }
  }
  // controllo verticale
  if ((Ly_mis < Ly_max) &&
      (Ly_mis > Ly_min)) // se la misura verticale é accettabile
  {
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

void ritornacentro() // lavora su guessedlocation
{
  if (status_x == EST) {
    if (status_y == SUD) {
      drivePID(330, VEL_RET);
    } else if (status_y == CENTRO) {
      drivePID(270, VEL_RET);
    } else if (status_y == NORD) {
      drivePID(225, VEL_RET);
    } else { // non conosco la y
      recenter(1.0);
    }
  }
  if (status_x == OVEST) {
    if (status_y == SUD) {
      drivePID(45, VEL_RET);
    } else if (status_y == CENTRO) {
      drivePID(90, VEL_RET);
    } else if (status_y == NORD) {
      drivePID(135, VEL_RET);
    } else { // non conosco la y
      recenter(1.0);
    }
  }
  if (status_x == CENTRO) {
    if (status_y == SUD) {
      drivePID(0, VEL_RET);
    } else if (status_y == CENTRO) {
      recenter(1.0);
    } else if (status_y == NORD) {
      drivePID(180, VEL_RET);
    } else { // non conosco la y
      recenter(1.0);
    }
  }
  if (status_x == 255) {
    if (status_y == SUD) {
      drivePID(0, VEL_RET);

    } else if (status_y == CENTRO) {
      recenter(1.0);

    } else if (status_y == NORD) {
      drivePID(180, VEL_RET);

    } else { // non conosco la y
      recenter(1.0);
    }
  }
  return;
}

void fuga_centro() {
  long t0;

  if (status_x == 255 && status_y == 255) // non so dove sto
  {
    do {
      brake(); // sto fermo in attesa di conoscere la x o la y meglio se guardo
               // anche la palla
      update_sensors_all();
      update_location_complete();
      delay(1);
    } while (status_x == 255 && status_y == 255);
  }

  if (status_x != 255 && status_y != 255) // conosco sia la x che la y
  {
    for (byte i = 0; i < 200; i++) {
      update_sensors_all(); // serve per avere imu_current_euler aggiornata e
                            // gli ultrasuoni
      update_location_complete(); //  vede  dove si trova
      ritornacentro(); //  ritorna al centro del campo per circa 200+ ms
      delay(1);
    }
  } else // conosco per lo meno una coordinata
  {
    t0 = millis();       // istante inizio ricentra piano solo su una coordinata
    if (status_x != 255) // conosco la x
    {
      do {
        switch (status_x) {
        case EST:
          drivePID(270, 100);
          delay(10);
          break;
        case OVEST:
          drivePID(90, 100);
          delay(10);
          break;
        }
        update_sensors_all();
        WhereAmI();
      } while ((status_x != CENTRO) && ((millis() - t0) < 200));
    } else // conosco la y
    {
      do {
        switch (status_y) {
        case NORD:
          drivePID(180, 100);
          delay(10);
          break;
        case SUD:
          drivePID(0, 100);
          delay(10);
          break;
        }
        update_sensors_all();
        WhereAmI();
      } while ((status_y != CENTRO) && ((millis() - t0) < 200));
    }
  }
  return;
}

void ritornaporta(int posizione) // chiamata da gestione portiere
{
  if (posizione == 255) {
    recenter(1.0);
  } else {
    switch (posizione) {
    case NORD_CENTRO:
      drivePID(180, VEL_RET);
      break;
    case NORD_EST:
      drivePID(210, VEL_RET);
      break;
    case NORD_OVEST:
      drivePID(150, VEL_RET);
      break;
    case SUD_CENTRO:
      recenter(1.0);
      break;
    case SUD_EST:
      drivePID(270, VEL_RET);
      break;
    case SUD_OVEST:
      drivePID(90, VEL_RET);
      break;
    case CENTRO_CENTRO:
      drivePID(180, VEL_RET);
      break;
    case CENTRO_EST:
      drivePID(270, VEL_RET);
      break;
    case CENTRO_OVEST:
      drivePID(90, VEL_RET);
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

void centroporta() {
  int larghezza = 0;
  if (status_x == CENTRO) {
    if (status_y == CENTRO) {
      drivePID(180, 150);
    }
    else if (status_y == SUD) {
      if (us_px > 20) drivePID(180, 110);
      else if (us_px < 15) drivePID(0, 130);
      else recenter(1.0);
    }
    else ritornacentro();
  }
  else if (status_x == 255) {
    if (us_px > 50) drivePID(180, 110);
    else if (us_px < 30) drivePID(0, 130);
    else recenter(1.0);
  }
  else ritornacentro();
}

void testPosition(){
  update_sensors_all();
  WhereAmI();
  Serial.print("Measured location:\t");
  Serial.print(status_x);
  Serial.print(" | ");
  Serial.println(status_y);
}

int zone[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

void testGuessZone(){
  guessZone();
  Serial.println("-----------------");

    for(int j = 0; j < 3; j++){
    for(int i = 0; i < 3; i++){
        Serial.print(zone[i][j]);
        Serial.print(" | ");
      }
      Serial.println();
    }
  Serial.println("-----------------");
  Serial.print("Guessed location:\t");
  Serial.print(guessed_x);
  Serial.print(" | ");
  Serial.println(guessed_y);
}

void guessZone(){
  updateGuessZone();
  int top = 0;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(zone[i][j] > top){
        guessed_x = i;
        guessed_y = j;
      }
    }
  }
}

void updateGuessZone(){
  if(status_x == 255 && status_y != 255){
    for(int i = 0; i < 3; i++){
      if(zone[i][status_y] < 150)
        zone[i][status_y] += 2;
    }
  }else if(status_x != 255 && status_y == 255){
    for(int i = 0; i < 3; i++){
      if(zone[status_x][i] < 150)
        zone[status_x][i] += 2;
    }
  }else{
    if(zone[status_x][status_y] < 150)
      zone[status_x][status_y] += 6;
  }

  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(zone[i][j]-1 >= 0)
        zone[i][j]-=1;
    }
  }
}
