//---------------------- Serial commands defines --------------------//
#define Enable 'e'
#define Function 'f'
#define Send 's'
#define Change 'c'
#define Enabled '1'
#define Disabled '0'
#define Receive 'r'

#define Information 'i'
#define Firmware 'f'
#define Time_Constants 't'
#define LD_Current_Constant 'g'
#define Ref_Rezistor_Constant 'f'
#define Save 's'
#define get_settings 's'
#define get_readings 'r'
#define Find_LD_Voltage 'v'
#define Mode 'm'
//-------------------------------------------------------------------//
void ACK()
{
  Serial.println("<ACK>");// send Acknoledge
}
void ERR(int ErrCode)
{
  Serial.print("<ERR ");// send Error
  Serial.print(ErrCode);// send Error
  Serial.println(">");// send Error
}

void SwitchLaser(uint8_t LD_num, uint8_t iByte)  // L0
{ delay(1);

  if (iByte == 'D')
  { if (LaserEnabled) {
      Set_DAC_0(LD_num);
    }
    Laser_EN[LD_num] = LOW; return;
  }  // Change state on one laser only (combines migth have 4 lasers)
  if (iByte == 'E')
  { if (LaserEnabled) {
      Update_DAC(LD_num);
    }
    Laser_EN[LD_num] = HIGH; return;
  }

}

void PullUp()
{
  delay(1);
  incomingByte = Serial.read();
  if (incomingByte == 'D')
  {
    Laser_EN[4] = LOW;
  }
  if (incomingByte == 'U')
  {
    Laser_EN[4] = HIGH;
  }
  //digitalWrite(Input_pull_up,Laser_EN[4]);
  if (Laser_EN[4]) sbi(PORTD, 3); // Input_pull_up
  else cbi(PORTD, 3);
  ACK();
}

//--------------------------------------------
void SetLaserName(uint8_t LD_num) {
  byte bc, bn[4];
  
  incomingByte = Serial.read(); // ' '
  for (bc = 0; bc < 4; bc++) {
    delay(1);
    bn[bc] = Serial.read();
  }
  ACCESS_LEVEL_3
  for (bc = 0; bc < 4; bc++) {
    Laser[LD_num].Laser_name[bc] = 0;
    if (bn[bc] != 255) { // if not timout
      Laser[LD_num].Laser_name[bc] = bn[bc];
    }
  } 
  //  Laser[LD_num].Laser_name[i]=0;  // end of the string terminating character
  ACK();
}

//--------------------------------------------
void SetLaserCur(uint8_t LD_num) {
  int c_int;
  
  c_int = Serial.parseInt();
  ACCESS_LEVEL_2
  if (c_int <= Laser[LD_num].cur_lim)
  { Laser[LD_num].current = c_int;
    if ((LaserEnabled) && (Laser_EN[LD_num])) // <- bug is solved here. Does not allow to update DAC for disabled laser chanel
    {
      Update_DAC(LD_num);
    }
    ACK();
  }
  else
  {
    ERR(4);
  }
}

//----------------------------------------------------
void SetLaserCurLim(uint8_t LD_num) {
  int l_int;
  
  l_int = Serial.parseInt();
  ACCESS_LEVEL_3
  Laser[LD_num].cur_lim = l_int;
  ACK();
}

//----------------------------------------------------
void SerialRoutine() {
  uint16_t ui;
  
  incomingByte = Serial.read();

  if ( incomingByte == 'T')       // temperature coeficient
  {
    delay(1);
    int incomingByte2 = Serial.read();
    if (( incomingByte2 == 'C') || ( incomingByte2 == '1') || ( incomingByte2 == '2'))
    {
      delay(1);
      incomingByte = Serial.read();

      if ( incomingByte == '?')
      {
        Serial.print('<');
        switch (incomingByte2) {

          case 'C': {
              Serial.print(ppm_per_deg);
              break;
            }
          case '1': {
              Serial.print(NTC1_ppm_per_deg);
              break;
            }
          case '2': {
              Serial.print(NTC2_ppm_per_deg);
              break;
            }

        }
        Serial.println('>');
        return;
      }

      if ( incomingByte == ' ') {
        switch (incomingByte2) {
          case 'C': {
              ui = Serial.parseInt();
              ACCESS_LEVEL_3
              ppm_per_deg = ui;
              EEPROM.put(138, ppm_per_deg);
              break;
            }
          case '1': {
              ui = Serial.parseInt();
              ACCESS_LEVEL_3
              NTC1_ppm_per_deg = ui;
              EEPROM.put(153, NTC1_ppm_per_deg);
              break;
            }
          case '2': {
              ui = Serial.parseInt();
              ACCESS_LEVEL_3
              NTC2_ppm_per_deg = ui;
              EEPROM.put(155, NTC2_ppm_per_deg);
              break;
            }
        }
        ACK();
        return;
      }
    }
  }
  //
  if (incomingByte == 'L')       // Laser select
  {
    delay(1);
    incomingByte = Serial.read();
    uint8_t incomingByte2 = 0;
    switch (incomingByte) {

      case '1': {
          incomingByte2 = Serial.read();
          SwitchLaser(0, incomingByte2);
          ACK();
          return;
        }
      case '2': {
          incomingByte2 = Serial.read();
          SwitchLaser(1, incomingByte2);
          //SwitchLaser(2,incomingByte2);
          ACK();
          return;
        }
      case '3': {
          incomingByte2 = Serial.read();
          //SwitchLaser(1,incomingByte2);
          SwitchLaser(2, incomingByte2);
          ACK();
          return;
        }
      case '4': {
          incomingByte2 = Serial.read();
          SwitchLaser(3, incomingByte2);
          ACK();
          return;
        }
      case 'P': {
          PullUp();
          return;
        }
      case 'e': {          //which laser enabled 'Le?'
          delay(1);
          incomingByte = Serial.read();
          Serial.print('<');
          for (int i = 0; i < 5; i++) {
            Serial.print(Laser_EN[i]);
            Serial.print(' ');
          }
          Serial.println('>');
          return;
        }
      case 'r': {          // 'Lr' Actual diodes current
          Serial.print('<');
          for (int i = 0; i < 4; i++) {
            if ((LaserEnabled) && (Laser_EN[i])) {
              dtostrf(double(ADCtoI(ADCval[4 + i])), 3, 2, TextBuf);
              Serial.print(TextBuf);
            }
            else Serial.print('0');
            Serial.print(' ');
          }
          Serial.println("mA>");
          return;
        }

      case 'n': {
          delay(1);
          incomingByte = Serial.read();
          switch (incomingByte)
          {
            case '?': //Ln? return laser names
              {
                Serial.print('<');
                int i;
                for (i = 0; i < 4; i++)
                {
                  //   for (int y=0; y<4; y++)
                  //   { Serial.print(Laser[i].Laser_name[y]);}
                  Serial.print(Laser[i].Laser_name);
                  Serial.print(' ');
                }

                Serial.println('>');
                return;
              }
            case '1':     // Ln0 405 // set laser 0 name to "405"
              {
                SetLaserName(0);
                return;
              }
            case '2':
              {
                SetLaserName(1);
                return;
              }
            case '3':
              {
                SetLaserName(2);
                return;
              }
            case '4':
              {
                SetLaserName(3);
                return;
              }

          }

          return;
        }
      case 'c': {
          delay(1);
          incomingByte = Serial.read();
          switch (incomingByte)
          {
            case '?': //Ln? return laser names
              {
                Serial.print('<');
                int i;
                for (i = 0; i < 3; i++)
                {
                  //   for (int y=0; y<4; y++)
                  //   { Serial.print(Laser[i].Laser_name[y]);}
                  Serial.print(Laser[i].current);
                  Serial.print(' ');
                }
                Serial.print(Laser[i++].current);
                Serial.println('>');
                return;
              }
            case '1':     // Ln0 405 // set laser 0 name to "405"
              {
                SetLaserCur(0);
                return;
              }
            case '2':
              {
                SetLaserCur(1);
                return;
              }
            case '3':
              {
                SetLaserCur(2);
                return;
              }
            case '4':
              {
                SetLaserCur(3);
                return;
              }

          }

          return;
        }
      case 'm': { // "Lm
        delay(1);
        incomingByte = Serial.read();
        switch (incomingByte) {
          case '?': //Lm? return laser names
            {
              Serial.print('<');
              int i;
              for (i = 0; i < 3; i++)
              {
                //   for (int y=0; y<4; y++)
                //   { Serial.print(Laser[i].Laser_name[y]);}
                Serial.print(Laser[i].cur_lim);
                Serial.print(' ');
              }
              Serial.print(Laser[i++].cur_lim);
              Serial.println('>');
              return;
            }
          case '1':     // Ln0 405 // set laser 0 name to "405"
            {
              SetLaserCurLim(0);
              return;
            }
          case '2':
            {
              SetLaserCurLim(1);
              return;
            }
          case '3':
            {
              SetLaserCurLim(2);
              return;
            }
          case '4':
            {
              SetLaserCurLim(3);
              return;
            }
        }
        return;
      }
    }
  }



  // optical power gain resistor selection

  if ( incomingByte == 'R')       // Current measurement resistor
  {
    delay(1);
    incomingByte = Serial.read();
    switch (incomingByte) {

      case '?': {
          Serial.print('<');
          float resistor;
          EEPROM.get(90, resistor);
          Serial.print(resistor);
          Serial.println('>');
          return;
        }
      case '=': {
          float resistor;
          resistor = Serial.parseFloat();
          ACCESS_LEVEL_3
          EEPROM.put(90, resistor);
          ACK();
          return;
        }

    }
  }

  //---------------------------------------
  // Programable pin setting. (TTL pin or #4)

  if ( incomingByte == 'P')       //
  {
    delay(1);
    incomingByte = Serial.read();

    if (incomingByte == '?')  {
      Serial.println("<1>");
      //Serial.print(EEPROM.read(148));
      //Serial.print(ProgramablePin);
      //Serial.println('>');
      return;
    }
    else if (incomingByte == '1') {
      ACK();
      return;
    }

  }


  //---------------------------------------
  // Set APC/ACC mode on pin MOSI. for LDD_modulation hardware only.
  //
  if ( incomingByte == 'A') {      // temperature coeficient

    delay(1);
    incomingByte = Serial.read();
    switch (incomingByte) {
      case 'P': {        // case full command "AP"
          ACCESS_LEVEL_2
          EEPROM.write(149, 0);
          cbi(PORTB, 5); // digitalWrite(11, LOW); //LDD11_5_7 with modulation prototype on top
          ACK();
          return;
        }
      case 'C': {         // case full command "AC"
          ACCESS_LEVEL_2
          EEPROM.write(149, 1);
          sbi(PORTB, 5); // digitalWrite(11, HIGH); //LDD11_5_7 with modulation prototype on top
          ACK();
          return;
        }
      case 'L': {         // case full command "AL"
          ACCESS_LEVEL_2
          EEPROM.write(150, 0);
          //   digitalWrite(4, LOW); //LDD11_5_7 with modulation prototype on top
          ACK();
          return;
        }

      case 'H': {        // case full command "AH"
          ACCESS_LEVEL_2
          EEPROM.write(150, 1);
          //   digitalWrite(4, HIGH); //LDD11_5_7 with modulation prototype on top
          ACK();
          return;
        }

      case '?': {         // case full command "A?"
          Serial.print('<');
          Serial.print(EEPROM.read(149));
          Serial.println('>');
          return;
        }
    }
  }

  //---------------------------------------
  // Hardware
  if ( incomingByte == 'H')
  {
    delay(1);
    incomingByte = Serial.read();
    if (incomingByte == '?')
    {
      Serial.print('<');
      Serial.print(EEPROM.read(147));
      Serial.println('>');
      return;
    }
    if (incomingByte == '1')         // RESET to factory. temporaty command for debuging to return value to 255
    {
      ACCESS_LEVEL_3
      EEPROM.write(147, 1);
      ACK();
      Hw = 1;                       // DPSS
      return;
    }
    if (incomingByte == '2')         // RESET to factory. temporaty command for debuging to return value to 255
    {
      ACCESS_LEVEL_3
      EEPROM.write(147, 2);
      ACK();
      Hw = 2;                        // Direct diode
      return;
    }
    if (incomingByte == 'R')         // RESET to factory. temporaty command for debuging to return value to 255
    {
      ACCESS_LEVEL_3
      EEPROM.write(147, 255);
      ACK();
      Hw = 255;
      return;
    }
  }
  //---------------------------------------
  //---------------------------------------
  // Get firmware
  if ( incomingByte == 'F')
  {
    delay(1);
    incomingByte = Serial.read();
    if (incomingByte == 'w')
    {
      LaserFirmware();
      return;
    }
  }
  //---------------------------------------

  if ( incomingByte == 'N')
  {
    delay(1);
    incomingByte = Serial.read();
    if ( incomingByte == 'M')
    {
      incomingByte = Serial.read();

      if ( incomingByte == '?')
      {
        Serial.print('<');
        SendNM();
        Serial.println('>');
        return;
      }
    }
  }
  // ID000000  access to device then ID is unkown, typicaly can be used to set ID.
  // if ID is wrong device stay silence

  //
  // incomingByte = Serial.read();

  if ( incomingByte == 'I')
  {
    delay(1);
    incomingByte = Serial.read();
    if ( incomingByte == 'D')
    {
      incomingByte = Serial.read();

      if ( incomingByte == '?')
      {
        delay(random(1000));
        Serial.print('<');
        SendID();
        Serial.println('>');
        return;
      }
      for (int i = 36; i < 42; i++)
      {
        if (char(EEPROM.read(i)) != incomingByte)
          //   if (ID[i]!=incomingByte)
        {
          match = -1;
        }
        delay(1);
        incomingByte = Serial.read();
      }

      //     ignore_serial_till=0;
      if (match == -1)
      {
        //      Serial.println("ID not match");
        //      Serial.end;
        ignore_serial_till = millis() + 5; // ignore commands for 20ms if ID not match
        do {
          if (Serial.available() > 0) {
            incomingByte = Serial.read();
          }
          delay(1);
        }
        while (millis() < ignore_serial_till);

        //   delay(20);      //
        //   Serial.begin(115200);
        match = 0;
        return;
      }
      else {
        //Serial.println("ID match");
        //           Serial.print('<');
        //           SendID();
        //           Serial.print('>');
        match = 1;
        incomingByte = Serial.read();
        delay(1);
      }


    }

  }

  switch (incomingByte) {

    case Change: {
        ChangeCase();
        return;
      }
    case Function: {
        FunctionCase();
        return;
      }

    case Enable: {
        EnableCase();
        return;
      }
    case 't': {          // set timers to zero
        delay(1);
        incomingByte = Serial.read();
        ACCESS_LEVEL_3
        if (incomingByte == 'z') SetTimerZero();
        return;
      }
    case '0': {                // firmware update case
        delay(1);
        incomingByte = Serial.read();
        if  (incomingByte == ' ')
        {
          LaserDisable();
          Bootloader();
          return;
        }
      }

    case Receive: {
        incomingByte = Serial.read();
        delay(1);
        incomingByte = Serial.read();
        switch (incomingByte) {
          case Information: { //Information 'i'
              LaserFirmware();
              LaserInformation();
              return;
            }
          case get_settings: { //get_settings 's'
              IfIDinUse();
              GetSettings();
              return;
            }
          case get_readings: { //get_readings 'r'
              IfIDinUse();
              GetReadings();
              return;
            }
          case 't': { // 'r t'
              IfIDinUse();
              GetTime();
              return;
            }
          case 'T': { // 'r T'
              GetTime4();
              return;
            }
          case 'l': { //Get access level 't'
              IfIDinUse();
              GetAccessLevel();
              return;
            }
          case '4': {        //
              unsigned int u_int;
              u_int = (EEPROM.read(142) << 8);
              u_int += EEPROM.read(143);
              Serial.println(u_int);
              return;
            }
          case '6': {        //
              unsigned int u_int;
              u_int = (EEPROM.read(144) << 8);
              u_int += EEPROM.read(145);
              Serial.println(u_int);
              return;
            }

            break;
        }
      }

    default: break;

  }
  ERR(5);
}

//-------------------------------------------------------
void LaserFirmware()
{
  Serial.print("Firmware for MatchBox 2 ");
  Serial.println(FVversion);
}


//-------------------------------------------------------
void TEC_enable()
{
  ACK();
  LidSoldering = true;
  sbi(PORTB, 0); //digitalWrite(TEC_ENABLE_PIN, HIGH);
}


//-------------------------------------------------------
void GetAccessLevel(void)
{
  Serial.print("Access level: ");
  Serial.println(AccessLevel);
}


//-------------------------------------------------------
void GetTime()
{
  unsigned long StoredTime;


  // Serial.print("Laser operating time: ");
  EEPROM.get(21, StoredTime);
  Serial.print(StoredTime / 60);
  Serial.print("h ");
  Serial.print(StoredTime % 60);
  Serial.print(" min.");
  Serial.println();
  //  Serial.print("Laser was started: ");
  EEPROM.get(25, StoredTime);
  Serial.print(StoredTime);
  Serial.println(" times");
}


//-------------------------------------------------------
void GetTime4() { // 'r T'
  unsigned long StoredTime;
  unsigned int ui;

  for (ui = 0; ui < 4; ui++) {
    EEPROM.get(220 + ui * 4, StoredTime);
    if (Laser[ui].Laser_name[0] > '0') {
      Serial.print(Laser[ui].Laser_name); Serial.print(": ");
      Serial.print(StoredTime / 60); Serial.print("h ");
      Serial.print(StoredTime % 60); Serial.println(" min.");
    }
  }
}


//-------------------------------------------------------
void SetTimerZero() {  // 't z' Procedure sets counters to zero
  unsigned long StoredTime = 0;
  int i;

  EEPROM.put(21, StoredTime);
  EEPROM.put(25, StoredTime);
  for (i = 0; i < 16; i++) EEPROM.write(220 + i, 0); // 4 LDs work time
  ACK();
}


//-------------------------------------------------
void ChangeUser(void)
{
  incomingByte = Serial.read();
  switch (incomingByte) {
    case '1': {
        if (Serial.parseInt() == 1234)
        { AccessLevel = 1;
          ACK();
        }
        else {
          ERR(4);
        }
        break;
      }
    case '2': {
        if (Serial.parseInt() == 35488)
        { AccessLevel = 2;
          ACK();
        }
        else {
          ERR(4);
        }
        break;
      }
    case '3': {
        if (Serial.parseInt() == 38845)
        { AccessLevel = 3;
          ACK();
        }
        else {
          ERR(4);
        }
        break;
      }
    case '4': {
        if (Serial.parseInt() == 55465)
        { AccessLevel = 4;
          ACK();
        }
        else {
          ERR(4);
        }
        break;
      }

  }
}
void LaserInformation()
{
  Serial.print("Laser S/N:");
  SendID();
  Serial.println();
  Serial.print("Laser model:");
  SendNM();

  Serial.println();
  GetTime();
  // Serial.write(0);
}
void SendNM()   //laser name
{
  for (int i = 100; i < 130; i++)             //  (int i = 42; i < 50; i++)
  {
    char e = char(EEPROM.read(i));


    if (e == ' ')
    {
      break;
    }
    if (e < 20)
    {
      break;
    }
    Serial.print(e);

  }
}


void SendID()      // serial number
{
  int y = 0;

  for (int i = 36; i < 42; i++)
  {

    //  incomingByte = Serial.read();
    char a = char(EEPROM.read(i));
    Serial.print(a);
    ID[y] = a;
    y++;
  }

}
void IfIDinUse()
{

  if (match == 1)
  {
    Serial.print('<');
    SendID();
    Serial.print('>');
    match = 0;
  }
}
//----------------------- Serial Cases functions --------------------//

void ChangeCase() {
  incomingByte = Serial.read();
  delay(10);
  incomingByte = Serial.read();
  switch (incomingByte) {
    case '1': {      // set  LD temperature
        delay(2);
        unsigned long rLong;
        rLong = Serial.parseInt();
        ACCESS_LEVEL_3     //Check access level
        if (rLong > 5000) {
          ERR(4); // return error, setting out of range
        }
        else {
          Set_LD_temp = float(rLong) / 100;
          ACK();           // send acknowledge
        }
        return;
      }
    case '2': {      // set  Xl temperature
        delay(2);
        unsigned long rLong;
        rLong = Serial.parseInt();
        ACCESS_LEVEL_3     //Check access level
        if (rLong > 5000) {
          ERR(4); // return error, setting out of range
        }
        else {
          Set_Xl_temp = float(rLong) / 100;
          ACK();           // send acknowledge
        }
        return;
      }
    case '3': {
        delay(2);
        uint32_t rLong;
        rLong = Serial.parseInt();
        ACCESS_LEVEL_3     //Check access level
        if (rLong > mc) {
          ERR(4);         // return error, setting out of range
        }
        else {
          // LD_Current = rLong;
          if (LaserEnabled)
          {
            LD_Current_NewVal = uint16_t(rLong);
            TaskNumber = 5; //Ramp_I();
          }
          LD_Current = int(rLong);
          ACK();           // send acknowledge
        }

        return;
      }

    case '5': {            // Direct current change through DAC_D write 12bit. Mainly used for current calibration, and debugging.
        delay(2);
        unsigned long rLong;
        rLong = Serial.parseInt();
        ACCESS_LEVEL_4          //Check access level
        DAC_D_SetI = int(rLong);
        if (LaserEnabled)  {
          LASER_DAC.D_setVoltage(rLong * 8);
          if (Hw == 1)    //  1-LDD11_4_5
          {
            DAC_C_ch_val = 60000;
          }
          if (Hw == 2)    //  2-LDD11_5_7
          {
            DAC_C_ch_val = 30;
          }
          //  LASER_DAC.C_setVoltage(16);    // voltage limitation is off durring calibration
        }
        ACK();                 // send acknowledge
        return;
      }
    case '6': {            // Optical power change, direct DAC value change
        delay(2);
        long rLong;
        rLong = Serial.parseInt();
        ACCESS_LEVEL_1     //Check access level
        DAC_A_OpPwr = uint16_t(rLong);
        ACK();           // send acknowledge
        return;
      }
    case '7': {            // LD temperature change for user access level 2
        delay(2);
        unsigned long rLong;
        unsigned long u_int;
        rLong = Serial.parseInt();
        ACCESS_LEVEL_2     //Check access level
        u_int = (EEPROM.read(132) << 8);
        u_int += EEPROM.read(133);
        if (rLong > u_int) {
          ERR(4); // return error, setting out of range
          return;
        }
        u_int = (EEPROM.read(130) << 8);
        u_int += EEPROM.read(131);
        if (rLong < u_int) {
          ERR(4); // return error, setting out of range
          return;
        }
        else {
          Set_LD_temp = float(rLong) / 100;
          ACK();           // send acknowledge
        }
        return;
      }
    case '8': {            // LD temperature change for user access level 2
        delay(2);
        unsigned long rLong;
        unsigned long u_int;
        rLong = Serial.parseInt();
        ACCESS_LEVEL_2     //Check access level
        u_int = (EEPROM.read(136) << 8);
        u_int += EEPROM.read(137);
        if (rLong > u_int) {
          ERR(4); // return error, setting out of range
          return;
        }
        u_int = (EEPROM.read(134) << 8);
        u_int += EEPROM.read(135);
        if (rLong < u_int) {
          ERR(4); // return error, setting out of range
          return;
        }
        else {
          Set_LD_temp = float(rLong) / 100;
          ACK();           // send acknowledge
        }
        return;
      }

    case '9': {            // Direct current change through DAC_D write 12bit. Mainly used for current/power calibration, and debugging. This command is protected against overcurrent.
        delay(2);
        unsigned long rLong;
        rLong = Serial.parseInt();
        ACCESS_LEVEL_2          //Check access level

        if (rLong < ItoDAC(mc))
        { DAC_D_SetI = int(rLong);
          LASER_DAC.D_setVoltage(rLong * 8);
          ACK();
        }                 // send acknowledge
        else ERR(4);
        return;
      }
    case 'f': {            // Body temperature change for user access level 1
        delay(2);
        unsigned long rLong;
        rLong = Serial.parseInt();
        ACCESS_LEVEL_1     //Check access level
        if (rLong > 5000) {
          ERR(4); // return error, setting out of range
        }
        else {
          Set_body_temp = float(rLong) / 100;
          unsigned int uInt = int(Set_body_temp * 100);
          EEPROM.write(140, (uInt >> 8));
          EEPROM.write(141, uInt);
          ACK();           // send acknowledge
        }

        return;
      }
    case 'x': {            // Set temperature range for user access level 2
        unsigned int ui4[4];
        int i;
        delay(2);
        for (i = 0; i < 4; i++) ui4[i] = Serial.parseInt();
        ACCESS_LEVEL_3     //Check access level
        for (i = 130; i = 138; i = +2) EEPROM.put(i, ui4[i]);
        ACK();             // send acknowledge
        return;
      }
    case 'u': {          // Change user
        delay(2);
        incomingByte = Serial.read();
        delay(2);
        ChangeUser();
        return;
      }
    case 'a': {    // 'c a Autostart on/off
        delay(2);
        incomingByte = Serial.read();
        delay(2);
        incomingByte = Serial.read();
        ACCESS_LEVEL_1     //Check access level
        if (incomingByte == '0') {
          ACK();           // send acknowledge
          EEPROM.write(13, 0);             // Autostart  0-no, 1 -yes
          //Warm = false;
        }
        if (incomingByte == '1') {
          ACK();           // send acknowledge
          EEPROM.write(13, 1);             // Autostart  0-no, 1 -yes
          //Warm = false;
        }
        if (incomingByte == '2') {
          ACK();           // send acknowledge
          EEPROM.write(13, 2);             // Warm -yes
          //Warm = true;
        }
        return;
      }
    case 'g': {    // Continous reading update on/off
        delay(2);
        incomingByte = Serial.read();
        delay(2);
        incomingByte = Serial.read();
        ACCESS_LEVEL_3     //Check access level
        if (incomingByte == '0') {
          ACK();           // send acknowledge
          EEPROM.write(16, 0);             // Autostart  0-no, 1 -yes
        }
        if (incomingByte == '1') {
          ACK();           // send acknowledge
          EEPROM.write(16, 1);             // Autostart  0-no, 1 -yes
        }
        return;
      }
    case 'm': {            // Maximum current setting
        delay(2);
        incomingByte = Serial.read();
        delay(2);
        unsigned long rLong;
        rLong = Serial.parseInt();
        ACCESS_LEVEL_3     //Check access level
        mc = int(rLong);      // saves max current setting to RAM
        ACK();           // send acknowledge
        return;
      }
      //Serial.parseFloat() // returns the first valid floating point number from the Serial buffer. Characters that are not digits (or the minus sign) are skipped. parseFloat() is terminated by the first character that is not a floating point number.
  }
  ERR(5);
}


//-------------------------------------------------------------
void FunctionCase() {
  incomingByte = Serial.read();
  delay(2);
  incomingByte = Serial.read();
  switch (incomingByte) {

    case 'b': {
        Bootloader();
        return;
      }
    case 'k': {      //Enables TEC, without turning on the laser diode.
        sbi(PORTD, 2); //digitalWrite(LD_ENABLE_PIN, HIGH);     // for combiner hardware
        TEC_enable();
        return;
      }
    case 'h': {      //heat TEC to specified temperature. f h 90 // heats to 90deg
        delay(2);
        incomingByte = Serial.read();
        int rInt = Serial.parseInt();
        ACCESS_LEVEL_3     //Check access level
        Set_Xl_temp = float(rInt);
        Set_Xl_temp_with_offset = Set_Xl_temp;
        //   ACK();           // send acknowledge
        Xl_PID.SetOutputLimits(-0.8 * Xl_PID_range, 0.8 * Xl_PID_range); // Change PID output range. Allow to deliver higer current for TEC heating
        sbi(PORTD, 2); //digitalWrite(LD_ENABLE_PIN, HIGH);     // for combiner hardware
        TEC_enable();

        return;
      }
    case Save: {
        ACCESS_LEVEL_1     //Check access level
        if (TaskNumber == 0) {
          SaveFunction();
        }
        return;
      }

//    case 'p': {                               // optical power polinom members
//        incomingByte = Serial.read();
//        delay(10);
//        int i;
//        ACCESS_LEVEL_2
//        for (int i = 50; i < 70; i = i + 4)
//        {
//          //           incomingByte = Serial.read();
//          //           EEPROM.write(i, incomingByte);    //polynom e,d,c,b,a
//          EEPROM.put(i, GetScientificFloat());    //polynom e,d,c,b,a
//        }
//        ACK();           // send acknowledge
//        return;
//      }

//    case 'd': {                              // current polinom members
//        incomingByte = Serial.read();
//        delay(10);
//        ACCESS_LEVEL_4
//        for (int i = 70; i < 90; i = i + 4)
//        {
//          EEPROM.put(i, GetScientificFloat());    //polynom e,d,c,b,a
//        }
//        ACK();           // send acknowledge
//        return;
//      }
//    case 'a': {                              // current polinom members
//        incomingByte = Serial.read();
//        delay(10);
//        ACCESS_LEVEL_4
//        for (int i = 90; i < 110; i = i + 4)
//        {
//          EEPROM.put(i,  GetScientificFloat());    //polynom e,d,c,b,a
//        }
//        ACK();           // send acknowledge
//        return;
//      }

    case 'i': {        // set laser ID code 6 digit
      int i;
      char cn[6];
      
      incomingByte = Serial.read();    // ignore "space" symbol
      for (int i = 0; i < 6; i++) {
        cn[i] = ' ';  // Put space in case of serial time out
        cn[i] = Serial.read();
      }
      ACCESS_LEVEL_3       
      for (i = 0; i < 6; i++) EEPROM.write(36 + i, cn[i]);    // writes laser ID code 6 digit
      ACK();           // send acknowledge
      return;
      }
      
    case 'n': {        // Product name e.g. 40A-45A-52A-64A-11-DM-NT
      int i;
      char cn[30];

      incomingByte = Serial.read();    // ignore "space" symbol
      for (int i = 0; i < 30; i++) {
        cn[i] = ' ';  // Put space in case of serial time out
        cn[i] = Serial.read();
      }
      ACCESS_LEVEL_3       
      for (i = 0; i < 30; i++) EEPROM.write(100 + i, cn[i]);
      ACK();           // send acknowledge
      return;
    }
    case 'r': {        // reset to factory settings
        ACCESS_LEVEL_4
        ACK();           // send acknowledge
        SetDefaultValues();
        setup();
        return;
      }
    case '4': {        //
        incomingByte = Serial.read();
        unsigned int uInt = Serial.parseInt();
        ACCESS_LEVEL_3
        EEPROM.write(142, (uInt >> 8));
        EEPROM.write(143, uInt);
        ACK();           // send acknowledge
        return;
      }
    case '6': {        //
        incomingByte = Serial.read();
        unsigned int uInt = Serial.parseInt();
        ACCESS_LEVEL_3
        EEPROM.write(144, (uInt >> 8));
        EEPROM.write(145, uInt);
        ACK();           // send acknowledge
        return;
      }
  }
  ERR(5);
}


//--------------------------------------------------------
void EnableCase() {
  incomingByte = Serial.read();
  delay(2);
  incomingByte = Serial.read();
  switch (incomingByte) {
    case Enabled: { // 'e 1
        if (!LaserEnabled) { //if ((TaskNumber == 0) && (!LaserEnabled)) { // 2017 12 04
          LaserEnable();
        }
        else {
          ERR(2);
        }
        return;
      }
    case Disabled: { // 'e 0
        Warm = false;
        LaserDisable();
        return;
      }
    case '2': {        // end task function
        LaserWarm();
        // ACK();
        return;
      }
    case 't': {        // end task function
        TaskNumber = 0;
        ACK();
        return;
      }
  }
  ERR(5);
}


//--------------------------------------------------------
void LaserWarm() {

  PID_ouput_LD = 0;
  PID_ouput_Xl = 0;
  PWM_follow_out_LD = 0;
  PWM_follow_out_Xl = 0;
  sbi(PORTD, 2); //digitalWrite(LD_ENABLE_PIN, HIGH);
  sbi(PORTB, 0); //digitalWrite(TEC_ENABLE_PIN, HIGH);
  Warm = true;
  if (LaserEnabled)
  {
    LaserDisable();
  }
  else {
    ACK();
  }
}


//--------------------------------------------------------
void LaserEnable() {

  // ACK();           // send acknowledge
  LaserEnabled = true;
  Update_DAC();
  sbi(PORTD, 2); //digitalWrite(LD_ENABLE_PIN, HIGH);
  sbi(PORTB, 0); //digitalWrite(TEC_ENABLE_PIN, HIGH);

  if (!(Warm))
  {
    PID_ouput_LD = 0;
    PID_ouput_Xl = 0;
    PWM_follow_out_LD = 0;
    PWM_follow_out_Xl = 0;
  }

  ACK();           // send acknowledge

  //LASER_DAC.C_setVoltage(LD_Voltage);
  UpdateLaserStartCounter(); // increment laser start counter
  CallPrescaler = 0;
  //TaskNumber = 5;            // Ramp_I task
}


//--------------------------------------------------------
void LaserDisable()
{
  LaserEnabled = false;
  if (!(Warm)) {
    cbi(PORTD, 2); //digitalWrite(LD_ENABLE_PIN, LOW);
    cbi(PORTB, 0); //digitalWrite(TEC_ENABLE_PIN, LOW);
    //digitalWrite(11, LOW);    // MOSI pin external driver control for test
    PID_ouput_LD = 0;
    PID_ouput_Xl = 0;
    PWM_follow_out_LD = 0;
    PWM_follow_out_LD = 0;
  }
  else {
    sbi(PORTB, 0); //digitalWrite(TEC_ENABLE_PIN, HIGH);
  }
  LASER_DAC.D_setVoltage(0);
  LASER_DAC.C_setVoltage(0);
  LASER_DAC.B_setVoltage(0);
  LASER_DAC.A_setVoltage(0);
  UpdateTimeCounter();        // update operating time counter
  TaskNumber = 0;
  ACK();           // send acknowledge
}


//--------------------------------------------------------
void Update_DAC()
{
  if (Laser_EN[0]) {
    LASER_DAC.D_setVoltage(ItoDAC(Laser[0].current));
  }
  if (Laser_EN[1]) {
    LASER_DAC.C_setVoltage(ItoDAC(Laser[1].current));
  }
  if (Laser_EN[2]) {
    LASER_DAC.B_setVoltage(ItoDAC(Laser[2].current));
  }
  if (Laser_EN[3]) {
    LASER_DAC.A_setVoltage(ItoDAC(Laser[3].current));
  }
}
void Update_DAC(int ch)
{
  switch (ch) {
    case 0: {
        LASER_DAC.D_setVoltage(ItoDAC(Laser[0].current));
        return;
      }
    case 1: {
        LASER_DAC.C_setVoltage(ItoDAC(Laser[1].current));
        return;
      }
    case 2: {
        LASER_DAC.B_setVoltage(ItoDAC(Laser[2].current));
        return;
      }
    case 3: {
        LASER_DAC.A_setVoltage(ItoDAC(Laser[3].current));
        return;
      }
  }
}
void Set_DAC_0(int ch)
{
  switch (ch) {
    case 0: {
        LASER_DAC.D_setVoltage(0);
        return;
      }
    case 1: {
        LASER_DAC.C_setVoltage(0);
        return;
      }
    case 2: {
        LASER_DAC.B_setVoltage(0);
        return;
      }
    case 3: {
        LASER_DAC.A_setVoltage(0);
        return;
      }
  }
}



//----------------------Bootloader-----------------------------------//
void Bootloader()     // Jumps to bootloader
{
  cbi(PORTB, 6); //digitalWrite(12, LOW);
}


//---------------------Get Settings----------------------------------//
void GetSettings() {
  Serial.print('#');
  Serial.print("Settings: ");
  Serial.print(int(Set_LD_temp * 100));
  Serial.print(" ");
  Serial.print(int(Set_Xl_temp * 100));
  Serial.print(" ");
  Serial.print(LD_Current);
  Serial.print(" ");
  Serial.print(DAC_A_OpPwr);
  Serial.print(" ");
  Serial.print(OpPwr);
  Serial.print(" ");
  Serial.print(mc);
  Serial.print(" Autostart:");

  if ((EEPROM.read(13)) == 1)
  {

    Serial.print("ON ");
  }
  else
  {
    if ((EEPROM.read(13)) == 2)
    {
      Serial.print("Wrm ");
    }
    else
    {
      Serial.print("OFF ");
    }

  }
  Serial.print(AccessLevel);
  Serial.print(" ");
  Serial.println(int(Set_body_temp * 100));

}

//---------------------Get Readings 'r r' ----------------------------------//
void GetReadings() {
  // noInterrupts();
  Serial.print('#');
  Serial.print("Readings: ");
  for (int i = 1; i < 4; i++) {
    temperature = ADCval[i];
    temperature = temperature / 52429; // 52429;  //
    temperature = UtoTP3(temperature);
    dtostrf(temperature, 3, 3, TextBuf);
    Serial.print(TextBuf);
    Serial.print(" ");

  }

  if (LaserEnabled)
  {
    dtostrf(ave_current, 3, 1, TextBuf); // buvo 2017 04 06//


    Serial.print(TextBuf);    // commented for debugging reason 2016 01 23
    //Serial.print(t_Long);    // line added for debugging reason 2016 01 23
  }
  else
  {
    Serial.print("0.0");
  }
  Serial.print("mA ");
  Buffer2 = 0;// int(PID_ouput_LD * 100 / LD_PID_range);
  Serial.print(Buffer2);
  Serial.print("% ");
  Buffer2 =  int(PID_ouput_Xl * 100 / Xl_PID_range);
  //  sprintf(TextBuf, " ", Buffer2);
  Serial.print(Buffer2);
  Serial.print("% ");
  //        Serial.print(DAC_C_ch_val);
  //        Serial.print(" ");

  if (LaserEnabled)
  {

    Serial.print("ON ");

  }
  else
  {
    if (Warm)
    {
      Serial.print("Wrm "); // warm laser mode indication
    }
    else {
      Serial.print("OFF ");
    }
  }
  Buffer2 =  int(PID_ouput_FAN_ave * 100 / FAN_PID_range);
  Serial.print(Buffer2);
  Serial.print("% ");

  float t_float;
  t_float = ADCval[8] / 21865; // Input voltage calculation /87459
  dtostrf(t_float, 2, 2, TextBuf); // buvo 2016 01 23//dtostrf(ADCtoI(ADCval[4]), 3, 1, TextBuf);
  Serial.print(TextBuf);        // voltage output
  Serial.println("V ");

}

//-------------------- Serial commands functions --------------------//
void SaveFunction() {
  unsigned int uInt;
  EEPROM.write(0, 35);

  EEPROM.write(1, (LD_Voltage >> 8));
  EEPROM.write(2, LD_Voltage);
  uInt = int(Set_LD_temp * 100);
  EEPROM.write(3, (uInt >> 8));
  EEPROM.write(4, uInt);
  uInt = int(Set_Xl_temp * 100);
  EEPROM.write(5, (uInt >> 8));
  EEPROM.write(6, uInt);

  EEPROM.write(7, (LD_Current >> 8));
  EEPROM.write(8, LD_Current);
  EEPROM.write(9, (Ref_Rezistor >> 8)); // nenaudojamas
  EEPROM.write(10, Ref_Rezistor);
  EEPROM.write(11, (DAC_A_OpPwr >> 8));
  EEPROM.write(12, DAC_A_OpPwr);
  EEPROM.write(14, (mc >> 8));
  EEPROM.write(15, mc);
  uInt = int(Set_body_temp * 100);
  EEPROM.write(140, (uInt >> 8));
  EEPROM.write(141, uInt);
  EEPROM.put(160, Laser);
  EEPROM.put(152, Laser_EN);
  EEPROM.put(29, OpPwr);

  ACK();  // send ACK


}
