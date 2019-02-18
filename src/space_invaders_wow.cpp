// #include "goalie.h"
// #include "imu.h"
// #include "motors.h"
// #include "myspi_old.h"
// #include "pid.h"
// #include "position.h"
// #include "space_invaders.h"
// #include "us.h"
// #include "vars.h"
// #include <Arduino.h>
// #include <math.h>
//
// byte postSensor;
//
// void followBall() {}
//
// void space_invaders() {
//   int range;
//   int vel = 200;
//
//   // DEBUG_PRINT.println(zoneIndex);
//   if (zoneIndex == 7) {
//     if (ball_sensor >= 14 && ball_sensor <= 19) {
//       recenter(3.0);
//       preparePID(270, vel);
//     } else if (ball_sensor >= 1 && ball_sensor <= 6) {
//       recenter(3.0);
//       preparePID(90, vel);
//     } else {
//         recenter(3.0);
//     }
//   } else {
//     // if (!inSensorRange(postSensor, 2)) {
//     centerGoalPost();
//     //}
//   }
// }
//
// void centerGoalPost() {
//   int vel = 200;
//
//   if (zoneIndex < 6) {
//     preparePID(180, vel);
//   } else if (zoneIndex == 8) {
//     preparePID(270, vel);
//   } else if (zoneIndex == 6) {
//     preparePID(90, vel);
//   } else if (zoneIndex == 7) {
//     preparePID(0, 0);
//   }
//
//   postSensor = ball_sensor;
// }
//
// // void space_invaders() {
// //   if (us_px > 60)
// //     centerGoalPost();
// //   if (ball_sensor == 19 || ball_sensor == 18 ||
// //       (ball_sensor >= 0 && ball_sensor <= 2)) {
// //     recenter(2.0);
// //     brake();
// //   }
// //   if (ball_sensor >= 3 && ball_sensor <= 6) {
// //     recenter(2.0);
// //     brake();
// //     preparePID(90, 200);
// //     // recenter(2.0);
// //   }
// //   if (ball_sensor >= 14 && ball_sensor <= 17) {
// //     recenter(2.0);
// //     brake();
// //     preparePID(270, 200);
// //     // recenter(2.0);
// //   }
// //   if (ball_sensor >= 7 && ball_sensor <= 13)
// //     goalie();
// // }
//
// // void space_invaders() {
// //   if (zoneIndex >= 6) {
// //     float k = 0;
// //     float vel = 200;
// //     float dir = 0;
// //     float newDir;
// //
// //     float x, y;
// //
// //     if (us_px <= 45)
// //       k = 80;
// //     if (us_px >= 60)
// //       k = -80;
// //
// //     if (ball_sensor >= 14 && ball_sensor <= 19) {
// //       dir = 270;
// //     } else if (ball_seen >= 0 && ball_sensor <= 7) {
// //       dir = 90;
// //     }
// //
// //     // Something strange makes the cos() function work in radians instead
// //     of
// //     // degrees
// //     x = vel * cos(dir * PI / 180.0);
// //     y = vel * sin(dir * PI / 180.0);
// //
// //     // y += k;
// //
// //     newDir = atan2(y, x);
// //     newDir = (newDir * 4068) / 71;
// //     // atan2 restituisce i gradi in [-180,+180] e seguendo la circonf.
// //     // goniometrica.
// //     int map_angle = (int)newDir;
// //     map_angle = -(newDir) + 90; // Conversione + cambio di rotazione = nord
// //     0
// //                                 // gradi, senso orario positivo.
// //     map_angle = ((map_angle + 360) % 360) + 90;
// //
// //     if (map_angle != 360 && map_angle != 0) {
// //       BT.println(map_angle);
// //       preparePID(map_angle, vel);
// //     }
// //
// //   } else {
// //     centerGoalPost();
// //   }
// // }
