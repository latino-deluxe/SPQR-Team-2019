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
    loop cycle duration: 3.2 millis
**/

#define S9 (PINB & 1) >> 0
#define S8 (PINB & 2) >> 1
#define S7 (PINB & 4) >> 2
#define S6 (PINB & 8) >> 3
#define S5 (PINB & 16) >> 4
#define S4 (PINB & 32) >> 5

#define S3 (PINC & 1) >> 0
#define S2 (PINC & 2) >> 1
#define S1 (PINC & 4) >> 2
#define S0 (PINC & 8) >> 3

#define S15 (PIND & 4) >> 2
#define S14 (PIND & 8) >> 3
#define S13 (PIND & 16) >> 4
#define S12 (PIND & 32) >> 5
#define S11 (PIND & 64) >> 6
#define S10 (PIND & 128) >> 7

#define NCYCLES 255
#define BROKEN  900 //just a test

#define THRESHOLD0 200 
#define THRESHOLD1 170
#define THRESHOLD2 150 
#define THRESHOLD3 125
#define THRESHOLD4 100
#define THRESHOLD5 75
#define THRESHOLD6 7

#define DIST_THRESHOLD 90

/*
 * 200-150: distance 0
 * 
*/

int counter[16];
int pins[] = {A3, A2, A1, A0, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2};

int distance;

byte ballInfo = 0;

int nmax = 0;
int index = 0;

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

  pinMode(A4, OUTPUT);
}

void loop() {
  readBall();
}

void readBall() {
  for (int i = 0; i < 16; i++) {
    counter[i] = 0;
  }

  //reads from the register
  for (int i = 0; i < NCYCLES; i++) {
    for(int j = 0; j < 16; j++){
      counter[j] += !digitalRead(pins[j]);
    }
    /*
     * Non worka
    counter[0] += !S0;
    counter[1] += !S1;
    counter[2] += !S2;
    counter[3] += !S3;
    counter[4] += !S4;
    counter[5] += !S5;
    counter[6] += !S6;
    counter[7] += !S7;
    counter[8] += !S8;
    counter[9] += !S9;
    counter[10] += !S10;
    counter[11] += !S11;
    counter[12] += !S12;
    counter[13] += !S13;
    counter[14] += !S14;
    counter[15] += !S15;*/
  }
  
  for (int i = 0; i < 16; i++) {
    if (counter[i] > BROKEN) counter[i] = 0;
  }

  nmax = 0;
  //saves max value and index
  for (int i = 0; i < 16; i++) {
    if (counter[i] > nmax) {
      nmax = counter[i];
      index = i;
    }
  }

  //gets the distance based on thresholds
  if (nmax < THRESHOLD6) {
    nmax = 0;
    distance = 1;
    digitalWrite(A4, LOW);
  } else {
    if (nmax < DIST_THRESHOLD) distance = 1;
    else distance = 0;   

    digitalWrite(A4, HIGH);
  }

  //sends by serial
  ballInfo = (distance << 5) | index;

  Serial.write(ballInfo);
}

void test() {
  readBall();

  Serial.print(S0);
  Serial.print(" | ");
  Serial.print(S1);
  Serial.print(" | ");
  Serial.print(S2);
  Serial.print(" | ");
  Serial.print(S3);
  Serial.print(" | ");
  Serial.print(S4);
  Serial.print(" | ");
  Serial.print(S5);
  Serial.print(" | ");
  Serial.print(S6);
  Serial.print(" | ");
  Serial.print(S7);
  Serial.print(" | ");
  Serial.print(S8);
  Serial.print(" | ");
  Serial.print(S9);
  Serial.print(" | ");
  Serial.print(S10);
  Serial.print(" | ");
  Serial.print(S11);
  Serial.print(" | ");
  Serial.print(S12);
  Serial.print(" | ");
  Serial.print(S13);
  Serial.print(" | ");
  Serial.print(S14);
  Serial.print(" | ");
  Serial.print(S15);
  Serial.print(" ()  ");
  Serial.println(index);
}

void printCounter(){
  for(int i = 0; i < 16; i++){
    Serial.print(counter[i]);
    Serial.print(" | ");
  }
  Serial.println();
}


/*//copies of the register ports
  byte portb, portc, portd;
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
  }*/
