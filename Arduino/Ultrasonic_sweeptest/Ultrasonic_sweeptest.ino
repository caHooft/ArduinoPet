#include <Servo.h>

Servo myservo;
byte uspin = 10;

void setup() {
  myservo.attach(11);
  Serial.begin(9600);
}

void loop() {
  myservo.write(0);
  delay(1000);
  Serial.print(distance());
  Serial.print("cm links, ");
  myservo.write(90);
  delay(1000);
  Serial.print(distance());
  Serial.print("cm voor en ");
  myservo.write(180);
  delay(1000);
  Serial.print(distance());
  Serial.println("cm rechts.");
}

float distance(){
  pinMode(uspin, OUTPUT);
  digitalWrite(uspin, LOW);
  delayMicroseconds(2);
  digitalWrite(uspin, HIGH);
  delayMicroseconds(10);
  digitalWrite(uspin, LOW);
  pinMode(uspin, INPUT);
  return pulseIn(uspin, HIGH) / 29 / 2;
}

