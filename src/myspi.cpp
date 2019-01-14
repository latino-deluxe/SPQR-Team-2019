// #include <Arduino.h>
// #include "myspi.h"
// #include <SPI.h>
// #define DISTANCE 0b00001111
// #define DEGREES 0b00001010
//
// #define SPI_DELAY 1
// #define SS 10
//
// SPISettings settings(100000, MSBFIRST, SPI_MODE0);
// byte ball_distance;
// byte ball_sensor;
//
// void initSPI() {
//   pinMode(SS, OUTPUT);
//   digitalWrite(SS, HIGH);  // ensure 10 stays high for now
//
//   // Put SCK, MOSI, 10 pins into output mode
//   // also put SCK, MOSI into LOW state, and 10 into HIGH state.
//   // Then put SPI hardware into Master mode and turn SPI on
//   SPI.begin ();
//
//   // Slow down the master a bit
//   SPI.setClockDivider(SPI_CLOCK_DIV8);
// }
//
// void readBall(){
//   /**THIS PART COULD BE REFACTORED INTO A NICER THING, BUT IT'S JUST FOR EXAMPLE**/
//
//
//     //Sends a byte to the slave. The slave now prepares the response byte (The slave knows what to do)
//   SPI.beginTransaction(settings);
//   digitalWrite(SS, LOW);
//   SPI.transfer(DEGREES);
//   digitalWrite(SS, HIGH);
//   SPI.endTransaction();
//   delay(SPI_DELAY);
//
//   //Sends a byte to get the response that the slave has prepared
//   SPI.beginTransaction(settings);
//   digitalWrite(SS, LOW);
//   ball_sensor = SPI.transfer(0);
//   digitalWrite(SS, HIGH);
//   SPI.endTransaction();
//   delay(SPI_DELAY);
//
//   Serial.println(ball_sensor);
// }
