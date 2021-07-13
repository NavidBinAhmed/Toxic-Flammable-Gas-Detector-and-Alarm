/************************MQ9sensor************************************/
/************************Hardware Related Macros************************************/
#include <LiquidCrystal.h>

#define RS 9
#define E  8
#define D4 5
#define D5 4
#define D6 3
#define D7 2
//vss, vdd, v0----gnd, vcc, potentio....
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

//#define         MQ9PIN                       (3)      //define which analog input channel you are going to use
const int         MQ9PIN  = A0;         //define which analog input channel you are going to use
#define         RL_VALUE_MQ9                 (1)        //define the load resistance on the board, in kilo ohms
#define         RO_CLEAN_AIR_FACTOR_MQ9      (9.7990)    //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,
                                                        //which is derived from the chart in datasheet
const int BuzzerPin=11;       
                                                      
const int ledPin=12;

/***********************Software Related Macros************************************/
#define         CALIBARAION_SAMPLE_TIMES     (20)    //define how many samples you are going to take in the calibration phase
#define         CALIBRATION_SAMPLE_INTERVAL  (500)   //define the time interval(in milisecond) between each samples in the
                                                     //cablibration phase
#define         READ_SAMPLE_INTERVAL         (20)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (5)     //define the time interal(in milisecond) between each samples in 
                                                     //normal operation

/**********************Application Related Macros**********************************/
//#define         GAS_LPG                      (1)
//#define         GAS_CARBON_MONOXIDE          (3)
#define         GAS_METHANE                  (2)
#define         accuracy                     (0)   //for linearcurves
#define         accuracy                   (1)   //for nonlinearcurves, un comment this line and comment the above line if calculations 
                                                   //are to be done using non linear curve equations
/*****************************Globals***********************************************/
float           Ro = 0;                            //Ro is initialized to 10 kilo ohms

//int     MQRead = 0;

float rs=0;
float r0=0;
  
void setup() {
  Serial.begin(9600);                               //UART setup, baudrate = 9600bps
  pinMode(BuzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  lcd.begin(16,2);                  // Defining the LCD

  lcd.setCursor(0,0);
  lcd.print("Fine Tuning....");
  Serial.print("Calibrating.....");                //when you perform the calibration
  
  lcd.setCursor(0,1);
  lcd.print("Please Wait");
  Serial.print("Please Wait\n");                //when you perform the calibration
  Ro = MQCalibration(MQ9PIN);                       //Calibrating the sensor. Please make sure the sensor is in clean air 

  //lcd.clear();                          
  
  lcd.clear();                          
 
  Serial.print("Done...\n"); 
  Serial.print("Ro=");
  Serial.print(Ro);
  Serial.print("kohm");
  Serial.print("\n");

  lcd.setCursor(0,0);
  lcd.print("Done...");
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Thanks For");
  lcd.setCursor(0,1);
  lcd.print("Waiting");
  lcd.clear();
  delay(2000);

  lcd.print("Resist:");
  lcd.print(float(Ro));                   // Write the first bytes on the LCD
  lcd.print(" K");
  
  delay(2000);

  lcd.clear();                         
}

void loop() {
/*
  int BuzzerAlarm=0;
   BuzzerAlarm= analogRead(MQ9PIN);
   Serial.print("MQRead Value:"); 
   Serial.print(BuzzerAlarm);
   Serial.print("    ");    
   
   if (BuzzerAlarm >= 350)
  {
    digitalWrite(BuzzerPin, HIGH);   // sets the LED on
    digitalWrite(ledPin, HIGH); 
  }
  else
  {
  digitalWrite(BuzzerPin, LOW);    // sets the LED off
  digitalWrite(ledPin, LOW);
  }
 */
 /* 
   Serial.print("LPG:"); 
   Serial.print(MQGetGasPercentage(MQRead(MQ9PIN)/Ro,GAS_LPG) );
   Serial.print( "ppm" );
   Serial.print("    ");     
   Serial.print("CARBON_MONOXIDE:"); 
   Serial.print(MQGetGasPercentage(MQRead(MQ9PIN)/Ro,GAS_CARBON_MONOXIDE) );
   Serial.print( "ppm" );
   Serial.print("    ");   
   */
   Serial.print("METHANE:"); 
   Serial.print(MQGetGasPercentage(MQRead(MQ9PIN)/Ro,GAS_METHANE) );
   Serial.print( "ppm" );
   Serial.print("\n");
   delay(200);

//if (float(Ro)>=0.50)
//if (MQGetGasPercentage >= 2)
//if ((MQGetGasPercentage(MQRead(MQ9PIN)/Ro,GAS_LPG)) >= 4)
//if (int(GAS_LPG) >= 100)
  //{
    //digitalWrite(BuzzerPin, HIGH);   // sets the LED on
  //}
 //else if ((MQGetGasPercentage(MQRead(MQ9PIN)/Ro,GAS_CARBON_MONOXIDE))>=2)
  //{
  //digitalWrite(BuzzerPin, HIGH);    // sets the LED off
  //}
  //else
  //{ 
  //if ((MQGetGasPercentage(MQRead(MQ9PIN)/Ro,GAS_METHANE))>=2)
  //{
  //digitalWrite(BuzzerPin, LOW);    // sets the LED off
  //}
  
/*
  lcd.setCursor(0,0);
  lcd.print("LPG:");
  lcd.print((MQGetGasPercentage(MQRead(MQ9PIN)/Ro,GAS_LPG)));                   // Write the first bytes on the LCD
  lcd.print(" ppm");
  
  lcd.setCursor(0,0);
  lcd.print("CO:");
  lcd.print((MQGetGasPercentage(MQRead(MQ9PIN)/Ro,GAS_CARBON_MONOXIDE)));                   // Write the first bytes on the LCD
  lcd.print(" ppm");

  delay(2000);

lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Air is Normal");

  delay(2000);

  lcd.clear();
*/
 
  lcd.setCursor(0,0);
  lcd.print("Gas:");
  //lcd.print(0.006*(MQGetGasPercentage(MQRead(MQ9PIN)/Ro,GAS_METHANE)));                   // Write the first bytes on the LCD
  lcd.print((0.3*(MQGetGasPercentage(MQRead(MQ9PIN)/Ro,GAS_METHANE))),3);
  lcd.print(" p");

  lcd.setCursor(0,1);
  lcd.print("Resist:");
  lcd.print(float(Ro));                   // Write the first bytes on the LCD
  lcd.print(" K");
  delay(2000);

  lcd.clear();
 /* 
 if ((MQGetGasPercentage(MQRead(MQ9PIN)/Ro,GAS_METHANE)) >= 20000)
  {
    digitalWrite(BuzzerPin, HIGH);   // sets the LED on
    digitalWrite(ledPin, HIGH);
  
  lcd.setCursor(0,0);
  lcd.print("Air is Toxic");
  delay(2000);
  lcd.clear();
  
  }
  else
  {
  digitalWrite(BuzzerPin, LOW);    // sets the LED off
  digitalWrite(ledPin, LOW);
  
  lcd.setCursor(0,0);
  lcd.print("Air is Normal");
  delay(2000);
  lcd.clear();
  }
*/
}


/****************** MQResistanceCalculation ****************************************
Input:   raw_adc - raw value read from adc, which represents the voltage
Output:  the calculated sensor resistance
Remarks: The sensor and the load resistor forms a voltage divider. Given the voltage
         across the load resistor and its resistance, the resistance of the sensor
         could be derived.
************************************************************************************/ 
float MQResistanceCalculation(int raw_adc)
{
  return ( ((float)RL_VALUE_MQ9*(1023-raw_adc)/raw_adc));
}

/***************************** MQCalibration ****************************************
Input:   mq_pin - analog channel
Output:  r0 of the sensor
Remarks: This function assumes that the sensor is in clean air. It use  
         MQResistanceCalculation to calculates the sensor resistance in clean air 
         and then divides it with RO_CLEAN_AIR_FACTOR. RO_CLEAN_AIR_FACTOR is about 
         10, which differs slightly between different sensors.
************************************************************************************/ 
float MQCalibration(int mq_pin)
{
  int i;
  float RS_AIR_val=0,r0;

  for (i=0;i<CALIBARAION_SAMPLE_TIMES;i++) {                     //take multiple samples
    RS_AIR_val += MQResistanceCalculation(analogRead(mq_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  RS_AIR_val = RS_AIR_val/CALIBARAION_SAMPLE_TIMES;              //calculate the average value

  r0 = RS_AIR_val/RO_CLEAN_AIR_FACTOR_MQ9;                      //RS_AIR_val divided by RO_CLEAN_AIR_FACTOR yields the Ro 
                                                                 //according to the chart in the datasheet 

  return r0; 
}

/*****************************  MQRead *********************************************
Input:   mq_pin - analog channel
Output:  rs of the sensor
Remarks: This function use MQResistanceCalculation to caculate the sensor resistenc (Rs).
         The Rs changes as the sensor is in the different consentration of the target
         gas. The sample times and the time interval between samples could be configured
         by changing the definition of the macros.
************************************************************************************/ 
float MQRead(int mq_pin)
{
  {
  int i;
  float rs=0;

  for (i=0;i<READ_SAMPLE_TIMES;i++) {
    rs += MQResistanceCalculation(analogRead(mq_pin));
    delay(READ_SAMPLE_INTERVAL);
  }

  rs = rs/READ_SAMPLE_TIMES;

  return rs;  
}
}

float rs_r0_ratio ()
{
  //float rs=0;
  //float r0=0;
  
  float rs_r0_ratio = rs/r0;
return rs_r0_ratio;
}

/*****************************  MQGetGasPercentage **********************************
Input:   rs_ro_ratio - Rs divided by Ro
         gas_id      - target gas type
Output:  ppm of the target gas
Remarks: This function uses different equations representing curves of each gas to 
         calculate the ppm (parts per million) of the target gas.
************************************************************************************/ 
/*
int MQGetGasPercentage(float rs_ro_ratio, int gas_id)

{ 
  if ( accuracy == 0 ) {
  if ( gas_id == GAS_LPG ) {
    return (pow(10,((-2.132*(log10(rs_ro_ratio))) + 2.992)));
  } else if ( gas_id == GAS_CARBON_MONOXIDE ) {
    return (pow(10,((-2.199*(log10(rs_ro_ratio))) + 2.766 )));
  } else if ( gas_id == GAS_METHANE ) {
    return (pow(10,((-2.636*(log10(rs_ro_ratio))) + 3.646)));
  }   
} 

  else if ( accuracy == 1 ) {
    if ( gas_id == GAS_LPG ) {
    return (pow(10,((-2.132*(log10(rs_ro_ratio))) + 2.992)));
  } else if ( gas_id == GAS_CARBON_MONOXIDE ) {
    return (pow(10,((-2.199*(log10(rs_ro_ratio))) + 2.766 )));
  } else if ( gas_id == GAS_METHANE ) {
    return (pow(10,(-0.670*pow((log10(rs_ro_ratio)), 2) - 2.399*(log10(rs_ro_ratio)) + 3.650)));
  } 
}    
  return 0;
}
*/

int MQGetGasPercentage(float rs_r0_ratio, int gas_id)
//int MQGetGasPercentage(float rs/ro, int gas_id)
{ 
  if ( accuracy == 0 ) {
  if 
  //( gas_id == GAS_LPG ) {
  //  return (pow(10,((-2.132*(log10(rs_ro_ratio))) + 2.992)));
  // } else if ( gas_id == GAS_CARBON_MONOXIDE ) {
  //  return (pow(10,((-2.199*(log10(rs_ro_ratio))) + 2.766 )));
  // } else if 
   ( gas_id == GAS_METHANE ) {
    return (pow(10,((-2.6364*(log10(rs_r0_ratio))) + 3.6465)));
  }   
} 

  else if ( accuracy == 1 ) {
    if 
    //( gas_id == GAS_LPG ) {
    //return (pow(10,((-2.132*(log10(rs_ro_ratio))) + 2.992)));
    // } else if ( gas_id == GAS_CARBON_MONOXIDE ) {
    // return (pow(10,((-2.199*(log10(rs_ro_ratio))) + 2.766 )));
    // } else if 
    ( gas_id == GAS_METHANE ) {
    return (pow(10,(-0.6723*pow((log10(rs_r0_ratio)), 2) - 2.3990*(log10(rs_r0_ratio)) + 3.6543)));
    //Serial.print ((pow(10,(-0.670*pow((log10(rs_ro_ratio)), 2) - 2.399*(log10(rs_ro_ratio)) + 3.650))));
  } 
}    
  return 0;
}
