
//https://extramaster.net/tools/midiToArduino/

//All methods
/*
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
#include <Wire.h>
#include <SimpleDHT.h>
#include "pitches.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
WiFiServer server(80);
WiFiClient client;

const char* ssid     = "KikkerOfKinker";
const char* password = "12345678";
//Declaring pins
//Niet gebruiken ivm WiFi shield: 6 tm 11
#define TH 2
#define neckpin 3
#define LED1 5
#define LED2 4 // gewijzigd van 6 naar 4
#define spkr 12 // gewijzigd van 8 naar 12

#define LDR A0

//Declaring some variables
float lightvalue;
float THvalue;
byte THtemp;
byte THhumid;
int err = SimpleDHTErrSuccess;
String song = "empty";
//Declaring some hardware
SimpleDHT11 dht11;

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
  //Serial.begin(9600);
  Serial.println("Arduino UNO 1 start");
  
  //Init Wifi  
  Serial.begin(115200);
  
  //Initializing pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(spkr, OUTPUT);
  pinMode(LDR, INPUT);
  pinMode(TH, INPUT);
  
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  server.begin();
/*
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
*/}

void loop() 
{  
  Serial.println("-------------------------------------------------");
  Serial.println();
  Serial.println("Restart loop");
  Serial.println();

  ServerActivity();
  Serial.println();
  ReadLight();
  Serial.println();
  ReadTH();
  Serial.println();
  Sounds(song);
  Serial.println();
}

void ServerActivity()
{  
  client = server.available();
  // wait for a client (web browser) to connect
  if (client)
  {
    while(client.connected())
    {
      // read line by line what the client (web browser) is requesting
      if (client.available())
      {
        String line = client.readStringUntil('\r');
        ReceiveClientData(line);
      }  
      Serial.println();
      ReadLight();
      Serial.println();
      ReadTH();
      Serial.println();
      Sounds(song);
      Serial.println();
    }
    client.stop();
    Serial1.println("[Client disonnected]");      
    delay(1); // give the web browser time to receive the data
  } 
}

void SendSensorValues()
{
  String cmd = "data";
  cmd += "LDR"+ (String)lightvalue + "|";
  cmd += "Humidity"+ (String)THhumid +"}"; 
  cmd += "Temperature" + (String)THtemp +";";
  client.print(cmd);
  Serial1.println(cmd);
}

//Method for rerceiving lient data
void ReceiveClientData(String cmd)
{
  Serial.print("Receiving data from app ");
  
  int LEDvaluecmd = cmd.indexOf("LightsToggle");
  int mtrvaluecmd = cmd.indexOf("MotorBool");
  int mtrdireccmd = cmd.indexOf("MotorCommand");
  int mipspeedcmd = cmd.indexOf("MIPSpeed");
  int moodchangecmd = cmd.indexOf("MoodChange");
  int choosesongcmd = cmd.indexOf("ChooseSong");
  int AITogglecmd = cmd.indexOf("AIToggle");  
  int UpdateValuecmd = cmd.indexOf("Update");
  
  if(UpdateValuecmd> 0)
  {    
    SendSensorValues();
  }  
  if(AITogglecmd> 0) 
  {
     Serial.print("Set AI to : ");
     Serial.println(cmd[AITogglecmd +8]);
  }
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

//Method for measuring temperature & humidity
void ReadTH()
{
  Serial.print("Sample DHT11..."); 
  Serial.print(analogRead(TH));
  if((err = dht11.read(TH, &THtemp, &THhumid, NULL)) != SimpleDHTErrSuccess){
    Serial.print("Read DHT11 failed, err=");
    Serial.println(err);
    delay(1000);
    return;
  }

  Serial.print("Sample OK: ");
  Serial.print((int)THtemp); 
  Serial.print(" *C, ");
  Serial.print((int)THhumid);
  Serial.println(" H");
  delay(1500);
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

//Method for activating WiFi Shield
void InitWiFi()
{
  
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

