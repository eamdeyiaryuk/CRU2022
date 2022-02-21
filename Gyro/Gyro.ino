#include "gyrocomplete.h"

gyro g;

void setup() 
{
 Serial.begin(115200);
 attachInterrupt(0, gyro_interrupt, RISING);
 g.setOffset(220, 76, -85, 1788); // offset  
 g.initializer(); // setup
 g.prepare(2000); // wait 3000 ms per 1 check
 pinMode(13, OUTPUT);
 digitalWrite(13, HIGH);
}
long timereset = millis();
void loop() 
{
 float angle = g.getVal(true);
 analogWrite(3, map(angle, -180, 180, 5, 250));
 Serial.println(angle);
 /*
 if(millis()-timereset >= 5000)
 {
  gyro.setpointReset();
  timereset = millis();
 }
 */
}
void gyro_interrupt()
{
  g.mpuInterrupt = true;
}
