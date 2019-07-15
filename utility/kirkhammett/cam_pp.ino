void x_porta() {
while (Serial1.available()) {
    // get the new byte:
    char inChar = (char)Serial1.read();
    // if the incoming character is a 'Y', set the start packet flag
    if (inChar == 'Y') {
      startpY = 1;
    }
    // if the incoming character is a 'Y', set the start packet flag
    if (inChar == 'B') {
      startpB = 1;
    }
    // if the incoming character is a '.', set the end packet flag
    if (inChar == 'y') {
      endpY = 1;
    }
    // if the incoming character is a '.', set the end packet flag
    if (inChar == 'b') {
      endpB = 1;
    }
      
    if ( (startpY == 1) && (endpY == 0) ) {
        if (isDigit(inChar)) {
          // convert the incoming byte to a char and add it to the string:
          valStringY += inChar;
        }
    }

    if ( (startpB == 1) && (endpB == 0) ) {
        if (isDigit(inChar)) {
          // convert the incoming byte to a char and add it to the string:
          valStringB += inChar;
        }
    }
     

    if ( (startpY == 1) && (endpY == 1) ) {
        valY = valStringY.toInt();  // valid data
        valStringY = ""; 
        startpY = 0;
        endpY = 0;
        datavalid = 1;       
    }
    if ( (startpB == 1) && (endpB == 1) ) {
        valB = valStringB.toInt();  // valid data
        valStringB = ""; 
        startpB = 0;
        endpB = 0;
        datavalid = 1;       
    }

  }  // end of while

if (datavalid==1)  {
  if(p=1){          //leggi porta blu
    x=valB;
  }
  else {            //leggi porta gialla
    x=valY;
  }
  datavalid = 0;
  }
    update_location_complete();
    if(x>160) XP_SX=true;      //porta a sinistra del robot
    else XP_SX=false;
    if(x<35) XP_DX=true;      //porta a destra del robot
    else XP_DX=false;
    if(x==999) {
      if(status_x==EST) XP_SX==true;
      if(status_x==OVEST) XP_DX==true;
    }
}
//c 125
//s >140
//d <35
