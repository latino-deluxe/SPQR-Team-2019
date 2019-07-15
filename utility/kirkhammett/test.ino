
// logica dei test con serial monitor (PC attaccato)
//
//  1     >test ultrasuoni<
//  2     >test bussola<
//  3     >test sensori linea<
//  4     >test PID (recenter a fermo con SM)<
//  5     >test PID (recenter veloce senza SM)<
//  6     >test sensori palla<
//  7     >test motori con il robot tenuto sospeso
//  8     >test orizzontale/verticale<
//  9     >test posizione campo (1..9)<
//  a     >controllo pulsanti e sw<
//  b     >controllo led e buzzer<
//  c     >interrogazione I2C ultrasuoni e bussola<
//  d     >test cosa vede dopo interrupt
//  e     >visualizza interrupt
//  f     >ferma i motori
//  g     >tempo frenata
//  h     >visualizzo interrupt in gioco
//  k     >test camera porta

// altri caratteri       >usi futuri<


void rtest()   // utente puó digitare da tastiera il test da effettuare e cambiarlo durante il suo svolgimento
{
  byte test;
  brake();
  SerialTest.println("   Test disponibili");
  SerialTest.println("1  test ultrasuoni");
  SerialTest.println("2  test bussola");
  SerialTest.println("3  test sensori linea");
  SerialTest.println("4  test PID (recenter a fermo con SM)");
  SerialTest.println("5  test PID (senza SM) Attenzione ricentro VELOCE");
  SerialTest.println("6  test sensori palla");
  SerialTest.println("7  test motori mantenere il robot sospeso");
  SerialTest.println("8  test orizzontale/verticale");
  SerialTest.println("9  test posizione campo (1..9)");
  SerialTest.println("a  controllo pulsanti e sw");
  SerialTest.println("b  controllo led e buzzer");
  SerialTest.println("c  interrogazione I2C ultrasuoni e bussola");
  SerialTest.println("d  test cosa vede dopo interrupt");
  SerialTest.println("e  visualizza interrupt dopo frenata");
  SerialTest.println("f  ferma i motori");
  SerialTest.println("g  tempo frenata");
  SerialTest.println("h  visualizzo interrupt in gioco");

  SerialTest.println();
  SerialTest.println("velocitá 115200 e NESSUN FINE RIGA >no LF<");
  SerialTest.println("digitare il test (1..c) da eseguire e cliccare invia >no LF<");
  SerialTest.println("digitare 0 per uscire dai test >no LF<");
  SerialTest.println();

  while (SerialTest.available() == 0);
  do
  {
    test = SerialTest.read();
    SerialTest.println();
    SerialTest.print("Test "); SerialTest.print(char(test));

    if (test == '0') SerialTest.println("  Esce dal test e torna a giocare");
    if (test == '1') SerialTest.println("  test ultrasuoni");
    if (test == '2') SerialTest.println("  test bussola");
    if (test == '3') SerialTest.println("  test sensori linea");
    if (test == '4') SerialTest.println("  test PID (recenter a fermo con SM)");
    if (test == '5') SerialTest.println("  test PID (senza SM) Attenzione ricentro VELOCE");
    if (test == '6') SerialTest.println("  test sensori palla");
    if (test == '7') SerialTest.println("  test motori mantenere il robot sospeso");
    if (test == '8') SerialTest.println("  test orizzontale/verticale");
    if (test == '9') SerialTest.println("  test posizione campo (1..9)");
    if (test == 'a') SerialTest.println("  controllo pulsanti e sw");
    if (test == 'b') SerialTest.println("  controllo led e buzzer");
    if (test == 'c') SerialTest.println("  interrogazione I2C ultrasuoni e bussola");
    if (test == 'd') SerialTest.println("  test cosa vede dopo interrupt");
    if (test == 'e') SerialTest.println("  visualizza interrupt dopo frenata");
    if (test == 'f') SerialTest.println("  ferma i motori");
    if (test == 'g') SerialTest.println("  tempo frenata");
    if (test == 'h') SerialTest.println("  visualizza interrupt in gioco");
    if (test == '0')
    {
      SerialTest.println("  Fine test");
      flagtest = false;
      return;
    }
    do   // finché non riceve contrordine
    {
      switch (test)
      {
        case '1'://ultrasuoni
          us_test();
          delay (2000);
          break;
        case '2'://bussola
          imu_test();
          delay (2000);
          break;
        case '3'://sensori linea
          line_test();
          delay (500);
          break;
        case '4'://PID recenter da fermo
          PID_test(true);
          delay (500);
          break;
        case '5'://PID recenter veloce no SM
          PID_test(false);
          break;
        case '6'://sensori palla
          palla_test();
          delay (500);
          break;
        case '7'://motori
          motori_test();
          break;
        case '8'://test X e Y
          XY_test();
          delay (2000);
          break;
        case '9'://test zona (1..9)
          zona_test();
          delay (2000);
          break;
        case 'a'://controllo pulsanti e sw
          switch_test();
          delay (2000);
          break;
        case 'b'://controllo led e buzzer
          output_test();
          delay (2000);
          break;
        case 'c'://interrogazione I2C ultrasuoni e bussola
          I2C_test();
          delay (2000);
          break;
        case 'd'://test frenata dopo interrupt
          frenata_test();
          fermo();
          break;
        case 'e'://test visualizzo interrupt durante frenata
          visualizzo_interrupt();
          break;
        case 'f'://ferma i motori
          fermo();
          break;
        case 'g'://tempo frenata
          tempo_frenata();
          break;
        case 'h'://visualizza interrupt in gioco
          visualizzo_gioco();
          break;
        case 'k':
          test_porta();
          break;
        default:
        
          break;
      }
    }
    while (SerialTest.available() == 0);
  }
  while (test != '0');
}//----------------------------------------------------------


void us_test()
{
  us_start_measuring();
  delay(70);
  us_receive();

  us_fr = us_values[0]; //FRONT US
  us_dx = us_values[1]; //DX US
  us_px = us_values[2]; //BACK US
  us_sx = us_values[3]; //SX US

  SerialTest.print ("front      : "); SerialTest.println(us_fr);
  SerialTest.print ("destro     : "); SerialTest.println(us_dx);
  SerialTest.print ("posteriore : "); SerialTest.println(us_px);
  SerialTest.print ("sinistro   : "); SerialTest.println(us_sx);
  SerialTest.print ("larghezza  : "); SerialTest.println(us_sx + us_dx + robot);
  SerialTest.print ("lunghezza  : "); SerialTest.println(us_fr + us_px + robot);
  SerialTest.println();

  return;
}//-----------------------------------------------------------


void imu_test()
{
  SerialTest.print ("angolo      : "); SerialTest.println(read_euler());

  return;
}//-----------------------------------------------------------


void line_test()//0 vede la linea e 1 no
{
  SerialTest.println ("0 = vede la linea");
  SerialTest.print ("sensore S1  : "); SerialTest.println(digitalRead(A8));
  SerialTest.print ("sensore S2  : "); SerialTest.println(digitalRead(A9));
  SerialTest.print ("sensore S3  : "); SerialTest.println(digitalRead(A10));
  SerialTest.print ("sensore S4  : "); SerialTest.println(digitalRead(A11));
  SerialTest.print ("sensore S5  : "); SerialTest.println(digitalRead(A12));
  SerialTest.print ("sensore S6  : "); SerialTest.println(digitalRead(A13));
  SerialTest.println();
  return;
}//-------------------------------------------------------

void PID_test(bool SM)// ruotare il robot a mano una volta e vedere se si raddrizza
{
  imu_current_euler = read_euler();
  recenter(1.0);
  if (SM)
  {
    SerialTest.print ("bussola ante : "); SerialTest.print(imu_current_euler);
    SerialTest.print (" bussola post : "); SerialTest.println(read_euler());

  }
  return;
}//-------------------------------------------------------


void palla_test()
{
  spi_readfrom644l();//legge i sensori
  SerialTest.print ("sensore n.  : "); SerialTest.print(ball_sensor);
  SerialTest.print(" distanza    : "); SerialTest.println(ball_distance);

  return;
}//-------------------------------------------------------

void motori_test()
{
  //test motore 1,2,3
  for (int i = 1; i < 4; i++)
  {
    SerialTest.print("motore n. :"); SerialTest.print(i); SerialTest.print(" orario, ");
    digitalWrite(INA_MOT[i], 1);
    digitalWrite(INB_MOT[i], 0);
    analogWrite (PWM_MOT[i], 100);
    delay(1000);
    SerialTest.print(" stop ");
    digitalWrite(INA_MOT[i], 0);
    digitalWrite(INB_MOT[i], 0);
    analogWrite (PWM_MOT[i], 0);
    delay(300);
    SerialTest.print(", antiorario,");
    digitalWrite(INA_MOT[i], 0);
    digitalWrite(INB_MOT[i], 1);
    analogWrite (PWM_MOT[i], 100);
    delay(1000);
    SerialTest.println(" stop.");
    digitalWrite(INA_MOT[i], 0);
    digitalWrite(INB_MOT[i], 0);
    analogWrite (PWM_MOT[i], 0);
    delay(300);
  }
  SerialTest.println();
  return;
}//-------------------------------------------------------


void XY_test()
{
  //lettura degli ultrasuoni
  us_start_measuring();
  delay(70);
  us_receive();

  us_fr = us_values[0]; //FRONT US
  us_dx = us_values[1]; //DX US
  us_px = us_values[2]; //BACK US
  us_sx = us_values[3]; //SX US

  /*
    us_fr = 40; //FRONT US
    us_dx = 80 ; //DX US
    us_px = 131; //BACK US
    us_sx = 80; //SX US
  */

  old_status_x = status_x;
  old_status_y = status_y;
  WhereAmI(); //calcola la posizione x e y
  SerialTest.print ("larghezza  : "); SerialTest.println(us_sx + us_dx + robot);
  SerialTest.print ("lunghezza  : "); SerialTest.println(us_fr + us_px + robot);
  SerialTest.println();
  SerialTest.print("x = "); SerialTest.print(status_x);
  switch (status_x)
  {
    case EST:
      SerialTest.println(" EST");
      break;
    case OVEST:
      SerialTest.println(" OVEST");
      break;
    case CENTRO:
      SerialTest.println(" CENTRO");
      break;
    case 255:
      SerialTest.println(" NON LO SO");
      break;
  }

  SerialTest.print("y = "); SerialTest.print(status_y);
  switch (status_y)
  {
    case NORD:
      SerialTest.println(" NORD");
      break;
    case SUD:
      SerialTest.println(" SUD");
      break;
    case CENTRO:
      SerialTest.println(" CENTRO");
      break;
    case 255:
      SerialTest.println(" NON LO SO");
      break;
  }


  return;
}//-------------------------------------------------------

void zona_test()
{
  //lettura degli ultrasuoni
  us_start_measuring();
  delay(70);
  us_receive();

  us_fr = us_values[0]; //FRONT US
  us_dx = us_values[1]; //DX US
  us_px = us_values[2]; //BACK US
  us_sx = us_values[3]; //SX US

  /*
    us_fr = 40; //FRONT US
    us_dx = 30 ; //DX US
    us_px = 131; //BACK US
    us_sx = 100; //SX US
  */
  old_status_x = status_x;
  old_status_y = status_y;

  WhereAmI(); //calcola la posizione x e y

  cerco_zona();

  SerialTest.print("Zona n. :  "); SerialTest.print(currentlocation);
  switch (currentlocation)
  {
    case CENTRO_CENTRO:
      SerialTest.println(" CENTRO_CENTRO");
      break;
    case CENTRO_EST:
      SerialTest.println(" CENTRO_EST");
      break;
    case CENTRO_OVEST:
      SerialTest.println(" CENTRO_OVEST");
      break;
    case NORD_CENTRO:
      SerialTest.println(" NORD_CENTRO");
      break;
    case NORD_EST:
      SerialTest.println(" NORD_EST");
      break;
    case NORD_OVEST:
      SerialTest.println(" NORD_OVEST");
      break;
    case SUD_CENTRO:
      SerialTest.println(" SUD_CENTRO");
      break;
    case SUD_EST:
      SerialTest.println(" SUD_EST");
      break;
    case SUD_OVEST:
      SerialTest.println(" SUD_OVEST");
      break;
    case 255:
      SerialTest.println(" NON LO SO");
      break;
  }

  return;
}//-------------------------------------------------------


//checking if some button/switch is pressed at the startup SOLO PER USI FUTURI
void switch_test() {
  byte b1, b2, b3, bdx, bsx;
  b1 = digitalRead(PIN_BUTTON1);
  b2 = digitalRead(PIN_BUTTON2);
  b3 = digitalRead(PIN_BUTTON3);
  bdx = digitalRead(SWITCH_DX);
  bsx = digitalRead(SWITCH_SX);

  SerialTest.print("PIN_BUTTON1 "); SerialTest.println(b1);
  SerialTest.print("PIN_BUTTON2 "); SerialTest.println(b2);
  SerialTest.print("PIN_BUTTON3 "); SerialTest.println(b3);
  SerialTest.print("SWITCH_DX   "); SerialTest.println(bdx);
  SerialTest.print("SWITCH_SX   "); SerialTest.println(bsx);
  SerialTest.println();
  return;
}//--------------------------------------------------------


//turns off or on all the outputs (leds and stuff) (1 for on, 0 for off);
void output_test()
{
  SerialTest.println("Test LED ROSSO ");
  digitalWrite(PIN_LED_R, HIGH);
  delay(2000);
  digitalWrite(PIN_LED_R, LOW);
  SerialTest.println("Test LED GIALLO ");
  digitalWrite(PIN_LED_Y, HIGH);
  delay(2000);
  digitalWrite(PIN_LED_Y, LOW);
  SerialTest.println("Test LED VERDE ");
  digitalWrite(PIN_LED_G, HIGH);
  delay(2000);
  digitalWrite(PIN_LED_G, LOW);

  SerialTest.println("Test BUZZER ");
    tone(PIN_PIEZO,1000,500); 
  delay(3000);
  digitalWrite(PIN_PIEZO, LOW);


  return;
}//----------------------------------------------------------


void I2C_test()
{
  //prova a far partire gli ultrasuoni

  SerialTest.println("Interrogazione dei sensori I2C");
  if ((I2c.write(112, 0x00, 0x51) != 0))
  {
    SerialTest.println("Sensore ultrasuoni FRONTALE indirizzo 112 NON RISPONDE");
  }
  if ((I2c.write(113, 0x00, 0x51) != 0))
  {
    SerialTest.println("Sensore ultrasuoni DESTRO indirizzo 113 NON RISPONDE");
  }
  if ((I2c.write(114, 0x00, 0x51) != 0))
  {
    SerialTest.println("Sensore ultrasuoni POSTERIORE indirizzo 114 NON RISPONDE");
  }
  if ((I2c.write(115, 0x00, 0x51) != 0))
  {
    SerialTest.println("Sensore ultrasuoni SINISTRO indirizzo 115 NON RISPONDE");
  }

  //testing imu

  if ((IMU.checkconnection()) != 0)
  {
    SerialTest.println("LA BUSSOLA NON RISPONDE");
  }

  return;
}//---------------------------------------------------------

void frenata_test()  // cosa vede dopo interrupt
{
  long t0; // istante inizio frenata
  byte sens;    // numero di sensori attivi contemporaneamente
  flag_interrupt = false;
  // gioca normalmente fino a che non arriva un interrupt
  do
  {
    update_sensors_all();
    goalie();
  }
  while (flag_interrupt == false);
  t0 = millis();

    tone(PIN_PIEZO,1000,500);                           //suona
  while ((millis() - t0) <= 150) ; //attesa per la frenata di 100 ms
  digitalWrite(PIN_PIEZO, LOW);

  SerialTest.print("Il primo interrupt proviene dal sensore "); SerialTest.println(linesensor);

  SerialTest.print("Durante la frenata ho ricevuto  "); SerialTest.print(Nint); SerialTest.println(" interrupt");

  sens = linea[1];
  for (byte i = 1; i <= Nint; i++)
  {
    SerialTest.println(linea[i], BIN);
    sens = sens & linea[i];
  }
  SerialTest.println();

  SerialTest.println(sens);
  sens = ~( sens + 192 );
  SerialTest.println(sens);

  switch (sens)
  {
    case 0b000001:
    case 0b000010:
    case 0b000100:
    case 0b001000:
    case 0b010000:
    case 0b100000:
      SerialTest.println("Il robot ha toccato la linea solo con questo sensore" );
      break;
    case 0b000011:
      SerialTest.println("Si sono attivati i sensori 1 e 2");
      break;
    case 0b000110:
      SerialTest.println("Si sono attivati i sensori 2 e 3");
      break;
    case 0b000111:
      SerialTest.println("Si sono attivati i sensori 1  2 e 3");
      break;
    case 0b110000:
      SerialTest.println("Si sono attivati i sensori 5 e 6");
      break;
    case 0b011000:
      SerialTest.println("Si sono attivati i sensori 5 e 4");
      break;
    case 0b111000:
      SerialTest.println("Si sono attivati i sensori 6  5 e 4");
      break;
    case 0b100001:
      SerialTest.println("Si sono attivati i sensori 6 e 1");
      break;
    case 0b001100:
      SerialTest.println("Si sono attivati i sensori 4 e 3");
      break;
    case 0b100011:
      SerialTest.println("Si sono attivati i sensori 6  1 e 2");
      break;
    case 0b110001:
      SerialTest.println("Si sono attivati i sensori 6  1 e 5");
      break;
    case 0b001110:
      SerialTest.println("Si sono attivati i sensori 4  3 e 2");
      break;
    case 0b011100:
      SerialTest.println("Si sono attivati i sensori 4  3 e 5");
      break;
    case 0b011110:
      SerialTest.println("Si sono attivati i sensori 4  3  5 e 2");
      break;
    case 0b110011:
      SerialTest.println("Si sono attivati i sensori 6  1  5 e 2");
      break;
    case 0b000000:
      SerialTest.println("Tutti i sensori sono disattivi");
      break;
    default:
      SerialTest.println("Si sono attivati 5 o 6 sensori");
  }

  flag_interrupt = false;
  Nint = 0;
  return;
}//---------------------------------------------------------

void visualizzo_interrupt()
{
  do
  {
    update_sensors_all();
    goalie();
  }
  while (flag_interrupt == false);
  //brake();
    tone(PIN_PIEZO,1000,500); 
  delay(500);
  digitalWrite(PIN_PIEZO, LOW);
  flag_interrupt = false;

  SerialTest.print("Interrupt rilevati "); SerialTest.println(Nint);
  for (byte i = 1; i <= Nint; i++)
  {
    SerialTest.println(linea[i], BIN);
  }
  SerialTest.println();
  fermo();
  return;
}//---------------------------------------------------------

void fermo()
{
  brake();
  SerialTest.println("Motori disattivati");
  SerialTest.println("Scegliere il test da eseguire successivamente");
  while ( SerialTest.available() == 0);
  return;
}//---------------------------------------------------------

void tempo_frenata()
{
  long t0; // istante inizio frenata
  long t1; // istante fine frenata
  byte tasto;
  drivePID(0 , GOALIE_MAX);
  delay(1000);
    tone(PIN_PIEZO,1000,500); 
  t0 = millis();
  brake();
  SerialTest.println("Premere un tasto quando il robot si ferma");
  while ( SerialTest.available() == 0);
  t1 = millis();
  digitalWrite(PIN_PIEZO, LOW);
  SerialTest.print("Tempo trascorso "); SerialTest.println(t1 - t0);
  SerialTest.println();
  tasto = SerialTest.read(); // svuoto buffer seriale
  SerialTest.println("Scegliere il test da eseguire successivamente");
  while ( SerialTest.available() == 0);
  return;
}//---------------------------------------------------------

void visualizzo_gioco()
{
  do
  {
    do
    {
      update_sensors_all();
      goalie();
    }
    while (flag_interrupt == false);
    gest_interrupt();
    SerialTest.print("Interrupt rilevati "); SerialTest.println(Nint);
    for (byte i = 1; i <= Nint; i++)
    {
      SerialTest.print(i); SerialTest.print("  "); SerialTest.println(linea[i], BIN);
    }
    SerialTest.println();
  }
  while (SerialTest.available() == 0);
  return;
} //---------------------------------------------------------

//test automatico al setup
//turns off or on all the outputs (leds and stuff) (1 for on, 0 for off);
void test_toggle_outputs(byte onoff)
{

  digitalWrite(PIN_LED_R, onoff);

  digitalWrite(PIN_LED_Y, onoff);

  digitalWrite(PIN_LED_G, onoff);

  digitalWrite(PIN_PIEZO, onoff);
  return;
}//----------------------------------------------------------





void test_porta(){
  p=digitalRead(SWD);
  x_porta();
  Serial.print("X:");
  Serial.println(valY);
  Serial.println(valB);
  Serial.print("1 blu 0 gialla");
  Serial.println(p);
  Serial.print("XP_SX");
  Serial.println(XP_SX);
  Serial.print("XP_DX");
  Serial.println(XP_DX);
  delay(500);
}

