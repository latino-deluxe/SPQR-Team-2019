void init_bluetooth() {                                           //inizializza bluetooth
  bluetooth.begin(115200);
  tt=millis();
}

bool comunicazione (int intervallo) {                             //funzione di comunicazione

   if (bluetooth.available() > 0) {
    a = bluetooth.read();
  }
  if (a == 42) {
    compagno = true;
    digitalWrite(PIN_LED_G, HIGH);
    digitalWrite(PIN_LED_R, LOW);
    a = 0;
    old_timer = millis();
  }
  if ((millis() - old_timer ) > intervallo) {
    old_timer = millis();
    compagno = false;
    digitalWrite(PIN_LED_G, LOW);
    digitalWrite(PIN_LED_R, HIGH);
  }
  return compagno ;
}
