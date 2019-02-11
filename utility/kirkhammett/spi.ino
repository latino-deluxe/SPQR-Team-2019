
//initializing the spi pins and setting spi in master mode
void init_spi() {
  pinMode (_SCK, OUTPUT);
  pinMode (_MISO, INPUT);
  pinMode (_MOSI, OUTPUT);
  pinMode (_SS, OUTPUT);
  digitalWrite( _SS, HIGH); // Slave not selected
  SPCR = 81; //ARDUINO MEGA IS THE MASTER!
}//------------------------------------------------------------


//read from the spi slave that gives us the ball position
void spi_readfrom644l() //aggiorna ball_sensor e ball_distance
{
  PORTB = PORTB & 254;                       //slave selected = digitalWrite( _SS, LOW)
  spi_temp_byte = spi_tx_rx(255);            //sends 255 to the slave and stores the byte received
  PORTB = PORTB | 1;                         //slave disabled = digitalWrite( _SS, HIGH)
  if (spi_temp_byte == 255) return;          //if the data received is 255, the slave wasn't ready, uses the old ball informations

  ball_sensor = spi_temp_byte & 31;          //extracting the first 5 bits that tell us what ir sensor sees the ball
  ball_distance = (spi_temp_byte & 224) >> 5;//extracting the last 3 bits that tell us the ball distance
  return;
}//------------------------------------------------------------


//general function to receive and send 1 byte to the slave
byte spi_tx_rx( byte d)
{
  SPDR = d;                     //sending 1 byte to the slave
  while ( (SPSR & 128) == 0);   //wait until we got something back as a response

  return SPDR;                  //return the byte received
}//------------------------------------------------------------
