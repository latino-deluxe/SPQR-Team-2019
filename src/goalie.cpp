#include "goalie.h"
#include "myspi_old.h"
#include "pid.h"
#include "position.h"
#include "us.h"
#include "vars.h"
#include <Arduino.h>

void goalie() {
  // directions going around the ball
  int goaliedirection[20] = {AA0,  AA1,  AA2,  AA3,  AA4,  AA5,  AA6,
                             AA7,  AA8,  AA9,  AA10, AA11, AA12, AA13,
                             AA14, AA15, AA16, AA17, AA18, AA19};

  atk_speed = 180; // forse inutile, lo imposto per livellare
  atk_direction =
      goaliedirection[ball_sensor]; // going around the ball (inseguo la palla)

  // PALLA DIETRO
  palla_dietro();

  // STORCIMENTO (senza camera, alla vecchia maniera) FUNZNONA
  // storcimentoZone();

  // CENTROPORTA CON CAMERA
  storcimentoPorta();
  // CENTROPORTA CON CAMERA
  // storcimentoPorta();

  atk_direction = atk_direction + atk_offset;

  preparePID(atk_direction, atk_speed);
}

void palla_dietro() {
  if (ball_sensor == 9 || ball_sensor == 10 || ball_sensor == 11) {
    if (ball_distance < 4) { // se la palla è vicina decido come muovermi in
                             // base alla zona per non uscire
      atk_speed = 200;
      if (zoneIndex == 8 || zoneIndex == 5 || zoneIndex == 2)
        atk_direction = 225;
      if (zoneIndex == 0 || zoneIndex == 3 || zoneIndex == 9)
        atk_direction = 135;
      if (zoneIndex == 1 || zoneIndex == 4 || zoneIndex == 7)
        atk_direction = 250;
    } else if (ball_distance >= 4) { // se la palla è lontana mi avvicino più
                                     // velocemente con angolo più stretto
      atk_speed = 230;
      if (zoneIndex == 8 || zoneIndex == 5 || zoneIndex == 2)
        atk_direction = 200;
      if (zoneIndex == 0 || zoneIndex == 3 || zoneIndex == 9)
        atk_direction = 160;
      if (zoneIndex == 1 || zoneIndex == 4 || zoneIndex == 7)
        atk_direction = 180;
    } else if (ball_distance <
               2) { // se la palla è incredibilmente vicina VIRI ESTREMO
      atk_speed = 255;
      if (zoneIndex == 8 || zoneIndex == 5 || zoneIndex == 2)
        atk_direction = 270;
      if (zoneIndex == 0 || zoneIndex == 3 || zoneIndex == 9)
        atk_direction = 90;
      if (zoneIndex == 1 || zoneIndex == 4 || zoneIndex == 7)
        atk_direction = 100;
    }
  }
}

void palla_dietroP() {
  if (ball_sensor == 9 || ball_sensor == 10 || ball_sensor == 11) {
    if (ball_distance < 4) { // se la palla è vicina decido come muovermi in
                             // base alla zona per non uscire
      atk_speed = 200;
      if (zoneIndex == 8 || zoneIndex == 5 || zoneIndex == 2)
        atk_direction = 225;
      if (zoneIndex == 0 || zoneIndex == 3 || zoneIndex == 9)
        atk_direction = 135;
      if (zoneIndex == 1 || zoneIndex == 4 || zoneIndex == 7)
        atk_direction = 250;
    } else if (ball_distance >= 4) { // se la palla è lontana mi avvicino più
                                     // velocemente con angolo più stretto
      atk_speed = 230;
      if (zoneIndex == 8 || zoneIndex == 5 || zoneIndex == 2)
        atk_direction = 200;
      if (zoneIndex == 0 || zoneIndex == 3 || zoneIndex == 9)
        atk_direction = 160;
      if (zoneIndex == 1 || zoneIndex == 4 || zoneIndex == 7)
        atk_direction = 180;
    } else if (ball_distance <
               2) { // se la palla è incredibilmente vicina VIRI ESTREMO
      atk_speed = 255;
      if (zoneIndex == 8 || zoneIndex == 5 || zoneIndex == 2)
        atk_direction = 270;
      if (zoneIndex == 0 || zoneIndex == 3 || zoneIndex == 9)
        atk_direction = 90;
      if (zoneIndex == 1 || zoneIndex == 4 || zoneIndex == 7)
        atk_direction = 100;
    }
  }
  preparePID(atk_direction, atk_speed);
}

void storcimentoZone() {
  if (ball_distance < 2) {
    if (ball_sensor == 19 || ball_sensor == 0 || ball_sensor == 1) {
      atk_speed = 255;
      if (zoneIndex == 0)
        atk_offset = 90;
      if (zoneIndex == 1)
        atk_offset = 0;
      if (zoneIndex == 2)
        atk_offset = -90;
    }
  } else {
    atk_offset = 0;
  }
}

void storcimentoPorta() {
<<<<<<< HEAD
  /*------VECCHIO SISTEMA CON BOOLEANE------*/

  // if(x>160) XP_SX=true;      //porta a sinistra del robot
  // else XP_SX=false;
  // if(x<35) XP_DX=true;      //porta a destra del robot
  // else XP_DX=false;
  // if(x==999) {
  //   if(status_x==EST) XP_SX==true;
  //   if(status_x==OVEST) XP_DX==true;
  // }

  /*------PROVA CON DATO DINAMICO------*/
  // se per esempio il nostro centro della porta è 125
  // impostiamo uno storcimento dinamico in base a quanto il numero
  //è grande/piccolo da 125
  // esempio su codice:
  x = x - centrop;
  atk_offset = x;
  == == == =
               /*------VECCHIO SISTEMA CON BOOLEANE------*/

      // if(x>160) XP_SX=true;      //porta a sinistra del robot
      // else XP_SX=false;
      // if(x<35) XP_DX=true;      //porta a destra del robot
      // else XP_DX=false;
      // if(x==999) {
      //   if(status_x==EST) XP_SX==true;
      //   if(status_x==OVEST) XP_DX==true;
      // }

      /*------PROVA CON DATO DINAMICO------*/
      // se per esempio il nostro centro della porta è 125
      // impostiamo uno storcimento dinamico in base a quanto il numero
      //è grande/piccolo da 113
      // esempio su codice:

      // tone(BUZZER, 120000, 150);

      portx = portx - centrop;
  atk_offset = portx;
>>>>>>> a101796eb1626df179e98e23b834fd659a80ce63
}
