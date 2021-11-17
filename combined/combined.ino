#include <Servo.h>
#include <IRremote.h>


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
        //write
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


class numberHolder{
  private:
    int one;
    int ten;
    int hundred;
    int thousand;
    int previousNum1;
    int previousNum2;
    int prevNumber;
  public:
    numberHolder(){
      one = 0;
      ten = 0;
      hundred = 0;
      thousand = 0;
      previousNum1 = 0;
      previousNum2 = 0;
      prevNumber = 0;
    }
    void enterNumber(int newNumber){ // the limitation of this design is that the old thousand is lost, it cant be brought back
      previousNum2 = previousNum1;
      previousNum1 = thousand;
      thousand = hundred;
      hundred = ten;
      ten = one;
      one = newNumber;
    }
    void deleteNumber(){
      one = ten;
      ten = hundred;
      hundred = thousand;
      thousand = previousNum1;
      previousNum1 = previousNum2;
      previousNum2 = 0;
    }
    int first(){
      return thousand;
    }
    int second(){
      return hundred;
    }
    int third(){
      return ten;
    }
    int fourth(){
      return one;
    }
    void subractQuarter(){
      int total = one + (10 *ten) + (100*hundred) + (1000*thousand);
      total = total - 25;
      thousand = total / 1000;
      total -= (thousand * 1000);
      hundred = total /100;
      total -= (hundred*100);
      ten  = (total/10);
      total -= (ten *10);
      one = total;
    }
        void subractDime(){
      int total = one + (10 *ten) + (100*hundred) + (1000*thousand);
      total = total - 10;
      thousand = total / 1000;
      total -= (thousand * 1000);
      hundred = total /100;
      total -= (hundred*100);
      ten  = (total/10);
      total -= (ten *10);
      one = total;
    }
        void subractNickel(){
      int total = one + (10 *ten) + (100*hundred) + (1000*thousand);
      total = total - 5;
      thousand = total / 1000;
      total -= (thousand * 1000);
      hundred = total /100;
      total -= (hundred*100);
      ten  = (total/10);
      total -= (ten *10);
      one = total;
    }
        void subractPenny(){
      int total = one + (10 *ten) + (100*hundred) + (1000*thousand);
      total = total - 1;
      thousand = total / 1000;
      total -= (thousand * 1000);
      hundred = total /100;
      total -= (hundred*100);
      ten  = (total/10);
      total -= (ten *10);
      one = total;
    }
    int returnNumber(){
      return ( one + (10 *ten) + (100*hundred) + (1000*thousand));
    }
    void clear(){
      prevNumber = one + (10 *ten) + (100*hundred) + (1000*thousand);
      one = 0;
      ten = 0;
      hundred = 0;
      thousand = 0;
      previousNum1 = 0;
      previousNum2 = 0;
    }
    int getPrevious(){
      return prevNumber;
    }
};

//declare function to calculate coins
void coinMath(int change, coinQueue &quarter, coinQueue &dime, coinQueue &nickel, coinQueue &penny){


int quarters = 0; 
int dimes = 0; 
int nickels = 0; 
int pennies = 0; 

   quarters = change / 25; 
    change = change % 25; 
    dimes = change / 10; 
    change = change % 10; 
    nickels = change / 5; 
    change = change % 5; 
    pennies = change / 1; 
    change = change % 1; 

    for(int i = 0; i < quarters; i++) {
       quarter.addCount();
    }
        for(int i = 0; i < dimes; i++) {
        dime.addCount();
    }
        for(int i = 0; i < nickels; i++) {
       nickel.addCount();
    }
        for(int i = 0; i < pennies; i++) {
        penny.addCount();
    }


 

};

class irTimer{
  private:
    int timer = 100;
    bool accInput = true;
  public:
    void tick(){
      timer--;
      if(timer <= 0){
        accInput = true;
        timer = 100;
      }
    }
    bool acceptingInput(){
      return accInput;
    }
    void debounceActive(){
      accInput = false;
    }
  

};


//declare segment display pins
int Apin = 2;
int Bpin = 3;
int Cpin = 4;
int Dpin = 5;
int Epin = 6;
int Fpin = 7;
int Gpin = 8;

// declare the 4 digit displays
//create enumerator to increase readabiltiy of code
enum digPin { 
         dig1Pin = 9, 
             dig2Pin = 10, 
             dig3Pin = 11, 
             dig4Pin = 12
            };


//declare servo pins
int quarterServoPin = A0;
int dimeServoPin = A1;
int nickelServoPin = A2;
int pennyServoPin = A3;


//declare irRemotePin
int irSensorPin = 13;



//declare IRremote class
IRrecv irrecv(irSensorPin);


//this array maps a number to the 7 segment displays
//to get the segments for the number 5, call sevenMap[5][<specificc_segment>]
bool sevenMap[10][7] = { {1,1,1,1,1,1,0}, {0,1,1,0,0,0,0} , {1,1,0,1,1,0,1} ,
{1,1,1,1,0,0,1}, {0,1,1,0,0,1,1} , {1,0,1,1,0,1,1},
                    {1,0,1,1,1,1,1}, {1,1,1,0,0,0,0}, {1,1,1,1,1,1,1},
                    {1,1,1,0,0,1,1}
                   
                   };

//declare Servo
  Servo* quarterServo = new Servo;
  Servo* nickelServo = new Servo;
  Servo* dimeServo = new Servo;
  Servo* pennyServo = new Servo;

//declare classes
  coinQueue quarter;
  coinQueue dime; 
  coinQueue nickel;
  coinQueue penny;

//declare numbers to Display class
  numberHolder numDisp;


//declare the debounce timer class for the ir remote
  irTimer irDebouncer;

int danceCount = 4;


void setup()
{
  pinMode(Apin, OUTPUT);
  pinMode(Bpin, OUTPUT);
  pinMode(Cpin, OUTPUT);
  pinMode(Dpin, OUTPUT);
  pinMode(Epin, OUTPUT);
  pinMode(Fpin, OUTPUT);
  pinMode(Gpin, OUTPUT);
  
  pinMode(dig1Pin, OUTPUT);
  pinMode(dig2Pin, OUTPUT);
  pinMode(dig3Pin, OUTPUT);
  pinMode(dig4Pin, OUTPUT);
  
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
  
  irrecv.enableIRIn();
  
  
  Serial.begin(9600);
}

/* note about the display. In order to display to a digit, the dig pin must be set to high
Then all of the segments must also be set to high. */

/*

digitalWrite(dig1Pin, HIGH);
    digitalWrite(dig2Pin, HIGH);
    digitalWrite(Bpin, HIGH);
                 //is this a good idea to write to a ground pin to prevent the LED form diplaying?
                 //probabbly should use a transistor
               //the use of enumerators might be a great way to do this cycle between displays
                
*/


//use of enumerator increases readability in the for loop, without me having to create a data struture and rename the already declared pins

void loop()
{


  if (irrecv.decode()){ // have we received an IR signal?
     if(irDebouncer.acceptingInput()){
      Serial.println(irrecv.decodedIRData.command);
       switch(irrecv.decodedIRData.command){
          case 64: coinMath(numDisp.returnNumber(), quarter, dime, nickel, penny); numDisp.clear();  Serial.println("dispense");  break; // enter
          case 22: numDisp.enterNumber(0); Serial.println(0);    break; // 0
          case 12: numDisp.enterNumber(1); Serial.println(1);    break; // 1
          case 24: numDisp.enterNumber(2);Serial.println(2);    break; // 2
          case 94: numDisp.enterNumber(3); Serial.println(3);   break; // 3
          case 8: numDisp.enterNumber(4); Serial.println(4);   break;// 4
          case 28: numDisp.enterNumber(5); Serial.println(5);   break; // 5
          case 90: numDisp.enterNumber(6); Serial.println(6);   break; // 6
          case 66: numDisp.enterNumber(7);  Serial.println(7);  break; //7
          case 82: numDisp.enterNumber(8);  Serial.println(8); break; // 8
          case 74: numDisp.enterNumber(9);  Serial.println(9); break; // 9
          case 68: numDisp.deleteNumber(); Serial.println("backSpace"); break; // remove last entered number
          case 13: coinMath(numDisp.getPrevious(), quarter, dime, nickel, penny); Serial.println("dispense Previous"); break; // previous number dispense
          case 71: danceCount = 94; break;
          default:     /* do nothing */        ;
       }// End Case
       irDebouncer.debounceActive();
     } else {
      Serial.println("debounce");
      //the timer did not allow input
     } // if else for timer debounce
  }
  irrecv.resume(); // receive the next value
  
  int numToDisplay[4] = {numDisp.first(), numDisp.second(), numDisp.third(),numDisp.fourth()};
  for(int i = dig4Pin ; i >= dig1Pin ; i--){
    for(int j = 0; j<7; j++){
     digitalWrite(j+2, sevenMap[numToDisplay[i-9]][j] );           
    }
    digitalWrite(i, HIGH);
    delay(1);  // the clock delay must go between the display, othewise the display is really dim
    digitalWrite(i, LOW);
  }

  if(danceCount > 0){
    switch(danceCount){
      case 94: quarter.addCount(); break;
      case 70: nickel.addCount();break;
      case 47: penny.addCount();break;
      case 24:  dime.addCount();break;
    }
    danceCount --;
    
  }
  /*
  Serial.println(numDisp.first());
  Serial.println(numDisp.second());   //this is debuggin stuff
  Serial.println(numDisp.third());
  Serial.println(numDisp.fourth());
  */

  
  irDebouncer.tick();
  quarter.tick();
  dime.tick();
  nickel.tick();
  penny.tick();
  
}
