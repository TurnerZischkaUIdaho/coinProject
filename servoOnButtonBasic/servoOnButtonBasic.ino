#include <Servo.h>
int servo1 = A0;
int servo2 = A1;
int buttonPin = 8;

Servo quarterServo;
Servo nickelServo;

void setup() {
  // put your setup code here, to run once:
  pinMode(servo1, OUTPUT);
  pinMode(servo2, OUTPUT);
  quarterServo.attach(servo1);
  nickelServo.attach(servo2);
  

  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  
  
}

void loop() {
  nickelServo.write(0);
  quarterServo.write(0);
  if(digitalRead(buttonPin) == HIGH){
    quarterServo.write(100);
    nickelServo.write(100);
    delay(470);
    quarterServo.write(0);
    nickelServo.write(0);
  }else {
    // do nothign
  }//else  

}
