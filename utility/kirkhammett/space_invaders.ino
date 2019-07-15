/*
 * void space_invaders() {
  if (compagno == true) {
    if (us_px >= 25) centroporta();
    if (ball_sensor == 0) recenter(1.0);
    if ((ball_sensor >= 1) && (ball_sensor <= 8)) drivePID(90, GOALIE_P);
    if ((ball_sensor >= 12) && (ball_sensor <= 19)) drivePID(270, GOALIE_P);
    if ((ball_sensor >= 9) && (ball_sensor <= 11))  palla_dietro();
  }
  else {
    if ((ball_distance <= 3) && (ball_sensor == 0)) menamoli();
    else recenter(1.0);
    if ((ball_sensor >= 1) && (ball_sensor <= 7))   drivePID(90, GOALIE_P);
    if ((ball_sensor >= 13) && (ball_sensor <= 19)) drivePID(270, GOALIE_P);
    if ((ball_sensor >= 8) && (ball_sensor <= 12))  palla_dietro();
  }
}*/


  void space_invaders() {
    us_read();
    if (us_px >= 15) centroporta();
    if ((ball_sensor >= 1) && (ball_sensor <= 8)) drivePID(90, GOALIE_P);
    if ((ball_sensor >= 12) && (ball_sensor <= 19)) drivePID(270, GOALIE_P);
    if ((ball_sensor > 8) && (ball_sensor < 12)) palla_dietro();
  }


/*
   BACKUP
   void space_invaders() {
  unsigned long t4;
  unsigned long t5;
  int tira=300;
  if (compagno == true) {
    if (us_px >= 25) centroporta();
    if(((ball_sensor==0)||(ball_sensor==19)||(ball_sensor==1))&&(ball_distance<=1)) {
      t4=millis();
      do
        {
         drivePID (0,255);
       }
       while ( (millis() - t4) < tira);
       if(us_px<=75) tira=150;
       t5=millis();
      do
        {
         drivePID (180,255);
       }
       while ( (millis() - t5) < tira);
    }
    if ((ball_sensor >= 1) && (ball_sensor <= 7)) drivePID(90, GOALIE_P);
    if ((ball_sensor >= 12) && (ball_sensor <= 19)) drivePID(270, GOALIE_P);
    if ((ball_sensor > 8) && (ball_sensor < 12)) palla_dietro();
    else recenter(1.0);
  }
  else {
    if ((ball_distance <= 4) && ((ball_sensor == 19)||(ball_sensor == 0)||(ball_sensor == 1))) menamoli();
    if ((ball_sensor > 1) && (ball_sensor <= 7))   drivePID(90, GOALIE_P);
    if ((ball_sensor >= 13) && (ball_sensor < 19)) drivePID(270, GOALIE_P);
    if ((ball_sensor >= 8) && (ball_sensor <= 12)) palla_dietro();
  }
  }


  /*
   PROBABILE FUNZIONANTE
    void space_invaders() {
  if (compagno == true) {
    if (us_px >= 25) centroporta();
    if ((ball_sensor >= 1) && (ball_sensor <= 8)) drivePID(90, GOALIE_P);
    if ((ball_sensor >= 12) && (ball_sensor <= 19)) drivePID(270, GOALIE_P);
    if ((ball_sensor >= 9) && (ball_sensor <= 11))  palla_dietro();
  }
  else {
    if ((ball_distance <= 2) && (ball_sensor == 0)) menamoli();
    if ((ball_sensor >= 1) && (ball_sensor <= 7))   drivePID(90, GOALIE_P);
    if ((ball_sensor >= 13) && (ball_sensor <= 19)) drivePID(270, GOALIE_P);
    if ((ball_sensor >= 8) && (ball_sensor <= 12))  palla_dietro();
  }
  }
*/

/*
   BACKUP
   void space_invaders() {
  unsigned long t4;
  unsigned long t5;
  int tira=300;
  if (compagno == true) {
    if (us_px >= 25) centroporta();
    if(((ball_sensor==0)||(ball_sensor==19)||(ball_sensor==1))&&(ball_distance<=1)) {
      t4=millis();
      do
        {
         drivePID (0,255);
       }
       while ( (millis() - t4) < tira);
       if(us_px<=75) tira=150;
       t5=millis();
      do
        {
         drivePID (180,255);
       }
       while ( (millis() - t5) < tira);
    }
    if ((ball_sensor >= 1) && (ball_sensor <= 7)) drivePID(90, GOALIE_P);
    if ((ball_sensor >= 12) && (ball_sensor <= 19)) drivePID(270, GOALIE_P);
    if ((ball_sensor > 8) && (ball_sensor < 12)) palla_dietro();
    else recenter(1.0);
  }
  else {
    if ((ball_distance <= 4) && ((ball_sensor == 19)||(ball_sensor == 0)||(ball_sensor == 1))) menamoli();
    if ((ball_sensor > 1) && (ball_sensor <= 7))   drivePID(90, GOALIE_P);
    if ((ball_sensor >= 13) && (ball_sensor < 19)) drivePID(270, GOALIE_P);
    if ((ball_sensor >= 8) && (ball_sensor <= 12)) palla_dietro();
  }
  }

*/


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
