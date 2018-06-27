
//https://extramaster.net/tools/midiToArduino/

//All methods
/*
 * Tail
 * ReadTH
 * ReadLight
 * SendMoods
 * LED1M
 * LED2M
 * Sounds
 * Sing
 * Buzz
 */

//Including libraries
#include <Wire.h>
#include <Servo.h>
#include <dht.h>
#include "pitches.h"

//Declaring pins
#define TH 2
#define LED1 5
#define LED2 6
#define spkr 8
#define tailpin 9
#define LDR 16

//Declaring some variables
int servoValue;
float lightvalue;
float THvalue;
int THtemp;
int THhumid;
String song = "empty";

//Declaring some hardware
Servo tail;
dht DHT;

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
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Arduino UNO 1 start");
  
  //Seting up some hardware
  tail.attach(tailpin);
  tail.write(90);

  //Initializing pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(spkr, OUTPUT);
  pinMode(LDR, INPUT);
  pinMode(TH, INPUT);

  //Checking wire connection
  Wire.beginTransmission(9);
  Wire.write(1);
  Wire.endTransmission();
  delay(200);
  Wire.beginTransmission(9);
  Wire.write(0);
  Wire.endTransmission();
  delay(200);
  Wire.beginTransmission(9);
  Wire.write(1);
  Wire.endTransmission();
  delay(200);
  Wire.beginTransmission(9);
  Wire.write(0);
  Wire.endTransmission();
  delay(200);
}

void loop() 
{  
  Serial.println("-------------------------------------------------");
  Serial.println();
  Serial.println("Restart loop");
  Serial.println();
  
  ReadLight();
  Serial.println();
  ReadTH();
  Serial.println();
  Tail();
  Serial.println();
  Sounds(song);
  Serial.println();
}

//Method for rerceiving lient data
void ReceiveClientData(String cmd)
{
  Serial.print("Receiving data from app");
  
  int LEDvaluecmd = cmd.indexOf("LightsToggle");
  int mtrvaluecmd = cmd.indexOf("MotorBool");
  int mtrdireccmd = cmd.indexOf("MotorCommand");
  int mipspeedcmd = cmd.indexOf("MIPSpeed");
  int moodchangecmd = cmd.indexOf("MoodChange");
  int choosesongcmd = cmd.indexOf("ChooseSong");

  if(LEDvaluecmd > 0) 
  {
     int LEDvalue = cmd[LEDvaluecmd +1];
     
     Serial.print("Send LED3 command");
     
     LED1M(LEDvalue);
  }

  if(mtrvaluecmd > 0)
  {
    int mtrbool = cmd[mtrvaluecmd + 1];

    if(!mtrbool)
    {
      if(mtrdireccmd > 0)
      {
        int mtrdirec = cmd[mtrdireccmd + 1];

        Serial.print("Send motor command");  

        Wire.beginTransmission(9);
        Wire.write(mtrdirec);                       //Values between 8 and 11
        Wire.endTransmission();
      }
    }

    else
    {
      Serial.print("Send motor command");
      
      Wire.beginTransmission(9);
      Wire.write(2);                                  //Values between 2
      Wire.endTransmission();
    }
  }

  if(mipspeedcmd > 0)
  {
     int endValue = cmd.indexOf("]");
     int mipspeeed = cmd.substring(mipspeedcmd+8, endValue).toInt();
  }
  
  if(moodchangecmd > 0)
  {
    int moodchange = cmd[moodchangecmd + 1];

    Serial.print("Send mood command");

    Wire.beginTransmission(9);
    Wire.write(moodchange);                           //Values between 3 and 7
    Wire.endTransmission();
  } 

  if(choosesongcmd> 0) {    
     int endValue = cmd.indexOf("]");
     String song = cmd.substring(choosesongcmd+10, endValue);
     Serial.print("Change song to : ");
     Serial.println(song);
  }
}

//Method for sweeping the tail
void Tail()
{
  tail.write(180);
  delay(200);
  tail.write(0);
  delay(400);
  tail.write(90);
}

//Method for measuring temperature & humidity
void ReadTH()
{
  THvalue = DHT.read11(TH);
  THtemp = DHT.temperature;
  Serial.print("Temperature = ");
  Serial.println(THtemp);
  THhumid = DHT.humidity;  
  Serial.print("Humidity = ");
  Serial.println(THhumid);
}

//Method for reading LDR and turning on/of LEDs 
void ReadLight()
{
  lightvalue = analogRead(LDR);

  Serial.print("Read LDR at: ");
  Serial.println(lightvalue);

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

//Method for controlling LED batch 1
void LED1M(int LEDvalue)
{
  if(LEDvalue = 0)
  {
    Serial.println("LOW");
    digitalWrite(LED1, LOW);
  }

  if(LEDvalue = 1)
  {
    Serial.println("HIGH");
    
    digitalWrite(LED1, HIGH);
  }
}

//Method for controlling LED batch 2
void LED2M(byte b)
{
  digitalWrite(LED2, b);
}

//Method for the making of sounds
void Sounds(String s)
{ 
  song = s;
  
  Sing(song);
}

void Sing(String song) 
{
  Serial.print("Currently playing song: ");
  Serial.println(song);

  if(song == "empty")
  {
    delay(1500);
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

