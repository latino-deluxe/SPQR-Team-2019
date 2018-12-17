#include "libs.h"

void loop() {
  //Serial.println(digitalRead(5));
  Serial.println("ciao");
  delay(1000);
}

void testInterrupt(){
  for(int i = 0; i < 10; i++){
  Serial.println("TEST INTERRUPT");
}
