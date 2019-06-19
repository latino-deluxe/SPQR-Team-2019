#include <Arduino.h>
#include <TeensyThreads.h>
#include "chat.h"
#include "imu.h"
#include "us.h"
#include "threads.h"
#include "position.h"
#include "vars.h"


void pos() {
 while(1) {
    readIMU();
    readUS();
    calculateLogicZone();
  }
  threads.yield();
}


void chat() {
 while(1) {
     com(250);
     Ao();
  }
  threads.yield();
}