void setup()
{
  SerialTest.begin(115200);                                   //Velocità default di 115200
  I2c.begin();                                                //inizializza I2C
  I2c.timeOut(12);                                            //fissa a 12 ms il tempo di attesa della risposta
  gpio_setup();                                               //inizializza GPIO
  init_gpio_motors();                                         //inizializza GPIO motori
  init_linesensors();                                         //abilita i sensori di linea a chiamare interrupt come PCINT2
  init_spi();                                                 //inizializza comunicazione spi
  init_imu();                                                 //inizializza imu
  test_toggle_outputs(1);                                     //on tutti gli ouput
  init_omnidirectional_sins();                                //inizializza seni
  test_toggle_outputs(0);                                     //off tutti gli output
  linea[0] = 63;                                              //prima degli interrupt sensori linea ok
  SWS = digitalRead(SWITCH_SX);                               //lettura switch sinistro
  init_bluetooth();                                           //inizializza comunicazione BT
  valStringY.reserve(30);                                     //riserva 30byte per le stringhe
  valStringB.reserve(30);
  //initial_p();                                              //inizializza sensore presa palla
  tone(22, 1000, 500);                                        //tone iniziale
  //take_on_me();                                             //TAKE ON ME - AHA
  //imperial_march();                                         //IMPERIAL MARCH - STAR WARS
  //super_mario();                                            //SUPER MARIO - NINTENDO
  return;
}


void loop() {
  SWD = digitalRead(SWITCH_DX);                                         //lettura switch destro per cambio porta
  if (SWD == HIGH) p = 1;
  else  p = 0;

  //controllo e test-------------------
  if ((flagtest == true) || (SerialTest.available() > 0)) rtest();      //test

  update_sensors_all();
  /*legge ultrasuoni bussola e palla
     aggiorna le variabili globali:
        us_fr us_px us_dx us_sx (cm)
        imu_current_euler (gradi 0-359)
        ball_sensor (0-19)
        ball_distance (0-6)
        ball_seen (true/false)
  */
  if (flag_interrupt == true )                                            //c'e' stato un interrupt
  {
    gest_interrupt();                                                     //va a gestire l'interrupt
  }

  SWS = digitalRead(SWITCH_SX);                                           //lettura switch sinistro
  ruolo = SWS;                                                            //cambio ruolo
  
  update_location_complete();

  //COMUNICAZIONE BT
  if (count < 30 ) {
    count++;
  }
  else {
    count = 0;
    bluetooth.write(42);
  }

  //comunicazione(500);
  compagno=true;
  

  if (ball_seen == true)                                                  //SCELTA DEI RUOLI TRAMITE SWITCH E BT
  {
    if (ruolo == HIGH) {
      if (compagno == true) goalie();
      else space_invaders();
    }
    else {
      if (compagno == true) space_invaders();
      else space_invaders();
    }
  }
  else {
    if (ruolo == HIGH) {
      if (compagno == true) ritornacentro();
      else centroporta();
    }
    else {
      if (compagno == true) centroporta();
      else centroporta();
    }
  }
  return;
}


//SETTING PINS TO INPUT OR OUTPUT
void gpio_setup()
{
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_Y, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_PIEZO, OUTPUT);
  pinMode(PIN_BUTTON1, INPUT_PULLUP);
  pinMode(PIN_BUTTON2, INPUT_PULLUP);
  pinMode(PIN_BUTTON3, INPUT_PULLUP);
  pinMode(SWITCH_SX, INPUT_PULLUP);
  pinMode(SWITCH_DX, INPUT_PULLUP);
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);
  pinMode(A12, INPUT);
  pinMode(A13, INPUT);
  return;
}
