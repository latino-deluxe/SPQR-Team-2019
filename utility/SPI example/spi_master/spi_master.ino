// Written by Nick Gammon
// February 2011

#include <SPI.h>

void setup (void)
{

  //10 is the SS pin. Not the Gestapo one
  
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);  // ensure 10 stays high for now

  // Put SCK, MOSI, 10 pins into output mode
  // also put SCK, MOSI into LOW state, and 10 into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin ();

  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  
}  // end of setup


void loop (void)
{

  char c;

  // enable Slave Select
  digitalWrite(10, LOW);    // 10 is pin 10

  // send test string
  for (const char * p = "Hello, world!\n" ; c = *p; p++){
    Serial.print(c);
    SPI.transfer (c);
  }
  // disable Slave Select
  digitalWrite(10, HIGH);

  delay (1000);  // 1 seconds delay 
}  // end of loop
