long t = 0;
byte i = 0;
byte b = 0;

long last = 0;
bool comrade = false;

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);

}

void read() {
  while(Serial3.available()){   
    Serial.write((char)Serial3.read());
    last = millis();
  }
}

void loop() {
  digitalWrite(13, 1);
  if(millis() - last > 500) comrade = false;
  
  if(millis() - t >= 250){
    b = 48+i;
    Serial3.write(b);
    t = millis();
    i = (i+1)%9;
  }
  read();
}
