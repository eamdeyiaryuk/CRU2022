#define S0 24
#define S1 26
#define S2 28
#define S3 31
#define sensorOut 8

unsigned long curMillis;
unsigned long prevMillis = 0; //เวลาที่ผ่านไปแล้ว
unsigned long prevMillis2 = 0;
unsigned long prevMillis3 = 0;

boolean b_yellow = false;
boolean b_green = false;

int red = 0, r_value = 0,
    blue = 0, b_value = 0,
    green = 0, g_value = 0;


void colorsensor_setup(){
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
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
  Serial.println(blue); 

}
int r_read() {

  //-------------------------------------//
  curMillis = millis(); //เวลาปัจจุบัน
  if (curMillis - prevMillis >= 100) {
    prevMillis = curMillis;

    red = 0;
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    red = pulseIn(sensorOut, LOW);
  }
  //-------------------------------------//

  r_value = red;
  return r_value;

}

int g_read() {

  //-------------------------------------//
  curMillis = millis(); //เวลาปัจจุบัน
  if (curMillis - prevMillis2 >= 100) {
    prevMillis2 = curMillis;

    green = 0;
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    green = pulseIn(sensorOut, LOW);
  }
  //-------------------------------------//

  g_value = green;
  return g_value;
}

int b_read() {

  //-------------------------------------//
  curMillis = millis(); //เวลาปัจจุบัน
  if (curMillis - prevMillis3 >= 100) {
    prevMillis3 = curMillis;

    blue = 0;
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    blue = pulseIn(sensorOut, LOW);
  }
  //-------------------------------------//

  b_value = blue;
  return b_value;
}
void case_yellow() {
  //yellow
  if (180 <= red && red <= 250 && 350 <= green
      && green <= 430 && 650 <= blue
      && blue <= 800 ) {
    b_yellow = true;
    Serial.print("                      ---yellow");
  }
}
void case_green(){
   if (700 <= red && red <= 1000 && 800 <= green
      && green <= 1100 && 850 <= blue
      && blue <= 1200 ) {
    b_green = true;
    Serial.print("                     ----green");
      }
}
