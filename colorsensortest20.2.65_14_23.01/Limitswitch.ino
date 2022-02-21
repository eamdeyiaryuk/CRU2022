boolean reading1;
boolean state = HIGH;
boolean condition = false,
        timer = false;
int buttonPin1 = 44;
int Reading1;
unsigned long stored_time = 0, elapsed_time;
int count = 0;
void Open_Limitswitch(){
  digitalWrite(buttonPin1,INPUT);
}
void Press_Limitswitch(){
  Reading1 = digitalRead(buttonPin1);
  if(Reading1 == LOW)
  {
    motorstop();
    
    timer = true; stored_time = millis();
    do 
    {
      elapsed_time = millis() - stored_time;
      Serial.println(elapsed_time);
    }
    while (elapsed_time <= 20000 && timer == true);
    timer = false;

    count++;
    Serial.print(count);
  }
  else{
    Run('R');
  }
}
