// #include "myspi.h"
// #include "vars.h"
// #include <SPI.h>
//
// SPISettings settings1(100000, MSBFIRST, SPI_MODE0);
//
// void initSPINew() {
//   //10 is the SS pin. Not the Gestapo one
//
//   Serial.begin(9600);
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
// void testBallNew(){
//   /**THIS PART COULD BE REFACTORED INTO A NICER THING, BUT IT'S JUST FOR EXAMPLE**/
//   SPI.beginTransaction(settings1);
//   digitalWrite(SS, LOW);
//   SPI.transfer(DEGREES);
//   digitalWrite(SS, HIGH);
//   SPI.endTransaction();
//   delay(SPI_DELAY);
//
//   //Sends a byte to get the response that the slave has prepared
//   SPI.beginTransaction(settings1);
//   digitalWrite(SS, LOW);
//   ball_degrees = SPI.transfer(0);
//   digitalWrite(SS, HIGH);
//   SPI.endTransaction();
//   delay(SPI_DELAY);
//
//   Serial.println(ball_degrees);
// }
