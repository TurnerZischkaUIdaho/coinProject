#include <IRremote.h>

int irSensorPin  = 7;
IRrecv irrecv(irSensorPin);     // create instance of 'irrecv'

void setup() {
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn();
}

void loop()
{
  int tmpValue;
  if (irrecv.decode()) // have we received an IR signal?
  {
   switch(irrecv.decodedIRData.command)
  {
  case 64: Serial.println("PAUSE");    break;
  case 22: Serial.println("0");    break;
  case 12: Serial.println("1");    break;
  case 24: Serial.println("2");    break;
  case 94: Serial.println("3");    break;
  case 8: Serial.println("4");    break;
  case 28: Serial.println("5");    break;
  case 90: Serial.println("6");    break;
  case 66: Serial.println("7");    break;
  case 82: Serial.println("8");    break;
  case 74: Serial.println("9");    break;
 default: 
    Serial.println(" other button   ");

  }// End Case
   
    }
    irrecv.resume(); // receive the next value

  }
