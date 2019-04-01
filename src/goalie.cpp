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

  // PALLA DIETRO
  palla_dietro();

  atk_direction =
      goaliedirection[ball_sensor]; // going around the ball (inseguo la palla)

  if (role) {
    if ((ball_sensor == 18 || ball_sensor == 19 || ball_sensor == 0 ||
         ball_sensor == 1 || ball_sensor == 2) &&
        (ball_distance <= 2))
    storcimentoPortaIncr();
    else
      stincr = 0;
  } else {
    storcimentoZone();
    atk_direction = atk_direction + atk_offset;
    atk_direction = (atk_direction + 360) % 360;
    stincr = 0;
  }
  stincr = (stincr + 360) % 360;
  atk_speed = 200;
  preparePID(atk_direction, atk_speed, stincr);
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
    } else if (ball_distance < 2) {
      // se la palla è incredibilmente vicina VIRI ESTREMO
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

void storcimentoPortaIncr() {
  if (portx == 999) { // non vedo porta
    stincr = 0;
    digitalWrite(Y, LOW);
    digitalWrite(R, LOW);
  } else if (portx >= goalieCamMax) {
    stincr--; // la porta sta a destra
    if (stincr <= -30)
      stincr = -30;
    digitalWrite(Y, LOW);
    digitalWrite(R, HIGH);
  } else if (portx <= goalieCamMin) {
    stincr++;
    if (stincr >= 30)
      stincr = 30; // la porta sta a sinistra
    digitalWrite(Y, HIGH);
    digitalWrite(R, LOW);
  } else { // robot centrato con porta
    digitalWrite(Y, HIGH);
    digitalWrite(R, HIGH);
  }
}

void storcimentoZone() {
  if (zoneIndex == 1) {
    atk_offset = 0;
    digitalWrite(Y, HIGH);
    digitalWrite(R, HIGH);
  } else if (zoneIndex == 0) {
    atk_offset = 45;
    digitalWrite(Y, LOW);
    digitalWrite(R, HIGH);
  } else if (zoneIndex == 2) {
    atk_offset = -45;
    digitalWrite(Y, HIGH);
    digitalWrite(R, LOW);
  }
  if (zoneIndex >= 3) {
    digitalWrite(Y, LOW);
    digitalWrite(R, LOW);
  }
}

void leaveMeAlone() {
  if (zoneIndex >= 6)
    goCenter();
}

void storcimentoPorta2() {
  int pluto;
  atk_offset = 0;

  if (ball_distance <= 2) {
    if (ball_sensor == 19 || ball_sensor == 0 || ball_sensor == 1) {
      pluto = centrop - portx;
      atk_offset = pluto + imu_current_euler;
      if (atk_offset > 60)
        atk_offset = 60;
      if (atk_offset < -61)
        atk_offset = -60;
    }
  }
}

void storcimentoPortaOLDOLD() {
  // sistema di corsie di attacco
  // prendi il centro dalla costante centrop
  // fai meno -20 +20 e hai la tua fascia di non-storcimento
  // da -21 a -31 hai la prima fascia destra di attacco verso sinistra
  // da -31 in poi hai la seconda più violenta
  // da +21 a +31 hai la prima fascia sinistra di attacco verso destra
  // da +31 in poi hai la seconda più violenta
  // perché sottraendo si inverte!
  // i valori delle correzioni sono un po' a caso, da provare
  int pluto;

  pluto = portx - centrop;
  if ((pluto > -20) && (pluto < +20))
    atk_offset = 0;

  if ((pluto < -20) && (pluto > -31)) {
    atk_offset = 330;
    digitalWrite(30, HIGH);
    digitalWrite(29, LOW);
  }
  if (pluto < -31) {
    atk_offset = 315;
    digitalWrite(30, HIGH);
    digitalWrite(29, LOW);
  }

  if ((pluto > +20) && (pluto < +31)) {
    atk_offset = 30;
    digitalWrite(29, HIGH);
    digitalWrite(30, LOW);
  }
  if (pluto > +31) {
    atk_offset = 45;
    digitalWrite(29, HIGH);
    digitalWrite(30, LOW);
  }

  if (portx == 999)
    atk_offset = 45;
}

void storcimentoPortaOLD() {
  int pluto;
  pluto = portx - centrop;
  // if((pluto >= 150) && (pluto <= 170)) atk_offset = 0;
  // if(pluto <= 149) atk_offset = 30;
  // if(pluto >= 171) atk_offset = 330;
  atk_offset = pluto;
  if (pluto >= 40)
    atk_offset = 40;
  if (pluto <= -40)
    atk_offset = -40;
}

void storcimentoPorta() {
  if ((portx >= 111) && (portx <= 239))
    atk_direction = 0;
  if (portx >= 240)
    atk_direction = 345;
  if (portx <= 110)
    atk_direction = 15;
}
