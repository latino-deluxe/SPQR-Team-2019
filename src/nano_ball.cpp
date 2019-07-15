#include <Arduino.h>
#include "vars.h"
#include "nano_ball.h"

byte ballReadNano;

void readBallNano() {
    while(NANO_BALL.available() > 0)  {
      ballReadNano = NANO_BALL.read();

      if((ballReadNano & 0x01) == 1){
        ball_distance = ballReadNano;
        ball_seen = ball_distance > 1;
      }else{ 
        ball_degrees = ballReadNano * 2; 
      }
    
      /*ball_sensor = (ballReadNano & 0b00011111);
      ball_distance = ballReadNano >> 5;
      ball_seen  = ball_distance != 5;*/
    }
}

void testBallNano() {
  readBallNano();
  if(ball_seen){
    //DEBUG_PRINT.print(ball_sensor);
    DEBUG_PRINT.print(ball_degrees); 
    DEBUG_PRINT.print(" | ");
    DEBUG_PRINT.println(ball_distance); 
  }else{
    DEBUG_PRINT.println("Not seeing ball");
  }

  delay(100);
}

bool inAngle(int reachAngle, int startAngle, int range){
	return diff(reachAngle, startAngle) <= range;
}

int diff(int a, int b){
	int diffB = abs(min(a, b) - max(a, b));
	int diffB1 = 360-diffB;
	int diff = min(diffB, diffB1);
  return diff;
}