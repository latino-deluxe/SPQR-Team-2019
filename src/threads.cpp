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
int time=0, timeCam = 0;;
int imuOff = 0, fst = 0, stport = 0;

void storcimentoFigo() {
  stincr = 0;
  while(1) {
    if(millis() - time >= 350){
      stincr = tmp;
      time = millis();
    }else{
      if (inSensorRange(0,1) && (ball_distance <= 2)) {
        //camera portx fix based on imu
        //-30° --> -100 on camera x
        //+30° --> +100 on camera x

        if(millis() - time >= 20){
          if(portx != 999) {
            imuOff = imu_current_euler;
            if(imu_current_euler > 30 && imu_current_euler < 180) imuOff = 30;
            else if(imu_current_euler < 330 && imu_current_euler >= 180) imuOff = -30;
            else if (imu_current_euler <= 360 && imu_current_euler >= 330) imuOff = imu_current_euler - 360;
            else imuOff = imu_current_euler;

            fst = map(imuOff, -30, 30, -90, 90);
            stport = portx - fst;
            //Serial.println(stport);
          }

          // if((portx > goalieCamMin) && (portx < goalieCamMax)) tmp = 0;
          // else if(portx <= goalieCamMin) tmp = -30;
          // else if(portx >= goalieCamMax) tmp = 30;

          if (stport == 999) { // non vedo porta
            tmp = tmp * 0.8;
          } else if (stport >= 170) {
            tmp -= 3; // la porta sta a destra
            if (tmp <= -30)
              tmp = -30;
          } else if (stport <= 150) {
            tmp += 3;
            if (tmp >= 30)
              tmp = 30; // la porta sta a sinistra
          } else { // robot centrato con porta
          }
        }
      }
      else tmp *= 0.5;
    }
  }
  threads.yield();
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
