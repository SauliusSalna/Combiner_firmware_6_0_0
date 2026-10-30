
//------------------------------------------------------
float UtoTP3(float RefVoltage) //approximation range 3-50 C, approximation - 3rd order polynom
{
  float d = -37.3856;
  float c = 37.7841;
  float b = -8.50477 ;
  float a = 1.34762;
  float T = 0;

  T = a*RefVoltage*RefVoltage*RefVoltage + b*RefVoltage*RefVoltage + c*RefVoltage + d;

  return T;
} 

//------------------------------------------------------
int ItoDAC(float Current) { //Current setting to DAC value approximation, approximation - 4th order polynom
  float P, R;
   
  EEPROM.get(90,  R);
  P=R*52.4*Current; //assuming max foltage at 65536 is 1.25V
  if (P<0) {P=0;}
  return int(P);
} 

//------------------------------------------------------
float ADCtoI(float AD) { //ADC value to current, approximation - 4th order polynom
  float R ; // load resistor value

  EEPROM.get(90, R);
  //return AD / (953 * R);
  return AD / (238 * R);
} 
