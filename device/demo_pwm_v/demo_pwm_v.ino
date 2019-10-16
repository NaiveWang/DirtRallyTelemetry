int PIN_D=6;
int i=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_D, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(;i<255;i++){
    analogWrite(PIN_D, i);
    delay(100);
  }
  for(;i>0;i--){
    analogWrite(PIN_D, i);
    delay(100);
  }
}
