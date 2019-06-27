#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  char a = 0;

  do {
    Serial.println("What to do?\n\t1) Scan for i2C devices\n\t2) Change US address\n\t3) Test US measures\nRemember to put the newline mode in \"no line ending\"");
    while (Serial.available() <= 0);
    while (Serial.available() >  0) a = (char) Serial.read();

  } while (a != '1' && a != '2' && a != '3');

  switch (a) {
    case '1':
      scanI2C();
      break;
    case '2':
      changeAddressCLI();
      break;
    case '3':
      readUSCLI();
      break;
  }
}

void scanI2C() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++ ) {
    // The i2c_scanner uses the return value of
    // the Write.e      ndTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");
      Serial.print("I2C device found at address :");
      Serial.print(address, DEC);
      Serial.println("  !");


      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0) Serial.println("No I2C devices found\n");
  else Serial.println("done\n");
}


void readUS(int address) {

  Serial.print("Measuring address ");
  Serial.print(address);
  Serial.println(" send any key to stop measuring");

  while(Serial.available() <= 0) {
    int reading = 0;
    
    // step 1: instruct sensor to read echoes
    Wire.beginTransmission(address);
    Wire.write(byte(0x00));
    Wire.write(byte(0x51));
    Wire.endTransmission();
    
    // step 2: wait for readings to happen
    delay(70);
    
    // step 3: instruct sensor to return a particular echo reading
    Wire.beginTransmission(address);
    Wire.write(byte(0x02));
    Wire.endTransmission();
    
    // step 4: request reading from sensor
    Wire.requestFrom(address, 2);
    
    // step 5: receive reading from sensor
    if (2 <= Wire.available()) {
      reading = Wire.read();
      reading = reading << 8;
      reading |= Wire.read();
      Serial.println(reading);
    }
  delay(50);
  }
  while(Serial.available() > 0) Serial.read();
}

void readUSCLI() {
  Serial.println("Testing US measurement");
  
  char a = 0;

  do {
    Serial.println("Please input the US address from the menu below\n\t1) 112\n\t2) 113\n\t3) 114\n\t4) 115");
    while (Serial.available() <= 0);
    while (Serial.available() >  0) a = (char) Serial.read();

  } while (a != '1' && a != '2' && a != '3' && a != '4');
  
  switch (a) {
    case '1':
      readUS(112);
      break;
    case '2':
      readUS(113);
      break;
    case '3':
      readUS(114);
      break;
    case '4':
      readUS(115);
      break;
  }

}

void changeAddressCLI() {
  Serial.println("Changing US i2C address");
  
  char a = 0;
  char b = 0;
  byte add1 = 0;
  byte add2 = 0;

  do {
    Serial.println("Please input the current US address from the menu below\n\t1) 112\n\t2) 113\n\t3) 114\n\t4) 115");
    while (Serial.available() <= 0);
    while (Serial.available() >  0) a = (char) Serial.read();

  } while (a != '1' && a != '2' && a != '3' && a != '4');

  do {
    Serial.println("Please input the current US address from the menu below\n\t1) 112\n\t2) 113\n\t3) 114\n\t4) 115");
    while (Serial.available() <= 0);
    while (Serial.available() >  0) b = (char) Serial.read();

  } while (b != '1' && b != '2' && b != '3' && b != '4');

  switch (a) {
    case '1':
      add1 = (112);
      break;
    case '2':
      add1 = (113);
      break;
    case '3':
      add1 = (114);
      break;
    case '4':
      add1 = (115);
      break;
  }
  
  switch (b) {
    case '1':
      add2 = (224);
      break;
    case '2':
      add2 = (226);
      break;
    case '3':
      add2 = (228);
      break;
    case '4':
      add2 = (230);
      break;
  }

  changeAddress(add1, add2);

}


// The following code changes the address of a Devantech Ultrasonic Range Finder (SRF10 or SRF08)
// usage: changeAddress(0x70, 0xE6);

void changeAddress(byte oldAddress, byte newAddress) {
  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0xA0));
  Wire.endTransmission();

  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0xAA));
  Wire.endTransmission();

  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0xA5));
  Wire.endTransmission();

  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(newAddress);
  Wire.endTransmission();

  Serial.print("Changed address! From ");
  Serial.print(oldAddress);
  Serial.print(" to ");
  Serial.println(newAddress / 2);
}
