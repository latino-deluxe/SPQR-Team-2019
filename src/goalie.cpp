#include <Arduino.h>

#include "goalie.h"
#include "myspi_old.h"
#include "pid.h"
#include "position.h"
#include "us.h"
#include "vars.h"

void goalie() {
  int atk_direction = 0;
  int atk_speed = 0;
  // directions going around the ball
  int goaliedirection[20] = {AA0,  AA1,  AA2,  AA3,  AA4,  AA5,  AA6,
                             AA7,  AA8,  AA9,  AA10, AA11, AA12, AA13,
                             AA14, AA15, AA16, AA17, AA18, AA19};

  atk_speed = 180;                              //forse inutile, lo imposto per livellare
  atk_direction = goaliedirection[ball_sensor]; // going around the ball (inseguo la palla)

  //PALLA DIETRO
  if(ball_sensor==9 || ball_sensor==10 || ball_sensor==1) {
    if(ball_distance < 4) { //se la palla è vicina decido come muovermi in base alla zona per non uscire
      atk_speed = 200;
      if(zoneIndex==8 || zoneIndex==5 || zoneIndex==2) atk_direction = 225;
      if(zoneIndex==0 || zoneIndex==3 || zoneIndex==9) atk_direction = 135;
      if(zoneIndex==1 || zoneIndex==4 || zoneIndex==7) atk_direction = 250;
    }
  else {    //se la palla è lontana mi avvicino più velocemente con angolo più stretto
      atk_speed = 255;
      if(zoneIndex==8 || zoneIndex==5 || zoneIndex==2) atk_direction = 200;
      if(zoneIndex==0 || zoneIndex==3 || zoneIndex==9) atk_direction = 160;
      if(zoneIndex==1 || zoneIndex==4 || zoneIndex==7) atk_direction = 180;
    }
  }

  //STORCIMENTO (senza camera, alla vecchia maniera)
  if(ball_sensor==19 || ball_sensor==0 || ball_sensor==1) {
    atk_speed = 255;
    if(zoneIndex==0) atk_direction = 45;
    if(zoneIndex==1) atk_direction = 0;
    if(zoneIndex==2) atk_direction = 315;
  }

  preparePID(atk_direction, atk_speed);
}
