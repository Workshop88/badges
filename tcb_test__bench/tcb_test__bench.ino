#include <ZigduinoRadio.h>
#include <fontScroll.h>
#include <TcbTile.h>

#define CTL_CHECKIN 0x1
#define CTL_MESSAGE 0x2
#define CTL_REPORT  0x3
#define CTL_SQUELCH 0x4

const char* messages[] = {"Good Morning!","I need a Beer","BURP BURP BURP","Lunch Time!!! Nom Nom Nom","Fork My Dongle","Don\'t Hack Me","STFU","Applause","Dinner Time!!! Nom Nom Nom","See you at THOTCON 0x5","GTFO","c7five was here."};

uint16_t readVcc() {
  uint16_t result;
  ADMUX = _BV(REFS0) |  _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  ADCSRB = _BV(MUX5);
  delay(3);
  ADCSRA |= _BV(ADSC);
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  //result = 1126400L / result;
  return result;
}

void errHandle(radio_error_t err)
{
  Serial.println();
  Serial.print("Error: ");
  Serial.print((uint8_t)err, 10);
  Serial.println();
}

void setup() {
 // Activate LED Ports for Output
 
   DDRE |= (  (1<<PE0) | (1<<PE1) | (1<<PE2) | (1<<PE3) | (1<<PE4) );
   DDRF = 0xFF;
   // Set drive currect for LED Ports
   DPDS0 |= _BV(PFDRV1) | _BV(PFDRV0) | _BV(PEDRV1) | _BV(PEDRV0); 
 //radio_set_param(RP_CCAMODE(3));
 
 uint8_t frameHeader[] = {0x01,0x80,0x00,'T','H','X','T'};
 ZigduinoRadio.attachError(errHandle);
 //radio_set_param(RP_TXPWR(-17));
 ZigduinoRadio.begin(20,frameHeader);
 scrollMessage("*** Please thank our Sponsors ***");
 // Serial.begin(9600);
// randomSeed(analogRead(33));
// Serial.println("Init");
}

void loop(){
  //uncomment for random testing uint16_t i = random(9);  
  uint8_t i =0;
  uint8_t frmHdr[7];
  //msg[1] = CTL_CHECKIN; //ctl
  //msg[2] = i;
  /*
  for (i = 0; i < 10; i++)
  {*/
    ZigduinoRadio.beginTransmission();
    ZigduinoRadio.write(CTL_MESSAGE);
    ZigduinoRadio.write("Please thank our Sponsors!!!");
    ZigduinoRadio.endTransmission();
    /*
    Serial.print("Checkin: ");
    Serial.println(i);
    delay(300);
  }
  for (i = 0;  i < 12; i++)
  {
      ZigduinoRadio.beginTransmission();
     // Serial.print("Send: ");
      //Serial.println(i);
      ZigduinoRadio.write(CTL_REPORT);
  
      ZigduinoRadio.endTransmission();
      delay(300);
  /*
   Serial.println("Send Squelch: ");
   ZigduinoRadio.beginTransmission();
   ZigduinoRadio.write(CTL_SQUELCH);
   ZigduinoRadio.write(85);
   ZigduinoRadio.endTransmission();
   delay(10000);
   // Throw some random frame
   /*for (i = 0; i < 7; i++)
      frmHdr[i] = random(i);
   ZigduinoRadio.begin(20,frmHdr);
   ZigduinoRadio.beginTransmission();
   ZigduinoRadio.write("Test Bad Frame");
   ZigduinoRadio.endTransmission();
   */
   /*
   Serial.println("Report Request: ");
   ZigduinoRadio.beginTransmission();
   ZigduinoRadio.write(CTL_REPORT);
   ZigduinoRadio.endTransmission();  
   delay(300);
   Serial.println("Waiting on 15: ");
   ZigduinoRadio.setChannel(15);
   ZigduinoRadio.setState(STATE_RX);
 //  while(!ZigduinoRadio.available());
   if (ZigduinoRadio.available())
   {
     while(ZigduinoRadio.available())
     {
       Serial.print(ZigduinoRadio.read(),HEX);
       Serial.print(" ");
     }
   }
  */
   delay(300);
}

