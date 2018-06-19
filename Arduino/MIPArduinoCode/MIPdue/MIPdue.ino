
//All methods
/*
 * RandomMove
 * ControlMove
 * Turn
 * Tail
 * ReadUS
 * ReadTH
 * ReadLight
 * SendMoods
 * Sounds
 * LED1M
 * LED2M
 * InitWifi
 * PlayNote
 * PlayTone
 * JingleBells
 */

//Including libraries
#include <Servo.h>

//Declaring pins
//Niet gebruiken ivm WiFi shield: 4, 7, 10, 11, 12, 13
#define TH 3
#define LED1 5
#define LED2 6
#define spkr 8
#define servo 9
#define mtr1 50
#define mtr2 51
#define mtr3 52
#define mtr4 53

#define trig A0
#define echo A1
#define LDR A2

//Declaring some variables
float duration;
float distance;
int servoValue;
float lightvalue;
float THvalue;

//Declaring some hardware
Servo myServo;

void setup() 
{
  Serial.begin(9600);
  
  //Seting up some hardware
  myServo.attach(servo);
  myServo.write(90);

  //Initializing pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(spkr, OUTPUT);
}

void loop() 
{
  ReadLight();
  Sounds();
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

//Method for tail movement
void Tail()
{
  
}

//Method for reading ultra sonic sensor and avoiding collisions
void ReadUSonic()
{
  
}


//Method for measuring temperature & humidity
void ReadTH()
{
  
}

//Method for reading LDR and turning on/of LEDs 
void ReadLight()
{
  lightvalue = analogRead(LDR);

  if(lightvalue >= 200)
  {
    LED2M(HIGH);
  }

  else if(lightvalue < 200)
  {
    LED2M(LOW);
  }
}

//Method for sending mood to UNO
void SendMood()
{
  
}

//Method for the making of sounds
void Sounds()
{
  JingleBells();
}

//Method for controlling LED batch 1
void LED1M()
{
  
}

//Method for controlling LED batch 2
void LED2M(byte b)
{
  digitalWrite(LED2, b);
}

//Method for activating WiFi Shield
void InitWiFi()
{
  
}

void playNote(char note, int j) 
{
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) 
  {
    if (names[i] == note) 
    {
      playTone(tones[i], j);
    }
  }
}

void playTone(int tone, int j) 
{
  for (long i = 0; i < j * 1000L; i += tone * 12) 
  {
    digitalWrite(spkr, HIGH);
    delayMicroseconds(tone);
    digitalWrite(spkr, LOW);
    delayMicroseconds(tone);
  }
}

void JingleBells()
{
  int JingleBellstempo = 400;
  char JingleBellsnotes[] = "eeeeeeegcde fffffeeeeddedg";
  int JingleBellsbeats[] = {1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};
  
  for (int i = 0; i < 26; i++) 
  {
    if (JingleBellsnotes[i] == ' ') 
    {
      delay(JingleBellsbeats[i] * JingleBellstempo);
    } 
    
    else 
    {
      playNote(JingleBellsnotes[i], JingleBellsbeats[i] * JingleBellstempo);
    }
    
    delay(tempo / 2); 
  }
}

