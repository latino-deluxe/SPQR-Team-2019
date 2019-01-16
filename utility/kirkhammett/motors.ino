
//Motor pins initialization
void init_gpio_motors()
{
  pinMode(PWM_MOT [1] , OUTPUT);
  pinMode(INA_MOT [1] , OUTPUT);
  pinMode(INB_MOT [1] , OUTPUT);
  pinMode(PWM_MOT [2] , OUTPUT);
  pinMode(INA_MOT [2] , OUTPUT);
  pinMode(INB_MOT [2] , OUTPUT);
  pinMode(PWM_MOT [3] , OUTPUT);
  pinMode(INA_MOT [3] , OUTPUT);
  pinMode(INB_MOT [3] , OUTPUT);
  return;
}//----------------------------------------------------------


//brake all the motors
void brake()
{
  digitalWrite(INA_MOT[1], 1);
  digitalWrite(INB_MOT[1], 1);
  digitalWrite(INA_MOT[2], 1);
  digitalWrite(INB_MOT[2], 1);
  digitalWrite(INA_MOT[3], 1);
  digitalWrite(INB_MOT[3], 1);
  analogWrite (PWM_MOT[1], 255);
  analogWrite (PWM_MOT[2], 255);
  analogWrite (PWM_MOT[3], 255);
  return;
}//----------------------------------------------------------

void brakeI()  // chiamato solo da dentro l'interrupt
{
  digitalWrite(INA_MOT[1], 1);
  digitalWrite(INB_MOT[1], 1);
  digitalWrite(INA_MOT[2], 1);
  digitalWrite(INB_MOT[2], 1);
  digitalWrite(INA_MOT[3], 1);
  digitalWrite(INB_MOT[3], 1);
  analogWrite (PWM_MOT[1], 255);
  analogWrite (PWM_MOT[2], 255);
  analogWrite (PWM_MOT[3], 255);
  return;
}//----------------------------------------------------------


float torad(float deg) //conversione da gradi a radianti
{
  return (deg * PI / 180.0);
}//_________________________________________________________


void init_omnidirectional_sins() // calcola i seni degli angoli interi da 0..359
{
  for (int i = 0; i < 360; i++)
  {
    sins[i] = sin(torad(i));
  }
}//_________________________________________________________


//Function to send the speed to the motor
void mot (byte mot, int vel) {
  byte VAL_INA, VAL_INB;
  if (vel == 0) //no brake ma motore inerte corto a massa e vel=0 contro freno dove corto a VCC e vel=max
  {
    VAL_INA = 0;
    VAL_INB = 0;
  }
  else if (vel > 0) //clockwise
  {
    VAL_INA = 1;
    VAL_INB = 0;
  }
  else if (vel < 0) //counterclockwise
  {
    VAL_INA = 0;
    VAL_INB = 1;
    vel = -vel;
  }
  digitalWrite(INA_MOT[mot], VAL_INA);
  digitalWrite(INB_MOT[mot], VAL_INB);
  analogWrite (PWM_MOT[mot], vel);
  return;
}//____________________________________________________________
