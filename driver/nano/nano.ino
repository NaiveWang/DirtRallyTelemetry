#include <Wire.h>

//TM1650 - 4 digits

byte digits_d[11]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0xff, 0x6f, 0x00};

byte digits_d_r[12]={0x3f, 0x30, 0x5b, 0x79, 0x74, 0x6d, 0x6f, 0x38, 0xff, 0x7d, 0x00, 0x40};
//0x68, 0x6a, 0x6c, 0x6e
byte digits_a[4]={0x34, 0x35, 0x36, 0x37};
byte ctrl_a = 0x34;//0x48;
byte ctrl_d = 0x31;
byte bf[2];
int *i;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  //0x48>>1 = 0x24
  Wire.beginTransmission(0x24);
  //brightness 7, light on
  Wire.write(0x01);
  Wire.endTransmission();
  i=(int*)bf;
  wait();

}
void write_digit(byte a, int d){
  Wire.beginTransmission(digits_a[a]);
  Wire.write(digits_d[d]);
  Wire.endTransmission();

}
//reversed code
void write_digit_r(byte a, int d){
  Wire.beginTransmission(digits_a[a]);
  Wire.write(digits_d_r[d]);
  Wire.endTransmission();

}
void wait(){
  write_digit_r(3, 11);
  write_digit_r(2, 11);
  write_digit_r(1, 11);
  write_digit_r(0, 11);
}
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>2){
    //delay(10);
    Serial.readBytes(bf, 2);
    //order is big endian, reversed is little endian
    write_digit_r(3, *i>1000?*i/1000:10);
    write_digit_r(2, *i>100?(*i/100)%10:10);
    write_digit_r(1, *i>10?(*i/10)%10:10);
    write_digit_r(0, *i%10);
  }//else wait();

  //delay(1000);
}
