/*
#include "ohm.h"

#include "mult.h"
Resistor_value r1;  //?
int Vin=3.3;
int R1=1000;  ///?
int raw=0;  //?

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(A0,INPUT);  ///?
pinMode(D5,OUTPUT);
pinMode(D6,OUTPUT);
pinMode(D7,OUTPUT);
pinMode(D1,OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
raw=analogRead(A0);
Serial.print(raw);
digitalWrite(D5,0);//input A
digitalWrite(D6,0);//INPUT B
digitalWrite(D7,0);//INPUT C
digitalWrite(D1,0);
r1.ohms_setup(Vin,R1,raw);
char result=change_into_char(r1.calculate_ohms());
Serial.println (result);
delay(1000);
}*/
