
//All methods
/*
 * RandomMove
 * ControlMove
 * Turn
 * ReceiveMood
 * ChangeMood
 */

//Including libraries
#include <LiquidCrystal.h>

//Declaring pins
#define LCDrs 2
#define LCDen 3
#define LCDd4 4
#define LCDd5 5
#define LCDd6 6
#define LCDd7 7
#define mtr1 8
#define mtr2 9
#define mtr3 10
#define mtr4 11

//Declaring some hardware
LiquidCrystal lcd(LCDrs, LCDen, LCDd4, LCDd5, LCDd6, LCDd7);

void setup() 
{
  Serial.begin(9600);
  Serial.println("Arduino UNO 2 start");
  
  //Seting up some hardware
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("     __  __     ");

  //Initializing pins
  
}

void loop() 
{

}

//Method for random movement
void RandomMove()
{
  
}

//Method for controlled movement
void ControlMove()
{
  
}

//Method for steering
void Turn()
{
  
}

//Method for receiving mood from DUE
void ReceiveMood()
{
  
}

//Method for changing mood on LCD
void ChangeMood()
{
  
}
