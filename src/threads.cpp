#include <Arduino.h>
#include <TeensyThreads.h>
#include "camera.h"
#include "chat.h"
#include "goalie.h"
#include "music.h"
#include "myspi_old.h"
#include "imu.h"
#include "interrupt.h"
#include "pid.h"
#include "position.h"
#include "space_invaders.h"
#include "test.h"
#include "us.h"
#include "vars.h"


void update_everything_pos() {
  while(1) {        //this loop reads every sensor and calculates the zone
    // readIMU();     imu doesn't work with threads, dunno
    readUS();
    WhereAmI();
    guessZone();
    calculateZoneIndex();
  }
  threads.yield();  //slices the time in another thread
}

void update_atk() {
  while(1) {        //this loop updates ball position and goal position
    ball_read_position();
    goalPosition();
  }
  threads.yield();  //slices the time in another thread
}

void friendo() {
  while(1) {        //this loop says Ao to the other robot and hear the friendly Aoes.
    Ao();
    com(200);       //500 'cause they're always talking I guess, even with the interrupt.
  }
  threads.yield();  //slices the time in another thread
}

float tmp=0;
int time=0;

void storcimentoFigo() {
  stincr = 0;
  while(1) {
    if(millis() - time >= 300){
      stincr = tmp;
      time = millis();
    }else{
      if (inSensorRange(0,3) && (ball_distance <= 3)) {
        // if((portx > goalieCamMin) && (portx < goalieCamMax)) tmp = 0;
        // else if(portx <= goalieCamMin) tmp = -30;
        // else if(portx >= goalieCamMax) tmp = 30;
        if (portx == 999) { // non vedo porta
          tmp = tmp * 0.8;
          digitalWrite(Y, LOW);
          digitalWrite(R, LOW);
        } else if (portx >= goalieCamMax) {
          tmp -= 0.75; // la porta sta a destra
          if (tmp <= -30)
            tmp = -30;
          digitalWrite(Y, LOW);
          digitalWrite(R, HIGH);
        } else if (portx <= goalieCamMin) {
          tmp += 0.75;
          if (tmp >= 30)
            tmp = 30; // la porta sta a sinistra
          digitalWrite(Y, HIGH);
          digitalWrite(R, LOW);
        } else { // robot centrato con porta
          digitalWrite(Y, HIGH);
          digitalWrite(R, HIGH);
        }
      }
      else tmp *= 0.5;
    }
  }
  threads.yield();
}

void gameroutine() {  // the old loop in a thread
  while(1) {
    
    // for ports: 1=Blue 0=Yellow
    pAtk = 0;
    pDef = 1 - pAtk; // the other port for the keeper

    if ((flagtest == true) || (Serial.available() > 0)) testMenu(); // test

    // game routine

    if (flag_interrupt) int_nuovo();

    if (ball_seen == true) {
      if (role == HIGH) {
        if (comrade)
          goalie();
        else
          keeper();
      } else {
        if (stop_menamoli)
          centerGoalPost();
        else {
          if (ball_distance <= 2 && inSensorRange(0, 2) && !comrade) {
            goalie();
          } else {
            keeper();
          }
        }
      }
    } else {
      if (role == HIGH) {
        if (comrade)
          goCenter();
        else
          centerGoalPost();
      } else {
        centerGoalPost();
      }
    }

    // commentare se il robot sta fermo dopo essere uscito anche se la posizione
    // della palla cambia di tanto
    if (ball_seen && ball_sensor == lineBallSensor &&
        ball_distance == lineBallDistance && // potrebbe dar fastidio a portiere
        (globalDir > (((globalDir - 10) + 360) % 360)) &&
        (globalDir < (((globalDir + 10) + 360) % 360))) {
      preparePID(0, 0);
    }

    //letteralmente se ho palla faccio la marcia imperiale
    // if(ball_distance <= 1 && (ball_sensor == 19 || ball_sensor == 0 || ball_sensor == 1)) ball = true;
    // else ball = false;

    // if(ball) threads.restart(THRD4);
    // else threads.suspend(THRD4);

    // final drive pid
    if (globalSpeed != 0) {
      if (role) {
        globalSpeed = 150;
      } else {
        globalSpeed = 170;
      }
    }

    drivePID(globalDir, globalSpeed);
  }
  threads.yield();  //slices the time in another thread
}


void imperial_thread() {  //imperial march but with threads ;)
  while(1) {
    tone(buzzer,LA3,Q);
    threads.delay(1+Q); //threads.delay duration should always be 1 ms more than the note in order to separate them.
    tone(buzzer,LA3,Q);
    threads.delay(1+Q);
    tone(buzzer,LA3,Q);
    threads.delay(1+Q);
    tone(buzzer,F3,E+S);
    threads.delay(1+E+S);
    tone(buzzer,C4,S);
    threads.delay(1+S);

    tone(buzzer,LA3,Q);
    threads.delay(1+Q);
    tone(buzzer,F3,E+S);
    threads.delay(1+E+S);
    tone(buzzer,C4,S);
    threads.delay(1+S);
    tone(buzzer,LA3,H);
    threads.delay(1+H);

    tone(buzzer,E4,Q);
    threads.delay(1+Q);
    tone(buzzer,E4,Q);
    threads.delay(1+Q);
    tone(buzzer,E4,Q);
    threads.delay(1+Q);
    tone(buzzer,F4,E+S);
    threads.delay(1+E+S);
    tone(buzzer,C4,S);
    threads.delay(1+S);

    tone(buzzer,Ab3,Q);
    threads.delay(1+Q);
    tone(buzzer,F3,E+S);
    threads.delay(1+E+S);
    tone(buzzer,C4,S);
    threads.delay(1+S);
    tone(buzzer,LA3,H);
    threads.delay(1+H);

    tone(buzzer,LA4,Q);
    threads.delay(1+Q);
    tone(buzzer,LA3,E+S);
    threads.delay(1+E+S);
    tone(buzzer,LA3,S);
    threads.delay(1+S);
    tone(buzzer,LA4,Q);
    threads.delay(1+Q);
    tone(buzzer,Ab4,E+S);
    threads.delay(1+E+S);
    tone(buzzer,G4,S);
    threads.delay(1+S);

    tone(buzzer,Gb4,S);
    threads.delay(1+S);
    tone(buzzer,E4,S);
    threads.delay(1+S);
    tone(buzzer,F4,E);
    threads.delay(1+E);
    threads.delay(1+E);//PAUSE
    tone(buzzer,Bb3,E);
    threads.delay(1+E);
    tone(buzzer,Eb4,Q);
    threads.delay(1+Q);
    tone(buzzer,D4,E+S);
    threads.delay(1+E+S);
    tone(buzzer,Db4,S);
    threads.delay(1+S);

    tone(buzzer,C4,S);
    threads.delay(1+S);
    tone(buzzer,B3,S);
    threads.delay(1+S);
    tone(buzzer,C4,E);
    threads.delay(1+E);
    threads.delay(1+E);//PAUSE QUASI FINE RIGA
    tone(buzzer,F3,E);
    threads.delay(1+E);
    tone(buzzer,Ab3,Q);
    threads.delay(1+Q);
    tone(buzzer,F3,E+S);
    threads.delay(1+E+S);
    tone(buzzer,LA3,S);
    threads.delay(1+S);

    tone(buzzer,C4,Q);
    threads.delay(1+Q);
     tone(buzzer,LA3,E+S);
    threads.delay(1+E+S);
    tone(buzzer,C4,S);
    threads.delay(1+S);
    tone(buzzer,E4,H);
    threads.delay(1+H);

     tone(buzzer,LA4,Q);
    threads.delay(1+Q);
    tone(buzzer,LA3,E+S);
    threads.delay(1+E+S);
    tone(buzzer,LA3,S);
    threads.delay(1+S);
    tone(buzzer,LA4,Q);
    threads.delay(1+Q);
    tone(buzzer,Ab4,E+S);
    threads.delay(1+E+S);
    tone(buzzer,G4,S);
    threads.delay(1+S);

    tone(buzzer,Gb4,S);
    threads.delay(1+S);
    tone(buzzer,E4,S);
    threads.delay(1+S);
    tone(buzzer,F4,E);
    threads.delay(1+E);
    threads.delay(1+E);//PAUSE
    tone(buzzer,Bb3,E);
    threads.delay(1+E);
    tone(buzzer,Eb4,Q);
    threads.delay(1+Q);
    tone(buzzer,D4,E+S);
    threads.delay(1+E+S);
    tone(buzzer,Db4,S);
    threads.delay(1+S);

    tone(buzzer,C4,S);
    threads.delay(1+S);
    tone(buzzer,B3,S);
    threads.delay(1+S);
    tone(buzzer,C4,E);
    threads.delay(1+E);
    threads.delay(1+E);//PAUSE QUASI FINE RIGA
    tone(buzzer,F3,E);
    threads.delay(1+E);
    tone(buzzer,Ab3,Q);
    threads.delay(1+Q);
    tone(buzzer,F3,E+S);
    threads.delay(1+E+S);
    tone(buzzer,C4,S);
    threads.delay(1+S);

    tone(buzzer,LA3,Q);
    threads.delay(1+Q);
     tone(buzzer,F3,E+S);
    threads.delay(1+E+S);
    tone(buzzer,C4,S);
    threads.delay(1+S);
    tone(buzzer,LA3,H);
    threads.delay(1+H);

    threads.delay(2*H);
  }
  threads.yield();
}
