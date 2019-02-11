void init_linesensors()
{
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);
  pinMode(A12, INPUT);
  pinMode(A13, INPUT);
  ADMUX = 7; //imposto che solo i pin dal A0:A7 siano collegati al comparatore
  sei();//abilita l'interrupt
  PCICR = 4; //imposto che i pin PCINT 16:23 (PCINT2) possono chiamare interrupt >> PCICR Pin Change Interrupt Control Register
  PCMSK2 = 0x3F; // solo i primi 6, fino a PCINT21 possono chiamare interrupt
  return;
}//----------------------------------------------------


ISR(PCINT2_vect)
{
  byte lettura;
  brakeI();
  lettura = PINK & 63; // legge i sei sensori di linea al volo prima che cambino
  if (flag_interrupt == true)   // se é giá attivo un interrupt aggiorna solo le variabili di stato sensori
  {
    Nint++; // aumenta il contatore degli interrupt
    linea[Nint] = lettura; // memorizza tutte le lettura successive
    return;
  }

  /* if ((lettura & S1) == 0)  linesensor = 1;
    if ((lettura & S2) == 0)  linesensor = 2;
    if ((lettura & S3) == 0)  linesensor = 3;
    if ((lettura & S4) == 0)  linesensor = 4;
    if ((lettura & S5) == 0)  linesensor = 5;
    if ((lettura & S6) == 0)  linesensor = 6;
  */

  Nint = 1; // il primo interrupt ad essere servito
  linea[Nint] = lettura; // memorizza la prima lettura
  flag_interrupt = true;
  /*
    ISx = us_sx; // copia il valore degli ultrasuoni al momento del primo interrupt
    IDx = us_dx;
    IPx = us_px;
    IFr = us_fr;
  */
  return;
}//----------------------------------------------------


