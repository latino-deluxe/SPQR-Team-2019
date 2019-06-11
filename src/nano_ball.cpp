#include "Arduino.h"
#include "vars.h"

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

    /*
    ball_sensor = (ballReadNano & 0b00011111);
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

// bool inSensorRange(byte sensor, byte range) {
//   for (int i = 0; i <= range; i++) {
//     if (ball_sensor == ((sensor + 16) - i) % 16 ||
//         ball_sensor == ((sensor + 16) + i) % 16 ) {
//       return true;
//     }
//   }
//   return false;
// }
