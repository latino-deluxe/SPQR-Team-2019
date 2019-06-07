#include "Arduino.h"
#include "vars.h"

byte ballReadNano;

void readBallNano() {
    if(Serial4.available() > 0) ballReadNano = Serial4.read();
    if(ballReadNano == 255) return;

    ball_sensor = (ballReadNano & 00011111);
    ball_distance = ballReadNano >> 5;
    ball_seen = ball_distance <= 5;
}

void testBallNano() {
  readBallNano();
  // DEBUG_PRINT.print(ball_sensor);
  // DEBUG_PRINT.print(" | ");
  // DEBUG_PRINT.println(ball_distance);
  DEBUG_PRINT.println(ballReadNano);
  delay(500);
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
