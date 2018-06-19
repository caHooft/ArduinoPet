
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
 * Sing
 * Buzz
 */

//Including libraries
#include <Servo.h>
#include "pitches.h"

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
float USduration;
float USdistance;
int servoValue;
float lightvalue;
float THvalue;
int song = 0;

//Declaring some hardware
Servo myServo;

//Declaring song arrays
int mario_melody[] = 
{
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 0, NOTE_C7, NOTE_E7, 0, NOTE_G7, 0, 0,  0, NOTE_G6, 0, 0, 0, NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6,
  0, 0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0, NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0, NOTE_F7, NOTE_G7, 0, NOTE_E7, 0,
  NOTE_C7, NOTE_D7, NOTE_B6, 0, 0, NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0, 0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0,
  NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0, NOTE_F7, NOTE_G7, 0, NOTE_E7, 0, NOTE_C7, NOTE_D7, NOTE_B6, 0, 0,
};
int mario_tempo[] = 
{
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,12, 12, 12, 12, 
  9, 9, 9,12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
  9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
};
int underworld_melody[] = 
{
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,  NOTE_AS3, NOTE_AS4, 0,  0,  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,  NOTE_AS3, NOTE_AS4, 0,  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,  NOTE_DS3, NOTE_DS4, 0,  0,  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,  NOTE_CS4, NOTE_DS4,  NOTE_DS4, NOTE_GS3,  NOTE_G3, NOTE_CS4,  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3,
  NOTE_AS4, NOTE_A4,  NOTE_GS4, NOTE_DS4, NOTE_B3,  NOTE_AS3, NOTE_A3, NOTE_GS3,  0, 0, 0
};
int underworld_tempo[] = 
{
  12, 12, 12, 12,  12, 12, 6,  3,  12, 12, 12, 12,  12, 12, 6, 3,  12, 12, 12, 12, 12, 12, 6,  3, 12, 12, 12, 12, 12, 12, 6, 6, 18,
  18, 18, 6, 6, 6, 6, 6, 6, 18, 18, 18, 18, 18, 18, 10, 10, 10, 10, 10, 10, 3, 3, 3
};

int jingle_melody[] = 
{
  NOTE_e,NOTE_e,NOTE_e,NOTE_e,NOTE_e,NOTE_e,NOTE_e,NOTE_g,NOTE_c,NOTE_d,NOTE_e, NOTE_x, NOTE_f, NOTE_f, NOTE_f, NOTE_f, NOTE_f,NOTE_e,
  NOTE_e,NOTE_e,NOTE_e,NOTE_d,NOTE_d,NOTE_e,NOTE_d,NOTE_g
};

int jingle_tempo[] = 
{
 4, 4, 8, 4, 4, 8, 4, 4, 4, 4, 16, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8, 8 
};
/*
int jingle_tempo[] = 
{
 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2 
};
*/

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
  Sing(3);
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

void Sing(int s) 
{
  song = s;

  if(song == 1)
  {
    int size = sizeof(mario_melody) / sizeof(int);
    
    for (int i = 0; i < size; i++) 
    {
      int noteDuration = 1000 / mario_tempo[i];
 
      Buzz(mario_melody[i], noteDuration);
      
      int noteDelay = noteDuration * 1.30;
      delay(noteDelay);
 
      Buzz(0, noteDuration);
    }
  }
  
  if (song == 2) 
  {
    int size = sizeof(underworld_melody) / sizeof(int);
    
    for (int i = 0; i < size; i++) 
    {
      int noteDuration = 1000 / underworld_tempo[i];
 
      Buzz(underworld_melody[i], noteDuration);
 
      int noteDelay = noteDuration * 1.30;
      delay(noteDelay);
 
      Buzz(0, noteDuration);
    }
  } 

  if (song == 3) 
  {
    int size = sizeof(jingle_melody) / sizeof(int);
    
    for (int i = 0; i < size; i++) 
    {
      int noteDuration = 1000 / jingle_tempo[i];
 
      Buzz(jingle_melody[i], noteDuration);
 
      int noteDelay = noteDuration * 1.30;
      delay(noteDelay);
 
      Buzz(0, noteDuration);
    }
  } 
}

void Buzz(long frequency, long length) 
{
  long delayValue = 1000000 / frequency / 2;
  long Cycles = frequency * length / 1000; 
  
  for (long i = 0; i < Cycles; i++) 
  {
    digitalWrite(spkr, HIGH); 
    delayMicroseconds(delayValue); 
    digitalWrite(spkr, LOW); 
    delayMicroseconds(delayValue); 
  }
}

