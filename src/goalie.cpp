#include "goalie.h"
#include "camera.h"
#include "myspi_old.h"
#include "pid.h"
#include "position.h"
#include "us.h"
#include "vars.h"
#include <Arduino.h>

unsigned long timerstr = 0;

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

  if (inSensorRange(0,2) && ball_distance <= 3){
    atk_speed = 200;
    preparePID(atk_direction, atk_speed, stincr);
  }else{
    atk_speed = 200;
    preparePID(atk_direction, atk_speed, 0);    
  }

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

int stport;
void storcimentoPortaIncr() {
  if(ball_seen){
    if (portx == 999) { // non vedo porta
      //digitalWrite(Y, LOW);
      //digitalWrite(R, LOW);
      //digitalWrite(BUZZER, 0);
      return;
    }

    stport = fixCamIMU();

    // stport = portx;

    if (stport == 0) {
      stincr = stincr * 0.8;
      // digitalWrite(BUZZER, 1);
      return;
    }else if (stport >= goalieCamMax) {
      stincr -= 3.5; // la porta sta a destra
      if (stincr < -35)
        stincr = -35;
      digitalWrite(Y, LOW);
      digitalWrite(R, HIGH);
      digitalWrite(BUZZER, 0);
    } else if (stport <= goalieCamMin) {
      stincr += 3.5;
      if (stincr > 35)
        stincr = 35; // la porta sta a sinistra
      digitalWrite(Y, HIGH);
      digitalWrite(R, LOW);
      digitalWrite(BUZZER, 0);
    } else { // robot centrato con porta
      digitalWrite(Y, HIGH);
      digitalWrite(R, HIGH);
      digitalWrite(BUZZER, 0);
    }
  }else{
    stincr = 0;
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
