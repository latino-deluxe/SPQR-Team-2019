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
  //PALLA DIETRO
  /*if (ball_sensor == 10) {
    if(ball_distance<=3){
     atk_direction=112;
     atk_speed=GOALIE_SLOW1;
    }
    else {
      atk_direction=248;
      atk_speed=GOALIE_SLOW2;
    }
  }
  if(ball_sensor == 9) {
    if(ball_distance<=3) {
      atk_direction=135;
      atk_speed=GOALIE_SLOW1;
    }
    else {
      atk_direction=225;
      atk_speed=GOALIE_SLOW2;
    }
  }
  if(ball_sensor == 11) {
    if(ball_distance<=3) {
      atk_direction=225;
      atk_speed=GOALIE_SLOW1;
    }
    else {
      atk_direction=135;
      atk_speed=GOALIE_SLOW2;
    }
  }*/

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

  
  update_sensors_all();
  x_porta();                                //leggo la posizione della porta
  // se ha la palla vicino e davanti cerca di centrare la porta
  if ((ball_distance<=2) && ((ball_sensor == 19)||(ball_sensor == 0)||(ball_sensor == 1)))
  {
    if ((XP_SX==true)||(status_x==EST))                        // sto in fascia destra convergo a sinistra
    {
      if(status_x==EST){
        if(status_y==CENTRO) {                                                          //(x>141)&&(x<190)
          atk_direction=345;
          atk_speed=255;
        }
        if(status_y==NORD) {                                                            //(x>111)&&(x<140)
          atk_direction=340;
          atk_speed=255;
        }
      }
      if(status_x==CENTRO){
        if(status_y==CENTRO) {                                                          //(x>141)&&(x<190)
          atk_direction=355;
          atk_speed=255;
        }
        if(status_y==NORD) {                                                            //(x>111)&&(x<140)
          atk_direction=345;
          atk_speed=255;
        }
      }
     }
    if ((XP_DX==true)||(status_x==OVEST))                      // sto in fascia sinistra convergo a destra
    {
      if(status_x==OVEST) {
        if(status_y==CENTRO) {                                                          //(x>35)&&(x<60)
          atk_direction=15;
          atk_speed=255;
        }
        if(status_y==NORD) {                                                            //(x>8)&&(x<34)
          atk_direction=30;
          atk_speed=255;
        }
      }
      if(status_x==CENTRO) {
        if(status_y==CENTRO) {                                                          //(x>35)&&(x<60)
          atk_direction=5;
          atk_speed=255;
        }
        if(status_y==NORD) {                                                            //(x>8)&&(x<34)
          atk_direction=15;
        atk_speed=255;
        }
      }
    }
  }

  // --------------------------
  if ((millis() - tdanger) > 500) danger = false; // dichiara esaurito il pericolo dall'ultimo interrupt
  if (danger == true) atk_speed = GOALIE_DANGER;  // se ha terminato da poco la gestione interrupt rallenta
  // __________________________

  drivePID(atk_direction, atk_speed);

  return;
}
