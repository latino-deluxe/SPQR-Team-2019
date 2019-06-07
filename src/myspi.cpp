// #include "myspi_old.h"
// #include "vars.h"
// #include <Arduino.h>
// #include <SPI.h>
//
// #define DISTANCE 0b00001111
// #define DEGREES 0b00001010
//
// #define SPI_DELAY 1
//
// SPISettings settings(100000, MSBFIRST, SPI_MODE0);
// byte mess;
// void initSPI() {
//   pinMode(SS_PIN, OUTPUT);
//   SPI.begin();
//
//   digitalWrite(SS_PIN, HIGH);
// }
//
// void readSPI() {
//   if (millis() - tspi > 10) {
//     mess = 0;
//     /**THIS PART COULD BE REFACTORED INTO A NICER THING, BUT IT'S JUST FOR EXAMPLE**/
//
//     //Sends a byte to the slave. The slave now prepares the response byte (The slave knows what to do)
//     SPI.beginTransaction(settings);
//     digitalWrite(SS, LOW);
//     SPI.transfer(DISTANCE);
//     digitalWrite(SS, HIGH);
//     SPI.endTransaction();
//     delay(SPI_DELAY);
//
//     //Sends a byte to get the response that the slave has prepared
//     SPI.beginTransaction(settings);
//     digitalWrite(SS, LOW);
//     mess = SPI.transfer(0);
//     digitalWrite(SS, HIGH);
//     SPI.endTransaction();
//     delay(SPI_DELAY);
//
//     if(mess != 255){
//       ball_sensor = mess & 0b00011111;
//       ball_distance = (mess & 0b11100000) >> 5;
//     }
//
//     DEBUG_PRINT.println(mess);
//
//     //Waits between the printing and the next SPI communication. Serial printing slows down a lot
//     delay(SPI_DELAY);
//
//       //Sends a byte to the slave. The slave now prepares the response byte (The slave knows what to do)
//     SPI.beginTransaction(settings);
//     digitalWrite(SS, LOW);
//     SPI.transfer(DEGREES);
//     digitalWrite(SS, HIGH);
//     SPI.endTransaction();
//     delay(SPI_DELAY);
//
//     //Sends a byte to get the response that the slave has prepared
//     SPI.beginTransaction(settings);
//     digitalWrite(SS, LOW);
//     mess = SPI.transfer(0);
//     digitalWrite(SS, HIGH);
//     SPI.endTransaction();
//     delay(SPI_DELAY);
//
//     tspi = millis();
//     DEBUG_PRINT.println(mess);
//   }
//   return;
// }
//
// void ball_read_position() {
//   // getting our data from our spi slave
//   readSPI(); // in any other case the ball is seen by the robot
//   ball_seen = true;
//   if (ball_distance == 6) { // if the distance is 6 it means that the robot
//                             // doesnt see the ball
//     ball_seen = false;
//   }
//
//   if (old_s_ball != ball_sensor) {
//     old_s_ball = ball_sensor;
//     // how much time the same sensor sees the ball. Used in keeper
//     time_s_ball = millis();
//   }
//   return;
// }
//
// void testBall() {
//   ball_read_position();
//   DEBUG_PRINT.print(ball_sensor);
//   DEBUG_PRINT.print(" | ");
//   DEBUG_PRINT.println(ball_distance);
//
//   delay(500);
// }
//
// bool inSensorRange(byte sensor, byte range) {
//   // BT.println(lineball_sensor);
//   for (int i = 0; i <= range; i++) {
//     // BT.print(getSensorIndex(sensor - i));
//     // BT.print(" | ");
//     // BT.println(getSensorIndex(sensor + i))
//     if (ball_sensor == getSensorIndex(sensor - i) ||
//         ball_sensor == getSensorIndex(sensor + i)) {
//       return true;
//     }
//   }
//   return false;
// }
//
// byte getSensorIndex(byte sensor) {
//   sensor = sensor % 20;
//   return sensor < 0 ? (byte)(20 + sensor) : (byte)(sensor);
// }
