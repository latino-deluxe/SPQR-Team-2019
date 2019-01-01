// Written by Nick Gammon
// February 2011

#include <SPI.h>

#define DISTANCE 0b00001111
#define DEGREES 0b00001010

#define SPI_DELAY 150
#define SS 10

SPISettings settings(100000, MSBFIRST, SPI_MODE0);
byte mess;

void setup (void)
{

  //10 is the SS pin. Not the Gestapo one
  
  Serial.begin(9600);
  pinMode(SS, OUTPUT);
  digitalWrite(SS, HIGH);  // ensure 10 stays high for now

  // Put SCK, MOSI, 10 pins into output mode
  // also put SCK, MOSI into LOW state, and 10 into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin ();

  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  
}  // end of setup


void loop (void) {

  /**THIS PART COULD BE REFACTORED INTO A NICER THING, BUT IT'S JUST FOR EXAMPLE**/


  Serial.println();
  Serial.print("Sending byte: ");
  Serial.println(DISTANCE);

  //Sends a byte to the slave. The slave now prepares the response byte (The slave knows what to do)
  SPI.beginTransaction(settings);
  digitalWrite(SS, LOW);
  SPI.transfer(DISTANCE);
  digitalWrite(SS, HIGH);
  SPI.endTransaction();
  delay(SPI_DELAY);

  //Sends a byte to get the response that the slave has prepared
  Serial.print("Now getting response for previously asked byte: ");
  SPI.beginTransaction(settings);
  digitalWrite(SS, LOW);
  mess = SPI.transfer(0);
  digitalWrite(SS, HIGH);
  SPI.endTransaction();

  Serial.println(mess);
  delay(SPI_DELAY);


  //Does the same thing but with different bytes
  Serial.println();
  Serial.print("Sending byte: ");
  Serial.println(DEGREES);
  
  SPI.beginTransaction(settings);
  digitalWrite(SS, LOW);
  SPI.transfer(DEGREES);
  digitalWrite(SS, HIGH);
  SPI.endTransaction();
  delay(SPI_DELAY);

  
  Serial.print("Now getting response for previously asked byte: ");
  SPI.beginTransaction(settings);
  digitalWrite(SS, LOW);
  mess = SPI.transfer(0);
  digitalWrite(SS, HIGH);
  SPI.endTransaction();

  Serial.println(mess);
  delay(SPI_DELAY);



}
