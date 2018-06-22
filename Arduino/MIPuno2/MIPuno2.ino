
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

  if(x == 3) 
  {
    ControlMove(x);
  }

  if(x == 4) 
  {
    ControlMove(x);
  }

  if(x == 5) 
  {
    ControlMove(x);
  }
}

//Method for receiving commands
void ReceiveEvent(int bytes)
{
  x = Wire.read();
}

//Method for random movement
void RandomMove()
{
  
}

//Method for controlled movement
void ControlMove(int dir)
{
  if(dir == 3) 
  {
    
  }

  if(dir == 4) 
  {
    
  }

  if(dir == 5) 
  {

  }
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
void ChangeMood()
{
  
}

void LEDM(byte b)
{
  digitalWrite(LED, b);
  Serial.print("LED at: ");
  Serial.println(b);
}

