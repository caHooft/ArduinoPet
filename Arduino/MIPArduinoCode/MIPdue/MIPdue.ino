
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
float duration;
float distance;
int servoValue;
float lightvalue;
float THvalue;
int song = 0;

//Declaring some hardware
Servo myServo;

int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 0, NOTE_C7, NOTE_E7, 0, NOTE_G7, 0, 0,  0, NOTE_G6, 0, 0, 0, NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6,
  0, 0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0, NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0, NOTE_F7, NOTE_G7, 0, NOTE_E7, 0,
  NOTE_C7, NOTE_D7, NOTE_B6, 0, 0, NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0, 0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0,
  NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0, NOTE_F7, NOTE_G7, 0, NOTE_E7, 0, NOTE_C7, NOTE_D7, NOTE_B6, 0, 0,
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,12, 12, 12, 12, 
  9, 9, 9,12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
  9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = 
{
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,  NOTE_AS3, NOTE_AS4, 0,  0,  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,  NOTE_AS3, NOTE_AS4, 0,  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,  NOTE_DS3, NOTE_DS4, 0,  0,  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,  NOTE_CS4, NOTE_DS4,  NOTE_DS4, NOTE_GS3,  NOTE_G3, NOTE_CS4,  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3,
  NOTE_AS4, NOTE_A4,  NOTE_GS4, NOTE_DS4, NOTE_B3,  NOTE_AS3, NOTE_A3, NOTE_GS3,  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = 
{
  12, 12, 12, 12,  12, 12, 6,  3,  12, 12, 12, 12,  12, 12, 6, 3,  12, 12, 12, 12, 12, 12, 6,  3, 12, 12, 12, 12, 12, 12, 6, 6, 18,
  18, 18, 6, 6, 6, 6, 6, 6, 18, 18, 18, 18, 18, 18, 10, 10, 10, 10, 10, 10, 3, 3, 3
};
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
  sing(1);
  sing(1);
  sing(2);
  //Sounds();
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
  int JingleBellstempo = 300;
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
    
    delay(JingleBellstempo / 2); 
  }
}

void sing(int s) {
  // iterate over the notes of the melody:
  song = s;
  if (song == 2) {
    Serial.println(" 'Underworld Theme'");
    int size = sizeof(underworld_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
 
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / underworld_tempo[thisNote];
 
      buzz(spkr, underworld_melody[thisNote], noteDuration);
 
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
 
      // stop the tone playing:
      buzz(spkr, 0, noteDuration);
 
    }
 
  } else {
 
    Serial.println(" 'Mario Theme'");
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
 
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];
 
      buzz(spkr, melody[thisNote], noteDuration);
 
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
 
      // stop the tone playing:
      buzz(spkr, 0, noteDuration);
 
    }
  }
}
void buzz(int targetPin, long frequency, long length) {
  digitalWrite(13, HIGH);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  digitalWrite(13, LOW);
 
}

