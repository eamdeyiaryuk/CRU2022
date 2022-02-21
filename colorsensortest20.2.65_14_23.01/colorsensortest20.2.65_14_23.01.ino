
void setup()
{
  // เปิดport_serial_communicate baterate = 9600
  Serial.begin(9600);
  motorPinSetup();
  colorsensor_setup();
}
void loop(){
    read_colour();
    case_yellow();
        if (b_yellow == true) {
          Serial.print("---------------------------y");
        }
}



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
// 90 fr
// 0 r
// 180 l
