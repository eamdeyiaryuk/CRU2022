// fl
#define m11 12 //
#define m12 32 //
#define m1a 9 //ENA
// fr
#define m21 13 //
#define m22 25 //
#define m2b 11 //ENB
// br
#define m31 7  //IN3
#define m32 30 //IN4
#define m3a 6  //ENA
// bl
#define m41 27  //IN1
#define m42 4 //IN2
#define m4b 2 //ENB
// parameter
#define deg_to_rad PI/180

void motorPinSetup()
{
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m1a, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);
  pinMode(m2b, OUTPUT);
  pinMode(m31, OUTPUT);
  pinMode(m32, OUTPUT);
  pinMode(m3a, OUTPUT);
  pinMode(m41, OUTPUT);
  pinMode(m42, OUTPUT);
  pinMode(m4b, OUTPUT);
}
void motorFL(int spd)
{
 if(spd > 0)
  {
    digitalWrite(m11, LOW);
    digitalWrite(m12,  HIGH);   
  }
  else if(spd < 0)
  {
    digitalWrite(m11,  HIGH);
    digitalWrite(m12, LOW);       
  }
  else{
    digitalWrite(m11,  LOW);
    digitalWrite(m12,  LOW);  
  }
  analogWrite(m1a, abs(spd));
}
void motorFR(int spd)
{
   if(spd > 0)
  {
    digitalWrite(m21, LOW);
    digitalWrite(m22,  HIGH);   
  }
  else if(spd < 0)
  {
    digitalWrite(m21, HIGH);
    digitalWrite(m22, LOW);       
  }
  else{
    digitalWrite(m21,  LOW);
    digitalWrite(m22,  LOW);  
  }
  analogWrite(m2b, abs(spd));
}
void motorBR(int spd)
{
  if(spd > 0)
  {
    digitalWrite(m31, HIGH);
    digitalWrite(m32,  LOW);   
  }
  else if(spd < 0){
    digitalWrite(m31,  LOW);
    digitalWrite(m32, HIGH);       
  }
  else{
    digitalWrite(m31,  LOW);
    digitalWrite(m32,  LOW);  
  }
  analogWrite(m3a, abs(spd));
}
void motorBL(int spd)
{
  if(spd > 0)
  {
    digitalWrite(m41, HIGH);
    digitalWrite(m42,  LOW);   
  }
  else if(spd < 0){
    digitalWrite(m41,  LOW);
    digitalWrite(m42, HIGH);       
  }
  else{
    digitalWrite(m41,  LOW);
    digitalWrite(m42,  LOW);  
  }
  analogWrite(m4b, abs(spd));
}
void drive(float vec, float theta, float head)
{
  float c = cos(theta * deg_to_rad);
  float s = sin(theta * deg_to_rad);
  float v_fl = vec * (c * -0.707 + s * -0.707) + head;
  float v_fr = vec * (c * -0.707 + s *  0.707) + head;
  float v_bl = vec * (c *  0.707 + s * -0.707) + head;
  float v_br = vec * (c *  0.707 + s *  0.707) + head;
   
  motorFL(constrain(v_fl, -255, 255));
  motorFR(constrain(v_fr, -255, 255));
  motorBL(constrain(v_bl, -255, 255));
  motorBR(constrain(v_br, -255, 255));
}
void motorstop(){
  motorFL(0);
  motorFR(0);
  motorBL(0);
  motorBR(0);
}
  
