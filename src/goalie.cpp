#include "goalie.h"
#include "pid.h"
#include "position.h"
#include "us.h"
#include "vars.h"
#include "myspi_old.h"

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

  if (inSensorRange(0,3) && (ball_distance <= 4)){
    storcimentoPortaIncr();
    // noTone(BUZZER);
  // atk_direction = atk_direction + atk_offset;
  // atk_direction = (atk_direction + 360) % 360;
  // stincr = 0;
  // storcimentoPortaIncr();
  }else{
    stincr = 0;
    // tone(BUZZER, 20000, 500);
  // if (role) {
  //   if ((ball_sensor == 18 || ball_sensor == 19 || ball_sensor == 0 ||
  //        ball_sensor == 1 || ball_sensor == 2) &&
  //       (ball_distance <= 2) && zoneIndex <= 2)   storcimentoPortaIncr();
  //       // atk_direction = atk_direction + atk_offset;
  //       // atk_direction = (atk_direction + 360) % 360;
  //       // stincr = 0;
  //       // storcimentoPortaIncr();
  //       else
  //         stincr = 0;
  // } else {
  //   storcimentoZone();
  //   atk_direction = atk_direction + atk_offset;
  //   atk_direction = (atk_direction + 360) % 360;
  //   stincr = 0;
  // }
  }

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
        atk_direction = 135;
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
    stincr = stincr * 0.8;
    digitalWrite(Y, LOW);
    digitalWrite(R, LOW);
  } else if (portx >= goalieCamMax) {
    stincr -= 5; // la porta sta a destra
    if (stincr <= -45)
      stincr = -45;
    digitalWrite(Y, LOW);
    digitalWrite(R, HIGH);
  } else if (portx <= goalieCamMin) {
    stincr += 5;
    if (stincr >= 45)
      stincr = 45; // la porta sta a sinistra
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