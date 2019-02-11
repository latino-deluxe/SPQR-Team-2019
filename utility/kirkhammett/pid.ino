//TIMED PID CONTROL TESTING
void drivePID(signed int direzione, float vMot) //
{
  // mette in variabili globali direzione e velocitá precedenti e attuali
  old_Dir = new_Dir;
  new_Dir = direzione;
  old_vMot = new_vMot;
  new_vMot = vMot;


  speed1 = ((-(sins[((direzione - 60 ) + 360) % 360])) * vMot); //mot 1
  speed2 = ((sins[(direzione + 360) % 360]) * vMot);           //mot 2
  speed3 = ((-(sins[(direzione + 60 ) % 360])) * vMot);         //mot 3

  pidfactor = updatePid();

  if (reaching_ball == true) //da valutare se é opportuno
  {
    pidfactor = pidfactor * 1.2;
  }


  speed1 += pidfactor;
  speed2 += pidfactor;
  speed3 += pidfactor;

  CheckSpeed(); // normalizza la velocita' a 255 max al motore piu' veloce e gli altri in proporzione

  //Send every speed to his motor
  mot(2, int(speed2));
  mot(1, int(speed1));
  mot(3, int(speed3));
}//___________________________________________________________


float updatePid()
{
  float  errorP, errorD, errorI;
  float delta; // assumiamo che la bussola dia un intero positivo, questo lo rende da -179 a +180

  // calcola l'errore di posizione rispetto allo 0
  if (imu_current_euler < 180)
    delta = float(imu_current_euler);
  else
    delta = float(imu_current_euler - 360);

  // calcola correzione proporzionale
  errorP = KP * delta;

  // calcola correzione derivativa
  errorD = KD * (delta - errorePre);
  errorePre = delta;

  // calcola correzione integrativa
  integral = 0.5 * integral + delta; // corretta per non far divergere il contributo
  errorI = KI * integral;

  // calcota correzione complessiva
  return errorD + errorP + errorI;
}//________________________________________________________


void CheckSpeed()
{
  float Max, Min;
  if ((speed1 <= 255.0 && speed1 >= -255.0) && (speed2 <= 255.0 && speed2 >= -255.0) && (speed3 <= 255.0 && speed3 >= -255.0)) return;

  Max = speed1;
  if (speed2 > Max) Max = speed2;
  if (speed3 > Max) Max = speed3;
  Min = speed1;
  if (speed2 < Min) Min = speed2;
  if (speed3 < Min) Min = speed3;

  if (Max > 255.0)
  {
    Max = 255.0 / Max;
    speed1 = speed1 * Max;
    speed2 = speed2 * Max;
    speed3 = speed3 * Max;
    //speedx = 255.0 * speedx / Max;

  }
  if (Min < -255.0)
  {
    Min = -255.0 / Min;
    speed1 = speed1 * Min;
    speed2 = speed2 * Min;
    speed3 = speed3 * Min;
    //speedx = -255.0 * speedx / Min;

  }
}//__________________________________________________________________


void recenter(float spd) //recenter the robot while being steady; spd e' sempre 1
// da chiamare in test per vedere se raddrizza
{
  pidfactor = updatePid();
  speed1 = spd * pidfactor;
  speed2 = spd * pidfactor;
  speed3 = spd * pidfactor;

  CheckSpeed();

  //Send every speed to his motor
  mot(2, int(speed2));
  mot(1, int(speed1));
  mot(3, int(speed3));

  return;
}//______________________________________________________
