
//Including libraries
#include <LiquidCrystal.h>

//Declaring pins
#define LCDrs 8
#define LCDen 9
#define LCDd4 4
#define LCDd5 5
#define LCDd6 6
#define LCDd7 7

//Declaring some hardware
LiquidCrystal lcd(LCDrs, LCDen, LCDd4, LCDd5, LCDd6, LCDd7);

void setup() 
{
  //Seting up some hardware
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("     __  __     ");

  //Initializing pins
  
}

void loop() 
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
