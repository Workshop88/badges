/*

Run this sketch on two Zigduinos, open the serial monitor at 9600 baud, and type in stuff
Watch the Rx Zigduino output what you've input into the serial port of the Tx Zigduino

*/

#include <ZigduinoRadio.h>

void setup()
{
  ZigduinoRadio.begin(11); // use channel 11;
  
  
  ZigduinoRadio.attachError(errHandle);
  ZigduinoRadio.attachTxDone(onXmitDone);
  for (int iPin=0; iPin<9; iPin++)
    pinMode(iPin, OUTPUT);  //These are the 8 indicator LEDs.
  pinMode(10,OUTPUT); // txDone indicator
  pinMode(11,OUTPUT); // error indicator
}

void loop()
{
  // tx block
    ZigduinoRadio.beginTransmission();
    //a few sequence with delays so we can do some basic read/write verification
    ZigduinoRadio.write((char *)"1"); delay(2000);
    ZigduinoRadio.write((char *)"2"); delay(2000);
    ZigduinoRadio.write((char *)"3"); delay(2000);
    ZigduinoRadio.write((char *)"4"); delay(2000);
    ZigduinoRadio.write((char *)"5"); delay(2000);
    
    ZigduinoRadio.write((char *)"2"); delay(2000);
    ZigduinoRadio.write((char *)"4"); delay(2000);
    ZigduinoRadio.write((char *)"6"); delay(2000);
    ZigduinoRadio.write((char *)"8"); delay(2000);
    
    ZigduinoRadio.write((char *)"8"); delay(2000);
    ZigduinoRadio.write((char *)"7"); delay(2000);
    ZigduinoRadio.write((char *)"6"); delay(2000);
    ZigduinoRadio.write((char *)"5"); delay(2000);
   
    ZigduinoRadio.write((char *)"7"); delay(2000);
    ZigduinoRadio.write((char *)"3"); delay(2000);  
    ZigduinoRadio.write((char *)"5"); delay(2000);
    ZigduinoRadio.write((char *)"1"); delay(2000);  
   
    
    ZigduinoRadio.endTransmission();
 
  
  //Rx Block.  
  if (ZigduinoRadio.available())
  {
    
    int Pin2light = 0;
    while(ZigduinoRadio.available())
    {
      Pin2light = atoi((char *)ZigduinoRadio.read());
      digitalWrite(Pin2light,HIGH);
      delay(1000);
      digitalWrite(Pin2light,LOW);
      //simply reads the char and lights the corresponding pin, then waits a second, unsure of buffer race conditions here, may need to remove delays
    }    
  }
  
  delay(10000); //we'll need some wtf?!?! time
}

void errHandle(radio_error_t err) //light an indicator on error
{
  digitalWrite(11,HIGH);
  delay(1000);
  digitalWrite(11,LOW);
  
}
void onXmitDone(radio_tx_done_t x) //each transmition blinks this LED
{
  digitalWrite(10,HIGH);
  delay(1000);
  digitalWrite(10,LOW);
}

