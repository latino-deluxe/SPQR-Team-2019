#include "libs.h"
#include "pid.h"

void goalie()
{
  int atk_direction = 0; //direzione di attacco in funzione del sensore che vede la palla
  int atk_speed = 0;     //velocitá di attacco in funzione del sensore che vede la palla
  int goaliedirection[20] = { AA0, AA1 , AA2, AA3, AA4, AA5, AA6, AA7, AA8, AA9, AA10, AA11, AA12, AA13, AA14, AA15, AA16, AA17, AA18, AA19 }; //direzioni going around the ball

  atk_direction = goaliedirection[ball_sensor]; //going around the ball
  atk_speed = 255;
  drivePID(atk_direction, atk_speed);

  return;
}
