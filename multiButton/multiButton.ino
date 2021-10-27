#include <Servo.h>

using namespace std;

//declare used class

class coinQueue{
  private:
    Servo* myServo;
    int timer;
    int numToDo;  
    bool servPos; 
  public:
    coinQueue(){
      timer = 375;
      numToDo = 0;
    }
    void attach(Servo* aServo){
      myServo = aServo;
    }
    void addCount(){
      numToDo++;
      numToDo++;
    }
    void moveServo(){
      if(servPos == true){
        myServo->write(180);
      }else if (servPos ==false){
        myServo->write(0);
      }
    }
    void tick(){
      if(numToDo <= 0){
        timer = 375;
      } else {
        timer--;
        if(timer <= 0 ){
          timer = 375;
          numToDo--;
          servPos = !servPos;
          moveServo();
        } else {
          moveServo();
        }
      }
    }
};





// create pin names
  int quarterServoPin = A0;
  int dimeServoPin = A1;
  int nickelServoPin = A2;
  int pennyServoPin = A3;
  int quarterButton = 8;
  int dimeButton = 7;
  int nickelButton = 6;
  int pennyButton = 5;


//declare Servo
  Servo* quarterServo;
  Servo* nickelServo;
  Servo* dimeServo;
  Servo* pennyServo;

//declare classes
  coinQueue quarter;
  coinQueue dime; 
  coinQueue nickel;
  coinQueue penny;

void setup() {
  
  pinMode(quarterServoPin, OUTPUT);
  pinMode(dimeServoPin, OUTPUT);
  pinMode(nickelServoPin, OUTPUT);
  pinMode(pennyServoPin, OUTPUT);
  quarterServo->attach(quarterServoPin);
  dimeServo->attach(dimeServoPin);
  nickelServo->attach(nickelServoPin);
  pennyServo->attach(pennyServoPin);
  quarter.attach(quarterServo);
  dime.attach(dimeServo); 
  nickel.attach(nickelServo);
  penny.attach(pennyServo);

    

  

  pinMode(quarterButton, INPUT);
  pinMode(dimeButton, INPUT);
  pinMode(nickelButton, INPUT);
  pinMode(pennyButton, INPUT);

  
  Serial.begin(9600);
  
  
}

void loop() {
  

  if(digitalRead(quarterButton) == HIGH){
    quarter.addCount();
  }
   if(digitalRead(dimeButton) == HIGH){
    dime.addCount();
  }
   if(digitalRead(nickelButton) == HIGH){
    nickel.addCount();
  }
   if(digitalRead(pennyButton) == HIGH){
    penny.addCount();
  }

  delay(1);
  quarter.tick();
  dime.tick();
  nickel.tick();
  penny.tick();

}
