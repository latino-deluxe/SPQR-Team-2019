#include <SPI.h>

#define DISTANCE 0b00001111
#define DEGREES 0b00001010

byte c;
bool bSending = false;
byte bSendingByte;

void setup() {
  Serial.begin(9600);
  
  SPCR |= bit (SPE);

  pinMode(MISO, OUTPUT);
  SPI.attachInterrupt();

}

ISR(SPI_STC_vect ) {
  //the bool defines whether the slave is sending or not. 
  //It's assumed by both master and slave that the first communication is from master to slave
  if(bSending){
    //sends the previously prepared byte to the master
    SPCR = 64 & 127; // disble interrupt
    SPDR= bSendingByte;
    SPCR = 64 |128;  // enable interrupt
    Serial.print("Sending byte: ");
    Serial.println(bSendingByte);
  }else{
    //prepares output for next time it's asked, based on the received byte
    switch(SPDR){
      case DISTANCE:
        bSendingByte = 0b00111111;
        break;
      case DEGREES:
        bSendingByte = 0b11100011;
        break;
    }

    Serial.println();
    Serial.print("Received byte: ");
    Serial.print(SPDR);
    Serial.println(" - Preparing response byte");

    //sets SPDR (SPI byte) to be send next time
    SPDR = bSendingByte;
  }   

  //Negates bSesnding. If the slave has received, next time he will send and viceversa
  bSending = !bSending;    
}

void loop() {

}
