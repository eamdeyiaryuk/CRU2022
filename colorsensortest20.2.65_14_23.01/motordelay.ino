void fr_delay(int wait)
{
  unsigned long timer = millis();
  while(1){
    Run('F');
    if( millis() - timer >= wait ) { break; }
  }
  motorstop();
}
void R_delay(int wait)
{
  unsigned long timer = millis();
  while(1){
    Run('R');
    if( millis() - timer >= wait ) { break; }
  }
  motorstop();
}
void L_delay(int wait)
{
  unsigned long timer = millis();
  while(1){
    Run('L');
    if( millis() - timer >= wait ) { break; }
  }
  motorstop();
}
void B_delay(int wait){
  unsigned long timer = millis();
  while(1){
    Run('B');
    if( millis() - timer >= wait ) { break; }
  }
  motorstop();
} 
