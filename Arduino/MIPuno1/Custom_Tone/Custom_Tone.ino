void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void Tone(int buzzer, int Freq, int duration)
{
    int uSdelay = 1000000 / Freq;
    int on_time = uSdelay0.7;
    int off_time = uSdelay0.3;

    unsigned long ending = millis() + duration;
    while (millis() < ending) 
    {
        digitalWrite(buzzer, HIGH);
        delayMicroseconds(on_time);
        digitalWrite(buzzer, LOW);
        delayMicroseconds(off_time);
    }
}
