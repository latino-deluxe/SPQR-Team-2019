#include <Arduino.h>
#include "interrupt.h"
#include "vars.h"
#include "position.h"
#include "pid.h"
#include "motors.h"
#include "goalie.h"
#include "imu.h"

void handleInterruptNEW()   //utilizzato in semifinale
{
  long t0;                                         // istante inizio frenata
  long dt;                                         // tempo di fuga
  byte sens;                                       //  sensori attivi contemporaneamente
  int delta;                                       // angolo di rotazione del robot
  float tolleranza = 5.0;                          //PRIMA ERA 5 OCCHIO
  byte si, sf ;                                    // sensore iniziale e finale da mascherare per il tipo di uscita
  byte di, df;                                     // sensore iniziale e finale da mascherare intorno a quello che vede la palla
  byte ds = 2;                                     // numero di sensori da mascherare intorno a quello che vede la palla
  boolean d_uscita;                                // se true la palla si trova in zona da cui e' uscito in  precedenza
  boolean d_palla;                                 // se true la palla non si e' mossa rispetto a uscita precedente

  attesa=300;

  t0 = millis();

    tone(BUZZER,1800,500);                           //suona a una frequenza di 1800
  do
  {
    update_sensors_all();
  }
  while ((millis() - t0) <= 100) ; //attesa per la frenata di 100 ms
  digitalWrite(BUZZER, LOW);

  sens = 255;
  for (byte i = 1; i <= nint; i++)  // calcola quanti sensori si sono attivati nella frenata
  {
    sens = sens & linea[i];
  }
  sens = ~( sens + 192 ); // sens contiene 1 in corrispondenza dei sensori attivati

  // controllo se il robot si trova storto e calcolo di che angolo
  if (imu_current_euler < 180)
    delta = imu_current_euler;
  else
    delta = imu_current_euler - 360;

  if ((delta >= -tolleranza) && (delta <= tolleranza)) delta = 0; // se si trova poco storto non correggo

  if((us_sx<75)&&((ball_sensor==0)||(ball_sensor==1)||(ball_sensor==2))) goalie();
  if((us_dx<75)&&((ball_sensor==18)||(ball_sensor==19)||(ball_sensor==0))) goalie();



  switch (sens) {
    case 0b000001:            // sensori singoli 1
      mecojoni();
      break;

    case 0b000010:            // sensori singoli 2
      mecojoni();
      break;

    case 0b000100:            // sensori singoli 3
      mecojoni();
      break;

    case 0b001000:            // sensori singoli 4
      mecojoni();
      break;

    case 0b010000:            // sensori singoli 5
      mecojoni();
      break;

    case 0b100000:            // sensori singoli 6
      mecojoni();
      break;

    case 0b000011:   // attivati i sensori 1 e 2      // sta uscendo a destra
    case 0b000110:   // attivati i sensori 2 e 3
    case 0b000111:   // attivati i sensori 1  2 e 3
      dt = 340;
      si = 4;
      sf = 7;
      EXT_LINEA = 270;
      status_x = EST;
      break;

    case 0b110000:    // attivati i sensori 5 e 6       // sta uscendo a sinistra
    case 0b011000:   //  attivati i sensori 5 e 4
    case 0b111000:   //  attivati i sensori 6  5 e 4
      dt = 340;
      si = 13;
      sf = 16;
      EXT_LINEA = 90;
      status_x = OVEST;
      break;

    case 0b100001:    // attivati i sensori 6 1     sta uscendo in avanti
      dt = 360;
      si = 18;
      sf = 2;
      EXT_LINEA = 180;
      status_y = NORD;
      break;

    case 0b001100:    // attivati i sensori 4 3      sta uscendo indietro
      dt = 340;
      si = 9;
      sf = 11;
      if (us_px < 40) EXT_LINEA = 0;
      else EXT_LINEA = 180;
      status_y = SUD;
      break;

    case 0b100010:     // attivati 6 2
    case 0b100011:    //attivati i sensori 6 2 1   sta in angolo Nord Est
      dt = 340;
      si = 1;
      sf = 4;
      EXT_LINEA = 225;
      status_x = EST;
      status_y = NORD;
      break;

    case 0b010001:     //attivati 6 5
    case 0b110001:    // attivati i sensori 6 5 1   sta in angolo Nord Ovest
      dt = 340;
      si = 16;
      sf = 19;
      EXT_LINEA = 135;
      status_x = OVEST;
      status_y = NORD;
      break;

    case 0b001010:       // attivati 4 2
    case 0b001110:      //attivati i sensori 4 3 2   sta in angolo Sud Est
      dt = 340;
      si = 7;
      sf = 10;
      EXT_LINEA = 315;
      status_x = EST;
      status_y = SUD;
      break;

    case 0b010100:     // attivati i sensori 5 3
    case 0b011100:    // attivati i sensori 5 4 3     sta in angolo Sud Ovest
      dt = 340;
      si = 10;
      sf = 13;
      EXT_LINEA = 60;
      status_x = OVEST;
      status_y = SUD;
      break;


    case 0b011110:      //attivati i sensori 5 4 3 2     sta fuori quasi tutto dietro
      dt = 500;
      si = 7;
      sf = 13;
      if (us_px < 40) EXT_LINEA = 0;
      else EXT_LINEA = 180;
      status_y = SUD;
      break;

    case 0b001011:     //attivati i sensori 4 2 1
    case 0b001111:    //attivati i sensori 4 3 2 1
      dt = 500;
      si = 6;
      sf = 9;
      EXT_LINEA = 330;
      status_x = EST;
      break;

    case 0b110100:     //attivati i sensori 6 5 3
    case 0b111100:    //attivati i sensori 6 5 4 3
      dt = 500;
      si = 11;
      sf = 14;
      EXT_LINEA = 60;
      status_x = OVEST;
      break;

    case 0b011001:     //attivati i sensori 5 4 1
    case 0b111001:    //attivati i sensori 6 5 4 1
      dt = 500;
      si = 15;
      sf = 18;
      EXT_LINEA = 120;
      status_x = OVEST;
      break;

    case 0b100110:     //attivati i sensori 6 3 2 1
    case 0b100111:    //attivati i sensori 6 3 2 1
      dt = 500;
      si = 2;
      sf = 5;
      EXT_LINEA = 225;
      status_x = EST;
      break;

    case 0b110011:    // attivati i sensori 6  1  5 e 2 sta fuori quasi tutto avanti
      dt = 500;
      si = 16;
      sf = 4;
      EXT_LINEA = 180;
      status_y = NORD;
      break;

    case 0b101111:    // attivati i sensori 6  1  2  3  4 sta fuori a destra con solo 5 in campo
      dt = 600;
      si = 3;
      sf = 8;
      EXT_LINEA = 270;
      status_x = EST;
      break;

    case 0b111101:    // attivati i sensori 6  1  3  4  5 sta fuori a sinistra con solo 2 in campo
      dt = 600;
      si = 12;
      sf = 17;
      EXT_LINEA = 90;
      status_x = OVEST;
      break;

    case 0b110111:    // attivati i sensori 5  6  1  2  3   sta fuori a destra con solo 4 in campo (angolo NORD EST?)
      dt = 600;
      si = 18;
      sf = 6;
      EXT_LINEA = 220;
      status_x = EST;
      status_y = NORD;
      break;

    case 0b111011:    // attivati i sensori 4  5  6  1  2   sta fuori a sinistra con solo 3 in campo (angolo NORD OVEST?)
      dt = 600;
      si = 15;
      sf = 0;
      EXT_LINEA = 140;
      status_x = OVEST;
      status_y = NORD;
      break;

    case 0b111110:    // attivati i sensori 6  5  4  3  2  sta fuori indietro con solo 1 in campo (angolo SUD OVEST?)
      dt = 600;
      si = 10;
      sf = 13;
      EXT_LINEA = 30;
      status_x = OVEST;
      status_y = SUD;
      break;

    case 0b011111:    // attivati i sensori 1  2  3  4  5 sta fuori indietro con solo 6 in campo (angolo SUD EST?)
      dt = 600;
      si = 7;
      sf = 10;
      EXT_LINEA = 330;
      status_x = EST;
      status_y = SUD;
      break;

    case 0b000000:    // Tutti i sensori sono disattivi interrupt strano (line sensor =0)?
      // sporco sul campo?
      flag_interrupt = false;//considera conclusa la gestione dell'interrupt
      nint = 0;
      danger = false;
      return;
      break;

    case 0b000101:  //robot a cavallo della linea con fuori o solo il 2 oppure il 4,5,6
      if (us_dx <= 40)
      {
        status_x = EST;
        EXT_LINEA = 270;
        si = 4;
        sf = 7;
      }
      if (us_sx <= 30)
      {
        status_x = OVEST;
        EXT_LINEA = 90;
        si = 13;
        sf = 16;
      }
      break;

    case 0b101000:  //robot a cavallo della linea con fuori o solo il 5 oppure 1,2,3
      if (us_dx <= 30)
      {
        status_x = EST;
        EXT_LINEA = 270;
        si = 4;
        sf = 7;
      }
      if (us_sx <= 40)
      {
        status_x = OVEST;
        EXT_LINEA = 90;
        si = 13;
        sf = 16;
      }
      break;

    case 0b010010:  //robot a cavallo della linea con fuori solo o 1,6 oppure 4,3 (attivi 5 e 2)
      if ((delta >= -60) && (delta <= 60)) //sta dritto?
      {
        if ((ball_sensor > 14) || (ball_sensor < 6))   // vede la palla in avanti valutare && (us_fr<50)
        {
          status_y = NORD;
          EXT_LINEA = 180;
          si = 18;
          sf = 2;
        }
        if ((ball_sensor > 7) && (ball_sensor < 13))  // vede la palla dietro valutare && (us_px<50)
        {
          status_y = SUD;
          EXT_LINEA = 0;
          si = 8;
          sf = 12;
        }
      }
      else  //sta storto a destra o a sinistra
      {
        if (delta > 60) // girato verso destra
        {
          status_x = EST;
          EXT_LINEA = 270;
          si = 18;
          sf = 2;
        }
        if (delta < - 60) // girato a sinistra
        {
          status_x = OVEST;
          EXT_LINEA = 90;
          si = 8;
          sf = 12;
        }
      }
      break;


    default:    // Si sono attivati 6 sensori o caso non previsto inverto il moto
      dt = 450;
      EXT_LINEA = new_Dir + 180 ;
      if ( EXT_LINEA > 360) EXT_LINEA = EXT_LINEA - 360;
        tone(BUZZER,20000,500);  // avviso che sono uscito
      si = 0; // aggiustare
      sf = 1;

  }

  digitalWrite(30, HIGH);

  dt = 500;

  EXT_LINEA = EXT_LINEA - delta;    // sostituzione del +
  if (EXT_LINEA >= 360) EXT_LINEA = EXT_LINEA - 360;
  if (EXT_LINEA < 0) EXT_LINEA = EXT_LINEA + 360;

  //va nella direzione EXT_LINEA per un tempo dt a una velocità crescente fino a 220 raddrizzandosi

  st = 0; // elimina storcimento nella fuga
  t0 = millis();
  VL_INT = 100;  //velocita di fuga iniziale (prima era 50)
  do
  {
    update_sensors_all();
    // WhereAmI(); non conviene corro rischio di perdere informazione
    drivePID (EXT_LINEA, VL_INT);
    if (VL_INT < 255)  VL_INT++;  //limitazione velocita massima (prima era 220)
  }
  while ( (millis() - t0) < dt);

  digitalWrite(30, LOW);

  digitalWrite(BUZZER, LOW); // spero di essere rientrato

  brake();
  for (int i = 0; i < 30; i++) {
    readIMU(); //da testare
    // imu_current_euler = read_euler(); //reads the imu euler angle >imu_current_euler<
    recenter(1.0);
    delay(10);
  }

  brake();

  // calcola i limiti di df dei sensori pericolosi attorno a quello che vede la palla

  if ( (ball_sensor < (20 - ds) ) &&  (ball_sensor > (ds - 1) )) // non scavalla
  {
    di = ball_sensor - ds;
    df = ball_sensor + ds;
  }
  else
  {
    if ( ball_sensor >= (20 - ds)) // scavalla in avanti
    {
      di = ball_sensor - ds;
      df = (ball_sensor - 20) + ds;
    }
    else // scavalla indietro
    {
      di = (20 - ball_sensor) - ds;
      df = ball_sensor + ds;
    }
  }

  t0 = millis();

  // rimane in attesa ed esce se trascorso tempo > attesa  oppure la palla viene vista con un sensore non pericoloso
  do
  {
    update_sensors_all();
    // calcola le condizioni true/false da controllare per rimanere fermo
    if (si < sf) //sensori consecutivi
    {
      d_uscita = (ball_sensor >= si) && (ball_sensor <= sf);
    }
    else  // sensori scavallano
    {
      d_uscita = ((ball_sensor >= si) && (ball_sensor <= 19)) || ((ball_sensor >= 0) && (ball_sensor <= sf));
    }


    if (di < df) //sensori consecutivi
    {
      d_palla = (ball_sensor >= di) && (ball_sensor <= df);
    }
    else  // sensori scavallano
    {
      d_palla = ((ball_sensor >= di) && (ball_sensor <= 19)) || ((ball_sensor >= 0) && (ball_sensor <= df));
    }
  }
  while ( ((d_uscita == true) || (d_palla == true) ) && ((millis() - t0) < attesa));


  /*----------------- CONTROLLO CHE NESSUN SENSORE DI LINEA SIA ATTIVO -------------------*/
  // E CONTINUO A MUOVERMI FINO A CHE NON SONO TUTTI DISATTIVI

  // if ((PINK & 63) != 63) {
  //   t0 = millis();
  //   do {
  //     drivePID(EXT_LINEA, VL_INT);
  //   } while (((PINK & 63) != 63) && (millis() - t0) < 2000);
  // }

  /*--------------------------------------------------------------------------------------*/

  int tombola = millis();
  do{
    recenter(1.0);
  } while (tombola < 500);

  flag_interrupt = false;//considera conclusa la gestione dell'interrupt
  nint = 0;
  danger = true;
  tdanger = millis();
  return;

}

//gives zoneIndex based on guessed and measured zone
void calculateMixedZone(){
  int x, y;

  if(status_x == 255){
    x = guessed_x;
  }else{
    x = status_x;
  }

  if(status_y == 255){
    y = guessed_y;
  }else{
    y = status_y;
  }

  zoneIndex = y * 3 + x;

}

void handleInterrupt() {
  long t0;                                         // istante inizio frenata
  long dt;                                         // tempo di fuga
  byte sens;                                       //  sensori attivi contemporaneamente
  int delta;                                       // angolo di rotazione del robot
  float tolleranza = 5.0;                          //PRIMA ERA 5 OCCHIO
  byte si, sf ;                                    // sensore iniziale e finale da mascherare per il tipo di uscita
  byte di, df;                                     // sensore iniziale e finale da mascherare intorno a quello che vede la palla
  byte ds = 2;                                     // numero di sensori da mascherare intorno a quello che vede la palla
  boolean d_uscita;                                // se true la palla si trova in zona da cui e' uscito in  precedenza
  boolean d_palla;                                 // se true la palla non si e' mossa rispetto a uscita precedente

  // if(ruolo==HIGH) attesa=100;
  // else attesa=0;


  t0 = millis();

    tone(BUZZER,1800,500);                           //suona a una frequenza di 1800
  do
  {
    update_sensors_all();
    brake();
  }
  while ((millis() - t0) <= 200) ; //attesa per la frenata di 100 ms
  digitalWrite(BUZZER, LOW);

    mecojoni();

    recenter(1.0);

    flag_interrupt = false;//considera conclusa la gestione dell'interrupt
    nint = 0;
    danger = true;
    tdanger = millis();
    return;
}

void mecojoni() {
  calculateMixedZone();
  readIMU();

  if((imu_current_euler>=345 && imu_current_euler<=359) || (imu_current_euler>=0 && imu_current_euler<=15)) {
    int vel = 150;
    switch (zoneIndex) {
      case 0:
        for(int i = 0; i < 50; i++){
          drivePID(135, vel);
          readIMU();
          delay(10);
        }
        brake();
        delay(2000);
      break;
      case 1:
        for(int i = 0; i < 50; i++){
          drivePID(180, vel);
          readIMU();
          delay(10);
        }
        brake();
        delay(2000);
      break;
      case 2:
        for(int i = 0; i < 50; i++){
          drivePID(225, vel);
          readIMU();
          delay(10);
        }
        brake();
        delay(2000);
      break;
      case 3:
        for(int i = 0; i < 50; i++){
          drivePID(90, vel);
          readIMU();
          delay(10);
        }
        brake();
        delay(2000);
      break;
      case 4:
        tone(BUZZER,1800,500);                           //suona a una frequenza di 1800
        delay(1000);
        digitalWrite(BUZZER, LOW);
      break;
      case 5:
        for(int i = 0; i < 50; i++){
          drivePID(270, vel);
          readIMU();
          delay(10);
        }
        brake();
        delay(2000);
      break;
      case 6:
        for(int i = 0; i < 50; i++){
          drivePID(45, vel);
          readIMU();
          delay(10);
        }
        brake();
        delay(2000);
      break;
      case 7:
        for(int i = 0; i < 50; i++){
          drivePID(0, vel);
          readIMU();
          delay(10);
        }
        brake();
        delay(2000);
      break;
      case 8:
        for(int i = 0; i < 50; i++){
          drivePID(315, vel);
          readIMU();
          delay(10);
        }
        brake();
        delay(2000);
      break;
    }
  } else {
    maggica = true;
    recenter(1.0);
    mecojoni();
  }
}
