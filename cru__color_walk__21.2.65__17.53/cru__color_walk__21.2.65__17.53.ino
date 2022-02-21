
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

int red = 0, r_value = 0,
    blue = 0, b_value = 0,
    green = 0, g_value = 0;

int red2 = 0, r_value2 = 0,
    blue2 = 0, b_value2 = 0,
    green2 = 0, g_value2 = 0;

bool Yellow = false, Green = false, b_green = false, finish = false, b_green2 = false;
int count = 0;

unsigned long curMillis;
unsigned long prevMillis = 0; //เวลาที่ผ่านไปแล้ว

#define S0 24
#define S1 26
#define S2 28
#define S3 31
#define sensorOut 8

#define S00 29
#define S11 33
#define S22 34
#define S33 35
#define sensorOut2 3

void setup() {

  // เปิดport_serial_communicate baterate = 9600
  Serial.begin(9600);

  motorPinSetup();

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  pinMode(S00, OUTPUT);
  pinMode(S11, OUTPUT);
  pinMode(S22, OUTPUT);
  pinMode(S33, OUTPUT);
  pinMode(sensorOut2, INPUT);


  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  digitalWrite(S00, HIGH);
  digitalWrite(S11, LOW);

}

void loop() {
  read_colour(); read_colour2();

  switch (count)
  {
    case 0 : delay(2000); count++; Serial.print(count); break;
    case 1 :
      //Run('F');
      do {
        if (b_green == false) Run('F');
        read_colour(); read_colour2();
        case_green();

        //        curMillis = millis();
        //        if (curMillis - prevMillis >= 100) {
        //          prevMillis = curMillis;
        //          Serial.print("Green = ");
        //          Serial.println(Yellow);
        //        }

        if (b_green == true) {
          motorstop();
          finish = true;
        }
      } while (b_green == false && finish == false);
      finish = false; b_green = false;
      count++; Serial.print(count); break;

    case 2 :
      delay(100);
      b_delay(700);
      delay(100);
      do {
        if (b_green2 == false) Run('R');
        read_colour(); read_colour2();
        case_green2();

        if (b_green2 == true) {
          motorstop();
          finish = true;
        }
      } while (b_green2 == false && finish == false);
      count++; Serial.print(count); break;
    case 3 :
    delay(100);
    L_delay(600);
    delay(100);
    do {
        if (b_green2 == false) Run('B');
        read_colour(); read_colour2();
        case_green2();

        if (b_green2 == true) {
          motorstop();
          finish = true;
        }
      } 
   while (b_green2 == false && finish == false);
   count++; Serial.print(count); break;
}
}

void fr_delay(int wait)
{
  unsigned long timer = millis();
  while (1) {
    Run('F');
    if ( millis() - timer >= wait ) {
      break;
    }
  }
  motorstop();
}
void R_delay(int wait)
{
  unsigned long timer = millis();
  while (1) {
    Run('R');
    if ( millis() - timer >= wait ) {
      break;
    }
  }
  motorstop();
}
void L_delay(int wait)
{
  unsigned long timer = millis();
  while (1) {
    Run('L');
    if ( millis() - timer >= wait ) {
      break;
    }
  }
  motorstop();
}
void b_delay(int wait) {
  unsigned long timer = millis();
  while (1) {
    Run('B');
    if ( millis() - timer >= wait ) {
      break;
    }
  }
  motorstop();
}


void read_colour() {

  int r = r_read();  //อ่านค่าสีแดง
  int g = g_read();  //อ่านค่าสีเขียว
  int b = b_read();  //อ่านค่าสีฟ้า

  Serial.print("R = ");
  Serial.print(red);
  Serial.print(" G = ");
  Serial.print(green);
  Serial.print(" B = ");
  Serial.print(blue);

}


void read_colour2() {

  int r2 = r_read2();  //อ่านค่าสีแดง
  int g2 = g_read2();  //อ่านค่าสีเขียว
  int b2 = b_read2();  //อ่านค่าสีฟ้า

  Serial.print("\t");
  Serial.print("R2 = ");
  Serial.print(red);
  Serial.print(" G2 = ");
  Serial.print(green);
  Serial.print(" B2 = ");
  Serial.println(blue);

}


int r_read() {

  red = 0;
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  red = pulseIn(sensorOut, LOW);

  r_value = red;
  return r_value;

}

int r_read2() {

  red2 = 0;
  digitalWrite(S22, LOW);
  digitalWrite(S33, LOW);
  red2 = pulseIn(sensorOut2, LOW);

  r_value2 = red2;
  return r_value2;

}

int g_read() {

  green = 0;
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  green = pulseIn(sensorOut, LOW);

  g_value = green;
  return g_value;
}

int g_read2() {

  green2 = 0;
  digitalWrite(S22, HIGH);
  digitalWrite(S33, HIGH);
  green2 = pulseIn(sensorOut2, LOW);

  g_value2 = green2;
  return g_value2;
}

int b_read() {

  blue = 0;
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blue = pulseIn(sensorOut, LOW);

  b_value = blue;
  return b_value;
}

int b_read2() {

  blue2 = 0;
  digitalWrite(S22, LOW);
  digitalWrite(S33, HIGH);
  blue2 = pulseIn(sensorOut2, LOW);

  b_value2 = blue2;
  return b_value2;
}

bool case_yellow(bool b_yellow) {
  //yellow
  if (180 <= red && red <= 250 && 350 <= green
      && green <= 430 && 650 <= blue
      && blue <= 800 ) {
    b_yellow = true;
    Serial.print("                                           ---yellow");
  } else b_yellow = false;
  return b_yellow;
}

void case_green() {
  if (green >= 245 && red >= 301 && blue >= 235 &&
      green <= 672 && red <= 894 && blue <= 648 ) {
    b_green = true;
    Serial.print("                                          ----green");
  }
}

void case_green2() {
  if (green2 >= 245 && red2 >= 301 && blue2 >= 235 &&
      green2 <= 672 && red2 <= 894 && blue2 <= 648 ) {
    b_green2 = true;
    Serial.print("                                          ----green");
  }
}
//------------------------------------------------------------

void Run(char pos)
{
  int resultant_angle;
  if (pos == 'F') {
    resultant_angle = 90;
  }
  else if (pos == 'R') {
    resultant_angle = 0;
  }
  else if (pos == 'L') {
    resultant_angle = 180;
  }
  else if (pos == 'B') {
    resultant_angle = 270;
  }

  float dataIn = pulseIn(A7, HIGH, 5000);
  dataIn = constrain(dataIn, 40, 1970);
  float angle = map(dataIn, 40, 1970, -180, 180);

#define k 20
  drive(300, resultant_angle, -angle * k);


  //  Serial.print(int(-180));Serial.print("\t");
  //  Serial.print(int(180));Serial.print("\t");
  //  Serial.println(angle);
}

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
  if (spd > 0)
  {
    digitalWrite(m11, LOW);
    digitalWrite(m12,  HIGH);
  }
  else if (spd < 0)
  {
    digitalWrite(m11,  HIGH);
    digitalWrite(m12, LOW);
  }
  else {
    digitalWrite(m11,  LOW);
    digitalWrite(m12,  LOW);
  }
  analogWrite(m1a, abs(spd));
}
void motorFR(int spd)
{
  if (spd > 0)
  {
    digitalWrite(m21, LOW);
    digitalWrite(m22,  HIGH);
  }
  else if (spd < 0)
  {
    digitalWrite(m21, HIGH);
    digitalWrite(m22, LOW);
  }
  else {
    digitalWrite(m21,  LOW);
    digitalWrite(m22,  LOW);
  }
  analogWrite(m2b, abs(spd));
}
void motorBR(int spd)
{
  if (spd > 0)
  {
    digitalWrite(m31, HIGH);
    digitalWrite(m32,  LOW);
  }
  else if (spd < 0) {
    digitalWrite(m31,  LOW);
    digitalWrite(m32, HIGH);
  }
  else {
    digitalWrite(m31,  LOW);
    digitalWrite(m32,  LOW);
  }
  analogWrite(m3a, abs(spd));
}
void motorBL(int spd)
{
  if (spd > 0)
  {
    digitalWrite(m41, HIGH);
    digitalWrite(m42,  LOW);
  }
  else if (spd < 0) {
    digitalWrite(m41,  LOW);
    digitalWrite(m42, HIGH);
  }
  else {
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
void motorstop() {
  motorFL(0);
  motorFR(0);
  motorBL(0);
  motorBR(0);
}
