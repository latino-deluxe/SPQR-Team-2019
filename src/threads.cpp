#include <Arduino.h>
#include <TeensyThreads.h>
#include "camera.h"
#include "chat.h"
#include "music.h"
#include "myspi_old.h"
#include "imu.h"
#include "position.h"
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
  while(1) {
    Ao();
    com(500);
  }
  threads.yield();
}


void imperial_thread() {//tone(pin, note, duration)
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
