#include <SPI.h>

#define DISTANCE 0b00001111
#define DEGREES 0b00001010

byte c;
bool bSending = false;
byte bSendingByte;

void setup() {
  Serial.begin(9600);

	//THIS REGISTER IS ATMEGA-328P SPECIFIC
  SPCR |= bit (SPE);

  pinMode(MISO, OUTPUT);
  SPI.attachInterrupt();

}

//REMOVED SERIAL PRINT TO SPEED UP

ISR (SPI_STC_vect) {
  //the bool defines whether the slave is sending or not.
  //It's assumed by both master and slave that the first communication is from master to slave
  if(bSending) {
	//THOSE REGISTERS ARE ATMEGA-328P SPECIFIC
      //sends the previously prepared byte to the master
      SPCR = 64 & 127; // disble interrupt
      SPDR= bSendingByte;
      SPCR = 64 |128; // enable interrupt
  }else{
    //prepares output for next time it's asked, based on the received byte
    switch(SPDR) {
    case DISTANCE:
      bSendingByte = 0b00111111;
      bSending = !bSending;
      break;
    case DEGREES:
      bSendingByte = 0b11100011;
      bSending = !bSending;
      break;
    default:
      break;
    }

    //sets SPDR (SPI byte) to be send next time
    SPDR = bSendingByte;
  }
}

void loop() {

}
