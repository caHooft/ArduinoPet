
//https://extramaster.net/tools/midiToArduino/

//All methods
/*
 * MtrMove
 * Tail
 * Neck
 * Distance
 * ReadUS
 * ReadTH
 * ReadLight
 * SendMoods
 * LED1M
 * LED2M
 * InitWifi
 * Sounds
 * Sing
 * Buzz
 */

//Including libraries
#include <Servo.h>
#include "pitches.h"

//Declaring pins
//Niet gebruiken ivm WiFi shield: 4, 7, 10, 11, 12, 13
#define TH 2
#define neckpin 3
#define LED1 5
#define LED2 6
#define spkr 8
#define tailpin 9

#define trig A0
#define echo A1
#define LDR A2

//Declaring some variables
float USdistance1;
float USdistance2;
float USdistance3;
int servoValue;
float lightvalue;
float THvalue;
String song = "";

//Declaring some hardware
Servo neck;
Servo tail;

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
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,  NOTE_AS3, NOTE_AS4, 0,  0,  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,  NOTE_AS3, NOTE_AS4, 0, 0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,  NOTE_DS3, NOTE_DS4, 0,  0,  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,  NOTE_DS3, NOTE_DS4, 0, 0, 
  NOTE_DS4, NOTE_CS4, NOTE_D4,  NOTE_CS4, NOTE_DS4,  NOTE_DS4, NOTE_GS3,  NOTE_G3, NOTE_CS4,  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3,
  NOTE_AS4, NOTE_A4,  NOTE_GS4, NOTE_DS4, NOTE_B3,  NOTE_AS3, NOTE_A3, NOTE_GS3,  0, 0, 0
};

int underworld_tempo[] = 
{
  12, 12, 12, 12,  12, 12, 6,  3,  12, 12, 12, 12,  12, 12, 6, 3,  12, 12, 12, 12, 12, 12, 6,  3, 12, 12, 12, 12, 12, 12, 6, 6, 18,
  18, 18, 6, 6, 6, 6, 6, 6, 18, 18, 18, 18, 18, 18, 10, 10, 10, 10, 10, 10, 3, 3, 3
};

int jingle_melody[] = 
{
  NOTE_e, NOTE_e, NOTE_e, NOTE_e, NOTE_e, NOTE_e, NOTE_e, NOTE_g, NOTE_c, NOTE_d, NOTE_e, 0, 
  NOTE_f, NOTE_f, NOTE_f, NOTE_f, NOTE_f, NOTE_e, NOTE_e, NOTE_e, NOTE_e, NOTE_d, NOTE_d, NOTE_e, NOTE_d, NOTE_g
};

int jingle_beats[] = 
{
  1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2
};


void setup() 
{
  Serial.begin(9600);
  Serial.println("Arduino UNO 1 start");
  
  //Seting up some hardware
  neck.attach(neckpin);
  neck.write(90);
  tail.attach(tailpin);
  tail.write(97);

  //Initializing pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(spkr, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(LDR, INPUT);
}

void loop() 
{  
  Serial.println();
  Serial.println("Restart loop");
  Serial.println();
  ReadLight();
  Neck();
  Sounds();
}

//Method for moving
void MtrMove()
{
  
}

//Method for sweeping the tail
void Tail()
{
  
}

//Method for sweeping the neck
void Neck()
{
  neck.write(0);
  delay(1000);
  USdistance1 = Distance();
  Serial.print(USdistance1);
  Serial.println(" cm rechts");
  neck.write(90);
  delay(1000);
  USdistance2 = Distance();
  Serial.print(USdistance2);
  Serial.println(" cm voor");
  neck.write(180);
  delay(1000);
  USdistance3 = Distance();
  Serial.print(USdistance3);
  Serial.println(" cm links");
  neck.write(90);
}

//Method for reading ultra sonic sensor and avoiding collisions
float Distance()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  float USvalue = pulseIn(echo, HIGH) / 29 / 2;
  Serial.print("Read US on: ");
  return USvalue;
}


//Method for measuring temperature & humidity
void ReadTH()
{
  
}

//Method for reading LDR and turning on/of LEDs 
void ReadLight()
{
  lightvalue = analogRead(LDR);

  Serial.print("Read LDR at: ");
  Serial.println(lightvalue);

  if(lightvalue >= 400)
  {
    LED2M(HIGH);
  }

  else if(lightvalue < 400)
  {
    LED2M(LOW);
  }
}

//Method for sending mood to UNO
void SendMood()
{
  
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

//Method for the making of sounds
void Sounds()
{ 
  Sing("");
}

void Sing(String s) 
{
  song = s;

  Serial.print("Currently playing song: ");
  Serial.println(song);

  if(song == "")
  {
    delay(100);
    return;
  }
  
  if(song == "mario")
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
  
  if (song == "underworld") 
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

  if(song == "jingle")
  {
    int size = sizeof(jingle_melody) / sizeof(int);
    
    for (int i = 0; i < size; i++) 
    {
      int noteDuration = 1000 / jingle_beats[i];
 
      Tone(jingle_melody[i], noteDuration);
 
      int noteDelay = noteDuration * 1.30;
      delay(noteDelay);
 
      Tone(0, noteDuration);
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

void Tone(int Freq, int duration)
{
    int uSdelay = 1000000 / Freq;
    int on_time = uSdelay * 0.7;
    int off_time = uSdelay * 0.3;

    unsigned long ending = millis() + duration;
    while (millis() < ending) 
    {
        digitalWrite(spkr, HIGH);
        delayMicroseconds(on_time);
        digitalWrite(spkr, LOW);
        delayMicroseconds(off_time);
    }
}

