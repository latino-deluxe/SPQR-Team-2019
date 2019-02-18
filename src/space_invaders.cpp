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
// void space_invaders() {
//   if (zoneIndex == 7) {
//     double k = 0;
//     float vel = 100;
//     float dir = 0;
//     float newDir;
//
//     float x, y;
//
//     /*
//     correggo sta funzione ignorante aggiungendo ignoranza ahah
//     -bello il tentativo di scomporre in x,y mi piasce
//     -cercate di tenere x e y scalati in -1, +1, non moltiplicate per la
//     velocità -per come ho pensato io i vettori:
//       x = 1 -> nord, -1 -> sud
//       y = 1 -> destra, -1 -> sinistra
//     */
//     if(us_px <= 16) k = map((double)us_px, 16, 0, 0, 1);
//     if(us_px >= 40) k = -map((double)us_px, 40, 150, 0, 1);
//
//     DEBUG_PRINT.print(us_px);
//     DEBUG_PRINT.print(" ");
//     DEBUG_PRINT.println(k);
//
//     /*se il robot sta troppo indietro allora k aggiunge una componente y
//     positiva, quindi si muove verso avanti insieme al movimento per la palla
//     se il robot sta troppo avanti allora k aggiunge una componente y
//     negativa, quindi si muove verso dietro insieme al movimento per la palla
//     ora ho fatto una proporzione a caso, dovete testarla, in ogni caso ho
//     fatto corrispondere una correzione potente in avanti se il robot sta
//     mooolto vicino e una correzione sempre più potente in indietro se il
//     robot sta sempre più lontano. su devc++ ho dovuto mettere tutte le
//     variabili double, sennò map (copiato dalla libreria di arduino) mi dava
//     sempre zero, guardate se su arduino fa lo stesso
//      */
//     if (ball_sensor >= 14 && ball_sensor <= 19) {
//       dir = 270;
//     } else if (ball_sensor >= 0 && ball_sensor <= 7) {
//       dir = 90;
//     }
//
//     /*  tutte le funzioni trigonometriche in c funzionano in radianti
//       x è sin e y è cos perchè se disegnate il vettore direzione nella
//       circonferenza goniometrica scoprite che l'angolo (direzione) è l'angolo
//       opposto a quello che si usa convezionalmente, quindi o usate x =
//       cos(90-dir) oppure sin(dir), stessa cosa per la y. non moltiplicate per
//       la velocità, tanto poi la passate a preparepid manualmente.
//     */
//     x = sin(dir * PI / 180.0);
//     y = cos(dir * PI / 180.0);
//
//     //aggiungo k al vettore y per influenzare il movimento verticale
//     y += k;
//     //il movimento orizzontale non lo tocco, dipende solo dalla direzione per
//     inseguire la palla
//
//     newDir = atan2(y, x);
//     newDir = newDir * 180 / 3.14; // atan2 restituisce i gradi in [-180,+180]
//     e
//                                   // seguendo la circonf. goniometrica.
//
//     int map_angle = 0;
//     map_angle = (int)newDir;
//     map_angle = -(newDir) + 90; // Conversione + cambio di rotazione = nord 0
//                                  // gradi, senso orario positivo.
//     map_angle = (map_angle + 360) % 360;
//
//     /*map angle contiene la direzione in dir però influenzata verticalmente
//     dal valore dell'ultrasuono esempio se us_px = 45, allora map_angle =
//     circa dir se us_px = 200, e dir = 90, map_angle = 126 se us_px = 20, e
//     dir = 90, map_angle = 60 spero di aver capito l'idea che avevi, sennò ho
//     fatto una piccola lezione di trigonometria e scomposizione della
//     direzione lol
//     */
//     BT.println(map_angle);
//
//     preparePID(map_angle, vel);
//
//   } else {
//     centerGoalPost();
//   }
// }
//
// // void space_invaders() {
// //   int vel = 200;
// //
// //   if (us_px >= 30 || us_dx < 35 || us_sx < 35 || !ball_seen ){
// //     centerGoalPost();
// //   }else{
// //     preparePID(0, 0);
// //     if (ball_sensor >= 14 && ball_sensor <= 18) {
// //       preparePID(270, vel);
// //       return;
// //     }
// //     if (ball_sensor >= 1 && ball_sensor <= 6) {
// //       preparePID(90, vel);
// //       return;
// //     }
// //     centerGoalPost();
// //   }
// // }
//
// void centerGoalPost() {
//
//   int vel = 150;
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
// }
//
// // void centerGoalPost() {
// //     int larghezza = 0;
// //     if (status_x == CENTRO) {
// //       if (status_y == CENTRO) {
// //         preparePID(180, 150);
// //       }
// //       else if (status_y == SUD) {
// //         if (us_px > 20) preparePID(180, 110);
// //         else if (us_px < 15) preparePID(0, 130);
// //         else preparePID(0,0);
// //       }
// //       else goCenter();
// //     }
// //     else if (status_x == 255) {
// //       if (us_px > 50) preparePID(180, 110);
// //       else if (us_px < 30) preparePID(0, 130);
// //       else preparePID(0,0);
// //     }
// //     else goCenter();
// // }
