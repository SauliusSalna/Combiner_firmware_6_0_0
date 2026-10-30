/* Hardware Atmega1284P Bobuino pinout(standard version do not work rigth)!
 *  Combiner electronics
Ext 0x05
    0x9E
    0xFF
Bootloader
C:\Program Files (x86)\Arduino\hardware\MightyCore-master\avr\bootloaders\optiboot_flash\atmega1284p\optiboot_flash_atmega1284p_115200_16000000L.hex    
Note:
Reboot device after firmware update.
 */

#define FVversion "v6.0.0"  
 
/*--------------------------- Updates ------------------------------

v1.8.84
ADC coupling sumažinta 4 kartus. Dabar temperatūra atnaujinama kas 0,21 s.

2026 10 02
v1.8.83
Sutvarkyta komanda A?, Lm.
Sutvarkyta atsakas kai Access level netinka. 

2025 10 13
v1.8.82
Sutvarkyta, kad po 'e 2' (Warm režime) veiktų TECas;
Sutvarkyta, kad po 'c a 2' neįsijungtų Warm režimas.
Indvidualus diodų laiko skaičiavimas - komanda 'r T'. Rodo tik esančių LD skaitliukus.

2019 07 17
1.8.82
FAN speed control works. "P" commands disabled. TTL pin is not programable any more. TTL used for FAN control only. 
Enables two laser diodes with single switch. Used for double 488 diode comfguration to double the output power.

2019 06 07
1.8.81a
FAN support enabled.
no P commands. FAN is always enabled.

2018 11 14
TEC1 heating and cooling 80%
TEC2 value output disabled to avoid confusion.

2018 01 23
v1.8.6B -> 1.8.80
laser name 32 max characters

2018 01 23
v1.8.6B

LPD     // Laser TTL control input pull down 100K
LPU     // Laser TTL control input pull up  100K

Bug, If laser Disabled (False indication) after current change laser becomes actyve but Enable status stays "False".
Default laser settings must be changed from 65536 to 50 of 100mA
                                  
2017 06 11
v1.8.67
   Lc1 200 // current 200mA setting for laser diode '1'. Argument range 1..4 . ACCESS level 2
   Lc?     // Return current settings in mA <200 100 100 100 mA>
   Lm1 250 // Current limit 250mA for laser diode '0'. ACCESS level 3
   Lm?     // Return maximum current in mA <200 100 100 100 >
   Lr       // Retrun measured current in mA <0.01 0.01 0.2 1 mA>
   Le       // Returns diodes that are enabled <1 1 1 1 1> // first represents enabled diodes. Last number represend all channel pull up/ pull down state. 
            // This state can be changed with LPD(LaserPullDown) or LPU(LaserPullUp).
   L3D      // L3D disables '3' laser diode, L3E enables '3' diode. First argument is 0..3 laser diode number, second argument 0 (Enable) or 1 (Disable). Changes can be checked with 'Le' command.
   


2017 06 11
v1.7.67

AH //high voltage diode, use step-up conerter to increase voltage. 
AL //low voltage diode
during autostart or after execution 'e 1' programs checks if optical power calibrated and does fits to 0.. 1000 (mW) range, if you don't want to use optical power calibration table, enter '-1' to optical power setting using 'c 4 -1' command.
c 4 command overides current setting. This command can incease current to max allowed current, max allowed currend is set using 'c m 200' command with ACCESS_LEVEL 3.
removed 'f v' command, since LDD_modulation does not have voltage protection feature.
removed  'f j' no nead to test epprom
 

2017 04 13
v1.7.66
External eeprom for power calibration
f j // test external EEPROM
R=3.9 // instead of current calibration will require to enter only current sense resistor value.

v1.7.65

command for LDD_modulation version
AP/AC canges operation mode APC/ACC 
f g // get calibration table

2017 03 14
v1.7.64

f o 1000 10 //ACCESS_LEVEL 2. New function for not used function. Now this used for new type of calibration. Arguments Start_DAC_val as uint16, step as uint8. After executing this command optical power set to start DAC value
f u 127 98.65484  //ACCESS_LEVEL 2. Arguments: table_number as uint8, power_mW as float. 

2017 03 02
v1.7.63


Fixed combiner function bug, that overwrote settings during elektronics power on.
Remaining combiner bug: before saving settings, apply L0 or L with different argument before saving settings. This will ensure that setings will be saved.

2017 02 09
v1.7.62

Suports LDD11_4_9. DPSS laser electronics with hardware modulation support.

2017 02 07
v1.7.61
f h 65 shuts down TEC at higer current.
Updated defautl values T1=T2=-5500;

2017 02 02
Debugging Labview issue. Laser does not appare in the list. Labview receive '<ERR 5>' to 'r i' command.
Solved. 734 code line.

2016 11 29
v1.7.60

Default settings T1 = T2 = -20000, same as in .51 version. Default settings appare then firmware is written to device first time, also after execution "factory reset" using command 'f r'. 
In other case set manualy 'T1 -20000' and 'T2 -20000'. 


2016 11 29
v1.7.59

Error message on GUI solved

2016 10 24
v1.7.58

Body temperature coeficients for NTC1 and NTC2.
Use same as TC command. Get: T1?, T2?, Set: T1 100


2016 10 24
v1.7.55

868 line, disabled koeficients for body temperature compencation.

2016 09 22
v1.7.52
Neigyvendinta
P2 modulation mode software based now runs on interrupt. Be carefull do not run on higer modulation rates than 2kHz. Rapid interupts might slow down microcontroler or disrupt communication.


2016 09 22
v1.7.52
Neigyvendinta
P2 modulation mode software based now runs on interrupt. Be carefull do not run on higer modulation rates than 2kHz. Rapid interupts might slow down microcontroler or disrupt communication.

2016 09 22
v1.7.51

P2 bug solved. Issue: modulation didn't worked before.

2016 08 29
v1.7.50

Fixed f h command bug


2016 07 21
v1.7.49

Fixed. Symptom: sets high optical power then optical power set near 0 power.
Fixed-Optical power for display  didn't saved. But actual optical power was rigth.
Lr command removed for out of memory reason.
Removed. P4 and P5 commands for out of memory reason.

2016 07 13
v1.7.48

Optical Power calibration suported

Fixed bug's for Combiner.
Lr  //This command should be runned first once in new laser combiner.This Command inicializes parameters for combiner. Enters product name, laser diodes names, operating curents, temperatures.

2016 06 21
v1.7.44

Both NTC has compensation on DPSS hardware

2016 05 30
v1.7.43

Both ffeatures active for only Hw=1
For DPSS temperature compensation at diferent body temperature. Improves cycling results.
Heating TEC limited to 80%. Now 12x12 TEC can be connected to bidirectional TEC driver chanal. Result 1.6A output without TEC IC shut down.


2016 04 31
v1.7.41

Four Laser support


2016 04 31
v1.7.40

Current indication averanging filter uses weigth of 2, before was 4.   

2016 04 12
v1.7.39
Increased thermal protection from 45deg to 48deg.

2016 04 12
v1.7.38 eksperimentic P5 50 10 command for modulation. 1024 prescaler

2016 04 12
v1.7.35
// Increased FAN PWM from 62.5kHz to 250kHz.

2016 04 12
v1.7.35
// Improved FAN control loop
// New programable TTL pin mode
// P2       // Set programable pin (#4 TLL) as input. TLL low switches laser to StandBy mode, laser diode will operate below oerating threshhold. Few uW or sub mW migth be observed in output
            // Not recommended as safery feature. Laser must be started with 'e 0' or made as self start after turn on. Feature can be also described as 'hold' laser mode. Optical power DAC sets 0 then input is low.
            // FAN control is not available on this function and should be disconected. Avalable with accesss level 1.

2016 03 31
v1.7.32
//f h 90   // heat TEC to specified temperature, for solder curing. f h 90 // heats to 90deg, e 0 // stops heating. f h 25// makes fast cool down to room temperature. Reboot after this command.


2016 03 17
v1.7.31

Improved FAN PID coeficients

2016 03 10
v1.7.30

User uses higer DAC value (200) to detect hardware type
New commands to set hardware type.
H1  // DPSS. Access level 3
H2  // Direct diode. Access level 3
2016 02 19

v1.7.29
e 2   // Keeps laser warm, if laser enabled, after "e 2" , laser is stopped but TEC keep working.
c a 2 // Worms up laser after laser is plugged in. Stored to EEPROM. 
New laser state: Wrm - means that laser TEC are operating but laser does not operate
#Readings: 25.004 -37.386 24.514 0.0mA 0% -8% Wrm 0% 5.09V 0


2016 01 29
v1.7.23
r a
r d
Returns regular output numbers.

Automatic hardware detection after first executed 'e 1' command.
New command to check hardware
H?  <255> hardware not defined jet
    <1>   DPSS  (High current)
    <2>   Direct Diode (high voltage)  
    
Faster and more accurate calibration.
More stable current readings


2016 01 25
v1.7.22
Improved calibration linearty.
If updated  calibrated electronics with older firmware, measurements will be displayed with error ~-10mA or so. To re-calibrate electronics highly recomended if possible.
commands: 
r a
r d
Returns scientific output.

2016 01 23
v1.7.21
Solved fluctuations at ADC current readings at 80mA, 160mA, 320mA. 
Naujos komandos P0, P1, P? programable pin.

2015 12 12

1.7.12
Fan temerature saves with each setting change
-------------------------------------------------------------------*/

//#include <I2C_AD5625.h>
//For Arduino IDE 1.6.3
//
//#define Hardware LDD_11_5   //<--- define hardware, check on PCB silk screen
// fast calibration command set
// c u 4 55465      e 1         c 5 2000           f t 2000
// e 1     c 3 200    f v
//Commands table
//e 1/0/2     // start/stop laser/stop laser and stays warm.
//c 1 1800  // set LD (18deg x 100) temperature (ACCESS_LEVEL_3)
//c 2 1800  // set Xl (18deg x 100) temperature (ACCESS_LEVEL_3)
//c 3 180   // set LD current to 180mA. (ACCESS_LEVEL_3)
//c 4 100   // set 100mW optical power using polynom table(ACCESS_LEVEL_1)
//c 5 2000  // direct current set to DAC 12bit full range(ACCESS_LEVEL_4) // Direct current change through DAC_D write 12bit. Mainly used for current calibration, and debugging.
//c 6 1100  // set optical power DAC in 12bit full range (ACCESS_LEVEL_1)
//c 7 1800  // set LD (18deg x 100) temperature user (not finished)
//c 8 1800  // set Xl (18deg x 100) temperature user (not finished)
//c 9 1000  // Direct current change through DAC_D write 12bit. Mainly used for current/power calibration, and debugging. This command is protected against overcurrent.

//c f 3200   // Set FAN temperature (ACCESS_LEVEL_1)
//c a 1     // 1/0 enable/disable autostart after power on. (ACCESS_LEVEL_1). c a 2 enables warm function.
//c g 1     // 1/0 enable/disable continous send readings.
//c m 200    // maximum allowed current in mA 
//c u [0..4] [0, 1234, 35488, 38845, 55465]  // change user access level variable 'AccessLevel', second parameter - code to change access level
                                             // 0 Can read all settings, can start/stop laser, set optical power. 
//c x 1500 3500 1500 3500 // change user accessable temperature range LD, Xl. Also same range used for automatic temperature scan
//r s      // receive settings #Settings: 1800 2500 220 6500 nan 250 Autostart:OFF 4 3000 1801 //SetTemperature1, Set temperaure2, Set LD current, DAC for OpPwr, Optical power[mW], Max current, "Autostart:" ON/OFF/Wrm, AccessLevel, Fan Temperature, TC(temperature correction coeficient). 
//r r      // receive readings  #Readings: 25.378 -37.386 26.998 0.0mA 0% 0% OFF 0% 5.01V // Temperature1, Temperature2, BodyTemp, Current, TEC1%, TEC2%, Mode(OFF,ACC,APC,Wrm), FAN%, Supply
//r i      // show laser information
//ID?      // return product ID. Returns <123456> with random delay to 1000ms. To make a list of lasers connected to a bus.

//NM?      // laser Name. Returns laser name.
//r t      // receive operating hours 
//r T      // receive operating hours for each diode
//r p      // receive optical power polinom members
//r d      // returns DAC to current polynom members.Scientific output. 1.851E-3 3.403E-4 3.721E-10 -7.380E-16 4.847E-22
//r a      // returns ADC to current polynom members
//r m      // receive mode (APC/ACC)
//r l      // receive access level
//r 4      // Read max. optical power setting in mW    returns int
//r 6      // Read max. optical power setting in DAC units returns int
//r 9      // receive DAC_D ch setting

//f g       // get optical power calibration table
//f 4 100   // Set max. optical power setting in mW
//f 6 1000   // Set max. optical power setting in DAC units
//r x      // answer: 1500 3500 1500 3500 // temperature limits for user level 2 //not completed 
//f o 1000 10 //ACCESS_LEVEL 2. New function for not used function. Now this used for new type of calibration. Arguments Start_DAC_val as uint16, step as uint8.
//f u 127 98.65484  //ACCESS_LEVEL 2. Arguments: table_number as uint8, power_mW as float. 
//f s      // save changes (ACCESS_LEVEL_1)
//f p 1.556E+1 6.508E-1 -3.788E-5 1.932E-8 -2.340E-12         // Save optical power polynom values e d c b a
//f d 1.556E+1 6.508E-1 -3.788E-5 1.932E-8 -2.340E-12         // Put current to DAC polynom members f k
//f a -8.135E+1 5.401E-3 -3.433E-10 4.322E-16 -7.108E-22      // Put ADC to current polynom members f a -5.07557E-8 7.73523E-5 -0.0329334 -0.0329334 -0.0329334
//f i      // set laser ID 6 digit number. Characters are OK
//f n      // ACCESS_LEVEL 3. Set laser name e.g. f n 40A-45A-52A-64A-11-DM-NT
//f v      // Find operating voltage
//f r      // factory reset ACCESS_LEVEL_4
//f h 90   // heat TEC to specified temperature, for solder curing. f h 90 // heats to 90deg, e 0 // stops heating. f h 25// makes fast cool down to room temperature. Reboot after this command.
//f k      // turn on only TEC. For lid soldering.
//e t      // end task. Function to stop any calibration process
//f c 230      // current measurement, set value koeficient calibration. Send ampermeter readings in mA.
//f t 2000     // current table ADC[1] tab DAC.D-ch tab ADC[4] 
//TC 100    // optical power temperature dependence coeficient. %/deg x1000   (ACCESS_LEVEL_3)
//TC?       // get temperature coefient
//t z       // set timecounter to zero
//R1        // set optical signal aplifier resistor #1  (ACCESS_LEVEL_3)
//R2        // set optical signal aplifier resistor #2  (ACCESS_LEVEL_3)
//R?        // get resistor number (1 or 2). Result e.g.: <2>
//P0        // set programable pin (#4 TTL) as input to allow modulation with proper hardware. Does not work with SLM lasers and DPSS. (ACCESS_LEVEL_2)
//P1        // set programable pin (#4 TLL) as PWM output to control FAN speed and stabilize body temperature.  (ACCESS_LEVEL_2)
//P2        // Set programable pin (#4 TLL) as input. (ACCESS_LEVEL_2)
            //TLL low switches laser to StandBy mode, laser diode will operate below oerating threshhold. Few uW or sub mW migth be observed in output. (ACCESS_LEVEL_2)
            // Not recommended as safery feature. Laser must be started with 'e 0' or made as self start after turn on. Feature can be also described as 'hold' laser mode. Optical power DAC sets 0 then input is low.
            // FAN control is not available on this function and should be disconected. 
//P3        // TTL pin generates preset signal. Modulates laser if harware suports modulation. (ACCESS_LEVEL_3)
//P4        // TTL pin generates preset signal. Modulates laser if harware suports modulation. (ACCESS_LEVEL_3)
//P?        // get programable pin setting. 0 or 1.Result e.g.: <0>
//A0        // Set on automatic mode track
//A1        // Set off automatic mode track
//A?        // Check Automatic mode track setting
//AP        // Sets APC, uses MOSI pin. Supports only LDD_modualtion
//AC        // Sets ACC, uses MOSI pin. Supports only LDD_modualtion
//    Laser combiner commands (ACCESS_LEVEL_0)
//    L0, L1, L2, L3  laser select. Time out 100ms. Real should be about 20ms.(ACCESS_LEVEL_0)
//    L?      // which laser  returns: <0>..<3>     
//    Ln?     // Laser names, returns: <405,488,520,638> 
//    Ln1 488 // Set laser name "488" for laser 1, argument range 0..3 (ACCESS_LEVEL_3)
//    Lr      // Reset to factury settings Laser variable (ACCESS_LEVEL_3)
//    Lc1 200 // current 200mA setting for laser diode '1'. Argument range 0..3
//    Lc?     // Return current in mA <200,100,100,100>
//    Lm0 250 // Current limit 250mA for laser diode '0'.
//    Lm?     // Return maximum current in mA <200,100,100,100>
//     
                              
//H?        // get hardware type number (1 or 2, 255 - not set)         //not finished
//0         // restart to bootloader  (zero + space)

//-5.2350802 -68.51716608*x -260.1184400*x*x 124.3542000*x*x*x 2518.4827000
//-------------------------------------------------------------
// Error codes names for MatchBox2
//0 - Error name not asigned jet.
//1 - Command forbiden for current access level.
//2 - Laser alredy on or making starting ramp-up
//3 - Laser busy, task is not complete please wait for 1s and try again
//4 - Arguments out of range
//5 - Unknown command
//6 - Laser must be enabled to execute this command

//---------------Communication using ID------------------------
//input:ID123456 r r
//output:

/*----------------------------- INFO+

Date: 05-04-2015
v2.0
-Programa pritaikyta naujam MatchBox lazerinio driverio dizainui. Idiegtos kelios naujos f-jos:
  -> Sroves Ild nustatyas is programos (keiciand DAC'o D kanalo itampos verte);
  -> Sroves Ild nuskaitymas su ADC3 kanalu;
 
  
---------------------------------------------------------------------*/
#include <I2C.h>
#include <I2C_AD5625.h>
#include <EEPROM.h>
#include <PID_v1.h>
//#include <Wire.h>
//#include <TimerOne.h>
#include <avr/wdt.h>

//-------------------------Program code definition-------------------//
#define ACCESS_LEVEL_1  if (AccessLevel<1) {ERR(1); return;}      //Check access level
#define ACCESS_LEVEL_2  if (AccessLevel<2) {ERR(1); return;}      //Check access level
#define ACCESS_LEVEL_3  if (AccessLevel<3) {ERR(1); return;}      //Check access level
#define ACCESS_LEVEL_4  if (AccessLevel<4) {ERR(1); return;}      //Check access level     
//------------------------ Driver variables -------------------------//
//#define LD_ENABLE_PIN 2
//#define TEC_ENABLE_PIN 4
//#define TEC_PH  10
//#define ACC_APC 7      // read only
//#define Input_pull_up 3
//#define TTL_PIN 9
//#define LD_current_ch A3
//#define PCB_temp_ch A2
//#define LD_temp_ch A0
//#define Xl_temp_ch A1
#define DAC 0x0F
#define EEPROM_adr 0x50
#define LD_PID_range 500
#define Xl_PID_range 500
#define FAN_PID_range 1000

IO_RnD_AD5625 LASER_DAC;

//--------------------------- Sensor Pins ---------------------------//
#define Sensor1Pin A0
#define Sensor2Pin A1
#define CURRENT_SENSOR_PIN A3
//----------------------Variables for laser combiner-----------------//
uint8_t  LaserNo = 0;         // For combiner only 
struct LaserObject {
  uint16_t current=40;
  uint16_t cur_lim=200;
  uint16_t resistor=2000;   // 
  char Laser_name[5]={ '4', '0', '5', 0 };          // laser name 405, 445...1064                    
  } Laser[4];                   // declare laser array
boolean Laser_EN[5]={HIGH,HIGH,HIGH,HIGH,HIGH}; // For combiner. 1 - laser is active. Disabled laser DAC are set to 0. [4] member sets pull up to all Lx chanels.
//------------------------- Program variables -----------------------//
uint8_t  GainResistor = 1;      // 1 or 2 only. 1 is default. 2 not available for older electronics.
uint8_t  ProgramablePin = 0;    // 0 pin act as input, allow LD modulation with proper hardware. 1 pin operate as PWM signal for FAN control.
uint8_t  Hw = 0;                // Hardware indicator. 255 then electronics is new or undetected. 
uint8_t  AutoTrack = 0;         // 0 -off, 1 -on
uint16_t TickleCounter=0;       // Counts every Tickle on Autotrack function.
//Detection is done during first electronics start. First check EEPROM address 147 if value is 255 then DAC_D is set at 100 and DAC_C set to 0 then measure current. 
//Then DAC_C set to Max value, measure current again and compare with previous measurement. If Current(at DAC_C=0)>Current(at DAC_C=MAX) then Hardware=LDD11_5_x( Hw=2) else Hardware=LDD11_4_x(Hw=1)     
uint16_t LD_Current = 0;
uint16_t LD_Current_NewVal = 0;
uint16_t LD_Current_ramp=0;    // naudojamas sroves rampai
uint16_t LD_Voltage=0;
uint16_t Ref_Rezistor = 0;
uint16_t DAC_A_OpPwr = 0;
float    OpPwr = 0;      // optical power. Paramter can be changed with c 4 command
uint16_t DAC_D_SetI = 0; // for c 5 command and calibration
//volatile int DAC_power;        // optical power with temerature dependencs offset
uint16_t mc = 100;      // max allowed current in mA
byte  AccessLevel  = 0; //  0 - Final user, read only, 
                        //  1 - Integrator/User. Optical power change only, 
                        //  2 - Integrator/Installer. temperature (small window), optical powercalibration
                        //  3 - Assembly operator. Max current, operating  current. Laser name, laser S/N. Time counter reset.
                        //  4 - PCB debuger. Current calibration.
//-------------------------Time count------------------------------------//
unsigned long previous_millis_value=0;
unsigned long m;
unsigned long OperationTime=0;
uint8_t  minutes;
uint8_t  seconds;
uint8_t  hours;
unsigned long time;
unsigned long time_copy;
unsigned long ignore_serial_till=0;    // used to ignore commands then device ID not match
//-------------------------Used only in SLM calibration function---------//
unsigned long     Min_I;      
unsigned long     Max_I;
double   t_at_max_I[5];     // Maximum current temperature points
double   Scan_High_point;    // temperature 25.5
double   Scan_Low_point;    
uint8_t    LoopCount;
double     last_temperature;  
float      count_dir=0.01;    // this variable will be +1, -1, or 0 if scan is paused
boolean   I_calibration_EN=0;        // used to switch ADC to rigth settings
//boolean   laser_type;      // 0- direct diode, 1-DPSS laser


//------------------------- PID variables -----------------------//

double Set_LD_temp=23.0;          // Set point value
double Set_LD_temp_with_offset=23.0;          // Set point value
double Set_Xl_temp_with_offset=23.0;

double Set_Xl_temp=23.0;          // Set point value 
double Set_body_temp=28.0;        // Set body temperature

double Measured_LD_temp;             //Oversampled ADC value variable 
double Measured_Xl_temp;             //Oversampled ADC value variable 
double Measured_PCB_temp;
double Last_LD_temp;                 //Last Oversampled ADC value variable 
double Last_Xl_temp;                 //Last Oversampled ADC value variable 
double PID_ouput_LD=1;                       //High resolution PID output
double PID_ouput_Xl=1;                       //High resolution PID output
double PID_ouput_FAN=1;                      //High resolution PID output
double PID_ouput_FAN_ave=1;                      //High resolution PID output averanged

int  PWM_follow_out_LD=1;                       // PID output for 8bit PWM resolution
int  PWM_follow_out_Xl=1;                       // PID output for 8bit PWM resolution

uint8_t  PWM_ouput_LD=1;                       // PID output for 8bit PWM resolution
uint8_t  PWM_ouput_Xl=1;                       // PID output for 8bit PWM resolution
uint8_t  P_LD_coef =1;                         // PID coeficient 
uint8_t  I_LD_coef =1;                         // PID coeficient 
uint8_t  D_LD_coef =1;                         // PID coeficient
uint8_t  P_Xl_coef =1;                         // PID coeficient 
uint8_t  I_Xl_coef =1;                         // PID coeficient 
uint8_t  D_Xl_coef =1;                         // PID coeficient
//-------------------------
unsigned int PWM_phase=0; 
//unsigned int ADCvalue1 = 0;
//unsigned int ADCvalue2 = 0;
volatile float ADCval[10];
float ave_current=0;
char ID[6];
float  cur_RMS;
byte  ADC_ch_num=0;
int  ADC_sample_num =0;
unsigned long  ADC_buffer=0;
unsigned int Last_ADC_buffer=0;
char TextBuf[30];
byte TaskNumber=0;
int WindowSize = FAN_PID_range+10;      //for FAN PWM relay output function
unsigned long windowStartTime;      //for FAN PWM relay output function
unsigned int DAC_C_ch_val=0;
unsigned char Prescaler=0;
uint16_t Counter=0;         // Counter for task call period prescaler
uint16_t CallPrescaler=0;   // Counter for task call period prescaler
long TimeKeeper=0;          // Used for heating procedure only
int match=0;                // used to flag if ID match device ID
int16_t Buffer2 = 0;
uint16_t Buffer3 = 0;
uint8_t incomingByte = 0;
long Start_Time = 0;
long Start_Time2 = 0;
long Time_Out = 200;
int  ppm_per_deg=0;             // coeficient for optical power correction when base temperature changes. argument signed integer.
int  NTC1_ppm_per_deg=0;        // coeficient for temperature1 setting correction when base temperature changes. argument signed integer.
int  NTC2_ppm_per_deg=0;        // coeficient for temperature2 setting correction when base temperature changes. argument signed integer.

double temperature;
//PID LD_PID(&Measured_LD_temp, &PID_ouput_LD, &Set_LD_temp,100,12,20, REVERSE); //<-- sukeista
PID Xl_PID(&Measured_Xl_temp, &PID_ouput_Xl, &Set_Xl_temp,100,12,20, REVERSE); //<-- sukeista
PID FAN_PID(&Measured_PCB_temp, &PID_ouput_FAN, &Set_body_temp,20000,4000,10000, REVERSE);

boolean LaserEnabled = false;
boolean Warm = false;
boolean LidSoldering = false;


//************************************************************ 
ISR(ADC_vect) {//when new ADC value ready

  ADC_buffer = ADC_buffer + ADC;              
  if (ADC_sample_num > 255) {
    ADC_sample_num = 0; 
    ADCval[ADC_ch_num + 1] = ADC_buffer;
    ADC_ch_num++;
    if (ADC_ch_num > 7) {
      ADC_ch_num = 0;     
      FAN_PID.Compute();
      PID_ouput_FAN_ave = (19*PID_ouput_FAN_ave+PID_ouput_FAN)/20;  //averanges FAN PID output
      OCR2B = int(11 + (PID_ouput_FAN_ave / 19));   
    }   
    ADC_buffer = 0;        // clear buffer for next ADC ch read and accumulate.
    if (ADC_ch_num > 2) ADMUX =  0x80 + ADC_ch_num; // Atmega1284P 0xC0 corespond to 2.56V ref, 0x80-1.1V ref       
    else                ADMUX =  0x40 + ADC_ch_num;    // 0x40 - external ref. VCC. Needed for NTC readings    
  }          
  ADC_sample_num++; 

  PWM_phase++;
  if (PWM_phase > 31) PWM_phase = 0;
  update_PWM();                //update PWM
  ADCSRA |= 1<<ADSC;		// Start Conversion
}


//================================================================
void setup() { 
  int error;

  sbi(PORTB, 6); //MISO reset pulls high

  DDRA = B00000000; // All inputs
  DDRB = B01010001;
  //       | |   ∟ TEC_ENABLE_PIN
  //       | ∟ TEC_PHase
  //       ∟ MISO reset
  DDRC = 0;
  DDRD = B01011100;
  //       | ||∟ LD_ENABLE_PIN
  //       | |∟ Input_pull_up
  //       | ∟ EN DRV8838
  //       ∟ TTL_PIN
  PORTB = B01000000; // MISO reset High
//  PORTC = B00000100; // Load shunt transistor open. LD Output shorted.
  PORTD = B00000000;
 
  //--------------ADC interupt free run setup-------------

  ADCSRA = 0x8F;			// Enable the ADC and its interrupt feature
					// and set the ACD clock pre-scalar to clk/128
	ADMUX = 0x40;			// Select internal 2.56V as Vref, left justify 
					// data registers and select ADC0 as input channel 
 
	//sei();				// Enable Global Interrupts
	ADCSRA |= 1<<ADSC;		// Start Conversion
  //------------------------------------------------------
  
  Serial.begin(115200);
  Serial.setTimeout(10);
   
  // Set APC/ACC modes (nenaudojama)
  if (EEPROM.read(149)==1) sbi(PORTB, 5); //digitalWrite(11, HIGH); //LDD11_5_7 with modulation prototype on top
  else cbi(PORTB, 5); //digitalWrite(11, LOW);
    
//  digitalWrite(LD_ENABLE_PIN, LOW); 
//  digitalWrite(TTL_PIN, LOW);     // Set USB QC3 power supply at 9V
  
  ADC_ch_num = 0;
  ADC_sample_num = 0;
   I2c.timeOut(1000);
   I2c.setSpeed(0);
   I2c.begin();
   sbi(PORTC, 0); // Atmega1284p I2C port pull up. This 
   sbi(PORTC, 1); //
   error = I2c.checkDevice(DAC);
  if (error == 0)  // turi buti 0
    {
    LASER_DAC.begin(DAC);
    delay(500);
    LASER_DAC.internalReference(true);
    }
  else {
    Serial.print("I2C communication error");
    Serial.println(error);
  }
 // sei();				// Enable Global Interrupts
  delay(100);
  
  if (EEPROM.read(0) != 35)  // check if EEPROM values are already set
  {
    delay(100);
    if (EEPROM.read(0) == 255)
    {
      Serial.println("Setting default EEPROM values");
      SetDefaultValues();
    }
  }
  
  LD_Voltage = (EEPROM.read(1)<<8);
  LD_Voltage += EEPROM.read(2);
  
  Buffer3 = (EEPROM.read(3)<<8);
  Buffer3 += EEPROM.read(4);
  
  Set_LD_temp = float(Buffer3)/100;   // Stored value saved as uint16 x100, uint16 converts to float.
  
  Buffer3 = (EEPROM.read(5)<<8);
  Buffer3 += EEPROM.read(6);
  
  Set_Xl_temp = float(Buffer3)/100;   // Stored value saved as uint16 x100, uint16 converts to float.
  
  LD_Current = (EEPROM.read(7)<<8);
  LD_Current += EEPROM.read(8);
  
  Ref_Rezistor = (EEPROM.read(9)<<8);
  Ref_Rezistor += EEPROM.read(10);
  
  DAC_A_OpPwr = (EEPROM.read(11)<<8);
  DAC_A_OpPwr += EEPROM.read(12);
  
  mc = (EEPROM.read(14)<<8);
  mc += EEPROM.read(15);
  
  EEPROM.get(21, time);         // get current setting
  EEPROM.get(25, time_copy);    // get current readings
  EEPROM.get(29, OpPwr);        // get optical power setting
  
  EEPROM.get(138,ppm_per_deg);        // Read optical power dependance to body temperature coeficient 
  EEPROM.get(153,NTC1_ppm_per_deg);   // Read NTC1 to body temperature coeficient 
  EEPROM.get(155,NTC2_ppm_per_deg);   // Read NTC2 to body temperature coeficient 
  EEPROM.get(152,Laser_EN);          // Use same address as LaserNo (this not used any more)
  //pinMode(Input_pull_up, OUTPUT);   
  //digitalWrite(Input_pull_up,Laser_EN[4]);
  if (Laser_EN[4]) sbi(PORTD, 3); // Input_pull_up
  else cbi(PORTD, 3);
  Buffer3 =(EEPROM.read(140)<<8);
  Buffer3+= EEPROM.read(141);
  Set_body_temp=float(Buffer3)/100;  // loads body temperature st point

  ProgramablePin = EEPROM.read(148);

  EEPROM.get(160,Laser);        // Get laser structure
 
  LASER_DAC.A_setVoltage(DAC_A_OpPwr*8);
  
//  LD_PID.SetMode(AUTOMATIC);
//  LD_PID.SetOutputLimits(0, LD_PID_range); 
  Xl_PID.SetMode(AUTOMATIC);
  Xl_PID.SetOutputLimits(-Xl_PID_range*0.8, Xl_PID_range*0.8);
  FAN_PID.SetMode(AUTOMATIC);
  FAN_PID.SetOutputLimits(0, FAN_PID_range);
  
  PID_ouput_LD = 0;
  PID_ouput_Xl = 0;
  
  LASER_DAC.D_setVoltage(0);
  LASER_DAC.C_setVoltage(0);
  LASER_DAC.B_setVoltage(0);
  LASER_DAC.A_setVoltage(0);
   
 // Timer1.initialize(1);           // initialize timer1, and set a 1/2 second period
 // Timer1.pwm(30, 2);                // setup pwm on pin 9, 50% duty cycle
 // TEC PWM
//  TCCR1A |= (1 << WGM11) | (0 << WGM10); // Fast PWM, TOP-ICR1
//  TCCR1B |= (1 << WGM12) | (1 << WGM13);
  TCCR1A = _BV(COM1A1) | _BV(COM1B1)  /* non-inverting PWM */
           | _BV(WGM11);                   /* mode 14: fast PWM, TOP=ICR1 */
  TCCR1B = _BV(WGM13) | _BV(WGM12)
           | _BV(CS10);                    /* no prescaling */
  ICR1 = 15;
//  OCR1A = 8;
  OCR1B = 8;

  //pinMode(TTL_PIN, OUTPUT);
  //DDRD |= _BV(TTL_PIN);    
  // Fan PWM settings
//  TCCR2A |= _BV(COM0A1) | _BV(WGM00) | _BV(WGM01);
//  TCCR2B |= _BV(CS00); 
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS20);
  OCR2A = 64;
  OCR2B = 32;

  analogWrite(30,8); 
  delay(20);
  if ((EEPROM.read(13))==1) TaskNumber = 3;     // if autosatart enabled
  if ((EEPROM.read(13))==2) LaserWarm();     // if warm enabled
  sei(); 

}


//************************************************************ 
void serialEvent() {
  while (Serial.available()>1) {  //while (Serial.available()>1) {    //<== del uzkomentuotos eilutes Labview nematydavo lazerio. Gali buti kad siunciant simbolius budavo per ilgos pauzes.
    SerialRoutine();
  }
}


//================================================================
void loop() {
  float t_float;
  int temp;

  delay(10);
  
  if (Counter>CallPrescaler) {   
    if (TaskNumber!=0) TaskList(TaskNumber);   // check for any task.
    Counter=0;
  }
  Counter++;
              
  temperature = ADCval[2];
  temperature = temperature / 52429;                   // 52429;  //
  Measured_LD_temp = UtoTP3(temperature);
  
  temperature = ADCval[1];
  temperature = temperature / 52429;                   // 52429;  //
  Measured_Xl_temp = UtoTP3(temperature);      
  
  temperature = ADCval[3];
  temperature = temperature / 52429;                  // 52429;  //
  Measured_PCB_temp = UtoTP3(temperature);
   
  if((LaserEnabled)||(Warm)) {
         
    if(LaserEnabled) {  
      WorkHourCounter();
      //DAC_power=int((float)DAC_A_OpPwr-(float)DAC_A_OpPwr*(Measured_PCB_temp-25)*(float)ppm_per_deg/1000000); 
    }
        
    Set_LD_temp_with_offset = (float)Set_LD_temp-(float)Set_LD_temp*(Measured_PCB_temp-25)*(float)NTC1_ppm_per_deg/1000000;
    Set_Xl_temp_with_offset = (float)Set_Xl_temp-(float)Set_Xl_temp*(Measured_PCB_temp-25)*(float)NTC2_ppm_per_deg/1000000;
           
  //  LD_PID.Compute();
    Xl_PID.Compute();
    
    if ((Measured_LD_temp>48) || (Measured_Xl_temp>70) || (Measured_PCB_temp>70)) {
      LaserDisable(); 
      Warm=false;
    }         
         
  }
  else {
    if(LidSoldering) {
  //    LD_PID.Compute();
      Xl_PID.Compute();
    }
  }
    
 // }
}

          
//----------------------------------------------------
void WorkHourCounter(void) {
  unsigned long dif;

  dif = millis() - previous_millis_value;
  OperationTime =+ dif;
  if (OperationTime > 3600000) UpdateTimeCounter();
}


//----------------------------------------------------
void UpdateTimeCounter() {
  unsigned long StoredTime;
  int i;

  OperationTime = OperationTime / 60000;
  EEPROM.get(21,StoredTime);
  StoredTime +=  OperationTime;
  EEPROM.put(21, StoredTime);
  
  for (i = 0; i < 4; i++) {
    if (Laser_EN[i]) {
      EEPROM.get(220 + i * 4, StoredTime);
      StoredTime +=  OperationTime;
      EEPROM.put(220 + i * 4, StoredTime);
    }
  }
  OperationTime = 0;
  previous_millis_value = millis();
}


//----------------------------------------------------
void UpdateLaserStartCounter(void)
{
    unsigned long StoredCounts;
     EEPROM.get(25,StoredCounts);
     StoredCounts++;
     EEPROM.put(25, StoredCounts);
   
}

 
//----------------------------------------------------
void update_PWM() {
    int temp; 
       
//        temp= int(PID_ouput_LD);
//        if (PWM_follow_out_LD>temp)
//        {PWM_follow_out_LD--;}
//        
//        if (PWM_follow_out_LD<temp)
//        {PWM_follow_out_LD++;}
//        
//         temp= PWM_follow_out_LD+ PWM_phase;
//         temp= temp/32;
//               
//          if (OCR1A>temp)
//          {OCR1A--;}
//          if (OCR1A<temp)
//          {OCR1A++;}
        
       
        temp= int(PID_ouput_Xl);
        if (PWM_follow_out_Xl>temp)
        {PWM_follow_out_Xl--;}
        
        if (PWM_follow_out_Xl<temp)
        {PWM_follow_out_Xl++;}
        
       
       temp= PWM_follow_out_Xl+ PWM_phase;
       temp=(temp/32);
       
        if (temp>=0) {
           OCR1B=temp;
           cbi(PORTB, 4); //digitalWrite(TEC_PH, LOW); // buvo HIGH 2018 01 05
        }
        else {
           OCR1B=-temp;
           sbi(PORTB, 4); //digitalWrite(TEC_PH, HIGH);// buvo LOW 2018 01 05
       }  
}


//----------------------------------------------------
void analogStart(unsigned char pin) {
  ADMUX = (ADMUX & 0x40) | pin;
  sbi(ADCSRA, ADSC);
}


//----------------------------------------------------
void SetDefaultValues() {
  int i;
  
  EEPROM.write(0,35);
  EEPROM.write(1,(2000>>8));       //Voltage
  EEPROM.write(2,2000);            //Voltage
  EEPROM.write(3,(1800>>8));       //LD_temp
  EEPROM.write(4,1800);
  EEPROM.write(5,(2500>>8));       //Xl_temp
  EEPROM.write(6,2500);
  EEPROM.write(7,0);  //LD current
  EEPROM.write(8,0);
  EEPROM.write(9,(Ref_Rezistor>>8));
  EEPROM.write(10,Ref_Rezistor);
  EEPROM.write(11,0);              // optical power dac
  EEPROM.write(12,255);
  EEPROM.write(13,0);              // Autostart  0-no, 1 -yes, 2-warm
  EEPROM.write(14,250);       //max current 
  EEPROM.write(15,0);         //max current
  EEPROM.write(16,0);         // Send settings continiously  0-no, 1 -yes
  EEPROM.write(17,(1400>>8));       //Scan temperature low point
  EEPROM.write(18,1400);            //
  EEPROM.write(19,(3500>>8));       //Scan temperature high point
  EEPROM.write(20,3500);            //
  EEPROM.write(21,0);               // 21-24 reserved for time (long)
  EEPROM.write(22,0);
  EEPROM.write(23,0);
  EEPROM.write(24,0);
  
  EEPROM.write(25,0);               // 21-24 reserved for time copy (long)
  EEPROM.write(26,0);
  EEPROM.write(27,0);
  EEPROM.write(28,0);
  
  EEPROM.put(29,0);                 // 29-32 Optical power  
  EEPROM.write(130,(1800>>8));      // TEC1 Temperature limits for end user, and automatic temperature search
  EEPROM.write(131,1800);
  EEPROM.write(132,(3500>>8));
  EEPROM.write(133,3500);
  EEPROM.write(134,(1800>>8));      // TEC2 Temperature limits for end user, and automatic temperature search
  EEPROM.write(135,1800);
  EEPROM.write(136,(3500>>8));
  EEPROM.write(137,3500);
  EEPROM.write(138,0);              //optical power to base temperature dependency coeficient. ppm_per_deg
  EEPROM.write(139,0);
  EEPROM.write(140,(3000>>8));      //Base temperature setpoint
  EEPROM.write(141,3000);
  EEPROM.write(148, 0);
  EEPROM.put(152, Laser_EN); 

  for (i = 0; i < 4; i++) {
    Laser[i].cur_lim=120;
    Laser[i].current=50;
  }
  EEPROM.put(160, Laser);

  for (i = 0; i < 16; i++) EEPROM.write(220 + i, 0); // 4 LDs work time
  
}
