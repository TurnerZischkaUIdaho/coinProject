
int Apin = 2;
int Bpin = 3;
int Cpin = 4;
int Dpin = 5;
int Epin = 6;
int Fpin = 7;
int Gpin = 8;

int dig1Pin = 9;
int dig2Pin = 10;
int dig3Pin = 11;
int dig4Pin = 12;

//int irrPin = 13;

//this array maps a number to the 7 segment displays

bool sevenMap[10][7] = { {0,0,0,0,0,0,0}, {0,1,1,0,0,0,0} , {1,1,0,1,1,0,1} ,
{1,1,1,1,0,0,1}, {0,1,1,0,0,1,1} , {1,0,1,1,0,1,1},
                    {1,0,1,1,1,1,1}, {1,1,1,0,0,0,0}, {1,1,1,1,1,1,1},
                    {1,1,1,0,0,1,1}
                   
                   };

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

enum digPin { dig1PinE = 9, dig2PinE = 10, dig3PinE = 11, dig4PinE = 12};
//use of enumerator increases readability in the for loop, without me having to create a data struture and rename the already declared pins

void loop()
{
  int numToDisplay[4] = {0,2,3,8};
  for(int i = dig4PinE ; i >= dig1PinE ; i--){
    for(int j = 0; j<7; j++){
     digitalWrite(j+2, sevenMap[numToDisplay[i-9]][j] );           
    }
    digitalWrite(i, HIGH);
   
    delay(10);
    digitalWrite(i, LOW);
  }
  
}
