int pushButton = 2;
int motorControl = 9;

void setup() 
{
  pinMode(pushButton, INPUT);
  pinMode(motorControl, OUTPUT);  
}
void loop() {
  if(digitalRead(pushButton) == HIGH)
  { 
    // ramp up the motor speed
    for(int x = 0; x <= 255; x++){
      analogWrite(motorControl, x);
      delay(50);
    }

    // ramp down the motor speed
    for(int x = 255; x >= 0; x--){
      analogWrite(motorControl, x);
      delay(50);
    }    
  }

  delay(1);        // delay in between reads for stability
}

