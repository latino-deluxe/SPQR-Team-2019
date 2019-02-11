
void us_start_measuring() { //phase 1 of 2 for the us measures. This sends the "TRIGGER"
  for (byte i = 0 ; i < 4; i++) {
    I2c.write(112 + i, 0x00, 0x51);
  }
}

void us_scheduling() { //Non blocking delay. It starts phase 1 then after 70 msec it receives the data.
  if (us_flag == false) {
    us_start_measuring();
    us_flag = true;
    us_t0 = millis();
  }
  if (us_flag == true) {
    us_t1 = millis();
    if ((us_t1 - us_t0) > 70)
    {
      us_receive();
      us_flag = 0;
    }
  }
}

void us_receive() { //phase 2 of 2 for the us measures. This receives the "ECHO". In reality it received the already converted data in cm.
  for (byte i = 0; i < 4; i++)
  {
    I2c.read(112 + i, 0x02, 2);
    us_values[i] = I2c.receive() << 8;
    us_values[i] |= I2c.receive();
  }
}

void us_read() {
  us_scheduling();
  us_fr = us_values[0]; //FRONT US
  // us_fr =40; // Frontale non funzionante
  us_dx = us_values[1]; //DX US
  us_px = us_values[2]; //BACK US
  us_sx = us_values[3]; //SX US
}
