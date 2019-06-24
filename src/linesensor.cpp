#include "linesensor.h"
#include "goalie.h"
#include "position.h"
#include "pid.h"
#include "motors.h"
#include "music.h"
#include "vars.h"
#include "nano_ball.h"
#include <Arduino.h>

// init line sensors and attaches interrput
// void initLineSensors() {
//   pinMode(S0, INPUT);
//   pinMode(S1, INPUT);
//   pinMode(S2, INPUT);
//   pinMode(S3, INPUT);
// }

int linepinsI[4] = {S1I, S2I, S3I, S4I};
int linepinsO[4] = {S1O, S2O, S3O, S4O};
int linetriggerI[4];
int linetriggerO[4];
int lineCnt;
int CNTY;
int CNTX;
int prevDir;
int ai, ar;
int EXTIME = 700;
byte linesensbyteI;
byte linesensbyteO;
byte linesensbyte;
byte linesensbytefst;
byte linesensbyteOLDY;
byte linesensbyteOLDX;
elapsedMillis exitTimer;
elapsedMillis ltimer;

void checkLineSensors() {
  linesensbyteI = 0;
  linesensbyteO = 0;
  // linesensbyte  = 0;
  for(int i = 0; i < 4; i++) {
    linetriggerI[i] = analogRead(linepinsI[i]) > LINE_THRESH;
    linetriggerO[i] = analogRead(linepinsO[i]) > LINE_THRESH;
    if(linetriggerI[i] || linetriggerO[i]) {
      if(ltimer > 1700) lineCnt = 1200;
      else lineCnt = EXTIME;
    }
    linesensbyteI = linesensbyteI + (linetriggerI[i]<<i);
    linesensbyteO = linesensbyteO + (linetriggerO[i]<<i);
  }
  // playSafe();
  linesensbyte |= (linesensbyteI | linesensbyteO);
  // phyZoneLines(linesensbyte);
  if(linesensbyte > 0) bounds = true;
  else bounds = false;
  // if(bounds) 
  outOfBounds();                                            
}

void outOfBounds() {
  // if(lineCnt == EXTIME) {

  if(lineCnt == EXTIME) {
    if(linesensbytefst == 0) linesensbytefst = linesensbyte;
  }

  if(linesensbyte & 0x02) linesensbyteOLDY =  2;
  if(linesensbyte & 0x08) linesensbyteOLDY =  8;
  if(linesensbyte & 0x01) linesensbyteOLDX =  1;
  if(linesensbyte & 0x04) linesensbyteOLDX =  4;

  // if((linesensbyte == 2 || linesensbyte == 8)) {
  //   linesensbyteOLDY = linesensbyte;
  //   CNTY = 1500;
  //   CNTY--;
  // }
  // if(CNTY <= 0) {
  //   CNTY = 0;
  //   linesensbyteOLDY = 0;
  // }

  // if((linesensbyte == 1 || linesensbyte == 4)) {
  //   linesensbyteOLDX = linesensbyte;
  //   CNTX = 1500;  
  //   CNTX--;
  // }
  // if(CNTX <= 0) {
  //   CNTX = 0;
  //   linesensbyteOLDX = 0;
  // }

  if(linesensbyte == 15) {
    linesensbyte = linesensbytefst;
    digitalWrite(Y, HIGH);
  }

    switch(linesensbyte) {
      case 0:
        // outDir = prevDir;
        outDir = linesensbytefst;
        outVel = 255;
        // prevDir = -1;
        digitalWrite(R, LOW);
        digitalWrite(Y, LOW);
      break;

      case 11:
        if(linesensbyteOLDX == 1) outDir = 180;
        else outDir = 0;
        outVel = 255;
        ai = 0;
        ar = 60;
        
        digitalWrite(R, LOW);
        digitalWrite(Y, LOW);
        digitalWrite(G, HIGH);
      break;

      case 14:
        if(linesensbyteOLDX == 1) outDir = 180;
        else outDir = 0;
        outVel = 255;
        ai = 180;
        ar = 60;
        
        digitalWrite(R, LOW);
        digitalWrite(G, HIGH);
        digitalWrite(Y, LOW);
      break;


      case 10:
        if(linesensbyteOLDX == 1) {
          outDir = 180;
          outVel = 255;
          ai = 0;
          ar = 30;
          tone(30, F6);
        } else if(linesensbyteOLDX == 4) {
          outDir = 0;
          outVel = 255;
          ai = 180;
          ar = 30;
          tone(30, F4);
        } else {
          outDir = 0;
          outVel = 0;
          tone(30, LA3);
        }
        
        digitalWrite(R, HIGH);
        digitalWrite(Y, LOW);
        digitalWrite(G, HIGH);
      break;

      case 5:
        if(linesensbyteOLDY == 2) {
          outDir = 270;
          outVel = 255;
          ai = 90;
          ar = 30;
          tone(30, C6);
        } else if(linesensbyteOLDY == 8) {
          outDir = 90;
          outVel = 255;
          ai = 270;
          ar = 30;
          tone(30, C3);
        }
        else {
          outDir = 0;
          outVel = 0;
          tone(30, LA3);
        }
        
        digitalWrite(R, HIGH);
        digitalWrite(Y, LOW);
        digitalWrite(G, HIGH);
      break;

      case 1:
        outDir = 180;
        outVel = 255;
        ai = 0;
        ar = 30;
        digitalWrite(R, LOW);
        digitalWrite(G, LOW);
        digitalWrite(Y, LOW);
      break;

      case 2:
      case 7:
        outDir = 270;
        outVel = 255;
        ai = 90;
        ar = 60; 
        digitalWrite(R, LOW);
        digitalWrite(G, LOW);
        digitalWrite(Y, LOW);
      break;

      case 4:
        outDir = 0;
        outVel = 255;

        ai = 180;
        ar = 30;

        digitalWrite(R, LOW);
        digitalWrite(G, LOW);
        digitalWrite(Y, LOW);
      break;

      case 8:
      case 13:
        outDir = 90;
        outVel = 255;

        ai = 270;
        ar = 60;

        digitalWrite(R, LOW);
        digitalWrite(G, LOW);
        digitalWrite(Y, LOW);
      break;



      case 3:
        outDir = 225;
        outVel = 255;

        ai = 45;
        ar = 20;

        digitalWrite(R, LOW);
        digitalWrite(G, LOW);
        digitalWrite(Y, LOW);
      break;

      case 6:
        outDir = 315;
        outVel = 255;

        ai = 135;
        ar = 20;

        digitalWrite(R, LOW);
        digitalWrite(G, LOW);
        digitalWrite(Y, LOW);
      break;

      case 12:
        outDir = 45;
        outVel = 255;

        ai = 225;
        ar = 20;

        digitalWrite(R, LOW);
        digitalWrite(G, LOW);
        digitalWrite(Y, LOW);
      break;

      case 9:
        outDir = 135;
        outVel = 255;

        ai = 315;
        ar = 20;

        digitalWrite(R, LOW);
        digitalWrite(G, LOW);
        digitalWrite(Y, LOW);
      break;




      default:
        outDir = (atk_direction + 180) % 360;
        outVel = 255;
        prevDir = -1;
        digitalWrite(R, LOW);
        digitalWrite(G, LOW);
        digitalWrite(Y, HIGH);
      break;
    }
  // } 
   lineSensByteBak = linesensbyte;


  lineCnt--;
  
  
  if(lineCnt == 1) {
    slow = true;
    ltimer = 0;
  }
  else slow = false;


  if(lineCnt > 0 && outDir != -1) {
    ballMask(1);        //da mettere solo prima volta becco linea
    prevDir = outDir;
    preparePID(outDir, outVel, 0);
  }
  else prevDir = -1;

  if(lineCnt <= 0) {
    ballMask(0);
    noTone(30);
    lineCnt = 0;
    outDir = 0;
    linesensbyte =0;
  }
  
  


}

void playSafe() {
  switch(linesensbyte) {
    case 1:
    case 4:
      x = 1;
      y = 0;
    break;

    case 2:
    case 8:
      x = 0;
      y = 1;
    break;

    default:
      x = 1;
      y = 1;
    break;
  }
}

void testLineSensors(){

  checkLineSensors();

  Serial.println("----------");  
  for(int i = 0; i<4; i++) {
    Serial.print(linetriggerI[i]);
    Serial.print("-");
    Serial.print(linetriggerO[i]);
    Serial.print(" | ");
  }
  Serial.println();
  Serial.println("----------"); 
  
  Serial.print("Byte:   ");
  Serial.print(linesensbyteO);
  Serial.print("    Direzione:    ");
  Serial.println(outDir);
  delay(150);

  Serial.println("----------"); 

    if(linesensbyte == 1) {
      digitalWrite(G, LOW);
        digitalWrite(Y, LOW);
        digitalWrite(R, HIGH);
      }
      if(linesensbyte == 2) {
        digitalWrite(G, LOW);
        digitalWrite(Y, HIGH);
        digitalWrite(R, LOW);
      }
      if(linesensbyte == 4) {
        digitalWrite(G, HIGH);
        digitalWrite(Y, LOW);
        digitalWrite(R, LOW);
      }
      if(linesensbyte == 8) {
        digitalWrite(G, HIGH);
        digitalWrite(Y, HIGH);
        digitalWrite(R, LOW);
      }

}

int ball = -1;
elapsedMillis mask;
elapsedMillis slowly;

void ballMask(int on) {
  float diffB;

  if(on) {
    ball = ball_degrees;
    mask = 0;
  }
  else {
    if(ball != -1) {
      if(inAngle(ball_degrees, ai, ar) == 0) {
        ball = -1;
        return;
      }
      else {
        if(mask < 750) preparePID(0, 0, 0);
        else {
          ball = -1;
          return;
        }
      }
    } else return;
  }

}

void safetysafe() {
  if(slow)  slowly = 0;
  if(!slow) if(slowly < 600){
    if(ball_degrees > 45 && ball_degrees < 315) globalSpeed = globalSpeed / 2;
  } 
}

// (inAngle(ball_degrees, ai, 20)