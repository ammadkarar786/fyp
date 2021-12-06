
int pin_Out_S0 = D6;
int pin_Out_S1 = D7;
int pin_Out_S2 = D8;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(pin_Out_S0,OUTPUT);
pinMode(pin_Out_S1,OUTPUT);
pinMode(pin_Out_S2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:


 for (int i = 0; i < 8; i++){
    digitalWrite(pin_Out_S0, HIGH && (i & B00000001));
    digitalWrite(pin_Out_S1, HIGH && (i & B00000010));
    digitalWrite(pin_Out_S2, HIGH && (i & B00000100));
    delay(1000);
 
  
  }

 
}
