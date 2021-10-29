/* Arduino change counter from serial version 1 
Created on 10/12/21 by Gabe Nelson 
Last modified on 10/19/21 by Gabe Nelson 
*/ 
 
int change; 
int quarters = 0; 
int dimes = 0; 
int nickels = 0; 
int pennies = 0; 
 
void calcChange(); 
 
void setup() 
{ 
Serial.begin(9600); 
} 
 
void calcChange() 
{    
//the following code determines how many of each coin are needed to total the amount input 
    quarters = change / 25; 
    change = change % 25; 
    dimes = change / 10; 
    change = change % 10; 
    nickels = change / 5; 
    change = change % 5; 
    pennies = change / 1; 
    change = change % 1; 
   
//prints how many of each coin are used 
  Serial.print("q: "); 
  Serial.println(quarters); 
  Serial.print("d: "); 
  Serial.println(dimes); 
  Serial.print("n: "); 
  Serial.println(nickels); 
  Serial.print("p: "); 
  Serial.println(pennies); 
} 
 
void loop() 
{ 
/* 

The following code reads input from the serial monitor. 
This will likely be replaced by some kind of input from a keypad or remote 

*/ 
  if (Serial.available() > 0) { 

// reads input from serial monitor and assigns it a variable: 
    change = Serial.parseInt(); 
    // print what you got: 
    Serial.print("Change: "); 
    Serial.println(change); 
    // lists what change will dispense: 
    calcChange(); //user defined function to calculate minimum coins needed 
     
    /*  
    in the actual code, there would be more user defined functions here 
    that run a specific servo a number of times equivalent to each of the 
    individual change variables. For example 'dispenseQuarter()' 
    */ 
   
  } 
}
