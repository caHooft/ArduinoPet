
//All methods
/*
 * RandomMove
 * ControlMove
 * Movement
 * ReceiveMood
 * ChangeMood
 */

//Including libraries
#include <Wire.h>
#include <LiquidCrystal.h>

//Declaring pins
#define LCDrs 2
#define LCDen 3
#define LCDd4 4
#define LCDd5 5
#define LCDd6 6
#define LCDd7 7
#define LED 13

//Declaring some variables
int x;

//Declaring some hardware
LiquidCrystal lcd(LCDrs, LCDen, LCDd4, LCDd5, LCDd6, LCDd7);

void setup() 
{
  Wire.begin(9);
  Serial.begin(9600);
  Serial.println("Arduino UNO 2 start");
  
  //Seting up some hardware
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("     __  __     ");

  //Initializing pins
  pinMode(LED, OUTPUT);
}

void loop() 
{
  Serial.println("-------------------------------------------------");
  Serial.println();
  Serial.println("Restart loop");
  Serial.println();

  Wire.onReceive(ReceiveEvent);
  
  if(x == 0) 
  {
    LEDM(LOW);
  }

  if(x == 1) 
  {
    LEDM(HIGH);
  }

  if(x == 2) 
  {
    RandomMove();
  }

  if(x >= 3 && x < 8)
  {
    ChangeMood(x);
  }
}

//Method for receiving commands
void ReceiveEvent(int bytes)
{
  x = Wire.read();
}

void LEDM(byte b)
{
  digitalWrite(LED, b);
  Serial.print("LED at: ");
  Serial.println(b);
}

//Method for random movement
void RandomMove()
{
  
}

//Method for controlled movement
void ControlMove(int dir)
{

}

//Method for moving
void Movement()
{
  
}

//Method for receiving mood from DUE
void ReceiveMood()
{
  
}

//Method for changing mood on LCD
void ChangeMood(int i)
{
  if(i == 3)
  {
    
  }

  if(i == 4)
  {
    
  }

  if(i == 5)
  {
    
  }

  if(i == 6)
  {
    
  }

  if(i == 7)
  {
    
  }
}

void HappyBrows()
{
  byte browOne[8] = {0,0,0b00011,0b00111,0b01111,0b11100,0b01000};
  lcd.createChar(0, browOne);
  byte browTwo[8] = {0,0b11111,0b11111,0b11000,0,0,0,0};
  lcd.createChar(1, browTwo);
  byte browThree[8] = {0,0b11111,0b11111,0,0,0,0,0};
  lcd.createChar(2, browThree);
  byte browFour[8] = {0,0b11110,0b11111,0b00011,0,0,0,0};
  lcd.createChar(3, browFour);
  byte browFive[8] = {0,0b01111,0b11111,0b11000,0,0,0,0};
  lcd.createChar(4, browFive);
  byte browSix[8] = {0,0b11111,0b11111,0,0,0,0,0};
  lcd.createChar(5, browSix);
  byte browSeven[8] = {0,0b11111,0b11111,0b00011,0,0,0,0};
  lcd.createChar(6, browSeven);
  byte browEight[8] = {0,0,0b11000,0b11100,0b11110,0b00111,0b00010};
  lcd.createChar(7, browEight);

  lcd.setCursor(2,1);
  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.write(byte(2));
  lcd.write(byte(3));
  lcd.setCursor(10,1);
  lcd.write(byte(4));
  lcd.write(byte(5));
  lcd.write(byte(6));
  lcd.write(byte(7));
}

void AngryBrows()
{
  byte browOne[8] = {0b01111, 0b11111, 0b01111, 0b00000, 0b00000, 0b00000, 0b00000,0};
  lcd.createChar(0, browOne);
  byte browTwo[8] = {0b00000, 0b11100, 0b11111, 0b11111, 0b00111, 0b00000, 0, 0b00000};
  lcd.createChar(1, browTwo);
  byte browThree[8] = {0, 0, 0, 0b11111, 0b11111, 0b11111, 0b00001, 0};
  lcd.createChar(2, browThree);
  byte browFour[8] = {0,0,0,0,0b11000, 0b11110,0b11111,0b00111};
  lcd.createChar(3, browFour);
  byte browFive[8] = {0,0,0,0,0b00011,0b01111,0b11111,0b11100};
  lcd.createChar(4, browFive);
  byte browSix[8] = {0,0,0,0b11111,0b11111,0b11111,0b10000,0};
  lcd.createChar(5, browSix);
  byte browSeven[8] = {0, 0b00111, 0b11111, 0b11111, 0b11100, 0, 0, 0};
  lcd.createChar(6, browSeven);
  byte browEight[8] = {0b11110, 0b11111, 0b11110,0,0,0,0,0};
  lcd.createChar(7, browEight);

  lcd.setCursor(2,1);
  lcd.write(byte(0));
  lcd.write(byte(1));
  lcd.write(byte(2));
  lcd.write(byte(3));
  lcd.setCursor(10,1);
  lcd.write(byte(4));
  lcd.write(byte(5));
  lcd.write(byte(6));
  lcd.write(byte(7));
}


