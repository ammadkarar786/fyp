/*
#include "ohm.h"
Resistor_value r1;
int Vin=3.3;
int R1=1000;
int raw=0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(A0,INPUT);
pinMode(D5,OUTPUT);
pinMode(D6,OUTPUT);
pinMode(D7,OUTPUT);
pinMode(D2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
raw=analogRead(A0);
Serial.print(raw);
digitalWrite(D5,0);
digitalWrite(D6,0);
digitalWrite(D7,0);
digitalWrite(D2,0);
r1.ohms_setup(Vin,R1,raw);
int result=r1.calculate_ohms();

delay(1000);
}
*/
