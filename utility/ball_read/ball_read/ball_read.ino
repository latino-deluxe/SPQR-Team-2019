/**
  Sensor Mapping
    Sensor  Angle Pin Port
    S0      0     A3  C3
    S1            A2  C2
    S2            A1  C1
    S3            A0  C0
    S4      90    13  B5
    S5            12  B4
    S6            11  B3
    S7            10  B2
    S8      180   9   B1
    S9            8   B0
    S10           7   D7
    S11           6   D6
    S12     270   5   D5
    S13           4   D4
    S14           3   D3
    S15           2   D2

    portd starts from 2nd byte and needs previous shifting

    loop cycle duration: 3.2 millis
**/



#define NCYCLES 250
#define BROKEN 230

#define THRESHOLD0 200 // attaccato ma non sempre funziona   
#define THRESHOLD1 170 // circa 5-15cm
#define THRESHOLD2 150 // circa 15-80cm
#define THRESHOLD3 125 //  circa 80-140cm
#define THRESHOLD4 100  // circa oltre 140cm
#define THRESHOLD5 75   // lontanissima   
#define THRESHOLD6 7     //palla non vista

//copies of the register ports
byte portb, portc, portd;

int counter[16];
int distance;

byte ballInfo = 0;

void setup() {
  delay(1000);
  
  Serial.begin(57600);

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
}

void loop() {
  for (int i = 0; i < 16; i++) {
    counter[i] = 0;
  }

  //reads from the register
  for (int i = 0; i < NCYCLES; i++) {
    portb = PINB;
    portc = PINC;
    portd = PIND;

    counter[3] += !(portc & 0x01);
    portc >> 1;
    counter[2] += !(portc & 0x01);
    portc >> 1;
    counter[1] += !(portc & 0x01);
    portc >> 1;
    counter[0] += !(portc & 0x01);
    portc >> 1;

    counter[9] += !(portb & 0x01);
    portb >> 1;
    counter[8] += !(portb & 0x01);
    portb >> 1;
    counter[7] += !(portb & 0x01);
    portb >> 1;
    counter[6] += !(portb & 0x01);
    portb >> 1;
    counter[5] += !(portb & 0x01);
    portb >> 1;
    counter[4] += !(portb & 0x01);
    portb >> 1;

    //portd starts from 2nd byte and needs previous shifting
    portd >> 2;
    counter[15] += !(portd & 0x01);
    portd >> 1;
    counter[14] += !(portd & 0x01);
    portd >> 1;
    counter[13] += !(portd & 0x01);
    portd >> 1;
    counter[12] += !(portd & 0x01);
    portd >> 1;
    counter[11] += !(portd & 0x01);
    portd >> 1;
    counter[10] += !(portd & 0x01);
    portd >> 1;
  }

  for (int i = 0; i < 16; i++) {
    if (counter[i] > BROKEN) counter[i] = 0;
  }

  int nmax = 0;
  int index = 0;
  //saves max value and index
  for (int i = 0; i < 16; i++) {
    if (counter[i] > nmax) {
      nmax = counter[i];
      index = i;
    }
  }

  //gets the distance based on thresholds
  if (counter[nmax] < THRESHOLD6) {
    nmax = 0;
    distance = 6;
  } else {
    if (counter[nmax] < THRESHOLD0) distance = 0;
    if (counter[nmax] < THRESHOLD1) distance = 1;
    if (counter[nmax] < THRESHOLD2) distance = 2;
    if (counter[nmax] < THRESHOLD3) distance = 3;
    if (counter[nmax] < THRESHOLD4) distance = 4;
    if (counter[nmax] < THRESHOLD5) distance = 5;
  }

  //sends by serial
  distance=distance<<5;
  ballInfo =distance | nmax;

  Serial.write(ballInfo);
}
