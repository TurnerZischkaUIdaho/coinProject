#include <Servo.h>

using namespace std;

//declare used class
class coinQueue{
  private: 
    Servo* myServo;//holds servo
    int timer;     // default value 375, count down;
    int numToDo;  // this will be 2 times the button presses. If you want 4 coins dispensed, this number will start at 8
    bool servPos; //true  means pushed, false means not pushed in
  public:
    coinQueue(){ //default constructor
      timer = 375;
      numToDo = 0;
    }
    void attach(Servo* aServo){ //constructor helper function, this function should not be used, I should probabbly make this private
      myServo = aServo;
    }
    void addCount(){  //funciton caled when the button is pressed, it only adds. 
      numToDo++;
      numToDo++;
    }
    void moveServo(){   //function called every tick, it will set to the write position based on the servoPos variable. 
      if(servPos == true){
        myServo->write(180);
      }else if (servPos ==false){
        myServo->write(0);
      }
    }
    void tick(){     
      if(numToDo <= 0){ //if the queue is empty, put timer at max value
        timer = 0; //set to zero, so that when a button is pressed and numToDo goes up, the servo position automatically goes to the outward position. when it goes into the else right bellow
        servPos = false;
        moveServo();
      } else {    //if queueu as stuff in it
        timer--;    //decrement timer
        if(timer <= 0 ){  //if timer has run out, reset timer, decrease the num to do, and flip the servo position
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
