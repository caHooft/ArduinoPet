
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
#define LeftWheels 9
#define RightWheels 8

//Declaring some variables
int x;
int DistanceLeft = 0;
int DistanceFront = 0;
int DistanceRight = 0;

//Declaring some hardware
LiquidCrystal lcd(LCDrs, LCDen, LCDd4, LCDd5, LCDd6, LCDd7);

void setup() 
{
  Wire.begin(9);
  Wire.onReceive(ReceiveEvent);
  Serial.begin(9600);
  Serial.println("Arduino UNO 2 start");
  
  //Seting up some hardware
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("     __  __     ");

  //Initializing pins
  pinMode(LED, OUTPUT);
  pinMode(LeftWheels, OUTPUT);
  pinMode(RightWheels, OUTPUT);
}

void loop() 
{
  x = 0;
  
  Serial.println();
  Serial.println("-------------------------------------------------");
  Serial.println();
  Serial.println("Restart loop");
  Serial.println();

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

  if(x >= 3 && x < 9)
  {
    ChangeMood(x);
  }
  
  if(x >= 9 && x <= 12)
  {
    ToggleDir(x - 8);
  }
  
  if(x >= 15)
  {
    SaveUS();

    return;
  }
  
  if(DistanceLeft != 0 && DistanceFront != 0 && DistanceRight != 0)
  {
    RandomMove();
  }
}

//Method for receiving commands
void ReceiveEvent(int bytes)
{
  x = Wire.read();

  Serial.print("Read wire at: ");
  Serial.println(x);
}

void SaveUS()
{
  if(DistanceLeft == 0)
  {
    DistanceLeft = x;
  }

  else if(DistanceFront == 0)
  {
    DistanceFront = x;
  }

  else if(DistanceRight == 0)
  {
    DistanceRight = x;
  }

  else
  {
    DistanceLeft = 0;
    DistanceFront = 0;
    DistanceRight = 0;

    SaveUS();
  }
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
  //0.8125 is 90
  //1.625 is 180
  //3.25 is 360

  Serial.print("Left: ");
  Serial.println(DistanceLeft);
  Serial.print("Front: ");
  Serial.println(DistanceFront);
  Serial.print("Right: ");
  Serial.println(DistanceRight);

  if(50 >= DistanceLeft || 50 >= DistanceFront || 50 >= DistanceRight)
  {
    if(DistanceLeft >= DistanceFront && DistanceLeft >= DistanceRight)
    {
      digitalWrite(RightWheels, HIGH);
      delay(2000);
      digitalWrite(LeftWheels, HIGH);
      delay(1000);
      digitalWrite(LeftWheels, LOW);
      digitalWrite(RightWheels, LOW);
    }
    
    else if(DistanceFront >= DistanceLeft && DistanceFront >= DistanceRight)
    {
      if(DistanceLeft >= DistanceRight)
      {
        digitalWrite(RightWheels, HIGH);
        delay(2000);
        digitalWrite(RightWheels, LOW);
      }
      
      else
      {
        digitalWrite(LeftWheels, HIGH);
        delay(2000);
        digitalWrite(LeftWheels, LOW);
      }
    }
    
    else if(DistanceRight >= DistanceLeft && DistanceRight >= DistanceFront)
    {
      digitalWrite(LeftWheels, HIGH);
      delay(2000);
      digitalWrite(RightWheels, HIGH);
      delay(1000);
      digitalWrite(RightWheels, LOW);
      digitalWrite(LeftWheels, LOW);
    }
  }
  
  else
  {
    digitalWrite(LeftWheels, HIGH);
    digitalWrite(RightWheels, HIGH);
    delay(1000);
    digitalWrite(LeftWheels, LOW);
    digitalWrite(RightWheels, LOW);
  }
}

//Method for controlled movement
void ControlMove(int dir)
{

}

//Method for toggling the wheels
void ToggleDir(byte dir){
  if(dir == 1){
    digitalWrite(LeftWheels, HIGH);
    digitalWrite(RightWheels, HIGH);
  }
  else if(dir == 2){
    digitalWrite(RightWheels, HIGH);
    digitalWrite(LeftWheels, LOW);
  }
  else if(dir == 3){
    digitalWrite(LeftWheels, HIGH);
    digitalWrite(RightWheels, LOW);
  }
  else if(dir == 0){
    digitalWrite(LeftWheels, LOW);
    digitalWrite(RightWheels, LOW);
  }
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


