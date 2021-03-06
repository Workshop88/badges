#include <ZigduinoRadio.h>
#include <fontScroll.h>
#include <TcbTile.h>

#define CTL_CHECKIN 0x1
#define CTL_MESSAGE 0x2
#define CTL_REPORT  0x3
#define CTL_SQUELCH 0x4

const char* messages[] = {"Good Morning!",//0
			  "I need a Beer",
			  "BURP BURP BURP",//2
			  "Lunch Time!!! Nom Nom Nom",
			  "Fork My Dongle",//4
			  "Please Don\'t Hack Me",
			  "STFU",
			  "Applause",
			  "Dinner Time!!! Nom Nom Nom",
			  "See you at THOTCON 0x5",
			  "GTFO",
			  "c7five was here.", 
			  "It's a bird.",
			  "Rehire Adriana Richards!"};

const int I_am_checkin = 9;
const int my_message = 8;
int toggle = 1;

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
     TcbTileSetup();
 //radio_set_param(RP_CCAMODE(3));
 
 uint8_t frameHeader[] = {0x01,0x80,0x00,'T','H','X','T'};
 ZigduinoRadio.attachError(errHandle);
// radio_set_param(RP_TXPWR(-17));
 ZigduinoRadio.begin(20,frameHeader);
 scrollMessage(" Beacon ");
 show_screen(font5x8['1'-0x21+I_am_checkin], 150);
 //  Serial.begin(9600);
 randomSeed(analogRead(33));
 // Serial.println("Init");
}

void loop(){
  //uncomment for random testing uint16_t i = random(9);  
  uint8_t i =0;
  uint8_t frmHdr[7];
  //msg[1] = CTL_CHECKIN; //ctl
  //msg[2] = i;
 

  if (toggle)
    {
    ZigduinoRadio.beginTransmission();
    ZigduinoRadio.write(CTL_CHECKIN);
    ZigduinoRadio.write(I_am_checkin);
    ZigduinoRadio.endTransmission();
    ZigduinoRadio.flush();
    toggle = 0;
    }
  else
    {
      ZigduinoRadio.beginTransmission();
      ZigduinoRadio.write(CTL_MESSAGE);
      ZigduinoRadio.write((char *)messages[my_message]);
      ZigduinoRadio.endTransmission();
      ZigduinoRadio.flush();
   
      toggle = 1;
}
    show_screen(right_row1, 20);
    //Serial.print("Checkin: ");
    //Serial.println(i);
    delay(6000);
  
}

