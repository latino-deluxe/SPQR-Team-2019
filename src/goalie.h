#include "libs.h"
#include "pid.h"
#include "spi.h"
#include "us.h"


void goalie();

int status_x = CENTRO;                // posizione nel campo vale EST, OVEST o CENTRO o 255
int status_y = CENTRO;                // posizione nel campo vale SUD, NORD o CENTRO o 255
int currentlocation = CENTRO_CENTRO;  // risultato misure zone campo da 1 a 9 o 255 se undefined
int guessedlocation = CENTRO_CENTRO;  // risultato misure zone campo da 1 a 9 (da CENTRO_CENTRO a SUD_OVEST)

int old_status_x = CENTRO;        // posizione precedente nel campo vale EST, OVEST o CENTRO o 255 >USI FUTURI<
int old_status_y = CENTRO;        // posizione precedente nel campo vale SUD, NORD o CENTRO o 255 >USI FUTURI<
int old_currentlocation; // zona precedente del robot in campo da 1 a 9 o 255 se undefined >USI FUTURI<
int old_guessedlocation = CENTRO_CENTRO; // zona precedente del robot in campo da 1 a 9 (da CENTRO_CENTRO a SUD_OVEST) >USI FUTURI<

bool goal_zone = false;         // sto al centro rispetto alle porte         assegnata da WhereAmI ma non usata
bool good_field_x = true;      // vedo tutta la larghezza del campo si/no
bool good_field_y = true;     // vedo tutta la lunghezza del campo si/no

void goalie()
{
  int atk_direction = 0; //direzione di attacco in funzione del sensore che vede la palla
  int atk_speed = 0;     //velocitá di attacco in funzione del sensore che vede la palla
  int goaliedirection[20] = { AA0, AA1 , AA2, AA3, AA4, AA5, AA6, AA7, AA8, AA9, AA10, AA11, AA12, AA13, AA14, AA15, AA16, AA17, AA18, AA19 }; //direzioni going around the ball

  //PALLA DI FRONTE
  if (ball_sensor == 0)
  {
    if(ball_distance>=2) atk_speed = 180;
    atk_speed = GOALIE_MAX;
  }
  else
  {
    if(ball_distance>=2) atk_speed = 180;
    atk_speed = GOALIE_MIN;
  }



  atk_direction = goaliedirection[ball_sensor]; //going around the ball

  // controllo per ridurre oscillazione quando ha la palla in avanti
  if (ball_sensor == 1) {
    if (ball_distance <= 2) {   //se la palla è vicina
      atk_speed = GOALIE_MAX;
      atk_direction = 15;
    }
  }


  if (ball_sensor == 19) {
    if (ball_distance <= 2) {   //se la palla è vicina
      atk_speed = GOALIE_MAX;
      atk_direction = 345;
    }
  }

  if ((ball_sensor == 10) || (ball_sensor == 9) || (ball_sensor == 11))  //  se la palla é dietro e vicina la scanso a 90 a dx o sx dove ho piú spazio
  {
    if (ball_distance < 4)
    {
        if (us_sx>=80)
        {
          atk_direction = 225;
        }
        else
        {
          atk_direction = 135;
        }
     }
    else //la palla é lontana anche se dietro le vado quasi addosso in velocita
     {

      if(us_sx>=80) {
         atk_direction = 200;
         atk_speed = GOALIE_MAX;
       }
       else {
         atk_direction = 160;
         atk_speed = GOALIE_MAX;
       }

    }
  }
  if (ball_distance>=3){
      if ((status_x==OVEST) && (status_y==NORD)){
        atk_speed=200;
      }
      else if ((status_x==EST) && (status_y==NORD)) {
        atk_speed=200;
      }
  }
}
